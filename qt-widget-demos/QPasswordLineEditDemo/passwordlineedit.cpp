#include "passwordlineedit.h"

#include <QTimer>

QPasswordLineEdit::QPasswordLineEdit(QWidget *parent, int timeout)
    : QLineEdit(parent)
{
    m_Timeout = timeout;
    m_LineEditText = "";
    m_LastCharCount = 0;

    connect(this, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(displayPasswordAfterEdit(int, int)));
    connect(this, SIGNAL(textEdited(const QString&)), this, SLOT(getRealText(const QString&)));
}

QPasswordLineEdit::~QPasswordLineEdit()
{

}

void QPasswordLineEdit::displayPasswordAfterEdit(int oldPos, int newPos)
{
    if(oldPos >= 0 && newPos >= 0)
    {
        if(newPos > oldPos)
        {
            QTimer::singleShot(m_Timeout, this, SLOT(displayPassword()));
        }
        else
        {
            this->setCursorPosition(oldPos);
        }
    }
}

void QPasswordLineEdit::displayPassword()
{
    this->setText(getMaskString());
}

void QPasswordLineEdit::getRealText(const QString& text)
{
    if(text.count() > m_LastCharCount)
    {
        m_LineEditText.append(text.right(1));
    }
    else if(text.count() < m_LastCharCount)
    {
        m_LineEditText.remove(m_LineEditText.count() - 1, 1);
    }
    m_LastCharCount = m_LineEditText.count();
}

QString QPasswordLineEdit::getPassword() const
{
    return m_LineEditText;
}

void QPasswordLineEdit::setTimeout(int msec)
{
    m_Timeout = msec;
}

int	QPasswordLineEdit::getTimeout() const
{
    return m_Timeout;
}

QString QPasswordLineEdit::getMaskString()
{
    QString mask = "";
    int count = this->text().length();
    if(count > 0)
    {
        for(int i=0; i<count; i++)
        {
            mask += "*";
        }
    }
    return mask;
}
