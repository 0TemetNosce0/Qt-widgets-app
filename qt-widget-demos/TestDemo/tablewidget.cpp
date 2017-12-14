#include "tablewidget.h"
#include "ui_tablewidget.h"

TableWidget::TableWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TableWidget)
{
    ui->setupUi(this);
}

TableWidget::~TableWidget()
{
    delete ui;
}
