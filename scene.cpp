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

void Scene::resetScore()
{
    score = 0;
}
void Scene::startGame()
{
    //Bird
    bird->startFlying();
    //Pillars
    if(!pillarTimer->isActive())
    {
        cleanPillars();
        setGameOn(true);
        pillarTimer->start(1000);
        hideGameOverGraphics();
        resetScore();
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
            showGameOverGraphics();

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

void Scene::incrementScore()
{
    score++;
    if(score > bestScore)
    {
        bestScore = score;
    }
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

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/game_over_red.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/2));

    scoreTextItem = new QGraphicsTextItem();

    QString htmlString ="<p> Score: "+QString::number(score) + "</p>" + "<p> Best Score : "
            + QString::number(bestScore) + "</p>";

    QFont mFont("Consolas", 30, QFont::Bold);
    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::yellow);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
                          -gameOverPix->boundingRect().height()/2));
}

void Scene::hideGameOverGraphics()
{
    if(gameOverPix != nullptr)
    {
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }

    if(scoreTextItem != nullptr)
    {
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;


    }
}

void Scene::cleanPillars()
{
    QList<QGraphicsItem *> sceneItems = items();
    foreach(QGraphicsItem * item, sceneItems)
    {
        Pillar * pillar_temp = dynamic_cast<Pillar *>(item);
        if(pillar_temp)
        {
            removeItem(pillar_temp);
            delete pillar_temp;
        }
    }
}
