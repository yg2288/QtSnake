#include "Snake.h"
#include "ui_snake.h"
#include <iostream>
#include <QKeyEvent>

Snake::Snake(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::snake)
{
    ui->setupUi(this);
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

void Snake::timerEvent(QTimerEvent* t)
{
    std::cout << "Timer event" << t->timerId() << std::endl;
}

