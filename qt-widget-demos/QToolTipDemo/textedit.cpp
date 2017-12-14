#include "textedit.h"
#include <QEvent>
#include <QHelpEvent>
#include <QToolTip>

TextEdit::TextEdit()
{
    setFrameStyle(QFrame::NoFrame);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setText("hello Qt!");
}

bool TextEdit::event(QEvent* event)
{
    if(event->type() == QEvent::ToolTip)
    {
        QHelpEvent *helpEvent = static_cast<QHelpEvent*>(event);
        QTextCursor cursor = cursorForPosition(helpEvent->pos());
        cursor.select(QTextCursor::WordUnderCursor);
        QToolTip::showText(helpEvent->globalPos(), cursor.selectedText());

        return true;
    }

    return QTextEdit::event(event);
}

