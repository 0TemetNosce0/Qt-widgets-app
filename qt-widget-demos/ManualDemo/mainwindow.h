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
    MainWindow(QWidget *parent = 0);// �ṹ����
    ~MainWindow();//��������

protected:
    void closeEvent(QCloseEvent *event);//�ر��¼�

private slots:
    void menuTreeClick(QModelIndex);

private:    
    bool createConnect();//��������
    void createActions();//��������
    void createMenus();//�����˵���
    void createToolBars();//����������
    void createMenuTree();//����Ŀ¼��
    void createAd();//������
    void createTable();//������
    void readAd(int adId);//��ȡ���
    void readTable(int tableId);//��ȡ������
    void buildTableHeaderModel(QStandardItemModel& headerModel);//�󶨱�ͷ����
    void buildTableDataModel(QStandardItemModel& model);//������

private:
    QAction *exitAction;//�����˳�
    QAction *aboutAction;//��������
    QAction *searchAction;//��������
    QAction *goHomeAction;//��������Ŀ¼

    QMenu *fileMenu;//�����ļ��˵�
    QMenu *toolsMenu;//�������߲˵�
    QMenu *helpMenu;//���������˵�

    QToolBar *mainToolBar;//������������
    QLabel *searchLabel;//����������ǩ
    QComboBox *searchCombo;//����������

    QSqlDatabase db;//�������ݿ�
    QTreeView *menuTree;//����Ŀ¼��
    QStandardItemModel *treeModel;//����TREEMODE
    QSplitter *rightSplitter;//�����
    QTableView *dataTable;//���ݱ�

    QSplitter *mainSplitter;//���������

    AdGraphicsView *adView;//���
};

#endif // MAINWINDOW_H
