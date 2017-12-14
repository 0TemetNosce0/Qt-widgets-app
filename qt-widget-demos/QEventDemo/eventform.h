#ifndef EVENTFORM_H
#define EVENTFORM_H

#include <QWidget>

namespace Ui {
class EventForm;
}

#include <QDebug>
#include <QListWidget>
#include <QWheelEvent>
#include <QApplication>
#include <QListWidgetItem>

class EventForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit EventForm(QWidget *parent = 0);
    ~EventForm();
    
private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::EventForm *ui;
};

#endif // EVENTFORM_H
