#include "QDockManager.h"
#include "QDockFrame.h"
#include "QDockPanel.h"
#include <cassert>
#include "QDockNode.h"
#include <QList>
#include "QDockMaskWidget.h"
#include "QDockTabWidget.h"
#include "QDockSideButton.h"
#include "QDockSideBar.h"
#include "QDockTabBar.h"

QDockManager::QDockManager(QWidget *parent)
    : QObject(parent)
    , dockFrame_(new QDockFrame(this, parent))
{

}

QDockManager::~QDockManager()
{

}

QDockPanel* QDockManager::addPanel(int id, const QString& title, QPoint pos, QSize size, QWidget* contensWidget /*= NULL*/)
{
    if (dockPanels_.find(id) != dockPanels_.end())
    {
        return NULL;
    }

    QDockPanel* p = new QDockPanel(this, dockFrame_);
    p->setId(id);
    p->setWindowTitle(title);
    p->resetContensWidget(contensWidget);
    p->move(pos);
    p->resize(size);
    p->show();
    dockPanels_.insert(std::make_pair(id, p));

    return p;
}

QDockPanel* QDockManager::getDockPanelByID(int id)
{
    std::map<int, QDockPanel*>::iterator it = dockPanels_.find(id);

    if (it == dockPanels_.end())
    {
        return NULL;
    }

    return it->second;
}

bool QDockManager::dockPanelTo(QDockPanel* panel, QWidget* target, DockArea area)
{
    assert(panel != target);
    panel->dockTarget_ = target;
    panel->area_ = area;
    panel->floatPos_ = panel->pos();

    QDockFrame* dockFrmae = qobject_cast<QDockFrame*>(target);

    if (dockFrmae)
    {
        return dockPanelToFrame(panel, area);
    }

    QDockPanel* targetPanel = qobject_cast<QDockPanel*>(target);

    if (targetPanel)
    {
        return dockPanelToPanel(panel, targetPanel, area);
    }

    return false;
}

