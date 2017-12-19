#include "uiwidgetshow.h"

#include <Windows.h>
UiWidgetShow::UiWidgetShow(QWidget *parent):ui(new Ui::uiwidgetshow),QWidget(parent)
{

ui->setupUi(this);
//SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
//               WS_EX_TRANSPARENT | WS_EX_LAYERED);
}
