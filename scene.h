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

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void setUpPillarTimer();
    void freezeBirdAndPillarsInPlace();
    QTimer * pillarTimer;
    Bird * bird;

    bool gameOn;


};

#endif // SCENE_H
