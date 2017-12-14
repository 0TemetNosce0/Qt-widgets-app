#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QHBoxLayout;
class QPushButton;
class CompleteLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void init();

private:
    Ui::MainWindow *ui;

    CompleteLineEdit *edit;
    QPushButton *button;
    QHBoxLayout *layout;
};

#endif // MAINWINDOW_H
