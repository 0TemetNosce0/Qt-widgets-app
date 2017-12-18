#ifndef UIWIDGET_H
#define UIWIDGET_H
#include <QWidget>
#include "ui_form.h"
namespace Ui {
class uiwidget;
}
class UiWidget:public QWidget
{
public:
    UiWidget(QWidget *parent = 0);
    Ui::uiwidget *ui;
};

#endif // UIWIDGET_H
