#include <QGraphicsSceneEvent>
#include <QKeyEvent>
#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene{parent}, gameOn(false)
{
    setUpPillarTimer();

}

void Scene::addBird()
{
    bird = new Bird(QPixmap(":/images/bird_blue_up.png"));
    addItem(bird);
}

void Scene::startGame()
{
    //Bird
    bird->startFlying();
    //Pillars
    if(!pillarTimer->isActive())
    {
        setGameOn(true);
        pillarTimer->start(1000);
    }

}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=]()
    {
        Pillar * pillarItem = new Pillar();
        connect(pillarItem, &Pillar::collideFail,[=]()
        {
            pillarTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);

        });
        addItem(pillarItem);
    });
    // pillarTimer->start(1000);
}

void Scene::freezeBirdAndPillarsInPlace()
{
    bird->freezeInPlace();

    QList<QGraphicsItem *> sceneItems = items();
    foreach(QGraphicsItem * item, sceneItems)
    {
        Pillar * pillar_temp = dynamic_cast<Pillar *>(item);
        if(pillar_temp)
        {
            pillar_temp->freezeInPlace();
        }
    }
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(gameOn == true)
        {
            bird->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        if(gameOn == true)
        {
            bird->shootUp();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}
