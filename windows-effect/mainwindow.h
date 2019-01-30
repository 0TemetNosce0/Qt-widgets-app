#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QPushButton;
#include <QDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QPushButton * btn;
    QDialog * m_paintTool;
    ~MainWindow();
public slots:
    void on_btn_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
