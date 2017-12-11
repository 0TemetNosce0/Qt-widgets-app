#ifndef EXAMPLEMYFOCUS_H
#define EXAMPLEMYFOCUS_H

#include <QLineEdit>
#include "keyboard/widgetKeyBoard.h"


class exampleMyFocus : public QLineEdit
{
public:
    exampleMyFocus(widgetKeyBoard *keyBoard, QWidget *parent = NULL);

protected:
    void focusInEvent (QFocusEvent * event);

private:
    widgetKeyBoard *m_keyBoard;
};

#endif // EXAMPLEMYFOCUS_H
