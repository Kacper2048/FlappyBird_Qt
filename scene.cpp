#include <QGraphicsSceneEvent>
#include <QKeyEvent>
#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene{parent}
{
    setUpPillarTimer();

}

void Scene::addBird()
{
    bird = new Bird(QPixmap(":/images/bird_blue_up.png"));
    addItem(bird);
}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=]()
    {
        Pillar * pillarItem = new Pillar();

        addItem(pillarItem);

    });
    pillarTimer->start(1000);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        bird->shootUp();
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        bird->shootUp();
    }
    QGraphicsScene::keyPressEvent(event);
}
