#include "form.h"
#include "ui_form.h"
/*
 made by www.hnmade.com
 */
Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}
