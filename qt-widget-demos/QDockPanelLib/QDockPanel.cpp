#include "QDockPanel.h"
#include <QResizeEvent>
#include <QPainter>
#include <QMouseEvent>
#include "QDockNode.h"
#include <cassert>
#include "QDockFrame.h"
#include "QDockManager.h"
#include "QDockMaskWidget.h"
#include <QDebug>



QDockPanel::QDockPanel(QDockManager* manager, QWidget* frame)
    : QWidget(frame, Qt::FramelessWindowHint | Qt::Tool)
    , manager_(manager)
    , contensWidget_(NULL)
    , edgeWidth_(3)
    , titleRectHeight_(20)
    , dockStatus_(Floating)
    , arrows_(this)
    , lastMaskArea_(NoneArea)
    , isTabbed_(false)
    , parentTabPanel_(NULL)
    , panelType_(DockPanel)
    , dockTarget_(NULL)
    , area_(NoneArea)
    , autoHideBtn_(NULL)
    , isLBtnPressed_(false)
    , lastDragOverPanelOrFrame_(nullptr)
{
    title_ = new QDockPanelTitle(this);
    connect(this, SIGNAL(windowTitleChanged(const QString&)), title_, SLOT(setTitle(const QString&)));
    connect(title_, &QDockPanelTitle::pinButtonClicked, [this]
    {
        // assert(dockStatus_ == Docked || dockStatus_ == AutoHide);
        setAutoHide(dockStatus_ == Docked);
    });
    connect(title_, &QDockPanelTitle::doubleClicked, [this]
    {
//        if (!dockTarget_)
//        {
//            return;
//        }
        if (dockStatus() == Docked)
        {
            undock();
        }
        else if (dockStatus() == Floating)
        {
            manager_->dockPanelTo(this, dockTarget_, area_);
        }
    });

    title_->onTitleMousePressEvent = [this](QMouseEvent* e)
    {
        if (e->button() != Qt::LeftButton)
        {
            return;
        }
        isLBtnPressed_ = true;
        pressedPos_ = e->globalPos();
        oldPos_ = e->globalPos() - pos();
        lastDragOverPanelOrFrame_ = nullptr;
    };

    title_->onTitleMouseReleaseEvent = [this](QMouseEvent* e)
    {
        isLBtnPressed_ = false;
        lastDragOverPanelOrFrame_ = nullptr;

        IAcceptDrop* target = manager_->getDropTarget(e->globalPos(), this);
        if (target)
        {
            target->drop(this, e->globalPos());
        }
    };

    title_->onTitleMouseMoveEvent = [this](QMouseEvent* e)
    {
        if (!isLBtnPressed_)
        {
            return;
        }

        if (dockStatus_ == Docked)
        {
            oldPos_ -= parentWidget()->mapToGlobal(pos());
            undock();
        }

        move(e->globalPos() - oldPos_);

        if (QApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            return;
        }

        IAcceptDrop* target = manager_->getDropTarget(e->globalPos(), this);

        if (target != lastDragOverPanelOrFrame_)
        {
            if (target)
            {
                target->dragEnter();
            }
            if (lastDragOverPanelOrFrame_)
            {
                lastDragOverPanelOrFrame_->dragLeave();
            }
            lastDragOverPanelOrFrame_ = target;
        }

        if (lastDragOverPanelOrFrame_)
        {
            lastDragOverPanelOrFrame_->dragMove(e->globalPos());
        }
    };

    leftEdge_ = new QDockPanelEdgeLeft(this);
    leftTopEdge_ = new QDockPanelEdgeLeftTop(this);
    topEdge_ = new QDockPanelEdgeTop(this);
    rightTopEdge_ = new QDockPanelEdgeRightTop(this);
    rightEdge_ = new QDockPanelEdgeRight(this);
    rightBottomEdge_ = new QDockPanelEdgeRightBottom(this);
    bottomEdge_ = new QDockPanelEdgeBottom(this);
    leftBottomEdge_ = new QDockPanelEdgeLeftBottom(this);

    maskWidget_ = new QDockMaskWidget(this);
    maskWidget_->hide();

    setAcceptDrops(true);

    setMinimumSize(50, 50);
}


void QDockPanel::paintEvent(QPaintEvent*)
{
    QPainter p(this);
}

void QDockPanel::resizeEvent(QResizeEvent*)
{
    relayout();
}

void QDockPanel::resetContensWidgetPosAndSize()
{
    if (!contensWidget_)
    {
        return;
    }

    if (contensWidget_->parentWidget() != this)
    {
        contensWidget_->setParent(this);
    }

    if (dockStatus_ == Docked)
    {
        if (isTabbed_)
        {
            contensWidget_->move(0, 0);
            contensWidget_->resize(width(), height());
        }
        else
        {
            contensWidget_->move(0, edgeWidth_ + titleRectHeight_);
            contensWidget_->resize(width(), height() - edgeWidth_ - titleRectHeight_);
        }
    }
    else
    {
        contensWidget_->move(edgeWidth_, edgeWidth_ * 2 + titleRectHeight_);
        contensWidget_->resize(width() - edgeWidth_ * 2, height() - edgeWidth_ * 3 - titleRectHeight_);
    }
}

