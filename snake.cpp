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
    resize(_WIDTH, _HEIGHT);
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
    // W : 87  up arrow: 16777235
    // A : 65  left arrow: 16777234
    // S : 83  down arrow: 16777237
    // D : 68  right arrow: 16777236
    switch (e->key())
    {
        case 87:
        case 16777235:
            curKey = UP;
            break;
        case 65:
        case 16777234:
            curKey = LEFT;
            break;
        case 83:
        case 16777237:
            curKey = DOWN;
            break;
        case 68:
        case 16777236:
            curKey = RIGHT;
            break;
        default:
            break;
    }
}

void Snake::timerEvent(QTimerEvent* e)
{
    // std::cout << "Timer event" << e->timerId() << std::endl;
    update();
    // std::cout << curKey << std::endl;
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
    QPoint point{0, 0};
    p.drawImage(point, dot);
}

void Snake::initializeGame()
{
    // Clear drawings
    // Reset timer
    // Setup random dot
    // Setup random target
    // Initialize snake list
    // Setup valid initial direction
    // Setup initial key direction
}

QPoint Snake::randomPoint()
{
    int _w = rand() % (_WIDTH / dot.width());
    int _h = rand() % (_HEIGHT / dot.height());
    return {_w*dot.width(), _h*dot.height()};
}
