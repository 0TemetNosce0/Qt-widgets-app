#ifndef LOGOINWIDGET_H
#define LOGOINWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class Dialog;
class GLDMaskBox;

class LogoinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogoinWidget(QWidget *parent = 0);
    ~LogoinWidget();

signals:

public slots:
    void showDialog();

private:
    QLabel*      m_name;
    QLabel*      m_password;

    QLineEdit*   m_edtName;
    QLineEdit*   m_edtPwd;

    QPushButton* m_logoin;
    QPushButton* m_cancel;

    Dialog*      m_dialog;

    GLDMaskBox*  pMask;
};

#endif // LOGOINWIDGET_H
