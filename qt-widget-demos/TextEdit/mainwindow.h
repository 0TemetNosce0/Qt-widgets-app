#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MyMdi;
class QMdiSubWindow;//加入一个类相当于加入一个头文件？
class QSignalMapper;//这是个跟信号发射相关的类

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
 //   void set_active_sub_window(QWidget *window);
    MyMdi *CreateMyMdi();
    void set_active_sub_window(QWidget *window);
    void UpdateMenus();
    void ShowTextRowCol();
    void UpdateWindowMenu();
    void closeEvent(QCloseEvent *event);

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionClose_triggered();

    void on_actionCloseAll_triggered();

    void on_actionTile_triggered();

    void on_actionCascade_triggered();

    void on_actionNext_triggered();

    void on_actionPrevious_triggered();

    void on_actionAbout_triggered();

    void on_actionAboutQt_triggered();

private:
    Ui::MainWindow *ui;

    QAction *actionSeparator;
    QMdiSubWindow *FindMdiChild(const QString &file_name);//查找子窗口
    MyMdi *GetActiveWindow();
    QSignalMapper *window_mapper;
    void read_settings();
    void write_settings();
    void init_window();
};
#endif // MAINWINDOW_H
