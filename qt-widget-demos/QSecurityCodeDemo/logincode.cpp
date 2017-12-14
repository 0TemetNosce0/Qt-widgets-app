#include "logincode.h"

LoginCode::LoginCode(QWidget *parent)
    : QWidget(parent)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
//    m_pCodeArea = new CodeArea(this);
//    ui->CodeLayout->addWidget(m_pCodeArea);
    connect(ui->replaceBtn, SIGNAL(clicked()), this, SLOT(replaceCodePic()));
    connect(ui->loginBtn, SIGNAL(clicked()), this, SLOT(loginBtnClicked()));
    connect(ui->closeBtn, SIGNAL(clicked()), this, SLOT(closeBtnClicked()));
}

LoginCode::~LoginCode()
{
    if (m_pCodeArea)
    {
        delete m_pCodeArea;
        m_pCodeArea = nullptr;
    }

    if (m_pMsgBox)
    {
        delete m_pMsgBox;
        m_pMsgBox = nullptr;
    }
}

void LoginCode::replaceCodePic()
{
    ui->m_pCodeArea->replaceCodePic();
}

void LoginCode::loginBtnClicked()
{
    if (ui->m_pCodeArea->checkCode(ui->code->text()))
    {
        m_pMsgBox = new QMessageBox(QMessageBox::Information, QStringLiteral("提示"), QStringLiteral("登陆成功"),
            QMessageBox::Ok, this);
    }
    else
    {
        m_pMsgBox = new QMessageBox(QMessageBox::Information, QStringLiteral("提示"), QStringLiteral("验证码不正确"),
            QMessageBox::Ok, this);
    }

    m_pMsgBox->exec();
}

void LoginCode::closeBtnClicked()
{
    close();
}
