#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QMainWindow>

namespace Ui {
class TableWidget;
}

class TableWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = 0);
    ~TableWidget();

private:
    Ui::TableWidget *ui;
};

#endif // TABLEWIDGET_H
