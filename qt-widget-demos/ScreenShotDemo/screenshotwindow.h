#ifndef SCREENSHOTWINDOW_H
#define SCREENSHOTWINDOW_H

#include "fullscreenwidget.h"
#include <QMainWindow>
#include <QVBoxLayout>

namespace Ui {
class ScreenShotWindow;
}

class ScreenShotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScreenShotWindow(QWidget *parent = 0);
    ~ScreenShotWindow();

public slots:
    //���н����Ĳۺ���
    void screenshot();

signals:
    // ����pixmap��Ϣ
    void setPixmap(QPixmap pixmap);

private:
    Ui::ScreenShotWindow *ui;

    void createToolBars();
    void createActions();
    QToolBar *mainToolBar;
    QAction *newAct;
    QVBoxLayout *mainLayout;
    QPixmap fullPixmap; //ȫ��ͼƬ
    FullScreenWidget *fullWidget;
};

#endif // SCREENSHOTWINDOW_H
