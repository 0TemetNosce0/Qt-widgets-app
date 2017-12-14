#ifndef LISTITEM_H
#define LISTITEM_H

#include <QList>
#include <QVariant>

class ListItem
{
public:
    ListItem(const QList<QVariant> &data, ListItem *parent = 0);
    ~ListItem();

    void appendChild(ListItem *child);

    ListItem *child(int row);
    int childCount() const;
    void deleteChild(int row);
    void insertChild(int row, ListItem *item);
    int columnCount() const;
    QVariant data(int column) const;
    void setData(QList<QVariant> &data);
    int row() const;
    ListItem *parent();
    QList<ListItem*> childItems;

private:
    QList<QVariant> itemData;
    ListItem *parentItem;
};

#endif
