#ifndef LOGINCODE_H
#define LOGINCODE_H

#include <QtWidgets/QWidget>
#include "ui_logincode.h"
#include "codearea.h"
#include <QMessageBox>

class LoginCode : public QWidget
{
    Q_OBJECT

public:
    LoginCode(QWidget *parent = 0);
    ~LoginCode();

private slots:
    void replaceCodePic();
    void loginBtnClicked();
    void closeBtnClicked();

private:
    Ui::LoginCode* ui;

    CodeArea *m_pCodeArea;        // ��֤��������
    QMessageBox *m_pMsgBox;       // ��ʾ����
};

#endif // LOGINCODE_H
