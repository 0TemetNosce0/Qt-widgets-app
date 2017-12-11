#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    version = "1.0.0 Alpha";

    createAction_Menu();

    frame = new QFrame(this);
    createBlocks();
    drawLine();
    this->setCentralWidget(frame);
    this->setFixedSize(frame->width(),frame->height()+ui->statusBar->height()+ui->menuBar->height());

    this->setWindowIcon(QIcon(":/icon/icon2.png"));
    this->setWindowTitle(QStringLiteral("数独计算器"));
}

void MainWindow::createBlocks()
{
    for(int i = 0; i < Max; i++)
    {
        for(int j = 0; j < Max; j++)
        {
            blocks[i][j] = new Block(frame);
            blocks[i][j]->setPos(i,j);
            blocks[i][j]->move(j*50,i*50);
            // blocks[i][j]->setValue(i+1);
        }
    }

    int w = (50)*9+1;
    frame->setMinimumSize(w,w);
}

void MainWindow::drawLine()
{
    GLine *line_H[4];
    QColor color;
    QRgb rgb = qRgb(0,140,0);
    color.setRgb(rgb);
    for(int i = 0; i < 4; i++)
    {
        line_H[i] = new GLine(frame);
        line_H[i]->setPen(3,color);
        line_H[i]->draw(1,frame->height());
        if(i > 0)
            line_H[i]->move(blocks[0][i*3+1]->pos().x()+blocks[0][i*3+1]->width()-2,0);
        else
            line_H[i]->move(0,0);
    }

    GLine *line[4];
    for(int i = 0; i < 4; i++)
    {
        line[i] = new GLine(frame);
        line[i]->setPen(3,color);
        line[i]->draw(0,frame->width());
        if(i>0)
            line[i]->move(0,blocks[i*3-1][0]->pos().y()+blocks[i*3-1][0]->height()+ui->menuBar->height()-2);
        else
            line[i]->move(0,0);
    }

}


void MainWindow::createAction_Menu()
{
    operaMenu = new QMenu(QStringLiteral("操作(&O)"),this);
    ui->menuBar->addMenu(operaMenu);

    runAction = new QAction(QStringLiteral("执行"),this);
    runAction->setShortcut(QStringLiteral("Ctrl+r"));
    runAction->setStatusTip(QStringLiteral("计算数独解法"));
    connect(runAction,SIGNAL(triggered()),this,SLOT(run()));
    operaMenu->addAction(runAction);

    clearAction = new QAction(QStringLiteral("初始化"),this);
    clearAction->setShortcut(QStringLiteral("ctrl+d"));
    clearAction->setStatusTip(QStringLiteral("初始化当前数独表"));
    connect(clearAction, SIGNAL(triggered()), this, SLOT(clear()));
    operaMenu->addAction(clearAction);

    quitAction = new QAction(QStringLiteral("退出"),this);
    quitAction->setShortcut(QStringLiteral("ctrl+q"));
    quitAction->setStatusTip(QStringLiteral("退出程序"));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(close()));
    operaMenu->addAction(quitAction);

    helpMenu = new QMenu(QStringLiteral("帮助(&H)"),this);
    ui->menuBar->addMenu(helpMenu);
    aboutAction = new QAction(QStringLiteral("关于"),this);
    aboutAction->setShortcut(QStringLiteral("Ctrl+I"));
    aboutAction->setStatusTip(QStringLiteral("关于数独计算器"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    helpMenu->addAction(aboutAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::cmp1()
{
    int i,j,k;
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            if(fw[i][j] > 1 || fh[i][j] > 1)
            {
                return false;
            }
        }
    }

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            for(k = 0; k < 9; k++)
            {
                if(fs[i][j][k] > 1)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void MainWindow::run()
{
    init();
    int i,j;
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            map[i][j] = blocks[i][j]->data();
            //blocks[i][j]->setValue(map[i][j]);
            cerr << map[i][j] << " ";
            if(map[i][j] != -1)
            {
                fw[i][map[i][j]] += 1;
                fh[j][map[i][j]] += 1;
                fs[i/3][j/3][map[i][j]] += 1;
            }
            else
            {
                blocks[i][j]->changeColor(Qt::red);
            }
        }
        cerr << endl;
    }
    cerr << endl;
    if(cmp1() && dfs(0))
    {
        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                blocks[i][j]->setValue(map[i][j]);
                blocks[i][j]->setEna(false);
            }
        }
        ui->statusBar->showMessage("计算完成",5000);
    }
    else
    {
        QMessageBox::warning(this,"数独计算器","当前数独无解！",QMessageBox::Ok);
        ui->statusBar->showMessage("求解失败,当前数独无解",5000);
    }
}

void MainWindow::clear()
{
    for(int i=0;i<Max;i++)
        for(int j=0;j<Max;j++)
        {
            blocks[i][j]->setValue(-1);
            blocks[i][j]->changeColor(Qt::black);
            blocks[i][j]->setEna(true);
        }
    ui->statusBar->showMessage("初始化完成",3000);
}


void MainWindow::about()
{
    //    QMessageBox::about(this, "关于", QStringLiteral("<h1>数独计算器</h1>\n"
    //                                    "数独计算器是一个用于快速求解数独的简单程序,基于Qt5\n"
    //                                    "<h3>Version:%1</h3>"
    //                                    "<p><h3>By:Gxin</h3></p>").arg(version));
    QMessageBox::about(this, QStringLiteral("关于"), QStringLiteral("数独计算器"));
}


bool MainWindow::cmps(int i,int j,int k)
{
    if(fw[i][k] >= 1)
    {
        return 0;
    }
    if(fh[j][k] >= 1)
    {
        return 0;
    }
    if(fs[i/3][j/3][k] >= 1)
    {
        return 0;
    }
    return 1;
}

void MainWindow::init()
{
    memset(fw, 0, sizeof(fw));
    memset(fh, 0, sizeof(fh));
    memset(fs, 0, sizeof(fs));
}

bool MainWindow::dfs(int sum)
{
    int i,j;
    i = sum/9;
    j = sum%9;
    while(sum < 81 && map[i][j] != -1)
    {
        sum++;
        i = sum/9;
        j = sum%9;
    }
    i = sum/9;
    j = sum%9;
    if(sum >= 81)
    {
        return 1;
    }

    for(int k = 1; k <= 9; k++)
    {
        if(cmps(i,j,k))
        {
            map[i][j] = k;
            fw[i][k] = 1;
            fh[j][k] = 1;
            fs[i/3][j/3][k] = 1;
            if(dfs(sum+1))
            {
                return 1;
            }
            else
            {
                fw[i][k] = 0;
                fh[j][k] = 0;
                fs[i/3][j/3][k] = 0;
                map[i][j] = -1;
            }

        }
    }
    return 0;
}

