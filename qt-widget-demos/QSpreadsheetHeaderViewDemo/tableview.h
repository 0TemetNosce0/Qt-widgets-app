#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

class TableView : public QTableView
{
    Q_OBJECT

public:
    TableView(QWidget *parent = 0);

private:
    void loadStyleSheet(const QString& fileName = ":/qss/qscrollbar.qss");
};

#endif // TABLEVIEW_H
