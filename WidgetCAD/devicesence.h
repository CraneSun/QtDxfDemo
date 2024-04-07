#ifndef DEVICESENCE_H
#define DEVICESENCE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVector>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class __declspec(dllexport) DeviceSence : public QGraphicsScene
{
    //Q_OBJECT
public:
    explicit DeviceSence(QObject * parent = nullptr);
    static double distance(double x1, double y1, double x2, double y2);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public:
    std::vector<QGraphicsItem*> GraphicItems;
};

#endif // DEVICESENCE_H
