#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "student.h"
#include "customdelegate.h"
#include "insertwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setUpData(const QList<Student>& list);

public slots:
    void on_insertButton_clicked();
    void on_deleteButton_clicked();
    void on_selectAllButton_clicked();
    void on_unselectAllButton_clicked();

private:
    Ui::MainWindow *ui;
    CustomModel* m_model;
    CustomDelegate* m_delegate;
    InsertWidget* m_insertWidget;
};

#endif // MAINWINDOW_H
