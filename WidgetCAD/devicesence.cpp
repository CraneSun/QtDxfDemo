
#include "pch.h"
#include "devicesence.h"

DeviceSence::DeviceSence(QObject *parent)
    : QGraphicsScene{parent}
{

}


double DeviceSence::distance(double x1, double y1, double x2, double y2){
    return std::sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void DeviceSence::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if(event->button() == Qt::LeftButton){
        QPointF mp = event->scenePos();
        int minidx = -1;
        int idx = 0;
        double max_dis = DBL_MAX;
        for(auto & item : items()){
            if(0 == (item->flags() & QGraphicsItem::ItemIsSelectable)){
                idx++;
                continue;
            }
            double cx = item->boundingRect().x() + item->boundingRect().width()/2;
            double cy = item->boundingRect().y() + item->boundingRect().height()/2;
            double itemDis = distance(mp.x(),mp.y(),cx,cy);
            if(itemDis < max_dis){
                max_dis = itemDis;
                minidx = idx;
            }
            idx++;
        }

        if(minidx > -1){
            auto item = items().at(minidx);
            auto  mousex = mp.x();
            auto  mousey = mp.y();
            auto width = item->boundingRect().width();
            auto height = item->boundingRect().height();
            auto centerx = (item->boundingRect().x() + 0.5*width);
            auto centery = (item->boundingRect().y() + 0.5*height);
            auto measurex = abs(centerx-mousex);
            auto measurey = abs(centery-mousey);
            if((measurex < width) && (measurey<height)){
                item->advance(1);
                //                    std::cout <<" iiin "<<std::endl;
            }
        }

    }

    QGraphicsScene::mousePressEvent(event);
}

void DeviceSence::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
}
