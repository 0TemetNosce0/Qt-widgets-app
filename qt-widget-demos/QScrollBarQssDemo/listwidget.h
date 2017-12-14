#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QtGui>
#include <QLabel>
#include <QWidget>
#include <QListWidget>

namespace Ui {
class ListWidget;
}

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = 0);
    ~ListWidget();

private:
    Ui::ListWidget *ui;

    QLabel *label;
    QListWidget * listWidget;
};

#endif // LISTWIDGET_H
