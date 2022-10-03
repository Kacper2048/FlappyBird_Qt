#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillar.h"
#include "bird.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void addBird();
    void startGame();

    bool getGameOn() const;
    void setGameOn(bool newGameOn);
    void incrementScore();
    void resetScore();

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanPillars();
    void setUpPillarTimer();
    void freezeBirdAndPillarsInPlace();

    QTimer * pillarTimer = nullptr;
    Bird * bird = nullptr;

    bool gameOn;

    int score = 0;
    int bestScore = 0;

    QGraphicsPixmapItem * gameOverPix = nullptr;
    QGraphicsTextItem * scoreTextItem = nullptr;

};

#endif // SCENE_H
