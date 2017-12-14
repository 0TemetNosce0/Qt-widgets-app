#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableView>

class MyTableView : public QTableView
{
    Q_OBJECT

public:
    explicit MyTableView(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif