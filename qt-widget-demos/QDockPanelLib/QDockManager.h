#ifndef QDOCKMANAGER_H
#define QDOCKMANAGER_H

#include <QWidget>
#include <map>
#include "QDockCommon.h"

class QDockPanel;
class QDockFrame;
class QDockNode;
class IAcceptDrop;

class QDockManager : public QObject
{
    Q_OBJECT

public:
    QDockManager(QWidget *parent);
    ~QDockManager();

    QDockFrame* getDockFrame(){ return dockFrame_; }
    QDockPanel* addPanel(int id, const QString& title, QPoint pos, QSize size, QWidget* contensWidget = NULL);
    QDockPanel* getDockPanelByID(int id);

public slots:
    bool dockPanelTo(QDockPanel* panel, QWidget* target, DockArea area);
    bool dockPanelToFrame(QDockPanel* panel, DockArea area);
    bool dockPanelToPanel(QDockPanel* from, QDockPanel* target, DockArea area);
    bool autoHidePanel(QDockPanel* panel, bool hide);

public:
    bool isRootNode(QDockNode* node);

    void undockPanel(QDockPanel* panel);

private:
    void onDragEnterPanel();
    void onDragLeavePanel();
    void onEndDragAtPanel();
    bool dockPanelToFloatPanel(QDockPanel* from, QDockPanel* target, DockArea area);
    bool dockPanelToDockedPanel(QDockPanel* from, QDockPanel* target, DockArea area);

    template<typename T>
    T* findChild(const QPoint& pos, const QWidget* except = nullptr)
    {
        return findChild<T>(dockFrame_, pos, except);
    }
    template<typename T>
    T* findChild(QWidget* p, const QPoint& pos, const QWidget* except)
    {
        for (int i = p->children().size() - 1; i >= 0; --i)
        {
            QWidget *child = qobject_cast<QWidget*>(p->children().at(i));

            if (!child ||
                    //child->isWindow() ||
                    child->isHidden() ||
                    child->testAttribute(Qt::WA_TransparentForMouseEvents)
                    )
            {
                continue;
            }

            T* w = nullptr;

            if (w = findChild<T>(child, pos, except))
            {
                return w;
            }

            w = qobject_cast<T*>(child);

            if (!w || !w->rect().contains(w->mapFromGlobal(pos))
                   || w == except)
            {
                continue;
            }

            return w;
        }

        return nullptr;
    }

    IAcceptDrop* getDropTarget(const QPoint& pos, const QWidget* except);
private:
    QDockFrame* dockFrame_;
    std::map<int, QDockPanel*> dockPanels_;

    friend QDockPanel;
    friend QDockFrame;
};


#endif // QDOCKMANAGER_H
