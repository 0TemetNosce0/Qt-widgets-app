#ifndef PASSWORDLINEEDIT_H
#define PASSWORDLINEEDIT_H

#include <QLineEdit>

class QPasswordLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    QPasswordLineEdit(QWidget *parent, int timeout = 300);
    ~QPasswordLineEdit();

private slots:
    void	displayPasswordAfterEdit(int, int);
    void	displayPassword();
    void	getRealText(const QString&);

public:
    QString getPassword() const;
    void	setTimeout(int msec);
    int		getTimeout() const;

private:
    QString  getMaskString();

private:
    int		 m_Timeout;
    QString	 m_LineEditText;
    int		 m_LastCharCount;
};

#endif // PASSWORDLINEEDIT_H
