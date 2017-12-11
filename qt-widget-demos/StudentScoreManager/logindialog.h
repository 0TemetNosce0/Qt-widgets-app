#ifndef CODE_H
#define CODE_H

#include "head.h"

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void getSignInInfo();
    void setUpSignInWidget();
    void readStuInfo();

public slots:
    void signInSlot();
    void completedSignInSlot();
    void enterSlot();
    void teacherMode();
    void studentMode();
    void forgot();

private:
    QList<Stu> studentsList;
    QList<Key> signInKey;
    QLabel *account;
    QLabel *password;
    QLineEdit *accountInput;
    QLineEdit *passwordInput;
    QPushButton *enterButton;
    QPushButton *signInButton;
    QPushButton *forgotButton;
    QDialog *signInWidget;

    QLabel signInAccount;
    QLabel signInPassword;
    QLabel adminNum;
    QLineEdit signInAccountInput;
    QLineEdit signInPasswordInput;
    QLineEdit signInAdminNumInput;
    QPushButton signInEnterButton;

    QVBoxLayout mainLayout;
    QHBoxLayout accLayout;
    QHBoxLayout pasLayout;
    QHBoxLayout adminLayout;
    QHBoxLayout butLayout;

    QRadioButton *teacherButton;
    QRadioButton *studentButton;

    QButtonGroup *group;

};

#endif // CODE_H
