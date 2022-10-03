#ifndef PILLAR_H
#define PILLAR_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Pillar :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit Pillar();
    ~Pillar();

    qreal x() const;

    void freezeInPlace();


signals:
    void collideFail();

public slots:

    void setX(qreal newX);

private:

    bool collideWithBird();

    QGraphicsPixmapItem * topPillar = nullptr;
    QGraphicsPixmapItem * bottomPillar = nullptr;
    QPropertyAnimation * xAnimation = nullptr;
    int yPos = 0;

    qreal m_x;
};

#endif // PILLAR_H
