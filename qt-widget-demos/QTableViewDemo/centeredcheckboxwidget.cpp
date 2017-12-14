#include "centeredcheckboxwidget.h"

#include <QHBoxLayout>

CenteredCheckBoxWidget::CenteredCheckBoxWidget(QWidget *parent)
    : QWidget(parent)
{

    setContentsMargins(0, 0, 0, 0);
    setAutoFillBackground(true);

    QHBoxLayout *layout = new QHBoxLayout();
    checkbox = new QCheckBox();
    layout->addWidget(checkbox);
    layout->setAlignment(checkbox, Qt::AlignHCenter | Qt::AlignVCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    setLayout(layout);

    setFocusProxy(checkbox);
}

QCheckBox *CenteredCheckBoxWidget::checkBox() const
{
    return checkbox;
}
