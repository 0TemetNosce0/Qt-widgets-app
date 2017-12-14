#ifndef MAINTOPWIDGET_H
#define MAINTOPWIDGET_H

#include "../common/basestylewidget.h"

#include <QWidget>
#include <QPixmap>

#define MAIN_TOP_WIDTH      900
#define MAIN_TOP_HEIGHT     440

class UserWidget;
class WenliWidget;
class QStackedWidget;
class MainScoreWidget;
class TopBottomWidget;
class QPropertyAnimation;
class QParallelAnimationGroup;

class MainTopWidget : public BaseStyleWidget
{
    Q_OBJECT
public:
    explicit MainTopWidget(QWidget *parent = 0);

public slots:
    void setNums(int num);

signals:
    void playVideo();
    void showSkin();
    void showMenu();
    void showMin();
    void closeWidget();
    void goExamine();
    void goMain();

protected:
    void resizeEvent(QResizeEvent *);

private slots:
    void examineClicked();
    void viewClicked();
    void returnMain();
    void returnAnimationFinished();

private:
    void initUI();
    void initTopTitleWidget();
    void initConnect();
    void initAnimations();
    void updateSizeAndPos();

private:
    QWidget                 *m_titleWidget;
    UserWidget              *m_userWidget;
    WenliWidget             *m_backgroundWidget;
    QStackedWidget          *m_titleStacked;
    MainScoreWidget         *m_scoreWidget;
    TopBottomWidget         *m_bottomWidget;
    QParallelAnimationGroup *m_examineGroupAnimation;
    QParallelAnimationGroup *m_returnGroupAnimation;
};

#endif // MAINTOPWIDGET_H
