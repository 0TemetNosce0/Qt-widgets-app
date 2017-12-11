#ifndef MAINBOTTOMWIDGET_H
#define MAINBOTTOMWIDGET_H

#include "../common/basestylewidget.h"

#include <QWidget>

class QStackedLayout;
class MainExamineWidget;
class QPropertyAnimation;
class MainBottomFirstWidget;

class MainBottomWidget : public BaseStyleWidget
{
    Q_OBJECT

public:
    explicit MainBottomWidget(QWidget *parent = 0);

public slots:
    void goExamine();
    void goMain();

private slots:
    void goExamineFinished();
    void goMainFinished();

signals:
    void safeClicked();
    void cleanClicked();
    void youhuaClicked();
    void advtoolMoreClicked();

private:
    void initUI();
    void initAnimation();
    void initConnect();

private:
    QStackedLayout        *m_stackedWidget;
    MainExamineWidget     *m_examineWidget;
    QPropertyAnimation    *m_examineAnimation;
    QPropertyAnimation    *m_returnAnimation;
    MainBottomFirstWidget *m_firstWidget;
};

#endif // MAINBOTTOMWIDGET_H
