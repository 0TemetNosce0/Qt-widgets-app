#include "customactionwidget.h"
#include "customaction.h"

#include <QMenu>

CustomAction::CustomAction(QObject *parent)
    : QWidgetAction(parent)
{

}

void CustomAction::onButtonHovered()
{
    QMenu* menu = qobject_cast<QMenu*>(sender()->parent());

    if (menu)
    {
        menu->hideTearOffMenu();
        menu->setActiveAction(this);
    }

    hover();
}

void CustomAction::onButtonClicked()
{
    QMenu* menu = qobject_cast<QMenu*>(sender()->parent());

    if (menu)
    {
        menu->close();
    }
}

QWidget *CustomAction::createWidget(QWidget *parent)
{
    CustomActionWidget* w = new CustomActionWidget(parent);

    connect(w, SIGNAL(hovered()), SLOT(onButtonHovered()));
    connect(w, SIGNAL(buttonClicked()), SLOT(onButtonClicked()));

    return w;
}
