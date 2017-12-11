#include "QDockFrame.h"
#include "QDockNode.h"
#include "QDockMaskWidget.h"
#include "QDockPanel.h"
#include "QDockManager.h"
#include <QLayout>
#include "QDockSideButton.h"
#include "QDockSideBar.h"

QDockFrame::QDockFrame(QDockManager* manager, QWidget *parent)
    : QWidget(parent)
    , arrows_(this)
    , manager_(manager)
    , lastMaskArea_(NoneArea)
{
    maskWidget_ = new QDockMaskWidget(this);
    maskWidget_->hide();

    QVBoxLayout* vlay = new QVBoxLayout(this);
    QHBoxLayout* hlay = new QHBoxLayout;

    rootNode_ = new QDockNode(this);

    leftBar_ = new QDockSideBar(this);
    leftBar_->setOrientation(Qt::Vertical);
    rightBar_ = new QDockSideBar(this);
    rightBar_->setOrientation(Qt::Vertical);
    topBar_ = new QDockSideBar(this);
    topBar_->setOrientation(Qt::Horizontal);
    bottomBar_ = new QDockSideBar(this);
    bottomBar_->setOrientation(Qt::Horizontal);

    vlay->addWidget(topBar_);
    vlay->addLayout(hlay);
    vlay->addWidget(bottomBar_);
    hlay->addWidget(leftBar_);
    hlay->addWidget(rootNode_);
    hlay->addWidget(rightBar_);

    vlay->setMargin(0);
    hlay->setMargin(0);

    leftBar_->hide();
    rightBar_->hide();
    topBar_->hide();
    bottomBar_->hide();

    setAcceptDrops(true);
}

QDockFrame::~QDockFrame()
{

}

void QDockFrame::showArrow()
{
    if (rootNode_->count() == 0)
    {
        arrows_.show(CenterArea);
    }
    else
    {
        arrows_.show(LeftArea | TopArea | RightArea | BottomArea);
    }
}

void QDockFrame::onDragEnterPanel()
{
    showArrow();
    maskWidget_->showOnDockArea(NoneArea);
}

void QDockFrame::onDragLeavePanel()
{
    if (!rect().contains(mapFromGlobal(QCursor::pos())))
    {
        arrows_.show(NoneArea);
    }
    lastMaskArea_ = NoneArea;
    maskWidget_->showOnDockArea(NoneArea);
}

void QDockFrame::onEndDragAtPanel()
{
    arrows_.show(NoneArea);
    lastMaskArea_ = NoneArea;
    maskWidget_->showOnDockArea(NoneArea);
}

QDockSideButton* QDockFrame::addSideButton(const QString& title, DockArea area)
{
    QDockSideButton* btn = new QDockSideButton(title,this);
    btn->setCheckable(true);

    switch (area)
    {
    case CenterTopArea:
    case TopArea:
        if (topBar_->isHidden())
        {
            topBar_->show();
        }
        topBar_->addWidget(btn);
        break;
    case CenterRightArea:
    case RightArea:
        btn->setOrientation(Qt::Vertical);
        btn->setMirrored(true);
        if (rightBar_->isHidden())
        {
            rightBar_->show();
        }
        rightBar_->addWidget(btn);
        break;
    case CenterBottomArea:
    case BottomArea:
        if (bottomBar_->isHidden())
        {
            bottomBar_->show();
        }
        bottomBar_->addWidget(btn);
        break;
    case NoneArea:
    case LeftArea:
    case CenterArea:
    case CenterLeftArea:
    default:
        btn->setOrientation(Qt::Vertical);
        if (leftBar_->isHidden())
        {
            leftBar_->show();
        }
        leftBar_->addWidget(btn);
        break;
    }

    return btn;
}

void QDockFrame::dragEnter()
{
    showArrow();
}

void QDockFrame::dragLeave()
{
    // if (!rect().contains(mapFromGlobal(QCursor::pos())))
    {
        arrows_.show(NoneArea);
    }
    lastMaskArea_ = NoneArea;
    maskWidget_->showOnDockArea(NoneArea);
}

void QDockFrame::drop(QWidget* from, QPoint /*pos*/)
{
    QDockPanel* panel = qobject_cast<QDockPanel*>(from);

    if (panel && lastMaskArea_ != NoneArea)
    {
        manager_->dockPanelTo(panel, this, lastMaskArea_);
    }

    lastMaskArea_ = NoneArea;
    arrows_.show(NoneArea);
    maskWidget_->showOnDockArea(NoneArea);
}

void QDockFrame::dragMove(const QPoint& pos)
{
    DockArea area = arrows_.getDockAreaByPos(mapFromGlobal(pos));

    if (area != lastMaskArea_)
    {
        maskWidget_->showOnDockArea(area);
        lastMaskArea_ = area;
    }
}
