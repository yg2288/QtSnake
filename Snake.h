#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class snake; }
QT_END_NAMESPACE

class Snake : public QMainWindow
{
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);
    ~Snake();

protected:
    enum Direction {UP, DOWN, LEFT, RIGHT};

    void keyPressEvent(QKeyEvent*);
    void timerEvent(QTimerEvent*);
    void paintEvent(QPaintEvent*);
    void initializeGame();
    QPoint randomPoint();
    bool isValidMove(QPoint, Direction);
    void makeMove();

private:
    Ui::snake *ui;

    static const int _WIDTH = 600;
    static const int _HEIGHT = 600;

    int timerId;

    QImage dot;
    QImage target;

    Direction curKey;
    Direction curDir;

    QPoint curTarget;
    std::list<QPoint> snakePos;

    void loadImages();
};
#endif // SNAKE_H
