#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QGraphicsView>

class TreeView : public QGraphicsView
{
    Q_OBJECT

public:
    TreeView(QWidget *parent = 0);

signals:
    void zoomChanged();

public slots:
    qreal zoom();
    void zoomIn();
    void zoomOut();
    void zoomNormal();
    void setHandCursor();
    void setArrowCursor();

protected:
    void wheelEvent(QWheelEvent *event);

private:
    qreal m_zoom;
};

#endif /* TREEVIEW_H */
