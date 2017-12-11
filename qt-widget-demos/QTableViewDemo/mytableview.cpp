#include "mytableview.h"

#include <QKeyEvent>
#include <QDebug>

MyTableView::MyTableView(QWidget *parent)
    : QTableView(parent)
{

}

void MyTableView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        qDebug() << "123456";
    }

    QTableView::keyPressEvent(event);
}