#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class TextEdit : public QTextEdit
{
    Q_OBJECT

public:
    TextEdit();

protected:
    bool event(QEvent* event);
};

#endif // TEXTEDIT_H
