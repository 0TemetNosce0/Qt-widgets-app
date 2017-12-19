#ifndef UIWIDGETSHOW_H
#define UIWIDGETSHOW_H
#include "ui_formshow.h"
namespace Ui {
class uiwidgetshow;
}
class UiWidgetShow:public QWidget
{
public:
    UiWidgetShow(QWidget *parent = 0);
    Ui::uiwidgetshow * ui;
};

#endif // UIWIDGETSHOW_H
