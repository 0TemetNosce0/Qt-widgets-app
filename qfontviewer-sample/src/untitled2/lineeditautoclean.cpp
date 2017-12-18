#include "lineeditautoclean.h"

LineEditAutoclean::LineEditAutoclean(QWidget *parent) : QLineEdit(parent)
{
}

void LineEditAutoclean::keyPressEvent(QKeyEvent *event)
{
    QString text = event->text();
    if (!text.isEmpty()) {
        setText(text);
        emit textEdited(text);
    } else {
        QLineEdit::keyPressEvent(event);
    }
}

void LineEditAutoclean::mousePressEvent(QMouseEvent *event)
{
    setText(QString());
    QWidget::mousePressEvent(event);
}
