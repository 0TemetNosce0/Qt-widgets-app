#include "find_replace.h"
#include "ui_find_replace.h"

Find_Replace::Find_Replace(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Find_Replace)
{
    ui->setupUi(this);
    this->setFixedSize(420,160);//固定大小
    ui->radioButtonDownF->setChecked(true);//默认向下进行查找和替换
    ui->radioButtonDownR->setChecked(true);
    
    ui->nextButtonF->setEnabled(!ui->lineEditF->text().isEmpty());
    connect(ui->lineEditF,SIGNAL(textChanged(QString)),this,SLOT(button_Enabed()));

    ui->nextButtonR->setEnabled(!ui->lineEditR->text().isEmpty());
    connect(ui->lineEditR,SIGNAL(textChanged(QString)),this,SLOT(button_Enabed()));

    ui->pushButtonReplace->setEnabled(!ui->lineEditR->text().isEmpty());
    ui->pushButtonReplaceAll->setEnabled(!ui->lineEditR->text().isEmpty());


}

Find_Replace::~Find_Replace()
{
    delete ui;
}

void Find_Replace::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Find_Replace::button_Enabed()//判断“查找下一个”等等按钮是否可用
{
    ui->nextButtonF->setEnabled(!ui->lineEditF->text().isEmpty());

    ui->nextButtonR->setEnabled(!ui->lineEditR->text().isEmpty());

    ui->pushButtonReplace->setEnabled(!ui->lineEditR->text().isEmpty());

    ui->pushButtonReplaceAll->setEnabled(!ui->lineEditR->text().isEmpty());
}
