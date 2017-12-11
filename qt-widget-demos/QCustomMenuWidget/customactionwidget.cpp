#include "customactionwidget.h"
#include <QApplication>

CustomActionWidget::CustomActionWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    buttonOne = new QPushButton(QLatin1String("copy"), this);
    buttonTwo = new QPushButton(QLatin1String("paste"), this);

    layout->insertWidget(0, buttonOne);
    layout->insertWidget(1, buttonTwo);

    buttonOne->installEventFilter(this);
    buttonTwo->installEventFilter(this);

    connect(buttonOne, SIGNAL(clicked()), this, SIGNAL(buttonClicked()));
    connect(buttonTwo, SIGNAL(clicked()), this, SIGNAL(buttonClicked()));
}

bool CustomActionWidget::eventFilter(QObject* obj, QEvent* ev)
{
    if (buttonOne == obj || buttonTwo == obj)
    {
        if (ev->type() == QEvent::Enter)
        {
            emit hovered();
        }
    }

    return QWidget::eventFilter(obj, ev);
}

