#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GLDDateTimeEditEx.h"
#include "GLDDateTimeEdit.h"

#include <QMainWindow>
#include <QVBoxLayout>

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
    void testDateTimeEditEx();
    void testDateTimeEdit();

private:
    Ui::MainWindow *ui;
    GLDDateTimeEditEx *m_dateTimeEditEx;
    GLDDateTimeEdit *m_dateTimeEdit;
    QVBoxLayout *m_layout;
};

#endif // MAINWINDOW_H
