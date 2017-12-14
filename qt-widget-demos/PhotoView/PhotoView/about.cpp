#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(307,165);
    ui->retranslateUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_OK_clicked()
{
    close();
}


