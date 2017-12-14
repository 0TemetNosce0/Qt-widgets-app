#ifndef GTABLEWIDGET_H
#define GTABLEWIDGET_H


#include <QTableWidget>

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(int rows, int cols, QWidget* parent = 0);

    bool eventFilter(QObject* o, QEvent* e);

};


#endif // GTABLEWIDGET_H
