#ifndef QDOCKFRAME_H
#define QDOCKFRAME_H

#include <QtWidgets>
#include "QDockCommon.h"
#include "QDockArrows.h"
#include "IAcceptDrop.h"
#include <map>

class QDockPanel;
class QDockNode;
class QDockMaskWidget;
class QDockManager;
class QDockSideBar;
class QDockSideButton;

class QDockFrame : public QWidget, public IAcceptDrop
{
    Q_OBJECT

public:
    explicit QDockFrame(QDockManager* manager, QWidget *parent);
    virtual ~QDockFrame();
    void showArrow();
private:
    QDockArrows arrows_;
    QDockNode* rootNode_;
    QDockMaskWidget* maskWidget_;
    std::map<int, QDockPanel*> dockPanels_;
    QDockManager* manager_;

    DockArea lastMaskArea_;

    QDockSideBar* leftBar_;
    QDockSideBar* rightBar_;
    QDockSideBar* topBar_;
    QDockSideBar* bottomBar_;

private:
    void onDragEnterPanel();
    void onDragLeavePanel();
    void onEndDragAtPanel();

private:
    QDockSideButton* addSideButton(const QString& title, DockArea area);

    virtual void dragEnter();

    virtual void dragLeave();

    virtual void drop(QWidget* from, QPoint pos);

    virtual void dragMove(const QPoint& pos);

    friend QDockManager;
};

#endif // QDOCKFRAME_H
