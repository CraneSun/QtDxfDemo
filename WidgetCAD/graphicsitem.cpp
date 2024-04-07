#include "pch.h"
#include "graphicsitem.h"

static void qt_graphicsItem_highlightSelected(
    QGraphicsItem *item, QPainter *painter, const QStyleOptionGraphicsItem *option)
{
    const QRectF murect = painter->transform().mapRect(QRectF(0, 0, 1, 1));
    if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
        return;

    const QRectF mbrect = painter->transform().mapRect(item->boundingRect());
    if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
        return;

    qreal itemPenWidth;
    switch (item->type()) {
    case QGraphicsEllipseItem::Type:
        itemPenWidth = static_cast<QGraphicsEllipseItem *>(item)->pen().widthF();
        break;
    case QGraphicsPathItem::Type:
        itemPenWidth = static_cast<QGraphicsPathItem *>(item)->pen().widthF();
        break;
    case QGraphicsPolygonItem::Type:
        itemPenWidth = static_cast<QGraphicsPolygonItem *>(item)->pen().widthF();
        break;
    case QGraphicsRectItem::Type:
        itemPenWidth = static_cast<QGraphicsRectItem *>(item)->pen().widthF();
        break;
        //9
    case QGraphicsSimpleTextItem::Type:
        itemPenWidth = static_cast<QGraphicsSimpleTextItem *>(item)->pen().widthF();
        break;
        //6
    case QGraphicsLineItem::Type:
        itemPenWidth = static_cast<QGraphicsLineItem *>(item)->pen().widthF();
        break;
    default:
        itemPenWidth = 1.0;
    }
    const qreal pad = itemPenWidth / 2;

    const qreal penWidth = 0; // cosmetic pen

    const QColor fgcolor = option->palette.windowText().color();
    const QColor bgcolor( // ensure good contrast against fgcolor
        fgcolor.red()   > 127 ? 0 : 255,
        fgcolor.green() > 127 ? 0 : 255,
        fgcolor.blue()  > 127 ? 0 : 255);

    painter->setPen(QPen(bgcolor, penWidth, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));

    painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));
}




//code from qt everywhere
GraphicsRectItem::GraphicsRectItem(const QRectF &rect, QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
{
    setRect(rect);
    DrawingboundRect = rect;
}

GraphicsRectItem::GraphicsRectItem(qreal x, qreal y, qreal w, qreal h,
                                   QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
{
    QRectF bbox = QRectF(x,y,w,h);
    setRect(bbox);
    DrawingboundRect = bbox;
}

/*!
    Constructs a QGraphicsRectItem. \a parent is passed to
    QAbstractGraphicsShapeItem's constructor.

    \sa QGraphicsScene::addItem()
*/
GraphicsRectItem::GraphicsRectItem(QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem( parent)
{

}

/*!
    Destroys the QGraphicsRectItem.
*/
GraphicsRectItem::~GraphicsRectItem()
{

}

/*!
    Returns the item's rectangle.

    \sa setRect()
*/
QRectF GraphicsRectItem::rect() const
{
    return ShapeRect;
}

/*!
    \fn void QGraphicsRectItem::setRect(const QRectF &rectangle)

    Sets the item's rectangle to be the given \a rectangle.

    \sa rect()
*/
void GraphicsRectItem::setRect(const QRectF &rect)
{
    DrawingboundRect = rect;
    ShapeRect = rect;
    update();
}

QRectF GraphicsRectItem::boundingRect() const
{
    return DrawingboundRect;
}

/*!
    \reimp
*/
QPainterPath GraphicsRectItem::shape() const
{
    QPainterPath path;
    return path;
}

/*!
    \reimp
*/
bool GraphicsRectItem::contains(const QPointF &point) const
{
    return QAbstractGraphicsShapeItem::contains(point);
}

/*!
    \reimp
*/
void GraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRect(rect());

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}

/*!
    \reimp
*/
bool GraphicsRectItem::isObscuredBy(const QGraphicsItem *item) const
{
    return QAbstractGraphicsShapeItem::isObscuredBy(item);
}

/*!
    \reimp
*/
QPainterPath GraphicsRectItem::opaqueArea() const
{
    return QAbstractGraphicsShapeItem::opaqueArea();
}

int GraphicsRectItem::type() const
{
    return Type;
}

void GraphicsRectItem::advance(int phase)
{

}

bool GraphicsRectItem::supportsExtension(Extension extension) const
{
    Q_UNUSED(extension);
    return false;
}

void GraphicsRectItem::setExtension(Extension extension, const QVariant &variant)
{
    Q_UNUSED(extension);
    Q_UNUSED(variant);
}

/*!
    \internal
*/
QVariant GraphicsRectItem::extension(const QVariant &variant) const
{
    Q_UNUSED(variant);
    return QVariant();
}










GraphicsDotItem ::GraphicsDotItem(qreal _x, qreal _y, double Radius, unsigned int _uid , void (*_callback)(int) ,QGraphicsItem *parent)
    :QAbstractGraphicsShapeItem(parent)
{
    x=_x;
    y=_y;
    radius = Radius;
    setFlags(QGraphicsItem::ItemIsSelectable);
    //setBrush(Qt::SolidPattern);
    //        setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemIsMovable);
    double xs = x- 1*radius;
    double ys = y - 1*radius;
    double w = 2.0*radius;
    double h = 2.0*radius;
    DrawingboundRect =  QRectF(xs,ys,w,h);
    ShapeRect = QRectF(x-0.5*radius,y-0.5*radius, radius, radius);
    setData(USERINFO_UID, QString::number(_uid));
}

QRectF GraphicsDotItem::rect() const{
    return ShapeRect;
}

QRectF GraphicsDotItem::boundingRect() const {
    return DrawingboundRect;
}

void GraphicsDotItem::advance(int phase){
    qDebug() << "phase value is " << phase;
}

void GraphicsDotItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
}

int GraphicsDotItem::type() const
{
    return Type;
}

void  GraphicsDotItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(pen());
    //painter->setBrush(pen().color());
    painter->setBrush(brush());
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawEllipse(ShapeRect);
}



GraphicsPolygonItem::GraphicsPolygonItem(QGraphicsItem *parent)
    :QGraphicsPolygonItem(parent)
{
}


GraphicsPolygonItem::GraphicsPolygonItem(const QPolygonF &polygon,
                                  QGraphicsItem *parent)
    :QGraphicsPolygonItem(polygon,parent)
{

}

void GraphicsPolygonItem::advance(int phase){

}

void GraphicsPolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPolygonItem::paint(painter,option,widget);
}

int GraphicsPolygonItem::type() const{
    return Type;
}
