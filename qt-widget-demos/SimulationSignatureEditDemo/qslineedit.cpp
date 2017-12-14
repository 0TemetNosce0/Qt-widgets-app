#include "qslineedit.h"

QSLineEdit::QSLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    this->setFrame(true);
    this->setAutoFillBackground(true);
    this->setStyleSheet("QLineEdit{ background:rgba(0,0,0,0%); border:1px; font:10pt}"
                        "QLineEdit:hover{ border-image:url(:/btn_background.png); }"
                        "QLineEdit:!hover{background:rgba(0,0,0,0%);}"
                        "QLineEdit:focus {background:white;border-image:none; border:1px groove lightgray; border-radius:2px}");
}

void QSLineEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter - 1)
    {
        this->clearFocus();
    }

    QLineEdit::keyPressEvent(event);
}

void QSLineEdit::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();
    this->setCursor(QCursor(Qt::IBeamCursor));

    QLineEdit::mousePressEvent(event);
}

void QSLineEdit::mouseMoveEvent(QMouseEvent *event)
{
    if(this->hasFocus())
    {
        this->setCursor(QCursor(Qt::IBeamCursor));
    }
    else
    {
        this->setCursor(QCursor(Qt::ArrowCursor));
    }

    QLineEdit::mouseMoveEvent(event);
}
