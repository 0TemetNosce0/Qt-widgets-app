#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
    class MainWindow;
}


#include "greekpanel.h"
#include "hebrewpanel.h"

QT_BEGIN_NAMESPACE
class AboutDialog;
class QAction;
class QMenu;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    //tray
    void showHide(QSystemTrayIcon::ActivationReason);

    void aboutOpenSite();
    void sAddSymbol(QString f_symbol);

private:
    Ui::MainWindow *ui;

    //about
    AboutDialog *about;    // about dialog

    GreekPanel *GUI_GreekPanel;
    HebrewPanel *GUI_HebrewPanel;


    //tray
    QSystemTrayIcon *trIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    void createConnects();
    void createTrayIcon();
    void createActions();
};

#endif // MAINWINDOW_H
