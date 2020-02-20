#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>
#include <unordered_set>

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
    struct qpoint_hash
    {
        std::size_t operator () (const QPoint& point) const;
    };

    void keyPressEvent(QKeyEvent*);
    void timerEvent(QTimerEvent*);
    void paintEvent(QPaintEvent*);
    void initializeGame();
    QPoint randomPoint();
    QPoint getNextPos(QPoint, Direction);
    bool isValidMove(QPoint, Direction);
    void makeMove();
    void endGame();
    void updateDir();

public slots:
    void resetGame();

private:
    Ui::snake *ui;
    QMenu *gameMenu;

    static const int _WIDTH = 600;
    static const int _HEIGHT = 600;

    int timerId;

    QImage dot;
    QImage target;

    Direction curKey;
    Direction curDir;

    QPoint curTarget;
    std::list<QPoint> snakePos;
    std::unordered_set<QPoint, qpoint_hash> occupied;

    void loadImages();
    void createMenus();
};
#endif // SNAKE_H
