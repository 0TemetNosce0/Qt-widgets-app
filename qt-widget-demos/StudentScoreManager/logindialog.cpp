#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    setUpSignInWidget();
    getSignInInfo();
    readStuInfo();

    account = new QLabel(QStringLiteral("帐号  "), this);
    password = new QLabel(QStringLiteral("密码  "), this);
    accountInput = new QLineEdit(this);
    passwordInput = new QLineEdit(this);
    enterButton = new QPushButton(QStringLiteral("登陆"), this);
    forgotButton = new QPushButton(QStringLiteral("忘记密码"), this);
    signInButton = new QPushButton(QStringLiteral("注册"), this);
    teacherButton = new QRadioButton(QStringLiteral("教师"), this);
    studentButton = new QRadioButton(QStringLiteral("学生"), this);
    group = new QButtonGroup(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *accLayout = new QHBoxLayout(this);
    QHBoxLayout *pasLayout = new QHBoxLayout(this);
    QHBoxLayout *radLayout = new QHBoxLayout(this);
    QHBoxLayout *butLayout = new QHBoxLayout(this);

    passwordInput->setEchoMode(QLineEdit::Password);
    group->addButton(teacherButton);
    group->addButton(studentButton);
    teacherButton->setChecked(true);

    accLayout->addWidget(account);
    accLayout->addWidget(accountInput);

    pasLayout->addWidget(password);
    pasLayout->addWidget(passwordInput);

    radLayout->addSpacing(50);
    radLayout->addWidget(teacherButton);
    radLayout->addWidget(studentButton);


    butLayout->addWidget(enterButton);
    butLayout->addWidget(forgotButton);
    butLayout->addWidget(signInButton);

    mainLayout->addLayout(accLayout);
    mainLayout->addLayout(pasLayout);
    mainLayout->addLayout(radLayout);
    mainLayout->addLayout(butLayout);

    setLayout(mainLayout);

    connect(enterButton, SIGNAL(clicked()), this, SLOT(enterSlot()));
    connect(forgotButton, SIGNAL(clicked()), this, SLOT(forgot()));
    connect(signInButton, SIGNAL(clicked()), this, SLOT(signInSlot()));
    connect(teacherButton, SIGNAL(toggled(bool)), this, SLOT(teacherMode()));
    connect(studentButton, SIGNAL(toggled(bool)), this, SLOT(studentMode()));

    setFixedSize(250, 170);
}

void LoginDialog::readStuInfo()
{
    using namespace std;
    fstream file("students", ios_base::in);
    if (!file.is_open())
    {
        file.open("students", ios_base::out);
        file.close();
    }
    else
    {
        Stu temp;
        file.seekg(0, ios_base::beg);
        while(file.read((char *)&temp, sizeof(Stu)))
            studentsList.append(temp);
        file.close();
    }
}

void LoginDialog::forgot()
{
    signInAccount.setText(QStringLiteral("原帐号"));
    signInPassword.setText(QStringLiteral("新密码"));
    signInWidget->exec();
}

void LoginDialog::teacherMode()
{
    if (!teacherButton->isChecked())
        return;

    forgotButton->setEnabled(true);
    signInButton->setEnabled(true);
    passwordInput->setEnabled(true);
    account->setText(QStringLiteral("帐号  "));
}

void LoginDialog::studentMode()
{
    if (!studentButton->isChecked())
        return;

    forgotButton->setEnabled(false);
    signInButton->setEnabled(false);
    passwordInput->setEnabled(false);
    account->setText(QStringLiteral("学号  "));
}

void LoginDialog::getSignInInfo()
{
    using namespace std;

    fstream file("SignInInfo", ios_base::in);

    if (!file.is_open())
        return;
    file.seekg(0, ios_base::beg);

    Key temp;

    while(file.read((char *)&temp, sizeof(Key)))
        signInKey.append(temp);
    file.close();
}

void LoginDialog::signInSlot()
{
    signInAccount.setText(QStringLiteral("注册帐号"));
    signInPassword.setText(QStringLiteral("注册密码"));
    signInWidget->exec();
}

void LoginDialog::setUpSignInWidget()
{
    signInWidget = new QDialog(0);
    signInAccount.setText(QStringLiteral("注册帐号  "));
    signInAccount.setParent(signInWidget);
    signInPassword.setText(QStringLiteral("注册密码  "));
    signInPassword.setParent(signInWidget);
    adminNum.setText(QStringLiteral("管理员号  "));
    adminNum.setParent(signInWidget);
    signInAccountInput.setParent(signInWidget);
    signInPasswordInput.setParent(signInWidget);
    signInAdminNumInput.setParent(signInWidget);
    signInEnterButton.setText(QStringLiteral("确定"));
    signInEnterButton.setParent(signInWidget);

    signInPasswordInput.setEchoMode(QLineEdit::Password);
    signInAdminNumInput.setEchoMode(QLineEdit::Password);

    accLayout.addWidget(&signInAccount);
    accLayout.addWidget(&signInAccountInput);

    pasLayout.addWidget(&signInPassword);
    pasLayout.addWidget(&signInPasswordInput);

    adminLayout.addWidget(&adminNum);
    adminLayout.addWidget(&signInAdminNumInput);

    butLayout.addWidget(&signInEnterButton);

    mainLayout.addLayout(&accLayout);
    mainLayout.addLayout(&pasLayout);
    mainLayout.addLayout(&adminLayout);
    mainLayout.addLayout(&butLayout);

    signInWidget->setLayout(&mainLayout);

    connect(&signInEnterButton, SIGNAL(clicked()), this, SLOT(completedSignInSlot()));

    signInWidget->setFixedSize(250, 170);
    signInWidget->hide();
}

