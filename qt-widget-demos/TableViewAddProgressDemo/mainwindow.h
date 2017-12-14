#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TableView;
class QTimer;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void init();
    void initTimer();

public slots:
    void updateProgressValue();

private:
    TableView *tv;
    QTimer *timer;
};

#endif // MAINWINDOW_H
