#include <QPushButton>
#include "MainWidget.h"


CMainWidget::CMainWidget(QWidget *parent) : XThemeWindow(parent)
{
    initOutlook();
    initMembers();
    initTitleBar();
}

void CMainWidget::onBtnSetTheme()
{
    gp_themeHelper->show();
}

void CMainWidget::initMembers()
{
    mp_btnSetTheme = nullptr;
}

void CMainWidget::initContents()
{

}

void CMainWidget::initTitleBar()
{
    mp_btnSetTheme= new QPushButton;
        connect(mp_btnSetTheme, SIGNAL(clicked(bool)), this, SLOT(onBtnSetTheme()));
        mp_btnSetTheme->setObjectName("BtnTitleBar");
        mp_btnSetTheme->setIcon(QIcon(QPixmap(":/palette.ico").scaled(12,12)));
        mp_btnSetTheme->setIconSize(QSize(titleBar()->minimumHeight(), titleBar()->minimumHeight()));
        mp_btnSetTheme->setToolTip(tr("设置主题"));

        mp_btnSetTheme->setStyleSheet("QPushButton#BtnTitleBar{"
                                      "border: none;"

                                      "background-color: transparent;"
                                      "}"
                                      "QPushButton#BtnTitleBar:hover{"
                                      "background-color: rgba(0,0,0,45);"
                                      "}");

        addWidgetTotitleBar(mp_btnSetTheme);
}

void CMainWidget::initOutlook()
{
    setThemeColor(Qt::green);
    setThemeAlpha(90);
    setRadius(15, 10);
    setShadowColor(Qt::red);
    setShadowRadius(40);

    borderFrame()->setBorderWidth(0);
    borderFrame()->setBorderColor(Qt::red, Qt::blue);
}
