#include "chardialog.h"
#include "charstable.h"

class CharsTable;

CharDialog::CharDialog(QChar ch, const QString & fontFamily,
                       const CategoryString & categories,
                       QWidget *parent)
    : QDialog(parent)
{
    this->ch = ch;
    setupUi(this);
    setWindowTitle(tr("Character %1").arg(ch));
    character->setText(ch);

    QFont fn = QFont(character->font());
    fn.setFamily(fontFamily);
    character->setFont(fn);

    unicode->setText(CharsTable::unicodeChar(ch.unicode()));
    utf8->setText(CharsTable::utf8Char(ch));
    xmlDecimal->setText(CharsTable::xmlDecimal(ch.unicode()));
    category->setText(categories[ch.category()]);
}

CharDialog::~CharDialog()
{
}
