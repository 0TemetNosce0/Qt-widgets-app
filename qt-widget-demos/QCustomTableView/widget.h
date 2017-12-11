#ifndef WIDGET_H
#define WIDGET_H

#include <QTableView>

class Widget : public QTableView
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
