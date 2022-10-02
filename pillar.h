#ifndef PILLAR_H
#define PILLAR_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>

class Pillar :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Pillar();

signals:
public slots:

private:
    QGraphicsPixmapItem * topPillar;
    QGraphicsPixmapItem * bottomPillar;


};

#endif // PILLAR_H
