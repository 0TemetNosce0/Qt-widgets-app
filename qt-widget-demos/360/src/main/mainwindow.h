#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "common/shadowwidget.h"

class SafeWidget;
class CleanWidget;
class VideoWidget;
class YouhuaWidget;
class MainTopWidget;
class OpacityWidget;
class QStackedWidget;
class BaseStyleWidget;
class MainBottomWidget;
class QParallelAnimationGroup;

class MainWindow : public ShadowWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    void initUI();
    void initAnim();
    void initConnect();

private slots:
    void showMin();
    void showSkin();
    void showMenu();
    void goToSafe();
    void goToMain();
    void playVideo();
    void goToClean();
    void goToYouhua();
    void closeWidget();
    void upAnimFinished();

private:
    SafeWidget              *m_safeWidget;
    VideoWidget             *m_video;
    CleanWidget             *m_cleanWidget;
    YouhuaWidget            *m_youhuaWidget;
    MainTopWidget           *m_topWidget;
    OpacityWidget           *m_grayWidget;
    QStackedWidget          *m_stackWidget;
    MainBottomWidget        *m_bottomWidget;
    QParallelAnimationGroup *m_upGroup;
    QParallelAnimationGroup *m_downGroup;
};

#endif // MAINWINDOW_H
