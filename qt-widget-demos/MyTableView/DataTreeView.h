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

    //ͨ���кţ���ȡ���νڵ��index
    QModelIndex rowIndex(int rowNo);

    //ͨ�����ڵ��index��ȡ���ǵڼ���
    int indexRow(const QModelIndex& index);

    //����ָ���е�checkstate
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