bool QDockManager::dockPanelToFrame(QDockPanel* panel, DockArea area)
{
    if (panel->panelType_ == QDockPanel::SplitContainer)
    {
        QDockNode* fromNode = qobject_cast<QDockNode*>(panel->contensWidget_);
        assert(fromNode);
        panel->deleteLater();

        switch (area)
        {
        case LeftArea:
        {
            QList<int> sizes;
            sizes.push_back(30);
            sizes.push_back(70);

            int c = dockFrame_->rootNode_->count();
            if (c == 1)
            {
                dockFrame_->rootNode_->setOrientation(Qt::Horizontal);
                dockFrame_->rootNode_->insertWidget(0, fromNode);
                dockFrame_->rootNode_->setSizes(sizes);
            }
            else if (c == 2)
            {
                QDockNode* tmpNode = dockFrame_->rootNode_;
                dockFrame_->rootNode_ = new QDockNode(dockFrame_);
                dockFrame_->rootNode_->setOrientation(Qt::Horizontal);
                dockFrame_->rootNode_->insertWidget(0, fromNode);
                dockFrame_->rootNode_->insertWidget(1, tmpNode);
                dockFrame_->rootNode_->setSizes(sizes);
            }
            else
            {
                assert(false);
            }
            break;
        }
        case TopArea:
        {
            QList<int> sizes;
            sizes.push_back(30);
            sizes.push_back(70);

            int c = dockFrame_->rootNode_->count();
            if (c == 1)
            {
                dockFrame_->rootNode_->setOrientation(Qt::Vertical);
                dockFrame_->rootNode_->insertWidget(0, fromNode);
                dockFrame_->rootNode_->setSizes(sizes);
            }
            else if (c == 2)
            {
                QDockNode* tmpNode = dockFrame_->rootNode_;
                dockFrame_->rootNode_ = new QDockNode(dockFrame_);
                dockFrame_->rootNode_->setOrientation(Qt::Vertical);
                dockFrame_->rootNode_->insertWidget(0, fromNode);
                dockFrame_->rootNode_->insertWidget(1, tmpNode);
                dockFrame_->rootNode_->setSizes(sizes);
            }
            else
            {
                assert(false);
            }
            break;
        }
        case RightArea:
        {
            QList<int> sizes;
            sizes.push_back(70);
            sizes.push_back(30);

            int c = dockFrame_->rootNode_->count();
            if (c == 1)
            {
                dockFrame_->rootNode_->setOrientation(Qt::Horizontal);
                dockFrame_->rootNode_->insertWidget(1, fromNode);
                dockFrame_->rootNode_->setSizes(sizes);
            }
            else if (c == 2)
            {
                QDockNode* tmpNode = dockFrame_->rootNode_;
                dockFrame_->rootNode_ = new QDockNode(dockFrame_);
                dockFrame_->rootNode_->setOrientation(Qt::Horizontal);
                dockFrame_->rootNode_->insertWidget(0, tmpNode);
                dockFrame_->rootNode_->insertWidget(1, fromNode);
                dockFrame_->rootNode_->setSizes(sizes);
            }
            else
            {
                assert(false);
            }
            break;
        }
        case BottomArea:
        {
            QList<int> sizes;
            sizes.push_back(70);
            sizes.push_back(30);

            int c = dockFrame_->rootNode_->count();
            if (c == 1)
            {
                dockFrame_->rootNode_->setOrientation(Qt::Vertical);
                dockFrame_->rootNode_->insertWidget(0, fromNode);
                dockFrame_->rootNode_->setSizes(sizes);
            }
            else if (c == 2)
            {
                QDockNode* tmpNode = dockFrame_->rootNode_;
                dockFrame_->rootNode_ = new QDockNode(dockFrame_);
                dockFrame_->rootNode_->setOrientation(Qt::Vertical);
                dockFrame_->rootNode_->insertWidget(0, tmpNode);
                dockFrame_->rootNode_->insertWidget(1, fromNode);
                dockFrame_->rootNode_->setSizes(sizes);
            }
            else
            {
                assert(false);
            }
            break;
        }
        case CenterArea:
            assert(dockFrame_->rootNode_->count() == 0);
            dockFrame_->rootNode_->deleteLater();
            dockFrame_->rootNode_ = fromNode;
            fromNode->show();
            fromNode->setParent(dockFrame_);
            break;
        default:
            return false;
        }

        return true;
    }


    switch (area)
    {
    case LeftArea:
    {
        QList<int> sizes;
        sizes.push_back(30);
        sizes.push_back(70);

        int c = dockFrame_->rootNode_->count();
        if (c == 1)
        {
            dockFrame_->rootNode_->setOrientation(Qt::Horizontal);
            panel->setDockStatus();
            dockFrame_->rootNode_->insertWidget(0, panel);
            dockFrame_->rootNode_->setSizes(sizes);
        }
        else if (c == 2)
        {
            QDockNode* tmpNode = dockFrame_->rootNode_;
            panel->setDockStatus();
            dockFrame_->rootNode_ = new QDockNode(dockFrame_);
            dockFrame_->rootNode_->setOrientation(Qt::Horizontal);
            dockFrame_->rootNode_->insertWidget(0, panel);
            dockFrame_->rootNode_->insertWidget(1, tmpNode);
            dockFrame_->rootNode_->setSizes(sizes);
        }
        else
        {
            assert(false);
        }
        break;
    }
    case TopArea:
    {
        QList<int> sizes;
        sizes.push_back(30);
        sizes.push_back(70);

        int c = dockFrame_->rootNode_->count();
        if (c == 1)
        {
            dockFrame_->rootNode_->setOrientation(Qt::Vertical);
            panel->setDockStatus();
            dockFrame_->rootNode_->insertWidget(0, panel);
            dockFrame_->rootNode_->setSizes(sizes);
        }
        else if (c == 2)
        {
            QDockNode* tmpNode = dockFrame_->rootNode_;
            panel->setDockStatus();
            dockFrame_->rootNode_ = new QDockNode(dockFrame_);
            dockFrame_->rootNode_->setOrientation(Qt::Vertical);
            dockFrame_->rootNode_->insertWidget(0, panel);
            dockFrame_->rootNode_->insertWidget(1, tmpNode);
            dockFrame_->rootNode_->setSizes(sizes);
        }
        else
        {
            assert(false);
        }
        break;
    }
    case RightArea:
    {
        QList<int> sizes;
        sizes.push_back(70);
        sizes.push_back(30);

        int c = dockFrame_->rootNode_->count();
        if (c == 1)
        {
            dockFrame_->rootNode_->setOrientation(Qt::Horizontal);
            panel->setDockStatus();
            dockFrame_->rootNode_->insertWidget(1, panel);
            dockFrame_->rootNode_->setSizes(sizes);
        }
        else if (c == 2)
        {
            QDockNode* tmpNode = dockFrame_->rootNode_;
            panel->setDockStatus();
            dockFrame_->rootNode_ = new QDockNode(dockFrame_);
            dockFrame_->rootNode_->setOrientation(Qt::Horizontal);
            dockFrame_->rootNode_->insertWidget(0, tmpNode);
            dockFrame_->rootNode_->insertWidget(1, panel);
            dockFrame_->rootNode_->setSizes(sizes);
        }
        else
        {
            assert(false);
        }
        break;
    }
    case BottomArea:
    {
        QList<int> sizes;
        sizes.push_back(70);
        sizes.push_back(30);

        int c = dockFrame_->rootNode_->count();
        if (c == 1)
        {
            dockFrame_->rootNode_->setOrientation(Qt::Vertical);
            panel->setDockStatus();
            dockFrame_->rootNode_->insertWidget(0, panel);
            dockFrame_->rootNode_->setSizes(sizes);
        }
        else if (c == 2)
        {
            QDockNode* tmpNode = dockFrame_->rootNode_;
            panel->setDockStatus();
            dockFrame_->rootNode_ = new QDockNode(dockFrame_);
            dockFrame_->rootNode_->setOrientation(Qt::Vertical);
            dockFrame_->rootNode_->insertWidget(0, tmpNode);
            dockFrame_->rootNode_->insertWidget(1, panel);
            dockFrame_->rootNode_->setSizes(sizes);
        }
        else
        {
            assert(false);
        }
        break;
    }
    case CenterArea:
        assert(dockFrame_->rootNode_->count() == 0);
        panel->setDockStatus();
        //panel->setParent(dockFrmae_->rootNode_);
        dockFrame_->rootNode_->addWidget(panel);
        break;
    default:
        return false;
    }

    return true;
}