void QDockPanel::relayout()
{
    if (dockStatus_ == Docked)
    {
        if (isTabbed_)
        {
            title_->hide();
        }
        else
        {
            title_->move(0, 0);
            title_->resize(width(), titleRectHeight_);
            title_->show();
        }

        leftEdge_->hide();
        leftTopEdge_->hide();
        topEdge_->hide();
        rightTopEdge_->hide();
        rightEdge_->hide();
        rightBottomEdge_->hide();
        bottomEdge_->hide();
        leftBottomEdge_->hide();
    }
    else
    {
        title_->move(edgeWidth_, edgeWidth_);
        title_->resize(width() - edgeWidth_ * 2, titleRectHeight_);
        title_->show();

        leftEdge_->move(0, edgeWidth_);
        leftEdge_->resize(edgeWidth_, height() - edgeWidth_ * 2);
        leftEdge_->show();

        leftTopEdge_->move(0, 0);
        leftTopEdge_->resize(edgeWidth_, edgeWidth_);
        leftTopEdge_->show();

        topEdge_->move(edgeWidth_, 0);
        topEdge_->resize(width() - edgeWidth_ * 2, edgeWidth_);
        topEdge_->show();

        rightTopEdge_->move(width() - edgeWidth_, 0);
        rightTopEdge_->resize(edgeWidth_, edgeWidth_);
        rightTopEdge_->show();

        rightEdge_->move(width() - edgeWidth_, edgeWidth_);
        rightEdge_->resize(edgeWidth_, height() - edgeWidth_ * 2);
        rightEdge_->show();

        rightBottomEdge_->move(width() - edgeWidth_, height() - edgeWidth_);
        rightBottomEdge_->resize(edgeWidth_, edgeWidth_);
        rightBottomEdge_->show();

        bottomEdge_->move(edgeWidth_, height() - edgeWidth_);
        bottomEdge_->resize(width() - edgeWidth_ * 2, edgeWidth_);
        bottomEdge_->show();

        leftBottomEdge_->move(0, height() - edgeWidth_);
        leftBottomEdge_->resize(edgeWidth_, edgeWidth_);
        leftBottomEdge_->show();
    }

    resetContensWidgetPosAndSize();
}

void QDockPanel::setDockStatus()
{
    floatSize_ = size();
    setWindowFlags(Qt::SubWindow);
    relayout();
    dockStatus_ = Docked;
}

void QDockPanel::setFloatStatus()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    resize(floatSize_);
    relayout();
    dockStatus_ = Floating;
    isTabbed_ = false;
}

bool QDockPanel::dockTo(QWidget* target, DockArea area)
{
    return manager_->dockPanelTo(this, target, area);
}

void QDockPanel::undock()
{
    manager_->undockPanel(this);
}

void QDockPanel::dragEnter()
{
    showArrow();
}

void QDockPanel::dragLeave()
{
    arrows_.show(NoneArea);
    maskWidget_->showOnDockArea(NoneArea);
}

void QDockPanel::drop(QWidget* from, QPoint /*pos*/)
{
    QDockPanel* panel = qobject_cast<QDockPanel*>(from);

    if (panel && lastMaskArea_ != NoneArea)
    {
        manager_->dockPanelTo(qobject_cast<QDockPanel*>(panel), this, lastMaskArea_);
    }

    lastMaskArea_ = NoneArea;
    arrows_.show(NoneArea);
    maskWidget_->showOnDockArea(NoneArea);

    manager_->onEndDragAtPanel();
}

void QDockPanel::dragMove(const QPoint& pos)
{
    DockArea area = arrows_.getDockAreaByPos(mapFromGlobal(pos));

    if (area != lastMaskArea_)
    {
        maskWidget_->showOnDockArea(area);
        lastMaskArea_ = area;
    }
}

void QDockPanel::showArrow()
{
    arrows_.show(CenterArea | CenterLeftArea | CenterTopArea | CenterRightArea | CenterBottomArea);
}

void QDockPanel::startDrag()
{
    //title_->startDrag();
    PostMessage((HWND)winId(), WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(0, 0));
}

void QDockPanel::setAutoHide(bool hide)
{
    manager_->autoHidePanel(this, hide);

    dockStatus_ = hide ? AutoHide : Docked;
}

void QDockPanel::setTabbedStatus(bool isTabbed, QDockPanel* parentTabPanel)
{
    isTabbed_ = isTabbed;
    parentTabPanel_ = parentTabPanel;
    relayout();
}

void QDockPanel::setAutoHideStatus()
{
    setParent(manager_->dockFrame_);
    //setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    resize(floatSize_);
    dockStatus_ = AutoHide;
    relayout();
}
