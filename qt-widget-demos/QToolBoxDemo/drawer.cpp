#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>

Drawer::Drawer(QWidget *parent, Qt::WindowFlags f)
    :QToolBox(parent,f)
{
    setWindowTitle(QStringLiteral("My QQ"));  //����������ı���

    toolBtn1_1 = new QToolButton;
    toolBtn1_1->setText(QStringLiteral("����"));
    toolBtn1_1->setIcon(QPixmap(":/resource/11.png"));
    toolBtn1_1->setIconSize(QPixmap(":/resource/11.png").size());
    toolBtn1_1->setAutoRaise(true);
    toolBtn1_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_2 = new QToolButton;
    toolBtn1_2->setText(QStringLiteral("����"));
    toolBtn1_2->setIcon(QPixmap(":/resource/12.png"));
    toolBtn1_2->setIconSize(QPixmap(":/resource/12.png").size());
    toolBtn1_2->setAutoRaise(true);
    toolBtn1_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_3 = new QToolButton;
    toolBtn1_3->setText(QStringLiteral("����"));
    toolBtn1_3->setIcon(QPixmap("13.jpg"));
    toolBtn1_3->setIconSize(QPixmap("13.jpg").size());
    toolBtn1_3->setAutoRaise(true);
    toolBtn1_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_4 = new QToolButton;
    toolBtn1_4->setText(QStringLiteral("С��"));
    toolBtn1_4->setIcon(QPixmap("14.jpg"));
    toolBtn1_4->setIconSize(QPixmap("14.jpg").size());
    toolBtn1_4->setAutoRaise(true);
    toolBtn1_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_5 = new QToolButton;
    toolBtn1_5->setText(QStringLiteral("С��"));
    toolBtn1_5->setIcon(QPixmap("15.jpg"));
    toolBtn1_5->setIconSize(QPixmap("15.jpg").size());
    toolBtn1_5->setAutoRaise(true);
    toolBtn1_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox1 = new QGroupBox;
    QVBoxLayout *layout1 = new QVBoxLayout(groupBox1);  //(groupBox1);
    layout1->setMargin(10);                             //�����и��������ʾ���
    layout1->setAlignment(Qt::AlignHCenter);            //�����и��������ʾλ��
    layout1->addWidget(toolBtn1_1);
    layout1->addWidget(toolBtn1_2);
    layout1->addWidget(toolBtn1_3);
    layout1->addWidget(toolBtn1_4);
    layout1->addWidget(toolBtn1_5);
    layout1->addStretch();                              //����һ��ռλ��

    toolBtn2_1 = new QToolButton;
    toolBtn2_1->setText(QStringLiteral("С��"));
    toolBtn2_1->setIcon(QPixmap("21.png"));
    toolBtn2_1->setIconSize(QPixmap("21.png").size());
    toolBtn2_1->setAutoRaise(true);
    toolBtn2_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn2_2 = new QToolButton;
    toolBtn2_2->setText(QStringLiteral("С��"));
    toolBtn2_2->setIcon(QPixmap("22.png"));
    toolBtn2_2->setIconSize(QPixmap("22.png").size());
    toolBtn2_2->setAutoRaise(true);
    toolBtn2_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox2 = new QGroupBox;
    QVBoxLayout *layout2 = new QVBoxLayout(groupBox2);
    layout2->setMargin(10);
    layout2->setAlignment(Qt::AlignHCenter);
    layout2->addWidget(toolBtn2_1);
    layout2->addWidget(toolBtn2_2);

    toolBtn3_1 = new QToolButton;
    toolBtn3_1->setText(QStringLiteral("С��"));
    toolBtn3_1->setIcon(QPixmap("31.png"));
    toolBtn3_1->setIconSize(QPixmap("31.png").size());
    toolBtn3_1->setAutoRaise(true);
    toolBtn3_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn3_2 = new QToolButton;
    toolBtn3_2->setText(QStringLiteral("С��"));
    toolBtn3_2->setIcon(QPixmap("32.png"));
    toolBtn3_2->setIconSize(QPixmap("32.png").size());
    toolBtn3_2->setAutoRaise(true);
    toolBtn3_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox3 = new QGroupBox;
    QVBoxLayout *layout3 = new QVBoxLayout(groupBox3);
    layout3->setMargin(10);
    layout3->setAlignment(Qt::AlignHCenter);
    layout3->addWidget(toolBtn3_1);
    layout3->addWidget(toolBtn3_2);

    this->addItem((QWidget*)groupBox1,QStringLiteral("�ҵĺ���"));
    this->addItem((QWidget*)groupBox2,QStringLiteral("İ����"));
    this->addItem((QWidget*)groupBox3,QStringLiteral("������"));
}
