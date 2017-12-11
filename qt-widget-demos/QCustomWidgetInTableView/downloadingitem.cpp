#include "downloadingitem.h"
#include "ui_downloadingitem.h"
#include <QDebug>

downloadingitem::downloadingitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::downloadingitem)
{
    ui->setupUi(this);
}

downloadingitem::~downloadingitem()
{
    delete ui;
}

void downloadingitem::setItemIndex(const QModelIndex &index)
{
    m_index = index;
}

void downloadingitem::setItemIcon(QString url)
{
    //ui->iconLabel->setPixmap(QPixmap(url));
}

void downloadingitem::setItemName(QString name)
{
    // ui->nameLabel->setText(name);
}

void downloadingitem::setItemSize(qint64 size)
{
    // ui->sizeLabel->setText(QString::number(size));
}

void downloadingitem::setItemVersion(QString version)
{
    // ui->versionLabel->setText(version);
}

void downloadingitem::setItemProgress(int progress)
{
    // ui->progressBar->setValue(progress);
}

void downloadingitem::setItemDownloadedSize(qint64 size)
{
    // ui->downloadedSizeLabel->setText(QString::number(size));
}

void downloadingitem::setItemSpeed(qint64 speed)
{
    // ui->speedLabel->setText(QString::number(speed));
}

void downloadingitem::setItemStatus(int status)
{
    // switch (status)
    // {
    // case 0:
    // case 1:
    // ui->startButton->setEnabled(false);
    // ui->pauseButton->setEnabled(true);
    // break;
    // case 2:
    // case 3:
    // ui->startButton->setEnabled(true);
    // ui->pauseButton->setEnabled(false);
    // break;
    // case 4:
    // ui->startButton->setEnabled(false);
    // ui->pauseButton->setEnabled(false);
    // break;
    // }
}

void downloadingitem::on_startButton_clicked()
{
    qDebug() << m_index << "is clicked" << endl;
    emit startButtonClicked();
}

void downloadingitem::on_removeButton_clicked()
{
    emit removeButtonClicked();
}

void downloadingitem::on_pauseButton_clicked()
{
    emit pauseButtonClicked();
}
