#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainterPath>
#include <QPushButton>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include "barrier.h"
#include "define.h"
#include "roaditem.h"
#include "bird.h"
#include "gamecontroller.h"

class gameController;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGraphicsView *view;
    QGraphicsScene *scene;
    gameController *controller;
};

#endif // MAINWINDOW_H
