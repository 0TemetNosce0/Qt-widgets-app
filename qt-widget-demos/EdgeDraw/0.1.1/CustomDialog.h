#ifndef DIALOG_H
#define DIALOG_H

#include "GLDMaskBox.h"

#include <QDialog>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~Dialog();

protected:
    //virtual void mousePressEvent(QMouseEvent *mouseEvent);
    //virtual void mouseMoveEvent(QMouseEvent *mouseEvent);
public slots:
    void showPosition();

private:
    QPoint pPos;
    GLDMaskBox * m_mask;
    QPushButton* m_pPreButton;
    QPushButton* m_pNextButton;
};

#endif // DIALOG_H
