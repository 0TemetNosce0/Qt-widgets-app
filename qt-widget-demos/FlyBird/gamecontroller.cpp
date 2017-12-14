#include "gamecontroller.h"

#include <QPushButton>

gameController::gameController(QGraphicsScene &Scene, QObject *parent) :
    QObject(parent)
{
    scene = &Scene;
    current_Score = 0;
    distance = 20;

    score = new QLabel("0");
    roadOne = new roadItem(1);
    roadTwo = new roadItem(2);
    flyBird = new bird();
    gameLoopTimer = new QTimer(this);

    isBegin = false;
    inGame = false;

    scene->addItem(roadOne);
    scene->addItem(roadTwo);
    scene->addItem(flyBird);
    scene->addWidget(score);

    score->setFont(QFont("造字工房悦黑体验版纤细体", 13, 4, false));
    score->setGeometry(50, 50, 25, 25);
    score->setStyleSheet("background-color:QColor(197, 240, 255, 130)");
    score->setAlignment(Qt::AlignHCenter);
    score->setWindowOpacity(0.7);
    initReadyWidget();

    connect(gameLoopTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
}

void gameController::initReadyWidget()
{
    readyWidget = new QWidget();
    readyAnimation = new QPropertyAnimation(readyWidget, "pos");
    beginButton = new QPushButton(QStringLiteral("开始游戏"), readyWidget);
    quitButton = new QPushButton(QStringLiteral("退出游戏"), readyWidget);
    restartButton = new QPushButton(QStringLiteral("重新开始"), readyWidget);

    beginButton->setGeometry(137, 295, 110, 35);
    quitButton->setGeometry(137, 404, 110, 35);
    restartButton->setGeometry(137, 360, 110, 35);
    beginButton->setFont(QFont("造字工房悦黑体验版纤细体", 10, 2, false));
    quitButton->setFont(QFont("造字工房悦黑体验版纤细体", 10, 2, false));
    restartButton->setFont(QFont("造字工房悦黑体验版纤细体", 10, 2, false));
    restartButton->setEnabled(false);
    readyWidget->setStyleSheet("QWidget{background-image:url(:/resource/Resource/ready.png)}");

    readyWidget->setFixedSize(WIDTH, HEIGHT);
    scene->addWidget(readyWidget)->setZValue(1);

    connect(beginButton, SIGNAL(clicked()), this, SLOT(readyWidgetMove()));
    connect(quitButton, SIGNAL(clicked()), this, SIGNAL(close()));
    connect(restartButton, SIGNAL(clicked()), this, SLOT(readyWidgetMove()));

    scene->installEventFilter(this);
}

void gameController::readyWidgetMove()
{
    readyAnimation->setDuration(1300);
    readyAnimation->setStartValue(readyWidget->pos());
    readyAnimation->setEndValue(QPoint(readyWidget->pos().x(), readyWidget->pos().y() + 450));
    readyAnimation->start();
    connect(readyAnimation, SIGNAL(finished()), this, SLOT(startGame()));
}

void gameController::startGame()
{
    roadOne->beginMove();
    roadTwo->beginMove();

    isBegin = true;
    inGame = true;

    beginButton->setEnabled(false);
    restartButton->setEnabled(true);
    gameLoopTimer->start(GAME_LOOP_TIME);

    connect(flyBird, SIGNAL(adjustTimer()), gameLoopTimer, SLOT(start()));
}

void gameController::gameLoop()
{
    distance--;
    if (!distance)
    {
        QTime time = QTime::currentTime();
        qsrand(time.msec() + time.second() * 1000);

        if (0 == (qrand() % 2))
        {
           barrier *barrier1 = new barrier();
           scene->addItem(barrier1);
           barrierList.append(barrier1);
           connect(barrier1, SIGNAL(add_Score()), this, SLOT(add_Score()));
        }

        distance = 20;
    }

    flyBird->riseAndfall();

    if (flyBird->checkCollide() && inGame)
    {
        inGame = false;
        gameOver();
    }
}

bool gameController::eventFilter(QObject *object, QEvent *event)
{
    if ((event->type() == QEvent::KeyPress) && isBegin)
    {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        flyBird->keyPressEvent(key);
        return true;
    }
    else
        return QObject::eventFilter(object, event);
}

void gameController::gameOver()
{
    disconnect(flyBird, SIGNAL(adjustTimer()), gameLoopTimer, SLOT(start()));
    gameLoopTimer->stop();
    roadOne->stopMove();
    roadTwo->stopMove();
    foreach(barrier *bar, barrierList)
        delete bar;
    barrierList.clear();
    scene->update();
    readyAnimation->setDuration(1300);
    readyAnimation->setStartValue(readyWidget->pos());
    readyAnimation->setEndValue(QPoint(readyWidget->pos().x(), readyWidget->pos().y() - 450));
    readyAnimation->start();

    disconnect(readyAnimation, SIGNAL(finished()), this, SLOT(startGame()));
    connect(readyAnimation, SIGNAL(finished()), flyBird, SLOT(reset()));
}

void gameController::add_Score()
{
    current_Score++;
    score->setText(QString::number(current_Score));
}

