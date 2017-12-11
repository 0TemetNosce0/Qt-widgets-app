#ifndef DATATREEVIEW_H_
#define DATATREEVIEW_H_

#include <QTreeView>
#include <QWheelEvent>

class DataTreeView : public QTreeView
{
    Q_OBJECT

public:
    DataTreeView(QWidget* parent = NULL);
    ~DataTreeView();

    static DataTreeView* m_Instance;

    //通过行号，获取树形节点的index
    QModelIndex rowIndex(int rowNo);

    //通过树节点的index获取它是第几行
    int indexRow(const QModelIndex& index);

    //更新指定列的checkstate
    void updateCheckStateByCol(int col, Qt::CheckState state);

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    virtual void mouseMoveEvent ( QMouseEvent * event );

private slots:
    void onCollapsed ( const QModelIndex &index );
    void onExpanded ( const QModelIndex &index );

private:

};

#endif
