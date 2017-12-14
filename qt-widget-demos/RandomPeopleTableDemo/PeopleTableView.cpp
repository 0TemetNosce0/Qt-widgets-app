#include "PeopleTableView.h"

PeopleTableView::PeopleTableView(QWidget *parent) : QTableView(parent) {
}

QStyleOptionViewItem PeopleTableView::viewOptions() const {
    QStyleOptionViewItem option = QTableView::viewOptions();
    option.decorationAlignment = Qt::AlignHCenter | Qt::AlignVCenter;
    option.decorationPosition = QStyleOptionViewItem::Top;
    return option;
}
