#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "histogramview.h"

#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QSplitter>
#include <QTableView>
#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createAction();
    void createMenu();
    void setupModel();
    void setupView();
    void openFile(QString);

private:
    Ui::MainWindow *ui;

    QMenu *fileMenu;
    QAction *openAct;

    QTableView *table;
    QSplitter *splitter;
    HistogramView *histogram;
    QStandardItemModel *model;

public slots:
    void slotOpen();
};

#endif // MAINWINDOW_H
