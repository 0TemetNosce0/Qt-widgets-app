#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "mainwindow.h"

class roadItem;
class bird;
class barrier;

class gameController : public QObject
{
    Q_OBJECT

public:
    explicit gameController(QGraphicsScene &Scene, QObject *parent = 0);
    void initReadyWidget();

signals:
    void close();

public slots:
    void readyWidgetMove();
    void startGame();
    void gameLoop();
    void gameOver();
    void add_Score();

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    bool isBegin;
    bool inGame;
    int current_Score;
    int distance;
    QWidget *readyWidget;
    QWidget *scoreWidget;
    QLabel *score;
    QGraphicsScene *scene;
    QPropertyAnimation *readyAnimation;
    roadItem *roadOne;
    roadItem *roadTwo;
    bird *flyBird;
    QList<barrier *> barrierList;
    QPushButton *quitButton;
    QPushButton *beginButton;
    QPushButton *restartButton;
    QTimer *gameLoopTimer;
};


#endif // GAMECONTROLLER_H
