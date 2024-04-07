#include "pch.h"
#include "canvasview.h"
#include "ShapeDefine.h"
#include "graphicsitem.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <QtOpenGLWidgets/qopenglwidget.h>


#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()



CanvasView::CanvasView(QWidget *parent)
    : QGraphicsView(parent),
    m_translateButton(Qt::LeftButton),
    m_translateSpeed(1.0),
    m_zoomDelta(0.1),
    m_bMouseTranslate(false),
    m_scale(1.0)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setRenderHint(QPainter::Antialiasing);
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);

    setSceneRect(INT_MIN/2, INT_MIN/2, INT_MAX, INT_MAX);
    centerOn(0, 0);
    setAcceptDrops(true);

    ImageFileType.append(".jpg");
    ImageFileType.append(".bmp");
    ImageFileType.append(".png");

#if 1
    //use opengl to acclerate program
    auto gLWidget = new QOpenGLWidget();
#if 1
    try{
        this->setViewport(gLWidget);
        QSurfaceFormat fmt;
        fmt.setSamples(8);
        gLWidget->setFormat(fmt);
    }
    catch(std::exception & e)
    {
        (void)e;
    }
#else
    if(gLWidget->isValid()){
        this->setViewport(gLWidget);
        QSurfaceFormat fmt;
        fmt.setSamples(8);
        gLWidget ->setFormat(fmt);
        qDebug() <<"use opengl to acceralte";
    }else{
        qDebug() <<"opengl is invalid";
    }
#endif
#endif
}


void CanvasView::setUID(int uid)
{
    _uid = uid;
}

int CanvasView::UID(){
    return _uid;
}



void CanvasView::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == (Qt::ShiftModifier | Qt::ControlModifier) && event->key() == Qt::Key_C)
    {
        qDebug()<<"ShiftKey + controlKey + C";
        qDebug()<<BlinkIndexBak;
        fitInViewEx(FitedView);
        return;
    }
}

void CanvasView::mouseMoveEvent(QMouseEvent *event){
    switch(InterAction)
    {
    case ACT_MOVING:
    {
        QPoint delta = event->pos() - m_lastMousePos;
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        m_lastMousePos = event->pos();
    }
    break;
    }
}

void CanvasView::mousePressEvent(QMouseEvent *event){
    QGraphicsView::mousePressEvent(event);
    m_lastMousePos = event->pos();
    switch (event->button()) {
    case Qt::LeftButton:
    {
        if(nullptr != currentCanvasSelected){
            int id = (int)_uid;
            currentCanvasSelected(&id);
        }
    }
    break;
    case Qt::MiddleButton:
        InterAction = ACT_MOVING;
        break;
    case Qt::RightButton:
    {
        {
            switch (InterAction) {
            case ACT_NONE:
                break;
            default:
                break;
            }
        }
    }
    break;
    case (Qt::LeftButton | Qt::RightButton):
    default:
        break;
    }
}

void CanvasView::mouseReleaseEvent(QMouseEvent *event){
    InterAction = ACT_NONE;
    switch (event->button()) {
    case Qt::LeftButton:
    {
        for (QGraphicsItem *item : scene()->items())
        {
            item->setSelected(false);
        }
    }
    break;
    case Qt::MiddleButton:
        break;
    case Qt::RightButton:
        break;

    default:
        break;
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void CanvasView::wheelEvent(QWheelEvent *event){
    QPoint scrollAmount = event->angleDelta();
    scrollAmount.y() > 0 ? zoomIn() : zoomOut();
}

void CanvasView::paintEvent(QPaintEvent *event){
    return QGraphicsView::paintEvent(event);
}

void CanvasView::zoomIn()
{
    zoom(static_cast<float>(1 + m_zoomDelta));
}

void CanvasView::zoomOut()
{
    zoom(static_cast<float>(1 - m_zoomDelta));
}

void CanvasView::zoom(float scaleFactor)
{
    qreal factor = transform().scale(static_cast<qreal>(scaleFactor), static_cast<qreal>(scaleFactor)).mapRect(QRectF(0, 0, 1, 1)).width();
    if ((factor < 0.02) || (factor > 100.0))
        return;
    scale(static_cast<qreal>(scaleFactor), static_cast<qreal>(scaleFactor));
    m_scale *= static_cast<qreal>(scaleFactor);
}

void CanvasView::translate(QPointF delta)
{
    delta *= m_scale;
    delta *= m_translateSpeed;
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    QPoint newCenter(static_cast<int>(VIEW_WIDTH / 2 - delta.x()),  static_cast<int>(VIEW_HEIGHT / 2 - delta.y()));
    centerOn(mapToScene(newCenter));
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

void CanvasView::fitInViewEx(QRectF fit,bool isUpdateFitView, Qt::AspectRatioMode mode) {
    if(fit.width() < 1) return;
    if(isUpdateFitView){
        FitedView  = fit;
    }
    return QGraphicsView::fitInView(fit,mode);
}

QRectF CanvasView::getFitView() const
{
    return FitedView;
}



bool CanvasView::loadFile(std::string fileName)
{
    auto isOK = cadFile.readFile(fileName);
    if(isOK)
    {
        scene()->clear();
        auto blocks = cadFile.getRawData()->mBlock->ent;
        for (auto iter = blocks.begin(); iter != blocks.end(); iter++)
        {
            auto EType = (*iter)->eType;
            //auto name = magic_enum::enum_name(EType);
            int indexOfColor = cadFile.findIndexOfColorByEntity(*iter);
            auto color = cadFile.getColorByIndex(indexOfColor);
            auto layername = QString::fromStdString(cadFile.findLayerNameByEntity(*iter));
            qDebug() << layername;
            QPen ptpen;
            ptpen.setColor(QColor(color.r,color.g,color.b));
            ptpen.setWidth(1.1);
            ptpen.setCosmetic(true);
            switch(EType)
            {
             //include rectangle
            case DRW::LWPOLYLINE:
            {
                auto polyline = dynamic_cast<DRW_LWPolyline*>( *iter);
                QPolygonF poly;
                for( auto & pt : polyline->vertlist){
                    if(isInvAxisY){
                        poly.append(QPointF(pt->x, -(pt->y)));
                    }
                    else
                    {
                        poly.append(QPointF(pt->x, pt->y));
                    }
                }
                auto item = new GraphicsPolygonItem(poly);
                item->setPen(ptpen);
                scene()->addItem(item);
            }
                break;
                //line
            case DRW::LINE:
                break;
                //circle
            case DRW::CIRCLE:
                break;
                //s plinge
            case DRW::SPLINE:
                break;
                //ellipse
            case DRW::ELLIPSE:
                break;
            case DRW::POINT:
            {
                auto *point = dynamic_cast<DRW_Point*>( *iter);
            }
                break;
            case DRW::VIEWPORT:
                break;
            }
        }
    }
    return isOK;
}

void CanvasView::drawItem(int type)
{
    switch(type)
    {
    case SHAPE_RECTANGLE:
        break;
    }

}
