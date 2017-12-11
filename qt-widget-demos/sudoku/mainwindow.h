#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QToolBar>
#include <QMainWindow>

#include "sudokutable.h"
#include "settingsdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget * parent = 0);
    void createToolBar();
    void createActions();

public slots:
    void setPreviousActionEnabled(bool flag);
    void setNextActionEnabled(bool flag);
    void setEyeMode();
    void settings();
    void help();
    void about();
    void xiake();

private:
    SettingsDialog * settingsdialog;
    SudokuTable * sudokuTable;

    QToolBar * toolBar;
    QAction * newPuzzleAction;
    QAction * previousAction;
    QAction * nextAciton;
    QAction * eraseAction;
    QAction * clearAction;
    QAction * eyeModeAction;
    QAction * settingsAction;
    QAction * helpAction;
    QAction * aboutAction;
    QAction * xiakeAction;
};
#endif
