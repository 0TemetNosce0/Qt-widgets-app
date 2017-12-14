#ifndef DIALOG_H
#define DIALOG_H

#include "GLDMaskBox.h"

#include <QDialog>

class QTextEdit;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~Dialog();

protected:
    void initUI();

public slots:
    void showPosition();
    void showMask();

private:
    QPushButton* m_btn1;
    QPushButton* m_pNextButton;

    QTextEdit*   m_textEdt;
    GLDMaskBox*  m_pMask;
};

#endif // DIALOG_H
