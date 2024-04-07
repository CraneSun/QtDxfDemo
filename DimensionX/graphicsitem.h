#if 0
#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H
//rectitem 分两种，一种是用于cad的，一种是用于视觉调整的
#include <QtCore/qglobal.h>
#include <QGraphicsItem>
#include "../../DimensionX/WidgetCAD/widgetcad.h"


//not offer layer name any more
//and set/get the name through by setData(USER+1, QString)

class GraphicsRectItemPrivate;
class GraphicsRectItem : public QAbstractGraphicsShapeItem
{
public:
    explicit GraphicsRectItem(QGraphicsItem *parent = nullptr);
    explicit GraphicsRectItem(const QRectF &rect, QGraphicsItem *parent = nullptr);
    explicit GraphicsRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    ~GraphicsRectItem();
    QRectF rect() const;
    void setRect(const QRectF &rect);
    inline void setRect(qreal x, qreal y, qreal w, qreal h);
    QRectF boundingRect() const override;
    void advance(int phase);
    QPainterPath shape() const override;
    bool contains(const QPointF &point) const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    bool isObscuredBy(const QGraphicsItem *item) const override;
    QPainterPath opaqueArea() const override;
    enum { Type = SHAPE_RECTANGLE };
    int type() const override;
signals:
    void popMenu(int action);
protected:
    bool supportsExtension(Extension extension) const override;
    void setExtension(Extension extension, const QVariant &variant) override;
    QVariant extension(const QVariant &variant) const override;
private:
    //shape data
    mutable QRectF ShapeRect;
    QRectF DrawingboundRect;
    Q_DISABLE_COPY(GraphicsRectItem)
};



class  GraphicsDotItem : public QAbstractGraphicsShapeItem
{
public:
    GraphicsDotItem();
    explicit GraphicsDotItem(qreal _x, qreal _y, double _radius, unsigned int _uid = 0, void (*_callback)(int) = nullptr,QGraphicsItem *parent = nullptr);
    ~GraphicsDotItem(){}
public:
    //
    QRectF rect() const;
    QRectF boundingRect() const override;
    void advance(int phase) override;
    void setPen(const QPen & pen) {QAbstractGraphicsShapeItem::setPen(pen);}
    void setBrush(const QBrush & brush){QAbstractGraphicsShapeItem::setBrush(brush);}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override{
        setSelected(false);
        QGraphicsItem::mouseReleaseEvent(event);
    }
    enum { Type = SHAPE_DOT };
    int type() const override;
signals:
    void popMenu(int action);
private:
    //shapeData, dot need x y and radius
    double x = 0,y = 0,radius = 5;
    mutable QRectF ShapeRect;
    QRectF DrawingboundRect;
    Q_DISABLE_COPY(GraphicsDotItem)
};

















#endif // GRAPHICSITEM_H

#endif
