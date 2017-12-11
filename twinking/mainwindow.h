#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TwinkleLabel.h"
class CTwinkleLabel;
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
    void Res();
    void Res1();
private:
    Ui::MainWindow *ui;
    CTwinkleLabel*label;
};

#endif // MAINWINDOW_H
