#include "dialog.h"
#include "ui_dialog.h"
#include <QBitmap>
#include <QVBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    leEdit = new QSLineEdit(this);
    leEdit->setGeometry(QRect(20,20, 203, 21));

    leEdit2 = new QSLineEdit(this);
    leEdit2->setGeometry(QRect(90,90, 100, 21));

    this->setStyleSheet("QDialog{background-image:url(:/bg_main.jpg);  background-repeat:no-repeat; }");
    this->setFocus();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::mousePressEvent(QMouseEvent *e)
{
    leEdit->clearFocus();
    leEdit2->clearFocus();

    QDialog::mousePressEvent(e);
}
