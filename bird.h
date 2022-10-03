#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Bird : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Bird(QPixmap pixmap);
    qreal y() const;
    qreal rotation() const;
    void shootUp();
    void startFlying();
    void freezeInPlace();

signals:
public slots:
        void setY(qreal newY);
        void setRotation(qreal newRotation);
        void rotateTo(const qreal &end, const int &duration, const QEasingCurve& curve);
        void falltoGroundIfNecessary();

private:
    enum WingPosition
    {
        Up,
        Middle,
        Down
    };

    void updatePixmap();
    WingPosition wingPosition;
    bool wingDirection;
    qreal m_y;
    qreal m_rotation;

    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;

    qreal groundPosition;
    int fallingTime = 600;
};

#endif // BIRD_H
