#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMenu>
#include "customaction.h"
#include <QContextMenuEvent>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu* menu = new QMenu();

    menu->addMenu(QLatin1String("Sub-menu 1"))->addAction(QLatin1String("action"));

    menu->addSeparator();

    CustomAction* ca = new CustomAction();
    menu->addAction(ca);

    menu->addMenu(QLatin1String("Sub-menu 2"))->addAction(QLatin1String("action"));

    menu->addAction(new QAction(QLatin1String("cut"), menu));

    menu->exec(event->globalPos());
    delete menu;
}
