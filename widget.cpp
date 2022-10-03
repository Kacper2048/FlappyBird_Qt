#include <QGraphicsPixmapItem>

#include "widget.h"
#include "ui_widget.h"
#include "pillar.h"
#include "bird.h"

Widget::Widget(QWidget *parent): QWidget(parent) , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new Scene(this);
    scene->setSceneRect(-250,-800,1000,1300);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->centerOn(QPointF(0,0));

    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem(QPixmap(":/images/sky.png"));
    scene->addItem(pixItem);
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2, pixItem->boundingRect().height()/2));

    scene->addLine(-400,0,400,0,QPen(Qt::blue));
    scene->addLine(0,-400,0,400,QPen(Qt::blue));
    scene->addBird();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startGameButton_clicked()
{
    scene->startGame();
}