bool QDockManager::dockPanelToPanel(QDockPanel* from, QDockPanel* target, DockArea area)
{
    if (target->dockStatus() == Docked)
    {
        return dockPanelToDockedPanel(from, target, area);
    }
    else
    {
        QTimer* t = new QTimer;
        QObject::connect(t, &QTimer::timeout, [=]()
        {
            t->deleteLater();
            dockPanelToFloatPanel(from, target, area);
        });
        t->start(1);

        return true;
    }

    return false;
}

bool QDockManager::autoHidePanel(QDockPanel* panel, bool hide)
{
    //如果是一个包着tab的外壳panel，只关心里面的子panel
    if (panel->isTabbed_)
    {
        QDockTabWidget* tabWidget = qobject_cast<QDockTabWidget*>(panel->contensWidget_);
        assert(tabWidget);
        for (int i = 0; i < tabWidget->count();++i)
        {
            QDockPanel* subpanel = qobject_cast<QDockPanel*>(tabWidget->widget(i));
            autoHidePanel(subpanel, hide);
        }

        panel->deleteLater();
        return true;
    }

    //设置为自动隐藏
    if (hide)
    {
        panel->setAutoHideStatus();
        panel->autoHideBtn_ = dockFrame_->addSideButton(panel->windowTitle(),panel->area_);
        connect(panel->autoHideBtn_, &QDockSideButton::toggled, [panel](bool checked)
        {
            panel->setVisible(checked);
        });

        QPoint newPos;
        QSize newSize;
        switch (panel->area_)
        {
        case CenterTopArea:
        case TopArea:
            newPos.setX(0);
            newPos.setY(dockFrame_->topBar_->sizeHint().height());
            newSize.setWidth(dockFrame_->width());
            newSize.setHeight(dockFrame_->height() / 4);
            break;
        case CenterRightArea:
        case RightArea:
            newPos.setX(dockFrame_->width() / 4 * 3 - dockFrame_->rightBar_->sizeHint().width());
            newPos.setY(0);
            newSize.setWidth(dockFrame_->width() / 4);
            newSize.setHeight(dockFrame_->height());
            break;
        case CenterBottomArea:
        case BottomArea:
            newPos.setX(0);
            newPos.setY(dockFrame_->height() / 4 * 3 - dockFrame_->bottomBar_->sizeHint().height());
            newSize.setWidth(dockFrame_->width());
            newSize.setHeight(dockFrame_->height() / 4);
            break;
        case NoneArea:
        case LeftArea:
        case CenterArea:
        case CenterLeftArea:
        default:
            newPos.setX(dockFrame_->leftBar_->sizeHint().width());
            newPos.setY(0);
            newSize.setWidth(dockFrame_->width() / 4);
            newSize.setHeight(dockFrame_->height());
            break;
        }

        panel->move(newPos);
        panel->resize(newSize);

        panel->autoHideBtn_->setChecked(true);

        return true;
    }

    //取消自动隐藏
    panel->dockTo(panel->dockTarget_, panel->area_);

    panel->autoHideBtn_->deleteLater();
    panel->autoHideBtn_ = NULL;

    return true;
}

