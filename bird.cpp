#include <QTimer>
#include <QGraphicsScene>
#include "bird.h"

Bird::Bird(QPixmap pixmap) :
    wingPosition(WingPosition::Up),
    wingDirection(false)
{
    setPixmap(pixmap);

    QTimer * birdWingsTimer = new QTimer(this);
    connect(birdWingsTimer,&QTimer::timeout,[=]()
    {
        updatePixmap();

    });

    birdWingsTimer->start(80);
    groundPosition = scenePos().y() +250;

    yAnimation = new QPropertyAnimation(this,"y",this);
    yAnimation -> setStartValue(scenePos().y());
    yAnimation -> setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(fallingTime);
    //yAnimation->start();


    rotationAnimation = new QPropertyAnimation(this,"rotation",this);
    //rotateTo(90,1000,QEasingCurve::InQuad);

}

void Bird::updatePixmap()
{
    if(wingPosition == WingPosition::Middle)
    {
        if(wingDirection ==  true)
        {//Up
            setPixmap(QPixmap(":/images/bird_blue_up.png"));
            wingPosition = WingPosition::Up;
            wingDirection = false;
        }
        else
        {//Down
            setPixmap(QPixmap(":/images/bird_blue_down.png"));
            wingPosition = WingPosition::Down;
            wingDirection = true;
        }
    }
    else
    {
        setPixmap(QPixmap(":/images/bird_blue_middle.png"));
        wingPosition = WingPosition::Middle;
    }
}

qreal Bird::y() const
{
    return m_y;
}

void Bird::setY(qreal newY)
{

    moveBy(0,newY - m_y);
    m_y = newY;
}

qreal Bird::rotation() const
{
    return m_rotation;
}

void Bird::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal curPosY = y();

    yAnimation ->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/20);
    yAnimation->setDuration(200);

    connect(yAnimation,&QPropertyAnimation::finished, [=]()
    {
        falltoGroundIfNecessary();
    }
    );

    yAnimation->start();
    rotateTo(-20,200,QEasingCurve::OutCubic);

}

void Bird::startFlying()
{
    yAnimation->start();
    rotateTo(90,1000,QEasingCurve::InQuad);
}

void Bird::freezeInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void Bird::setRotation(qreal newRotation)
{
    m_rotation = newRotation;
    QPointF c = boundingRect().center();

    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(newRotation);
    t.translate(-c.x(), -c.y());
    setTransform(t);
}

void Bird::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);
    rotationAnimation->start();
}

void Bird::falltoGroundIfNecessary()
{
    if( y() <groundPosition)
    {
        rotationAnimation->stop();

        yAnimation -> setStartValue(y());
        yAnimation -> setEndValue(groundPosition);
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setDuration(fallingTime);
        yAnimation->start();

        rotateTo(90,1000,QEasingCurve::OutCubic);
    }
}
