#ifndef QDOCKPANEL_H
#define QDOCKPANEL_H

#include <QWidget>

#include "QDockCommon.h"
#include "QDockArrows.h"
#include "IAcceptDrop.h"
#include "QDockPanelComponents.h"

class QDockManager;
class QDockMaskWidget;
class QDockTabWidget;
class QDockSideButton;

class QDockPanel : public QWidget, IAcceptDrop
{
    Q_OBJECT
public:
    explicit QDockPanel(QDockManager* manager, QWidget* frame);

    QWidget* getContensWidget(){ return contensWidget_; }
    QWidget* resetContensWidget(QWidget* newWidget)
    {
        QWidget* old = contensWidget_;
        contensWidget_ = newWidget;
        resetContensWidgetPosAndSize();

        return old;
    }

    void setId(int id){ id_ = id; }
    int id(){ return id_; }

    DockStatus dockStatus(){ return dockStatus_; }
    bool dockTo(QWidget* target, DockArea area);
    void undock();
    void startDrag();
    void setAutoHide(bool hide);
private:
    void resizeWidget(int curX, int curY);
    void relayout();
    void setDockStatus();
    void setFloatStatus();
    void setTabbedStatus(bool isTabbed, QDockPanel* parentTabPanel);
    void setAutoHideStatus();

private:
    int id_;                 // panel ID
    int titleRectHeight_;    // panel窗口的标题栏的高度.
    QWidget* contensWidget_; // panel窗口内的widget.
    int edgeWidth_;          // 边框的宽度.
    QSize floatSize_;
    QDockManager* manager_;
    QDockArrows arrows_;
    DockArea lastMaskArea_;
    QDockMaskWidget* maskWidget_;

    bool isTabbed_;
    QDockPanel* parentTabPanel_;

    DockStatus dockStatus_;
    QWidget* dockTarget_;
    DockArea area_;
    QPoint floatPos_;
    QDockSideButton* autoHideBtn_;


    enum PanelType
    {
        DockPanel,
        TabContainer,
        SplitContainer,
    };

    PanelType panelType_;

    QDockPanelTitle* title_;
    QDockPanelEdgeLeft* leftEdge_;
    QDockPanelEdgeTop* topEdge_;
    QDockPanelEdgeRight* rightEdge_;
    QDockPanelEdgeBottom* bottomEdge_;
    QDockPanelEdgeLeftTop* leftTopEdge_;
    QDockPanelEdgeRightTop* rightTopEdge_;
    QDockPanelEdgeRightBottom* rightBottomEdge_;
    QDockPanelEdgeLeftBottom* leftBottomEdge_;


    bool isLBtnPressed_;
    QPoint oldPos_;
    QPoint pressedPos_;
    IAcceptDrop* lastDragOverPanelOrFrame_;


private:
    void showArrow();
protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent* e);
    void resetContensWidgetPosAndSize();

    virtual void dragEnter();

    virtual void dragLeave();

    virtual void drop(QWidget* from, QPoint pos);

    virtual void dragMove(const QPoint& pos);

    friend QDockManager;
    friend QDockPanelTitle;
    friend QDockTabWidget;
};

#endif // QDOCKPANEL_H
