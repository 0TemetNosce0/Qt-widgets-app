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
    //进行截屏的槽函数
    void screenshot();

signals:
    // 设置pixmap信息
    void setPixmap(QPixmap pixmap);

private:
    Ui::ScreenShotWindow *ui;

    void createToolBars();
    void createActions();
    QToolBar *mainToolBar;
    QAction *newAct;
    QVBoxLayout *mainLayout;
    QPixmap fullPixmap; //全屏图片
    FullScreenWidget *fullWidget;
};

#endif // SCREENSHOTWINDOW_H
