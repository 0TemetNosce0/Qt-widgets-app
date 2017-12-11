#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    setUpSignInWidget();
    getSignInInfo();
    readStuInfo();

    account = new QLabel(QStringLiteral("�ʺ�  "), this);
    password = new QLabel(QStringLiteral("����  "), this);
    accountInput = new QLineEdit(this);
    passwordInput = new QLineEdit(this);
    enterButton = new QPushButton(QStringLiteral("��½"), this);
    forgotButton = new QPushButton(QStringLiteral("��������"), this);
    signInButton = new QPushButton(QStringLiteral("ע��"), this);
    teacherButton = new QRadioButton(QStringLiteral("��ʦ"), this);
    studentButton = new QRadioButton(QStringLiteral("ѧ��"), this);
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
    signInAccount.setText(QStringLiteral("ԭ�ʺ�"));
    signInPassword.setText(QStringLiteral("������"));
    signInWidget->exec();
}

void LoginDialog::teacherMode()
{
    if (!teacherButton->isChecked())
        return;

    forgotButton->setEnabled(true);
    signInButton->setEnabled(true);
    passwordInput->setEnabled(true);
    account->setText(QStringLiteral("�ʺ�  "));
}

void LoginDialog::studentMode()
{
    if (!studentButton->isChecked())
        return;

    forgotButton->setEnabled(false);
    signInButton->setEnabled(false);
    passwordInput->setEnabled(false);
    account->setText(QStringLiteral("ѧ��  "));
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
    signInAccount.setText(QStringLiteral("ע���ʺ�"));
    signInPassword.setText(QStringLiteral("ע������"));
    signInWidget->exec();
}

void LoginDialog::setUpSignInWidget()
{
    signInWidget = new QDialog(0);
    signInAccount.setText(QStringLiteral("ע���ʺ�  "));
    signInAccount.setParent(signInWidget);
    signInPassword.setText(QStringLiteral("ע������  "));
    signInPassword.setParent(signInWidget);
    adminNum.setText(QStringLiteral("����Ա��  "));
    adminNum.setParent(signInWidget);
    signInAccountInput.setParent(signInWidget);
    signInPasswordInput.setParent(signInWidget);
    signInAdminNumInput.setParent(signInWidget);
    signInEnterButton.setText(QStringLiteral("ȷ��"));
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
        QMessageBox::warning(signInWidget, QStringLiteral("����"),
                             QStringLiteral("����д����"), QMessageBox::Yes);
    else
    {
        if ("ע���ʺ�" == signInAccount.text())
        {
            for (int i = 0; i < signInKey.count(); i++)
            {
                if (strcmp(signInKey.at(i).account, signInAccountInput.text().toStdString().data()) == 0)
                {
                    QMessageBox::warning(0, "ע��", "��������ͬ���ʺ�", QMessageBox::Yes);
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
            QMessageBox::information(0, "��ʾ", "ע��ɹ�", QMessageBox::Yes);
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
                        QMessageBox::information(0, "��ʾ", "�����޸ĳɹ�", QMessageBox::Yes);
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
                        QMessageBox::warning(0, "ע��", "����Ա�Ŵ���", QMessageBox::Yes);
                        return;
                    }
                }
            }

            QMessageBox::warning(0, "ע��", "�ʺŲ�����", QMessageBox::Yes);
        }
    }
}

void LoginDialog::enterSlot()
{
    if (signInKey.isEmpty())
    {
        QMessageBox::warning(this, QStringLiteral("ע��"),
                             QStringLiteral("û��ע����Ϣ!"), QMessageBox::Yes);
        return ;
    }
    if (teacherButton->isChecked())
    {
        if (accountInput->text().isEmpty() || passwordInput->text().isEmpty())
        {
            QMessageBox::warning(this, QStringLiteral("����"),
                                 QStringLiteral("�ʺŻ����벻��Ϊ��!"), QMessageBox::Yes);
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
                    QMessageBox::warning(this, QStringLiteral("ע��"),
                                                              QStringLiteral("��½ʧ��, ������"), QMessageBox::Yes);
                    return;
                }
                QTextStream out(&file);
                out << 1;
                file.close();
                this->accept();
                return;
            }
        }

        QMessageBox::warning(0, "ע��", "�ʺŻ��������", QMessageBox::Yes);
        return;
    }
    else
    {
        if (accountInput->text().isEmpty())
        {
            QMessageBox::warning(this, "����", "ѧ�Ų���Ϊ��!", QMessageBox::Yes);
            return ;
        }

        for (int i = 0; i < studentsList.count(); i++)
        {
            if (strcmp(studentsList.at(i).num, accountInput->text().toStdString().data()) == 0)
            {
                QFile file("which");
                if (!file.open(QIODevice::WriteOnly))
                {
                    QMessageBox::warning(this, "ע��", "��½ʧ��, ������", QMessageBox::Yes);
                    return;
                }
                QTextStream out(&file);
                out << 2 << endl << accountInput->text();
                file.close();
                this->accept();
                return;
            }
        }

        QMessageBox::warning(0, "ע��", "�޸�ѧ��", QMessageBox::Yes);
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

