#include "donewdialog.h"
#include "ui_donewdialog.h"
#include <QColorDialog>

DoNewDialog::DoNewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DoNewDialog)
{
    ui->setupUi(this);
    backColor = Qt::white;
}

DoNewDialog::~DoNewDialog()
{
    delete ui;
}

void DoNewDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

int DoNewDialog::getWidth()
{
    return ui->widthSpinBox->text().toInt();
}

int DoNewDialog::getHeight()
{
    return ui->heightSpinBox->text().toInt();
}

QColor DoNewDialog::getBackColor()
{
    return backColor;
}


void DoNewDialog::on_toolButton_clicked()
{
    QColor newColor = QColorDialog::getColor();  //����ɫ�Ի�������ɫ
    if (newColor.isValid())   //����õ����ǿ��õ���ɫ
    {
        backColor = newColor;

        QPalette palette = ui->textBrowser->palette(); //��ʾ�����ɫ
        palette.setColor(QPalette::Base,backColor);
        ui->textBrowser->setPalette(palette);
        update();
    }
}
