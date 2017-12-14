#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "block.h"
#include <QMenu>
#include <QFrame>
#include <QLayout>
#include <QAction>
#include <cstring>
#include <QPainter>
#include <QPushButton>
#include <QGridLayout>
#include "gline.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void run();
    void clear();
    void about();

private:
    void drawLine();
    void createBlocks();
    void createAction_Menu();
    bool dfs(int sum);
    void init();
    bool cmps(int i,int j,int k);
    bool cmp1();

private:
    Ui::MainWindow *ui;
    QString version;
    enum{Max=9};
    Block *blocks[Max][Max];
    QFrame *frame;
    //QPushButton *clearButton;
  //  QPushButton *runButton;

    QAction *clearAction;
    QAction *runAction;
    QAction *quitAction;
    QMenu *operaMenu;
    QMenu *helpMenu;
    QAction *aboutAction;

    ///algo
    int map[10][10];
    int fw[10][10];
    int fh[10][10];
    int fs[5][5][10];
};

#endif // MAINWINDOW_H
