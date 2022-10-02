#include "pillar.h"

Pillar::Pillar() :
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png")))
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,(topPillar->boundingRect().height()/2)+400));
    //topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,topPillar->boundingRect().height()/2));
    addToGroup(topPillar);
    addToGroup(bottomPillar);
}
