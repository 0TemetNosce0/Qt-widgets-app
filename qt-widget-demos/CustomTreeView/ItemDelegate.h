#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QTreeView>
#include <QStyledItemDelegate>

class ItemDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
    ItemDelegate(QObject * parent=0);
    virtual ~ItemDelegate(){}

    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void setView(QTreeView *treeView);
    void setIconSize(QSize size);
    void setExpandIcon(QString expandIconName);
    void setcollapseIcon(QString collapseIconName);

signals:
    void expanded(const QModelIndex &index);

private:
    int        m_pixmapHeight;
    int        m_pixmapWidth;
    QString    m_expandIconName;
    QString    m_collapseIconName;
    QTreeView  *m_treeView;

};
#endif // ITEMDELEGATE_H
