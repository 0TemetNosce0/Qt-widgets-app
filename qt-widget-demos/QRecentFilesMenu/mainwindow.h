#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QRecentFilesMenu.h"

class QAction;
class QMenu;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void open();
    void loadFile(const QString &fileName);

private:
    void createActions();
    void createMenus();

    QTextEdit *textEdit;
    QMenu *fileMenu;
    QRecentFilesMenu *recentFilesMenu;
    QAction *openAct;
    QAction *exitAct;
};

#endif