bool QDockManager::isRootNode(QDockNode* node)
{
    return node == dockFrame_->rootNode_;
}

void QDockManager::undockPanel(QDockPanel* panel)
{
    QDockNode* parentNode = qobject_cast<QDockNode*>(panel->parentWidget());

    panel->setParent(dockFrame_);
    panel->setFloatStatus();
    panel->move(panel->floatPos_);
    panel->show();

    if (parentNode)
    {
        if (isRootNode(parentNode))
        {
            QDockNode* otherChildNode = qobject_cast<QDockNode*>(parentNode->widget(0));
            if (otherChildNode)
            {
                QList<int> sizes = otherChildNode->sizes();
                parentNode->setOrientation(otherChildNode->orientation());
                parentNode->insertWidget(0, otherChildNode->widget(0));
                parentNode->insertWidget(1, otherChildNode->widget(0));
                parentNode->setSizes(sizes);
                otherChildNode->deleteLater();
            }
            return;
        }

        assert(parentNode->count() == 1);

        QDockPanel* containerPanel = qobject_cast<QDockPanel*>(parentNode->parentWidget());
        if (containerPanel)
        {
            QWidget* widget = parentNode->widget(0);
            QDockPanel* otherPanel = qobject_cast<QDockPanel*>(widget);
            if (otherPanel)
            {
                otherPanel->setParent(dockFrame_);
                otherPanel->setFloatStatus();
                otherPanel->resize(containerPanel->size());
                otherPanel->move(containerPanel->pos());
                otherPanel->show();
                containerPanel->close();
                containerPanel->deleteLater();
            }
            else if (QDockNode* otherNode = qobject_cast<QDockNode*>(widget))
            {
                containerPanel->contensWidget_->deleteLater();
                containerPanel->resetContensWidget(otherNode);
                otherNode->show();
            }
            else
            {
                assert(false);
            }
        }
        else
        {
            QDockNode* grandParentNode = qobject_cast<QDockNode*>(parentNode->parentWidget());
            assert(grandParentNode);
            QList<int> sizes = grandParentNode->sizes();
            QWidget* widget = parentNode->widget(0);
            int index = grandParentNode->indexOf(parentNode);
            parentNode->close();
            parentNode->deleteLater();
            grandParentNode->insertWidget(index, widget);
            grandParentNode->setSizes(sizes);

        }
        return;
    }

    return;
}

void QDockManager::onDragEnterPanel()
{
    dockFrame_->onDragEnterPanel();
}

void QDockManager::onDragLeavePanel()
{
    dockFrame_->onDragLeavePanel();
}

void QDockManager::onEndDragAtPanel()
{
    dockFrame_->onEndDragAtPanel();
}

