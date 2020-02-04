#include "Snake.h"
#include "ui_snake.h"
#include <iostream>
#include <QKeyEvent>
#include <QPainter>

Snake::Snake(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::snake)
{
    ui->setupUi(this);
    loadImages();
    startTimer(1000);
}

Snake::~Snake()
{
    delete ui;
}

void Snake::keyPressEvent(QKeyEvent* e)
{
    std::cout << e->key() << std::endl;
}

void Snake::timerEvent(QTimerEvent* e)
{
    // std::cout << "Timer event" << e->timerId() << std::endl;
    update();
}

void Snake::loadImages()
{
    bool dotIsLoaded = dot.load(":/dot.png");
    bool targetIsLoaded = target.load(":/target.png");
    std::cout << dotIsLoaded << " " << targetIsLoaded << std::endl;
}

void Snake::paintEvent(QPaintEvent* e)
{
    QPainter p{this};
    QPointF point{10, 10};
    p.drawImage(point, dot);
}
