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
    void keyPressEvent(QKeyEvent*);
    void timerEvent(QTimerEvent*);
    void paintEvent(QPaintEvent*);

private:
    Ui::snake *ui;

    QImage dot;
    QImage target;

    enum Direction {UP, DOWN, LEFT, RIGHT};
    Direction curKey;

    void loadImages();
};
#endif // SNAKE_H
