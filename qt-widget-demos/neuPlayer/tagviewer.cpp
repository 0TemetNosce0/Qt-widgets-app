#include "tagviewer.h"
#include "ui_tagviewer.h"

TagViewer::TagViewer(QList<QString> currentMediaInfo, QPixmap *cover, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TagViewer)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    a_metas = currentMediaInfo;
    setupInfos(cover); //send the only thing missing
}

void TagViewer::setupInfos(QPixmap *cover)
{
    ui->a_num->setText(a_metas.at(0));
    ui->a_title->setText(a_metas.at(1));
    ui->a_title->setToolTip(a_metas.at(1));
    ui->a_artist->setText(a_metas.at(2));
    ui->a_artist->setToolTip(a_metas.at(2));
    ui->a_album->setText(a_metas.at(3));
    ui->a_album->setToolTip(a_metas.at(3));
    ui->a_year->setText(a_metas.at(4));
    ui->a_genre->setText(a_metas.at(5));
    if(!cover->isNull())
        ui->a_coverArt->setPixmap(*cover);
}
TagViewer::~TagViewer()
{
    delete ui;
}
