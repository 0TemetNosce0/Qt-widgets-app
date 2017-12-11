#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class PageWidget;

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void changeMaxPage();

private:
    Ui::Widget *ui;
    PageWidget *pageWidget;
};

#endif // WIDGET_H
