#ifndef TAGMNGRLISTVIEW_H
#define TAGMNGRLISTVIEW_H

#include <QListView>

class QPoint;

class TagMngrListView : public QListView
{
    Q_OBJECT

public:
    explicit TagMngrListView(QWidget *parent = 0);
    
protected:
    void startDrag(Qt::DropActions supportedActions);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *e);

    QModelIndex indexVisuallyAt(const QPoint& p);
    
public slots:
    
};

#endif // TAGMNGRLISTVIEW_H
