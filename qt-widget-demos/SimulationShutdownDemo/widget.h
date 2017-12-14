#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QStateMachine>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void resizeEvent(QResizeEvent* event);

private:
    Ui::Widget *ui;

    QStateMachine* mMachine;
    QSignalTransition* mTransition;
    QState* mMaxState;
    QState* mMinState;
    QPushButton* mButton;
    bool mResized;
};

#endif // WIDGET_H
