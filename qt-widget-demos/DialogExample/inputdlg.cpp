#include "inputdlg.h"
#include <QInputDialog>

InputDlg::InputDlg(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(QStringLiteral("��׼����Ի����ʵ��"));

    nameLabel1 =new QLabel;
    nameLabel1->setText(QStringLiteral("����:"));
    nameLabel2 =new QLabel;
    nameLabel2->setText(QStringLiteral("����"));                    	//�����ĳ�ʼֵ
    nameLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    nameBtn =new QPushButton;
    nameBtn->setText(QStringLiteral("�޸�����"));

    sexLabel1 =new QLabel;
    sexLabel1->setText(QStringLiteral("�Ա�:"));
    sexLabel2 =new QLabel;
    sexLabel2->setText(QStringLiteral("��"));                       	//�Ա�ĳ�ʼֵ
    sexLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    sexBtn =new QPushButton;
    sexBtn->setText(QStringLiteral("�޸��Ա�"));

    ageLabel1 =new QLabel;
    ageLabel1->setText(QStringLiteral("����:"));
    ageLabel2 =new QLabel;
    ageLabel2->setText(QStringLiteral("21"));                       //����ĳ�ʼֵ
    ageLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    ageBtn =new QPushButton;
    ageBtn->setText(QStringLiteral("�޸�����"));

    scoreLabel1 =new QLabel;
    scoreLabel1->setText(QStringLiteral("�ɼ�:"));
    scoreLabel2 =new QLabel;
    scoreLabel2->setText(QStringLiteral("80"));                 	//�ɼ��ĳ�ʼֵ
    scoreLabel2->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    scoreBtn =new QPushButton;
    scoreBtn->setText(QStringLiteral("�޸ĳɼ�"));

    mainLayout =new QGridLayout(this);
    mainLayout->addWidget(nameLabel1,0,0);
    mainLayout->addWidget(nameLabel2,0,1);
    mainLayout->addWidget(nameBtn,0,2);

    mainLayout->addWidget(sexLabel1,1,0);
    mainLayout->addWidget(sexLabel2,1,1);
    mainLayout->addWidget(sexBtn,1,2);

    mainLayout->addWidget(ageLabel1,2,0);
    mainLayout->addWidget(ageLabel2,2,1);
    mainLayout->addWidget(ageBtn,2,2);

    mainLayout->addWidget(scoreLabel1,3,0);
    mainLayout->addWidget(scoreLabel2,3,1);
    mainLayout->addWidget(scoreBtn,3,2);

    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);

    connect(nameBtn,SIGNAL(clicked()),this,SLOT(ChangeName()));
    connect(sexBtn,SIGNAL(clicked()),this,SLOT(ChangeSex()));
    connect(ageBtn,SIGNAL(clicked()),this,SLOT(ChangeAge()));
    connect(scoreBtn,SIGNAL(clicked()),this,SLOT(ChangeScore()));
}

void InputDlg::ChangeName()
{
    bool ok;
    QString text=QInputDialog::getText(this,QStringLiteral("��׼�ַ�������Ի���"),QStringLiteral("������������"), QLineEdit::Normal,nameLabel2->text(),&ok);
    if (ok && !text.isEmpty())
        nameLabel2->setText(text);
}

void InputDlg::ChangeSex()
{
    QStringList SexItems;
    SexItems << QStringLiteral("man") << QStringLiteral("woman");

    bool ok;
    QString SexItem = QInputDialog::getItem(this, QStringLiteral("strandard item select frame"),
      QStringLiteral("please select sex:"), SexItems, 0, false, &ok);
    if (ok && !SexItem.isEmpty())
        sexLabel2->setText(SexItem);
}

void InputDlg::ChangeAge()
{
    bool ok;
    int age = QInputDialog::getInt(this, QStringLiteral("strandard int input frame"),
     QStringLiteral("please inpute age"), ageLabel2->text().toInt(&ok), 0, 100, 1, &ok);
    if (ok)
        ageLabel2->setText(QString(QStringLiteral("%1")).arg(age));
}

void InputDlg::ChangeScore()
{
    bool ok;
    double score = QInputDialog::getDouble(this, QStringLiteral("strandard double input frame"),
     QStringLiteral("please input score:"),scoreLabel2->text().toDouble(&ok), 0, 100, 1, &ok);
    if(ok)
        scoreLabel2->setText(QString(QStringLiteral("%1")).arg(score));
}