void LoginDialog::completedSignInSlot()
{
    using namespace  std;

    if (signInPasswordInput.text().isEmpty() ||  signInAccountInput.text().isEmpty() || signInAdminNumInput.text().isEmpty())
        QMessageBox::warning(signInWidget, QStringLiteral("警告"),
                             QStringLiteral("请填写完整"), QMessageBox::Yes);
    else
    {
        if ("注册帐号" == signInAccount.text())
        {
            for (int i = 0; i < signInKey.count(); i++)
            {
                if (strcmp(signInKey.at(i).account, signInAccountInput.text().toStdString().data()) == 0)
                {
                    QMessageBox::warning(0, "注意", "不能有相同的帐号", QMessageBox::Yes);
                    signInAccountInput.setText("");
                    signInPasswordInput.setText("");
                    signInAdminNumInput.setText("");
                    return;
                }
            }
            Key temp;

            strcpy(temp.account, signInAccountInput.text().toStdString().data());
            strcpy(temp.password, signInPasswordInput.text().toStdString().data());
            strcpy(temp.admin, signInAdminNumInput.text().toStdString().data());
            signInKey.append(temp);
            fstream file("SignInInfo", ios_base::out);

            if (!file.is_open())
                this->reject();

            QListIterator<Key> iterator(signInKey);

            while(iterator.hasNext())
                file.write((char *)&iterator.next(), sizeof(Key));
            file.close();
            QMessageBox::information(0, "提示", "注册成功", QMessageBox::Yes);
            signInAccountInput.setText("");
            signInPasswordInput.setText("");
            signInAdminNumInput.setText("");
            signInWidget->accept();
        }
        else
        {
            for (int i = 0; i < signInKey.count(); i++)
            {
                if (strcmp(signInKey.at(i).account, signInAccountInput.text().toStdString().data()) == 0)
                {
                    if (strcmp(signInKey.at(i).admin, signInAdminNumInput.text().toStdString().data()) == 0)
                    {
                        strcpy(signInKey[i].password, signInPasswordInput.text().toStdString().data());
                        QMessageBox::information(0, "提示", "密码修改成功", QMessageBox::Yes);
                        signInAccountInput.setText("");
                        signInPasswordInput.setText("");
                        signInAdminNumInput.setText("");

                        using namespace std;

                        fstream file("SignInInfo", ios_base::out);

                        if (!file.is_open())
                            return;
                        file.seekg(0, ios_base::beg);

                        QListIterator<Key> iterator(signInKey);

                        while(iterator.hasNext())
                            file.write((char *)&iterator.next(), sizeof(Key));

                        file.close();


                        signInWidget->accept();
                        return;
                    }
                    else
                    {
                        QMessageBox::warning(0, "注意", "管理员号错误", QMessageBox::Yes);
                        return;
                    }
                }
            }

            QMessageBox::warning(0, "注意", "帐号不存在", QMessageBox::Yes);
        }
    }
}

void LoginDialog::enterSlot()
{
    if (signInKey.isEmpty())
    {
        QMessageBox::warning(this, QStringLiteral("注意"),
                             QStringLiteral("没有注册信息!"), QMessageBox::Yes);
        return ;
    }
    if (teacherButton->isChecked())
    {
        if (accountInput->text().isEmpty() || passwordInput->text().isEmpty())
        {
            QMessageBox::warning(this, QStringLiteral("警告"),
                                 QStringLiteral("帐号或密码不能为空!"), QMessageBox::Yes);
            return ;
        }

        for (int i = 0; i < signInKey.count(); i++)
        {
            if (strcmp(signInKey.at(i).account, accountInput->text().toStdString().data()) == 0 &&
                    strcmp(signInKey.at(i).password, passwordInput->text().toStdString().data()) == 0)
            {
                QFile file("which");
                if (!file.open(QIODevice::WriteOnly))
                {
                    QMessageBox::warning(this, QStringLiteral("注意"),
                                                              QStringLiteral("登陆失败, 请重试"), QMessageBox::Yes);
                    return;
                }
                QTextStream out(&file);
                out << 1;
                file.close();
                this->accept();
                return;
            }
        }

        QMessageBox::warning(0, "注意", "帐号或密码错误", QMessageBox::Yes);
        return;
    }
    else
    {
        if (accountInput->text().isEmpty())
        {
            QMessageBox::warning(this, "警告", "学号不能为空!", QMessageBox::Yes);
            return ;
        }

        for (int i = 0; i < studentsList.count(); i++)
        {
            if (strcmp(studentsList.at(i).num, accountInput->text().toStdString().data()) == 0)
            {
                QFile file("which");
                if (!file.open(QIODevice::WriteOnly))
                {
                    QMessageBox::warning(this, "注意", "登陆失败, 请重试", QMessageBox::Yes);
                    return;
                }
                QTextStream out(&file);
                out << 2 << endl << accountInput->text();
                file.close();
                this->accept();
                return;
            }
        }

        QMessageBox::warning(0, "注意", "无该学生", QMessageBox::Yes);
    }
}

LoginDialog::~LoginDialog()
{
    delete account;
    delete password;
    delete accountInput;
    delete passwordInput;
    delete enterButton;
    delete signInButton;
    delete teacherButton;
    delete studentButton;
    delete group;
}

