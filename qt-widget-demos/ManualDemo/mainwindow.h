#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QSqlError>
#include <QComboBox>
#include <QTreeView>
#include <QSqlQuery>
#include <QSplitter>
#include <QSqlDriver>
#include <QTableView>
#include <QCloseEvent>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QStandardItemModel>

#include "adgraphicsview.h"
#include "ProxyModelWithHeaderModels.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);// 结构函数
    ~MainWindow();//析构函数

protected:
    void closeEvent(QCloseEvent *event);//关闭事件

private slots:
    void menuTreeClick(QModelIndex);

private:    
    bool createConnect();//创建连接
    void createActions();//创建动作
    void createMenus();//创建菜单栏
    void createToolBars();//创建工具栏
    void createMenuTree();//创建目录树
    void createAd();//广告面板
    void createTable();//表格面板
    void readAd(int adId);//读取广告
    void readTable(int tableId);//读取表单数据
    void buildTableHeaderModel(QStandardItemModel& headerModel);//绑定表头数据
    void buildTableDataModel(QStandardItemModel& model);//绑定数据

private:
    QAction *exitAction;//动作退出
    QAction *aboutAction;//动作关于
    QAction *searchAction;//动作搜索
    QAction *goHomeAction;//动作返回目录

    QMenu *fileMenu;//声明文件菜单
    QMenu *toolsMenu;//声明工具菜单
    QMenu *helpMenu;//声明帮助菜单

    QToolBar *mainToolBar;//声明主工具栏
    QLabel *searchLabel;//声明搜索标签
    QComboBox *searchCombo;//声明搜索框

    QSqlDatabase db;//声明数据库
    QTreeView *menuTree;//声明目录树
    QStandardItemModel *treeModel;//声明TREEMODE
    QSplitter *rightSplitter;//右面板
    QTableView *dataTable;//内容表单

    QSplitter *mainSplitter;//声明主面板

    AdGraphicsView *adView;//广告
};

#endif // MAINWINDOW_H