bool QDockManager::dockPanelToFloatPanel(QDockPanel* from, QDockPanel* target, DockArea area)
{
    if (from->panelType_ == QDockPanel::TabContainer)
    {
        switch (area)
        {
        case CenterArea:
        {
            QDockTabWidget* tabWidget = qobject_cast<QDockTabWidget*>(from->contensWidget_);
            assert(tabWidget);
            from->move(target->pos());
            from->resize(target->size());
            tabWidget->addTab(target, target->windowTitle());
            target->setDockStatus();
            target->setTabbedStatus(true, from);
        }
            break;
        case CenterLeftArea:
        {
            QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
            tabPanel->panelType_ = QDockPanel::SplitContainer;
            tabPanel->resize(target->size());
            tabPanel->move(target->pos());
            tabPanel->setAcceptDrops(false);
            QDockNode* node = new QDockNode(tabPanel);
            tabPanel->resetContensWidget(node);
            node->setOrientation(Qt::Horizontal);
            from->setDockStatus();
            target->setDockStatus();
            node->insertWidget(0, from);
            node->insertWidget(1, target);
            tabPanel->setWindowTitle(QString("%1 & %2").arg(from->windowTitle()).arg(target->windowTitle()));
            tabPanel->show();
        }
            break;
        case CenterTopArea:
        {
            QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
            tabPanel->panelType_ = QDockPanel::SplitContainer;
            tabPanel->resize(target->size());
            tabPanel->move(target->pos());
            tabPanel->setAcceptDrops(false);
            QDockNode* node = new QDockNode(tabPanel);
            tabPanel->resetContensWidget(node);
            node->setOrientation(Qt::Vertical);
            from->setDockStatus();
            target->setDockStatus();
            node->insertWidget(0, from);
            node->insertWidget(1, target);
            tabPanel->setWindowTitle(QString("%1 & %2").arg(from->windowTitle()).arg(target->windowTitle()));
            tabPanel->show();
        }
            break;
        case CenterRightArea:
        {
            QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
            tabPanel->panelType_ = QDockPanel::SplitContainer;
            tabPanel->resize(target->size());
            tabPanel->move(target->pos());
            tabPanel->setAcceptDrops(false);
            QDockNode* node = new QDockNode(tabPanel);
            tabPanel->resetContensWidget(node);
            node->setOrientation(Qt::Horizontal);
            from->setDockStatus();
            target->setDockStatus();
            node->insertWidget(0, target);
            node->insertWidget(1, from);
            tabPanel->setWindowTitle(QString("%1 & %2").arg(target->windowTitle()).arg(from->windowTitle()));
            tabPanel->show();
        }
            break;
        case CenterBottomArea:
        {
            QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
            tabPanel->panelType_ = QDockPanel::SplitContainer;
            tabPanel->resize(target->size());
            tabPanel->move(target->pos());
            tabPanel->setAcceptDrops(false);
            QDockNode* node = new QDockNode(tabPanel);
            tabPanel->resetContensWidget(node);
            node->setOrientation(Qt::Vertical);
            from->setDockStatus();
            target->setDockStatus();
            node->insertWidget(0, target);
            node->insertWidget(1, from);
            tabPanel->setWindowTitle(QString("%1 & %2").arg(target->windowTitle()).arg(from->windowTitle()));
            tabPanel->show();
        }
            break;
        }

        return true;
    }


    if (from->panelType_ == QDockPanel::SplitContainer)
    {
        switch (area)
        {
        case CenterArea:
        {

        }
            break;
        case CenterLeftArea:
        {
            QWidget* tmp = from->contensWidget_;
            QDockNode* node = new QDockNode(from);
            from->resetContensWidget(node);
            node->setOrientation(Qt::Horizontal);
            node->show();

            from->move(target->pos());
            from->resize(target->size());

            node->insertWidget(0, tmp);
            target->setDockStatus();
            node->insertWidget(1, target);
        }
            break;
        case CenterTopArea:
        {
            QWidget* tmp = from->contensWidget_;
            QDockNode* node = new QDockNode(from);
            from->resetContensWidget(node);
            node->setOrientation(Qt::Vertical);
            node->show();

            from->move(target->pos());
            from->resize(target->size());

            node->insertWidget(0, tmp);
            target->setDockStatus();
            node->insertWidget(1, target);
        }
            break;
        case CenterRightArea:
        {
            QWidget* tmp = from->contensWidget_;
            QDockNode* node = new QDockNode(from);
            from->resetContensWidget(node);
            node->setOrientation(Qt::Horizontal);
            node->show();

            from->move(target->pos());
            from->resize(target->size());

            target->setDockStatus();
            node->insertWidget(0, target);
            node->insertWidget(1, tmp);
        }
            break;
        case CenterBottomArea:
        {
            QWidget* tmp = from->contensWidget_;
            QDockNode* node = new QDockNode(from);
            from->resetContensWidget(node);
            node->setOrientation(Qt::Vertical);
            node->show();

            from->move(target->pos());
            from->resize(target->size());

            target->setDockStatus();
            node->insertWidget(0, target);
            node->insertWidget(1, tmp);
        }
            break;
        }
        return true;
    }

    switch (area)
    {
    case CenterArea:
    {
        QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
        tabPanel->panelType_ = QDockPanel::TabContainer;
        tabPanel->resize(target->size());
        tabPanel->move(target->pos());
        tabPanel->setAcceptDrops(false);
        QDockTabWidget* tabWidget = new QDockTabWidget(tabPanel);
        tabPanel->resetContensWidget(tabWidget);
        tabWidget->addTab(target, target->windowTitle());
        target->setDockStatus();
        target->setTabbedStatus(true, tabPanel);
        from->setDockStatus();
        from->setTabbedStatus(true, tabPanel);
        tabWidget->addTab(from, from->windowTitle());
        connect(tabWidget, SIGNAL(setBasePanelTitle(const QString&)), tabPanel, SLOT(setWindowTitle(const QString &)));
        tabPanel->setWindowTitle(tabWidget->currentWidget()->windowTitle());
        tabPanel->show();
    }
        break;
    case CenterLeftArea:
    {
        QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
        tabPanel->panelType_ = QDockPanel::SplitContainer;
        tabPanel->resize(target->size());
        tabPanel->move(target->pos());
        tabPanel->setAcceptDrops(false);
        QDockNode* node = new QDockNode(tabPanel);
        tabPanel->resetContensWidget(node);
        node->setOrientation(Qt::Horizontal);
        from->setDockStatus();
        target->setDockStatus();
        node->insertWidget(0, from);
        node->insertWidget(1, target);
        tabPanel->setWindowTitle(QString("%1 & %2").arg(from->windowTitle()).arg(target->windowTitle()));
        tabPanel->show();
    }
        break;
    case CenterTopArea:
    {
        QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
        tabPanel->panelType_ = QDockPanel::SplitContainer;
        tabPanel->resize(target->size());
        tabPanel->move(target->pos());
        tabPanel->setAcceptDrops(false);
        QDockNode* node = new QDockNode(tabPanel);
        tabPanel->resetContensWidget(node);
        node->setOrientation(Qt::Vertical);
        from->setDockStatus();
        target->setDockStatus();
        node->insertWidget(0, from);
        node->insertWidget(1, target);
        tabPanel->setWindowTitle(QString("%1 & %2").arg(from->windowTitle()).arg(target->windowTitle()));
        tabPanel->show();
    }
        break;
    case CenterRightArea:
    {
        QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
        tabPanel->panelType_ = QDockPanel::SplitContainer;
        tabPanel->resize(target->size());
        tabPanel->move(target->pos());
        tabPanel->setAcceptDrops(false);
        QDockNode* node = new QDockNode(tabPanel);
        tabPanel->resetContensWidget(node);
        node->setOrientation(Qt::Horizontal);
        from->setDockStatus();
        target->setDockStatus();
        node->insertWidget(0, target);
        node->insertWidget(1, from);
        tabPanel->setWindowTitle(QString("%1 & %2").arg(target->windowTitle()).arg(from->windowTitle()));
        tabPanel->show();
    }
        break;
    case CenterBottomArea:
    {
        QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
        tabPanel->panelType_ = QDockPanel::SplitContainer;
        tabPanel->resize(target->size());
        tabPanel->move(target->pos());
        tabPanel->setAcceptDrops(false);
        QDockNode* node = new QDockNode(tabPanel);
        tabPanel->resetContensWidget(node);
        node->setOrientation(Qt::Vertical);
        from->setDockStatus();
        target->setDockStatus();
        node->insertWidget(0, target);
        node->insertWidget(1, from);
        tabPanel->setWindowTitle(QString("%1 & %2").arg(target->windowTitle()).arg(from->windowTitle()));
        tabPanel->show();
    }
        break;
    }

    return true;
}

