#include "Snake.h"
#include "ui_snake.h"
#include <iostream>
#include <QKeyEvent>
#include <QPainter>
#include <QMessageBox>
#include <QPushButton>
#include <QInputDialog>

Snake::Snake(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::snake)
{
    ui->setupUi(this);
    createMenus();
    resize(_WIDTH, _HEIGHT);
    loadImages();
    initializeGame();
    timerId = startTimer(gameSpeed);
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
    makeMove();
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
    for (auto pos : snakePos)
        p.drawImage(pos, dot);
    p.drawImage(curTarget, target);
}

std::size_t Snake::qpoint_hash::operator()(const QPoint& point) const
{
    std::size_t h1 = std::hash<int>()(point.x());
    std::size_t h2 = std::hash<int>()(point.y());

    return h1 ^ h2;
}


void Snake::initializeGame()
{
    // Clear drawings
    // Reset timer
    // Setup random dot
    QPoint initSnake = randomPoint();
    snakePos.clear();
    snakePos.push_front(initSnake);
    occupied.clear();
    occupied.insert(initSnake);
    // Setup random target
    curTarget = randomPoint();
    while (curTarget == initSnake)
        curTarget = randomPoint();
    // Setup valid initial direction
    curDir = static_cast<Direction>(rand() % 4);
    while (!isValidMove(initSnake, curDir))
        curDir = static_cast<Direction>(rand() % 4);
    // Setup initial key direction
    curKey = curDir;
}

QPoint Snake::randomPoint()
{
    int _w = rand() % (_WIDTH / dot.width());
    int _h = rand() % (_HEIGHT / dot.height());
    return {_w*dot.width(), _h*dot.height()};
}

QPoint Snake::getNextPos(const QPoint& pos, Direction d)
{
    int dx{}, dy{};
    switch (d)
    {
        case UP:
            dy = -dot.width();
            break;
        case DOWN:
            dy = dot.width();
            break;
        case LEFT:
            dx = -dot.width();
            break;
        case RIGHT:
            dx = dot.width();
            break;
    }
    QPoint nPos{pos.x()+dx, pos.y()+dy};
    return nPos;
}

bool Snake::isValidMove(const QPoint& pos, Direction d)
{
    // check for out of boundary
    QPoint nPos = getNextPos(pos, d);
    if (nPos.x() < 0 || nPos.x() == _WIDTH ||
        nPos.y() < 0 || nPos.y() == _HEIGHT)
        return false;
    // check for collision with self
    occupied.erase(snakePos.back());
    if (occupied.count(nPos) > 0)
        return false;
    occupied.insert(snakePos.back());
    return true;
}

void Snake::makeMove()
{
    // makes move and either continues game or ends game
    updateDir();
    QPoint head = snakePos.front();
    if (!isValidMove(head, curDir)) {
        endGame();
        return;
    }
    QPoint nPos = getNextPos(head, curDir);
    snakePos.push_front(nPos);
    occupied.insert(nPos);
    // check for target
    if (nPos == curTarget) {
        // TODO : check for won game - no more targets
        curTarget = randomPoint();
        while (occupied.count(curTarget) > 0)
            curTarget = randomPoint();
    } else {
        occupied.erase(snakePos.back());
        snakePos.pop_back();
    }
}

void Snake::updateDir()
{
    if ((curDir == UP && curKey == DOWN) ||
        (curDir == DOWN && curKey == UP) ||
        (curDir == RIGHT && curKey == LEFT) ||
        (curDir == LEFT && curKey == RIGHT) ||
        (curDir == curKey))
        return;
    curDir = curKey;
}

void Snake::endGame()
{
    killTimer(timerId);
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);
    QPushButton *restartButton = msgBox.addButton(tr("Restart"), QMessageBox::ButtonRole::DestructiveRole);
    msgBox.setText("Game Over!");
    msgBox.exec();
    if (msgBox.clickedButton() == restartButton) {
        resetGame();
    } else {
        this->close();
    }
}

void Snake::resetGame()
{
    killTimer(timerId);
    initializeGame();
    timerId = startTimer(gameSpeed);
}

void Snake::setSpeedDialog()
{
    bool ok;
    int speed = QInputDialog::getInt(this, tr("Set snake speed"),
                                     tr("Snake speed:"), gameSpeed, 1, 1000, 1, &ok);
    if (ok)
        gameSpeed = speed;
}

void Snake::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("Game"));
    QAction *newGame = gameMenu->addAction(tr("New Game"));
    QAction *setSpeed = gameMenu->addAction(tr("Set Speed"));
    QAction *closeGame = gameMenu->addAction(tr("Close"));
    connect(newGame, &QAction::triggered,
            this, &Snake::resetGame);
    connect(setSpeed, &QAction::triggered,
            this, &Snake::setSpeedDialog);
    connect(closeGame, &QAction::triggered,
            this, &Snake::close);
}
