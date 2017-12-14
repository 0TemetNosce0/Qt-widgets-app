#include "insertwidget.h"
#include "ui_insertwidget.h"

InsertWidget::InsertWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InsertWidget)
{
    ui->setupUi(this);

    connect(ui->okButton, &QPushButton::clicked, this, &InsertWidget::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &InsertWidget::close);
}

InsertWidget::~InsertWidget()
{
    delete ui;
}

int InsertWidget::num() const
{
    return ui->numEdit->text().toInt();
}

QString InsertWidget::name() const
{
    return ui->nameEdit->text();
}

int InsertWidget::id() const
{
    return ui->idEdit->text().toInt();
}

QString InsertWidget::phone() const
{
    return ui->phoneEdit->text();
}

QString InsertWidget::level() const
{
    return ui->levelEdit->text();
}

QString InsertWidget::desc() const
{
    return ui->descEdit->text();
}
