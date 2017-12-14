#include "setupUtiliteKill.h"
#include "ui_setupUtiliteKill.h"
#include <QDir>
#include <QFile>
#include <QSettings>

setupUtiliteKill::setupUtiliteKill(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::setupUtiliteKill)
{
    ui->setupUi(this);

    this->setWindowTitle("Utilite for close connection");
    this->setFixedSize(this->width(),this->height());

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(hide()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(actionApply()));

    QSettings conf(QDir::homePath()+"/.config/qnetstatview/qnetstatview.ini", QSettings::IniFormat);
    conf.setPath(QSettings::IniFormat, QSettings::UserScope, QDir::currentPath());

    ui->lineEdit->setText(conf.value("General/prockill","").toString());

}

setupUtiliteKill::~setupUtiliteKill()
{
    delete ui;
}

void setupUtiliteKill::actionApply()
{

    QSettings conf(QDir::homePath()+"/.config/qnetstatview/qnetstatview.ini", QSettings::IniFormat);
    conf.setPath(QSettings::IniFormat, QSettings::UserScope, QDir::currentPath());

    conf.setValue("General/prockill",ui->lineEdit->text());

    hide();
}
