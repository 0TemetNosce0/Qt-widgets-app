#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QObject>
#include <QMainWindow>
#include <QApplication>
#include <QSortFilterProxyModel>

#include "TableView.h"
#include "HHeaderModel.h"
#include "HHeaderView.h"
#include "NodeManager.h"
#include "DataModel.h"

#include "VHeaderModel.h"
#include "VHeaderView.h"
#include "DataTreeView.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void InitHHeaderModel(HHeaderModel* horizontalHeaderModel);
    void InitDataModel();
    void InitSetting();

private:
    Ui::MainWindow *ui;

	TableView* ptableView;
};

#endif // MAINWINDOW_H
