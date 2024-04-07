#include "canvasview.h"

#include "canvasview.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <QtOpenGLWidgets/qopenglwidget.h>

#include <cfloat>

#include <QVector>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QGraphicsItem>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsObject>
#include <QDebug>


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
    // 去掉滚动条
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

#if 0
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




void CanvasView::keyPressEvent(QKeyEvent *event)
{

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
    }
    break;
    case Qt::MiddleButton:
        //QGraphicsView::fitInView(FitedView,Qt::KeepAspectRatio);
        qDebug() << "continue middlebutton ";
        break;
    case Qt::RightButton:
    {
        bool isAnyItemSelected = false;
        {
            switch (InterAction) {
            case ACT_NONE:
                if(false == isAnyItemSelected)
                {
                    InterAction = ACT_MOVING;
                }
                break;
                break;
            default:
                break;
            }
        }
    }
    break;
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

void CanvasView::loadFile(std::string fileName)
{

}

void CanvasView::drawItem(int type)
{
    // switch(type)
    // {
    // case GraphicsRectItem::Type:
    //     break;
    // }

}
