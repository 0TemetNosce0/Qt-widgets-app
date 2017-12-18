#include "uiwidget.h"
#include <Windows.h>
#include "uiwidgetshow.h"
UiWidget::UiWidget(QWidget *parent):
    ui(new Ui::uiwidget)
  ,QWidget(parent)
{
ui->setupUi(this);
//SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
//               WS_EX_TRANSPARENT/* | WS_EX_LAYERED*/);


LONG nRet = ::GetWindowLong((HWND)(this->winId()), GWL_EXSTYLE);
nRet = nRet | WS_EX_LAYERED;
::SetWindowLong((HWND)(this->winId()), GWL_EXSTYLE, nRet);
SetLayeredWindowAttributes((HWND)(this->winId()), 0,  100, LWA_ALPHA);
//setAttribute(Qt::WA_TranslucentBackground, true);
SetWindowLong((HWND)(this->winId()), GWL_EXSTYLE, GetWindowLong((HWND)(this->winId()), GWL_EXSTYLE) | WS_EX_NOACTIVATE |WS_EX_TRANSPARENT);


//::Modi
//ModifyStyleEx
//ModifyStyleEx(0, WS_EX_LAYERED);
//CDC *pDCDst=GetDC();
//CDC dcSrc;
//dcSrc.CreateCompatibleDC(pDCDst);
//UiWidgetShow * test = new UiWidgetShow(this);
//UpdateLayeredWindow(this->GetDC(),pDCDst,&CPoint(0,0),&CSize(300,300),
//                    &dcSrc,&CPoint(0,0),
//                    0,&_Blend,ULW_ALPHA);


}
