#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "kjmodel.h"
#include "kjstyleditemdelegate.h"

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

    KJModel *m_model;
    KJStyledItemDelegate *m_styledItemDelegate;

private slots:
    void slotOnButtonAddClicked();
    void slotOnButtonRemoveClicked();
};

#endif // MAINWINDOW_H