bool QDockManager::dockPanelToDockedPanel(QDockPanel* from, QDockPanel* target, DockArea area)
{
    if (target->isTabbed_)
    {
        switch (area)
        {
        case CenterArea:
        {
            if (from->panelType_ == QDockPanel::SplitContainer)
            {
                return true;
            }

            if (from->panelType_ == QDockPanel::TabContainer)
            {
                return true;
            }

            QDockTabWidget* tabWidget = qobject_cast<QDockTabWidget*>(target->parentTabPanel_->contensWidget_);
            from->setDockStatus();
            from->setTabbedStatus(true, target->parentTabPanel_);
            tabWidget->addTab(from, from->windowTitle());
        }
            break;
        case CenterLeftArea:
        case CenterTopArea:
        case CenterRightArea:
        case CenterBottomArea:
            dockPanelToPanel(from, target->parentTabPanel_, area);
            break;
        }

        return true;
    }

//    if (from->panelType_ == QDockPanel::TabPanel)
//    {
//        return true;
//    }

    if (from->panelType_ == QDockPanel::SplitContainer)
    {
        QList<int> sizes;
        sizes.push_back(5);
        sizes.push_back(5);

        QDockNode* parentNode = qobject_cast<QDockNode*>(target->parentWidget());
        QWidget* fromWidget = from->contensWidget_;
        from->deleteLater();

        assert(parentNode);
        if (parentNode->count() == 1)
        {
            assert(isRootNode(parentNode));
            switch (area)
            {
            case CenterLeftArea:
                parentNode->setOrientation(Qt::Horizontal);
                parentNode->insertWidget(0, fromWidget);
                parentNode->setSizes(sizes);
                break;
            case CenterTopArea:
                parentNode->setOrientation(Qt::Vertical);
                parentNode->insertWidget(0, fromWidget);
                parentNode->setSizes(sizes);
                break;
            case CenterRightArea:
                parentNode->setOrientation(Qt::Horizontal);
                parentNode->insertWidget(1, fromWidget);
                parentNode->setSizes(sizes);
                break;
            case CenterBottomArea:
                parentNode->setOrientation(Qt::Vertical);
                parentNode->insertWidget(1, fromWidget);
                parentNode->setSizes(sizes);
                break;
            case CenterArea:
            {
            }
                break;
            default:
                return false;
            }
            return true;
        }

        //parentNode->count() != 1
        int parentIndex = parentNode->indexOf(target);
        QList<int> parentSizes = parentNode->sizes();

        QDockNode* node = new QDockNode(NULL);
        switch (area)
        {
        case CenterLeftArea:
            node->setOrientation(Qt::Horizontal);
            node->insertWidget(0, fromWidget);
            node->insertWidget(1, target);
            node->setSizes(sizes);
            parentNode->insertWidget(parentIndex, node);
            parentNode->setSizes(parentSizes);
            break;
        case CenterTopArea:
            node->setOrientation(Qt::Vertical);
            node->insertWidget(0, fromWidget);
            node->insertWidget(1, target);
            node->setSizes(sizes);
            parentNode->insertWidget(parentIndex, node);
            parentNode->setSizes(parentSizes);
            break;
        case CenterRightArea:
            node->setOrientation(Qt::Horizontal);
            node->insertWidget(0, target);
            node->insertWidget(1, fromWidget);
            node->setSizes(sizes);
            parentNode->insertWidget(parentIndex, node);
            parentNode->setSizes(parentSizes);
            break;
        case CenterBottomArea:
            node->setOrientation(Qt::Vertical);
            node->insertWidget(0, target);
            node->insertWidget(1, fromWidget);
            node->setSizes(sizes);
            parentNode->insertWidget(parentIndex, node);
            parentNode->setSizes(parentSizes);
            break;
        case CenterArea:
        {
        }
            break;
        default:
            return false;
        }

        return true;
    }

    QList<int> sizes;
    sizes.push_back(5);
    sizes.push_back(5);

    QDockNode* parentNode = qobject_cast<QDockNode*>(target->parentWidget());
    assert(parentNode);
    if (parentNode->count() == 1)
    {
        assert(isRootNode(parentNode));
        switch (area)
        {
        case CenterLeftArea:
            from->setDockStatus();
            parentNode->setOrientation(Qt::Horizontal);
            parentNode->insertWidget(0, from);
            parentNode->setSizes(sizes);
            break;
        case CenterTopArea:
            from->setDockStatus();
            parentNode->setOrientation(Qt::Vertical);
            parentNode->insertWidget(0, from);
            parentNode->setSizes(sizes);
            break;
        case CenterRightArea:
            from->setDockStatus();
            parentNode->setOrientation(Qt::Horizontal);
            parentNode->insertWidget(1, from);
            parentNode->setSizes(sizes);
            break;
        case CenterBottomArea:
            from->setDockStatus();
            parentNode->setOrientation(Qt::Vertical);
            parentNode->insertWidget(1, from);
            parentNode->setSizes(sizes);
            break;
        case CenterArea:
        {
            QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
            tabPanel->panelType_ = QDockPanel::TabContainer;
            tabPanel->setAcceptDrops(false);
            QDockTabWidget* tabWidget = new QDockTabWidget(tabPanel);
            tabPanel->resetContensWidget(tabWidget);
            tabWidget->addTab(target, target->windowTitle());
            from->setDockStatus();
            from->setTabbedStatus(true, tabPanel);
            tabWidget->addTab(from, from->windowTitle());
            target->setTabbedStatus(true, tabPanel);
            tabPanel->resize(target->size());
            tabPanel->setDockStatus();
            parentNode->insertWidget(0, tabPanel);
            connect(tabWidget, SIGNAL(setBasePanelTitle(const QString&)), tabPanel, SLOT(setWindowTitle(const QString &)));
            tabPanel->setWindowTitle(tabWidget->currentWidget()->windowTitle());
        }
            break;
        default:
            return false;
        }
        return true;
    }

    int parentIndex = parentNode->indexOf(target);
    QList<int> parentSizes = parentNode->sizes();

    QDockNode* node = new QDockNode(NULL);
    switch (area)
    {
    case CenterLeftArea:
        from->setDockStatus();
        node->setOrientation(Qt::Horizontal);
        node->insertWidget(0, from);
        node->insertWidget(1, target);
        node->setSizes(sizes);
        parentNode->insertWidget(parentIndex, node);
        parentNode->setSizes(parentSizes);
        break;
    case CenterTopArea:
        from->setDockStatus();
        node->setOrientation(Qt::Vertical);
        node->insertWidget(0, from);
        node->insertWidget(1, target);
        node->setSizes(sizes);
        parentNode->insertWidget(parentIndex, node);
        parentNode->setSizes(parentSizes);
        break;
    case CenterRightArea:
        from->setDockStatus();
        node->setOrientation(Qt::Horizontal);
        node->insertWidget(0, target);
        node->insertWidget(1, from);
        node->setSizes(sizes);
        parentNode->insertWidget(parentIndex, node);
        parentNode->setSizes(parentSizes);
        break;
    case CenterBottomArea:
        from->setDockStatus();
        node->setOrientation(Qt::Vertical);
        node->insertWidget(0, target);
        node->insertWidget(1, from);
        node->setSizes(sizes);
        parentNode->insertWidget(parentIndex, node);
        parentNode->setSizes(parentSizes);
        break;
    case CenterArea:
    {
        QDockPanel* tabPanel = new QDockPanel(this, dockFrame_);
        tabPanel->panelType_ = QDockPanel::TabContainer;
        tabPanel->setAcceptDrops(false);
        QDockTabWidget* tabWidget = new QDockTabWidget(tabPanel);
        tabPanel->resetContensWidget(tabWidget);
        tabWidget->addTab(target, target->windowTitle());
        from->setDockStatus();
        from->setTabbedStatus(true, tabPanel);
        tabWidget->addTab(from, from->windowTitle());
        target->setTabbedStatus(true, tabPanel);
        tabPanel->resize(target->size());
        tabPanel->setDockStatus();
        parentNode->insertWidget(parentIndex, tabPanel);
        parentNode->setSizes(sizes);
        connect(tabWidget, SIGNAL(setBasePanelTitle(const QString&)), tabPanel, SLOT(setWindowTitle(const QString &)));
        tabPanel->setWindowTitle(tabWidget->currentWidget()->windowTitle());
    }
        break;
    default:
        return false;
    }

    return true;
}

IAcceptDrop* QDockManager::getDropTarget(const QPoint& pos, const QWidget* except)
{
    IAcceptDrop* target = findChild<QDockTabBar>(pos, except);
    if (!target)
    {
        target = findChild<QDockPanel>(pos, except);
    }

    if (!target)
    {
        target = dockFrame_->rect().contains(dockFrame_->mapFromGlobal(pos)) ? dockFrame_ : nullptr;
    }

    return target;
}

