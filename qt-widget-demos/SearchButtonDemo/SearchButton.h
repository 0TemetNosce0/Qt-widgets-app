#ifndef SEARCHBUTTON_H
#define SEARCHBUTTON_H

#include <QPushButton>

class QString;
class QLineEdit;

class SearchButton : public QPushButton
{
    Q_OBJECT

public:
    SearchButton(const QString &text, QLineEdit *edit);
};

#endif // SEARCHBUTTON_H
