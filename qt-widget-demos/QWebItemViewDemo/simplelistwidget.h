#ifndef SIMPLELISTWIDGET_H
#define SIMPLELISTWIDGET_H

#include <QWidget>

namespace Ui {
class SimpleListWidget;
}

class SimpleListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleListWidget(QWidget *parent = 0);
    ~SimpleListWidget();

private:
    Ui::SimpleListWidget *ui;
};

#endif // SIMPLELISTWIDGET_H
