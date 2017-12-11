#include "QDockTabWidget.h"
#include "QDockTabBar.h"
#include <QDrag>
#include <QMimeData>
#include "QDockNode.h"
#include "QDockPanel.h"
#include <QList>

QDockTabWidget::QDockTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    QDockTabBar* bar = new QDockTabBar(this);
    bar->setMovable(false);

    connect(bar, SIGNAL(dragTabOut(int)), this, SLOT(onDragTabOut(int)), Qt::QueuedConnection);
    setTabBar(bar);

    setTabPosition(South);

    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onCurrenChanged(int)));
}

QDockTabWidget::~QDockTabWidget()
{

}

void QDockTabWidget::onDragTabOut(int index)
{
    QDockPanel* currentPanel = qobject_cast<QDockPanel*>(widget(index));
    currentPanel->undock();
    currentPanel->show();
    currentPanel->startDrag();
}

void QDockTabWidget::onCurrenChanged(int)
{
    QWidget* cur = currentWidget();
    if (!cur)
    {
        return;
    }
    emit setBasePanelTitle(cur->windowTitle());
}

void QDockTabWidget::tabRemoved(int)
{
    if (count() == 1)
    {
        QDockPanel* panel = qobject_cast<QDockPanel*>(widget(0));
        QDockPanel* parentPanel = qobject_cast<QDockPanel*>(parentWidget());
        QDockNode* parentNode = qobject_cast<QDockNode*>(parentPanel->parentWidget());

        if (parentNode)
        {
            QList<int> sizes = parentNode->sizes();
            int thisIndex = parentNode->indexOf(parentPanel);
            parentPanel->setParent(NULL);
            parentPanel->close();
            parentPanel->deleteLater();
            panel->setTabbedStatus(false, NULL);
            parentNode->insertWidget(thisIndex, panel);
            parentNode->setSizes(sizes);
        }
        else
        {
            panel->undock();
            panel->show();
            panel->move(parentPanel->pos());
            panel->resize(parentPanel->size());

            parentPanel->close();
            parentPanel->deleteLater();
        }
    }
}
