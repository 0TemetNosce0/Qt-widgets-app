#ifndef LINKLABEL_H
#define LINKLABEL_H

#include <QLabel>

class LinkLabel : public QLabel
{
    Q_OBJECT

public:
    LinkLabel(QWidget *parent = 0);
    ~LinkLabel();

    void setLinkRange(int min, int max);

private:
    QString *numsAtBeginingSmallBox;
    QString *numsAtBegining;
    QString *numsAtMiddle;
    QString *numsAtEnd;
    QString linkButtons;

    int minLinkValue;
    int maxLinkValue;
    int currentValue;

    enum { START_POINT = 1, VISIBLE_COUNT_MARKER = 6, NUMS_AT_LEFT = 2, NUMS_AT_RIGHT = 3 };
    enum { POINT_SIZE = 10 };

    void refreshLabel(int curIndex);
    void setLabelWithoutScrolling(int currentIndex);
    void setScrolledLabel_specialRange(int curIndex);
    void setScrolledLabel_middleRange(int curIndex);
    void switchLinkButtons(int pressedIndex);

private slots:
    void getPressedLink(QString text);

signals:
    void linkPressed(int value);
};

#endif // LINKLABEL_H
