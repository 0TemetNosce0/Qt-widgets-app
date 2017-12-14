#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "../common/dynamicbutton.h"

#include <QWidget>

class NumbersAnimWidget;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void buttonClicked();
    void updateNum();

private:
    DynamicButton *m_dyButton;
    NumbersAnimWidget *m_numsWidget;
    QTimer *m_timer;
};

#endif // MAINWIDGET_H
