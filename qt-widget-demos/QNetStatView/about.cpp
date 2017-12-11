#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :    QDialog(parent),    ui(new Ui::About){
    ui->setupUi(this);

    ui->label->setText(
        tr("QNetStatView - program that will show you detailed listings of all TCP and UDP endpoints on your system, including the local and remote addresses and state of TCP connections.")+"<BR><BR>"+
        tr("The program is distributed under the GPLv3")
    );

}

About::~About(){
    delete ui;

}

void About::on_pushButton_clicked(){
    this->hide();
}
