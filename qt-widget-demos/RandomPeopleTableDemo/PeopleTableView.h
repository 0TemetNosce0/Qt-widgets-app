#pragma once

#include <QTableView>

class PeopleTableView : public QTableView {
public:
    PeopleTableView(QWidget *parent);
    QStyleOptionViewItem viewOptions() const;
};