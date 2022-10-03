#include "pillar.h"
#include <QRandomGenerator>
#include <QGraphicsScene>

#include <QDebug>

Pillar::Pillar() :
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png")))
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,(topPillar->boundingRect().height()/2)+300));
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,100));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0)+QPoint(260+ xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this,"x",this);
    xAnimation->setStartValue(260+xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);
    xAnimation->start();

    connect(xAnimation,&QPropertyAnimation::finished,[=]()
    {
       qDebug() << "Animation Finished";
       scene()->removeItem(this);
       delete this;
    });



}

Pillar::~Pillar()
{
    qDebug() << "Deleting Pillar";
}

qreal Pillar::x() const
{
    return m_x;
}

void Pillar::setX(qreal newX)
{
    qDebug() << "Pillar's position : " << newX;
    m_x = newX;
    setPos(QPoint(0,0)+QPointF(newX,yPos));
}
