#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class AccountItem : public QWidget
{
    Q_OBJECT
public:
    explicit AccountItem(QWidget *parent = 0);
    ~AccountItem();

    void setAccountNumber(QString account_text);
    QString getAccountNumber();

protected:
    bool mouse_press;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

signals:
    void showAccount(QString account);
    void removeAccount(QString account);

public slots:
    void removeAccount();

private:
    QLabel *m_label;
    QPushButton *deleteButton;
};

#endif // ACCOUNTITEM_H
