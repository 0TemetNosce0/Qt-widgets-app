#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

class CComboBox;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CComboBox *accountComboBox;
    QListWidget *listWidget;

private slots:
    void showAccount(QString account);
    void removeAccount(QString account);
};

#endif // MAINWINDOW_H
