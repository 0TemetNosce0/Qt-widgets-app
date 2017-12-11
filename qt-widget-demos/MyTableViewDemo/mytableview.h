#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QMainWindow>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QPixmap>

namespace Ui {
class MyTableView;
}

class MyTableView;
class MyItemDelegate;
class MyStandardItemModel;

class MyTableView : public QTableView
{
public:
    MyTableView(QWidget * parent=0);
    virtual ~MyTableView(){}

protected:
    void mouseMoveEvent(QMouseEvent * event);

private:
    Ui::MyTableView *ui;

    MyItemDelegate * delegate;
    MyStandardItemModel * model;
};

class MyItemDelegate : public QItemDelegate
{
public:
    MyItemDelegate(QObject *parent = 0);
    virtual ~ MyItemDelegate(){}

    void paint(QPainter *painter,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const;

    bool editorEvent(QEvent *event,
            QAbstractItemModel *model,
            const QStyleOptionViewItem &option,
            const QModelIndex &index);
private:
    QPixmap favouritePixmap;
    QPixmap notFavouritePixmap;

};

class MyStandardItemModel : public QStandardItemModel
{
public:
    MyStandardItemModel(QObject *parent=0)
        :QStandardItemModel(parent){}

    virtual ~ MyStandardItemModel(){}

    QVariant data(const QModelIndex &index,
                  int role=Qt::DisplayRole) const;

    QVariant headerData(int section,
            Qt::Orientation orientation,
            int role = Qt::DisplayRole) const;
};
#endif // MYTABLEVIEW_H
