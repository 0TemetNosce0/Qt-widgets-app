#include "charstable.h"

#include <QChar>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets>
#else
#include <QtGui>
#endif

CharsTable::CharsTable(QWidget *parent) : QWidget(parent)
{
    squareSize = 24;
    key = -1;
    setMouseTracking(true);
    initCharCategories();
}

CharsTable::~CharsTable()
{
}

void CharsTable::initCharCategories()
{
    categories.insert(QChar::Mark_NonSpacing, "Mark nonspacing");
    categories.insert(QChar::Mark_SpacingCombining, "Mark spacing combining");
    categories.insert(QChar::Mark_Enclosing, "Mark enclosing");
    categories.insert(QChar::Number_DecimalDigit, "Number decimal digit");
    categories.insert(QChar::Number_Letter, "Number letter");
    categories.insert(QChar::Number_Other, "Number other");
    categories.insert(QChar::Separator_Space, "Separator space");
    categories.insert(QChar::Separator_Line, "Separator line");
    categories.insert(QChar::Separator_Paragraph, "Separator paragraph");
    categories.insert(QChar::Other_Control, "Other control");
    categories.insert(QChar::Other_Format, "Other format");
    categories.insert(QChar::Other_Surrogate, "Other surrogate");
    categories.insert(QChar::Other_PrivateUse, "Other private use");
    categories.insert(QChar::Other_NotAssigned, "Other not assigned");
    categories.insert(QChar::Letter_Uppercase, "Letter uppercase");
    categories.insert(QChar::Letter_Lowercase, "Letter lowercase");
    categories.insert(QChar::Letter_Titlecase, "Letter titlecase");
    categories.insert(QChar::Letter_Modifier, "Letter modifier");
    categories.insert(QChar::Letter_Other, "Letter other");
    categories.insert(QChar::Punctuation_Connector, "Punctuation connector");
    categories.insert(QChar::Punctuation_Dash, "Punctuation dash");
    categories.insert(QChar::Punctuation_Open, "Punctuation open");
    categories.insert(QChar::Punctuation_Close, "Punctuation close");
    categories.insert(QChar::Punctuation_InitialQuote, "Punctuation initial quote");
    categories.insert(QChar::Punctuation_FinalQuote, "Punctuation final quote");
    categories.insert(QChar::Punctuation_Other, "Punctuation other");
    categories.insert(QChar::Symbol_Math, "Symbol math");
    categories.insert(QChar::Symbol_Currency, "Symbol currency");
    categories.insert(QChar::Symbol_Modifier, "Symbol modifier");
    categories.insert(QChar::Symbol_Other, "Symbol other");
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    categories.insert(QChar::Other_NotAssigned, "No category");
#else
    categories.insert(QChar::NoCategory, "No category");
#endif
}

QSize CharsTable::sizeHint() const
{
    return QSize(COLUMNS * squareSize, ROWS * squareSize);
}

void CharsTable::setFontStyle(const QFont & font)
{
    if (this->font == font)
        return;

    this->font = font;
    refresh();
}

void CharsTable::setSubset(QFontDatabase::WritingSystem subset)
{
    this->subset = subset;
}

void CharsTable::goToChar(const QChar & character)
{
    QWidget *viewport = qobject_cast<QWidget *>(parent()->parent());
    QScrollArea *scrollArea = qobject_cast<QScrollArea *>(viewport->parent());
    QScrollBar *bar = scrollArea->verticalScrollBar();

    bar->setValue(character.unicode() / COLUMNS * squareSize);
    key = character.unicode();
    update();
}

QString CharsTable::unicodeChar(uint key)
{
    QString code = QString::number(key, 16);
    while (code.length() < 4)
        code = '0' + code;
    return "U+" + code;
}

QString CharsTable::utf8Char(QChar ch)
{
    QByteArray bytes = QString(ch).toUtf8();
    QString utf8Text;
    for (int i = 0; i < bytes.size(); ++i) {
        if (i > 0)
            utf8Text += ' ';
        utf8Text += "0x" + QString::number((uchar)bytes[i], 16);
    }
    return utf8Text;
}

inline QString CharsTable::xmlDecimal(uint key, bool escape)
{
    return QString(escape ? "&amp;#%1;" : "&#%1;").arg(key);
}

void CharsTable::goToChar(const QString & character)
{
    if (!character.isEmpty())
        goToChar(character[0]);
}

void CharsTable::mouseMoveEvent(QMouseEvent *event)
{
    QPoint widgetPosition = mapFromGlobal(event->globalPos());
    uint key = (widgetPosition.y() / squareSize) * COLUMNS +
               widgetPosition.x() / squareSize;
    QChar ch(key);
    QString text = QString::fromLatin1("<p>Character: <span style=\"\
font-size: 24pt; font-family: %1\">%2</span></p>"
"Unicode: %3<br/>"
"UTF-8: %4<br/>"
"XML decimal: %5")
        .arg(font.family(), ch,
             unicodeChar(key), utf8Char(ch), xmlDecimal(key, true));
    QToolTip::showText(event->globalPos(), text, this);
}

void CharsTable::mousePressEvent(QMouseEvent *event)
{
    key = (event->y() / squareSize) * COLUMNS + event->x() / squareSize;
    QChar qKey = currentChar();

    if (event->button() == Qt::LeftButton) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
        if (qKey.category() != QChar::Other_NotAssigned)
#else
        if (qKey.category() != QChar::NoCategory)
#endif
            emit characterSelected(qKey);
        update();
    } else if (event->button() == Qt::RightButton) {
        CharDialog dialog(qKey, font.family(), categories, this);
        dialog.exec();
    } else {
        QWidget::mousePressEvent(event);
    }
}

void CharsTable::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (!systemColors)
        painter.fillRect(event->rect(), QBrush(Qt::white));
    painter.setFont(font);

    int beginRow = event->rect().top() / squareSize;
    int endRow = event->rect().bottom() / squareSize;
    int beginColumn = event->rect().left() / squareSize;
    int endColumn = event->rect().right() / squareSize;

    if (!systemColors)
        painter.setPen(QPen(Qt::gray));

    for (int row = beginRow; row <= endRow; ++row) {
        for (int column = beginColumn; column <= endColumn; ++column) {
            painter.drawRect(column*squareSize, row*squareSize,
            squareSize, squareSize);
        }
    }

    QFontMetrics fontMetrics(font);
    if (!systemColors)
        painter.setPen(QPen(Qt::black));

    for (int row = beginRow; row <= endRow; ++row) {
        for (int column = beginColumn; column <= endColumn; ++column) {
            int currentKey = row * COLUMNS + column;
            painter.setClipRect(column*squareSize, row*squareSize,
                                squareSize, squareSize);

            if (currentKey == key)
                painter.fillRect(column*squareSize + 1, row*squareSize + 1,
                                 squareSize, squareSize,
                                 QPalette().highlight());

            painter.drawText(column*squareSize + (squareSize / 2) -
                             fontMetrics.width(QChar(currentKey))/2,
                             row*squareSize + 4 + fontMetrics.ascent(),
                             QString(QChar(currentKey)));
        }
    }

    setFixedSize(COLUMNS * squareSize + 1, ROWS * squareSize + 1);
}
