#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:


    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void initModel();
    void setupUi();
//    void on_alarmDialog_close();
//    void on_actionNew_triggered();

private:
    Ui::Widget *ui;

    QStandardItemModel* itemModel;
};

#endif // WIDGET_H
