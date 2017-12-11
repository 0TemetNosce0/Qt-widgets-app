#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "roundedcornerwidget.h"
#include <QMainWindow>

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
    void changeColor();
    void changeText();

private:
    Ui::MainWindow *ui;
    RoundedCornerWidget*   m_roundedCornerWidget;
};

#endif // MAINWINDOW_H
