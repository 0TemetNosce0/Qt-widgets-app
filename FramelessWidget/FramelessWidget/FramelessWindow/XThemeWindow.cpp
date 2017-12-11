#include "XThemeWindow.h"
#include <QDebug>

XThemeWindow::XThemeWindow(QWidget *parent) : XWindow(parent)
{
    initMembers();
    clientFrame()->setBackgroundColor(Qt::white, Qt::white);
    connect(gp_themeHelper, SIGNAL(themeColorChanged(QColor)), this, SLOT(onThemeColorChanged(QColor)));
    connect(gp_themeHelper, SIGNAL(themeAlphaChanged(int)), this, SLOT(onThemeAlphaChanged(int)));
    connect(gp_themeHelper, SIGNAL(backgroundImageChanged(QPixmap)), SLOT(onBackgroundImageChanged(QPixmap)));
}

XThemeWindow::~XThemeWindow()
{

}

void XThemeWindow::setThemeHelperEnable(bool blEnable)
{
    mo_blThemehelper = blEnable;
}

void XThemeWindow::onThemeColorChanged(QColor color)
{
    //qDebug() << "ThemeColor Changed";
    if(!mo_blThemehelper)   return;
    setThemeColor(color);
}

void XThemeWindow::onThemeAlphaChanged(int ntAlpha)
{
    if(!mo_blThemehelper)   return;
    setThemeAlpha(ntAlpha);
}

void XThemeWindow::onBackgroundImageChanged(QPixmap pixmap)
{
    if(!mo_blThemehelper)   return;
    setBackgroundImage(pixmap);
}

void XThemeWindow::initMembers()
{
    mo_blThemehelper = true;
}
