#include "uitabwidget.h"
#include <QTabBar>

UiTabWidget::UiTabWidget(QWidget *parent)
	: QTabWidget(parent)
{
	tabBar()->hide();
}

UiTabWidget::~UiTabWidget()
{

}
