#include "msgboxdlg.h"
#include <QMessageBox>

MsgBoxDlg::MsgBoxDlg(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(QStringLiteral("标准消息对话框的实例"));              //设置对话框的标题
    label = new QLabel;
    label->setText(QStringLiteral("请选择一种消息框"));

    questionBtn = new QPushButton;
    questionBtn->setText(QStringLiteral("QuestionMsg"));

    informationBtn = new QPushButton;
    informationBtn->setText(QStringLiteral("InformationMsg"));

    warningBtn = new QPushButton;
    warningBtn->setText(QStringLiteral("WarningMsg"));

    criticalBtn = new QPushButton;
    criticalBtn->setText(QStringLiteral("CriticalMsg"));

    aboutBtn = new QPushButton;
    aboutBtn->setText(QStringLiteral("AboutMsg"));

    aboutQtBtn = new QPushButton;
    aboutQtBtn->setText(QStringLiteral("AboutQtMsg"));

    //布局
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(label,0,0,1,2);
    mainLayout->addWidget(questionBtn,1,0);
    mainLayout->addWidget(informationBtn,1,1);
    mainLayout->addWidget(warningBtn,2,0);
    mainLayout->addWidget(criticalBtn,2,1);
    mainLayout->addWidget(aboutBtn,3,0);
    mainLayout->addWidget(aboutQtBtn,3,1);

    //事件关联
    connect(questionBtn,SIGNAL(clicked()),this,SLOT(showQuestionMsg()));
    connect(informationBtn,SIGNAL(clicked()),this,SLOT(showInformationMsg()));
    connect(warningBtn,SIGNAL(clicked()),this,SLOT(showWarningMsg()));
    connect(criticalBtn,SIGNAL(clicked()),this,SLOT(showCriticalMsg()));
    connect(aboutBtn,SIGNAL(clicked()),this,SLOT(showAboutMsg()));
    connect(aboutQtBtn,SIGNAL(clicked()),this,SLOT(showAboutQtMsg()));
}

void MsgBoxDlg::showQuestionMsg()
{
    label->setText(QStringLiteral("Question Message Box"));
    switch(QMessageBox::question(this, QStringLiteral("Question Message"),
         QStringLiteral("you have completed, if you want to end this"),
         QMessageBox::Ok | QMessageBox::Cancel,
         QMessageBox::Ok))
    {
    case QMessageBox::Ok:
        label->setText("Question button/Ok");
        break;
    case QMessageBox::Cancel:
        label->setText("Question button/Cancel");
        break;
    default:
        break;
    }
    return;
}
void MsgBoxDlg::showInformationMsg()
{
    label->setText(QStringLiteral("Information Message Box"));
    QMessageBox::information(this,QStringLiteral("Information Message Frame"),
                             QStringLiteral("this is information test, Welcome"));
    return;
}
void MsgBoxDlg::showWarningMsg()
{
    label->setText(QStringLiteral("Warning Message Box"));
    switch(QMessageBox::warning(this,QStringLiteral("Warning Message"),
         QStringLiteral("您修改的内容还未保存,是否要保存对文档的修改？"),
         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
         QMessageBox::Save))
    {
    case QMessageBox::Save:
        label->setText(QStringLiteral("Warning button/Save"));
        break;
    case QMessageBox::Discard:
        label->setText(QStringLiteral("Warning button/Discard"));
        break;
    case QMessageBox::Cancel:
        label->setText(QStringLiteral("Warning button/Cancel"));
        break;
    default:
        break;
    }
    return;
}

void MsgBoxDlg::showCriticalMsg()
{
    label->setText(QStringLiteral("Critical Message Box"));
    QMessageBox::critical(this,QStringLiteral("Critical Message"),QStringLiteral("this is critical message"));
    return;
}

void MsgBoxDlg::showAboutMsg()
{
    label->setText(QStringLiteral("About Message Box"));
    QMessageBox::about(this,QStringLiteral("About"),QStringLiteral("this is about message"));
    return;
}

void MsgBoxDlg::showAboutQtMsg()
{
    label->setText(QStringLiteral("About Qt Message Box"));
    QMessageBox::aboutQt(this,QStringLiteral("About Qt Message"));
    return;
}


