#include "mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    settingsdialog = new SettingsDialog(this);
    sudokuTable = new SudokuTable(this);
    setCentralWidget(sudokuTable);
    setWindowTitle(QStringLiteral("数独计算器"));
    setWindowIcon(QIcon(":/images/sudoku.png"));
    createActions();
    createToolBar();
    setFixedHeight(351);
    setFixedWidth(317);

    connect(sudokuTable, SIGNAL(setNextEnabled(bool)),
            this, SLOT(setNextActionEnabled(bool)));
    connect(sudokuTable, SIGNAL(setPreviousEnabled(bool)),
            this, SLOT(setPreviousActionEnabled(bool)));

    previousAction->setEnabled(false);
}

void MainWindow::createActions()
{
    newPuzzleAction = new QAction(QStringLiteral("出题"), this);
    newPuzzleAction->setIcon(QIcon(":/images/newPuzzle.png"));
    connect(newPuzzleAction, SIGNAL(triggered()), sudokuTable, SLOT(newPuzzle()));

    previousAction = new QAction(QStringLiteral("上一个答案"), this);
    previousAction->setIcon(QIcon(":/images/previous.png"));
    connect(previousAction, SIGNAL(triggered()), sudokuTable, SLOT(previous()));

    nextAciton = new QAction(QStringLiteral("下一个答案"), this);
    nextAciton->setIcon(QIcon(":/images/next.png"));
    connect(nextAciton, SIGNAL(triggered()), sudokuTable, SLOT(next()));

    eraseAction = new QAction(QStringLiteral("清除答案"), this);
    eraseAction->setIcon(QIcon(":/images/erase.png"));
    connect(eraseAction, SIGNAL(triggered()), sudokuTable, SLOT(erase()));

    clearAction = new QAction(QStringLiteral("清空"), this);
    clearAction->setIcon(QIcon(":/images/clear.png"));
    connect(clearAction, SIGNAL(triggered()), sudokuTable, SLOT(clear()));

    eyeModeAction = new QAction(QStringLiteral("天眼模式"), this);
    eyeModeAction->setIcon(QIcon(":/images/eyeOn.png"));
    connect(eyeModeAction, SIGNAL(triggered()), this, SLOT(setEyeMode()));

    settingsAction = new QAction(QStringLiteral("设置"), this);
    settingsAction->setIcon(QIcon(":/images/settings.png"));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(settings()));

    helpAction = new QAction(QStringLiteral("帮助"), this);
    helpAction->setIcon(QIcon(":/images/help.png"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));

    aboutAction = new QAction(QStringLiteral("关于"), this);
    aboutAction->setIcon(QIcon(":/images/about.png"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    xiakeAction = new QAction(QStringLiteral("侠客风云传"), this);
    xiakeAction->setIcon(QIcon(":/images/xiake.png"));
    connect(xiakeAction, SIGNAL(triggered()), this, SLOT(xiake()));
}

void MainWindow::createToolBar()
{
    toolBar = addToolBar(tr("ToolBar"));
    toolBar->addAction(newPuzzleAction);
    toolBar->addAction(previousAction);
    toolBar->addAction(nextAciton);
    toolBar->addAction(eraseAction);
    toolBar->addAction(clearAction);
    toolBar->addAction(eyeModeAction);
    toolBar->addAction(settingsAction);
    toolBar->addAction(helpAction);
    toolBar->addAction(aboutAction);
    toolBar->addAction(xiakeAction);
    toolBar->setMovable(false);
}

//public slots:
void MainWindow::setPreviousActionEnabled(bool flag)
{
    previousAction->setEnabled(flag);
}

void MainWindow::setNextActionEnabled(bool flag)
{
    nextAciton->setEnabled(flag);
}

//private:
void MainWindow::setEyeMode()
{
    if (sudokuTable->eyeMode())
    {
        sudokuTable->setEyeMode(false);
        eyeModeAction->setIcon(QIcon(":/images/eyeOff.png"));
    }
    else
    {
        sudokuTable->setEyeMode(true);
        eyeModeAction->setIcon(QIcon(":/images/eyeOn.png"));
    }
}

void MainWindow::settings()
{
    settingsdialog->setSolutions(sudokuTable->dataSolutions());
    if (settingsdialog->exec())
        sudokuTable->setDataSolutions(settingsdialog->solutions());
}

void MainWindow::help()
{
    QMessageBox::information(this, QStringLiteral("帮助"),
                             QStringLiteral("<h2> 数独游戏规则 </h2> \
                                            <p>1.每一行填写1-9不能重复。\
                                                                 <p>2.每一列填写1-9不能重复。\
                                                                                      <p>3.每个宫填写1-9不能重复。\
                                                                                                           <p>4.在遵守的前面三个要求下，根据现有的数字，推理出所有空格该填写的数字。"));
}

                                                                                                                                                  void MainWindow::about()
    {
                                                                                                                                                  QMessageBox::about(this, QStringLiteral("关于"),
                                                                                                                                                                     QStringLiteral("<h2> 数独计算器 V0.9 </h2> \
                                                                                                                                                                                    <p>数独计算器能用来求解数独题，也能用来出数独题。 \
                                                                                                                                                                                                                 <p>本软件使用Qt编写。\
                                                                                                                                                                                                                                 <p>作者: 蜻蜓 \
                                                                                                                                                                                                                                             <p>QQ：1099965906"));
}

                                                                                                                                                                                                                                                   void MainWindow::xiake()
    {
                                                                                                                                                                                                                                                   QMessageBox::information(this, QStringLiteral("侠客风云传"),
                                                                                                                                                                                                                                                                            QStringLiteral("<h2> 国产单机游戏《侠客风云传》已经开始预售！ </h2> \
                                                                                                                                                                                                                                                                                           <p> 《侠客风云传》为河洛工作室制作的第四部单机游戏，前作为《武林群侠传》。\
                                                                                                                                                                                                                                                                                                                                     <p> 河洛工作室曾经开发过河洛三部曲，分别是：《金庸群侠传》、《武林群侠传》、《三国群侠传》。\
                                                                                                                                                                                                                                                                                                                                                                                        后来，因为各种原因而解散了，十多年后，工作室重组，开发出《侠客风云传》。\
                                                                                                                                                                                                                                                                                                                                                                                                                               <p> 《侠客风云传》是《武林群侠传》的新制版，尽管是新制版，但诚意十足（至少个人这么认为）。\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 添加超过一倍以上的剧情，可以追的妹子增加到十位以上，以高自由度为特色，没有虐心的悲剧，更没有无聊的刷怪。\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        <p> 个人认为《侠客风云传》一款与众不同的单机游戏，战斗可能只占20%，剩下的80%则是丰富的内容，比如打猎，钓鱼，挖矿，\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         打铁、交友、琴棋书画，各种奇遇，多支路的剧情等等，主要内容是讲一个无名小卒成长为一代大侠的故事（当然也可能是乞丐）。\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      <p> 《侠客风云传》已于6月1日开始预售，将于7月28日开始正式发售，已通过steam青睐之光，数字版还没出，但估计50元左右（看一场电影的价格）。\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    <p> 尽管个人觉得很棒，但不确定其他人是否也喜欢这种类型，可以玩玩前作《武林群侠传》（老游戏，2d画面），\
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             或者看看官方宣传视频，或者等正式发售后找朋友借来玩玩，再作决定。更多详情，请百度：侠客风云传官网。"));
}
