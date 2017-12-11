#include <QFont>
#include <QDebug>
#include <QString>

#include "LinkLabel.h"

LinkLabel::LinkLabel(QWidget *parent)
    : QLabel(parent)
{
    this->setTextFormat(Qt::RichText);
    this->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    QFont labelFont(this->font());
    labelFont.setPointSize(POINT_SIZE);
    this->setFont(labelFont);

    numsAtBeginingSmallBox = new QString(tr("Pages:  %1 | "
                                            "%2"));

    numsAtBegining = new QString(tr("Pages:  %1 ... "
                                             "<a href = \"%2\">%2</a> | "
                                             "%3"));
    numsAtMiddle = new QString(tr("Pages: <a href = \"%1\">%1</a> ... "
                                  "%2 ... "
                                  "<a href = \"%3\">%3</a> | "
                                  "%4"));
    numsAtEnd = new QString(tr("Pages: <a href = \"%1\">%1</a> ... "
                               "%2 "
                               "%3"));

    connect(this, SIGNAL(linkActivated(QString)), this, SLOT(getPressedLink(QString)));
}

LinkLabel::~LinkLabel()
{
    delete numsAtBeginingSmallBox;
    delete numsAtBegining;
    delete numsAtMiddle;
    delete numsAtEnd;
}

void LinkLabel::getPressedLink(QString text)
{
    if (text == "#NEXT")
    {
        // set next link
        refreshLabel(currentValue + 1);
        return;
    }
    else if (text == "#PREVIOUS")
    {
        // set previous link
        refreshLabel(currentValue - 1);
        return;
    }

    bool ok = false;
    int index = text.toInt(&ok);

    // check convertation from string to int
    if (!ok)
    {
        qDebug() << "ERROR: cannot convert to int in "
                "void LinkLabel::getPressedLink(QString text)";
        return;
    }
    refreshLabel(index);
}

void LinkLabel::refreshLabel(int curIndex)
{
    // set pressed value to current Value
    currentValue = curIndex;
    // processes Previous and Next Links
    switchLinkButtons(curIndex);
    // if mail count <= VISIBLE_COUNT_MARKER set label link without ... last
    if (maxLinkValue < minLinkValue + VISIBLE_COUNT_MARKER)
    {
        setLabelWithoutScrolling(curIndex);
        return;
    }
    // if index from start or from end range of label ("special range")
    if (curIndex < minLinkValue + VISIBLE_COUNT_MARKER - 1 ||
        curIndex > maxLinkValue - VISIBLE_COUNT_MARKER + 1)
    {
        setScrolledLabel_specialRange(curIndex);
    }
    // paint range in the middle
    else
    {
        setScrolledLabel_middleRange(curIndex);
    }
}

void LinkLabel::setLabelWithoutScrolling(int currentIndex)
{
    int linkValue = minLinkValue;
    QString linkString;

    while (linkValue <= maxLinkValue)
    {
        // if number is pressed disable it
        if (linkValue == currentIndex)
        {
            linkString.append(QString("%1 | ")
                                      .arg(QString::number(linkValue)));
        }
        else
        {
            linkString.append(QString("<a href = \"%1\">%1</a> | ")
                                      .arg(QString::number(linkValue)));
        }
        ++linkValue;
    }
    // set to Label
    setText(numsAtBeginingSmallBox->arg(linkString, linkButtons));
    emit linkPressed(currentIndex);
}

void LinkLabel::setScrolledLabel_specialRange(int curIndex)
{
    // if selected index from beginning of label
    if (curIndex < minLinkValue + VISIBLE_COUNT_MARKER - 1)
    {
        int linkValue = minLinkValue;
        QString linkString;
        while (linkValue <= minLinkValue + VISIBLE_COUNT_MARKER - 1)
        {
            // current link disabled
            if (linkValue == curIndex)
            {
                linkString.append(QString("%1 | ")
                                  .arg(QString::number(linkValue)));
            }
            else
            {
                linkString.append(QString("<a href = \"%1\">%1</a> | ")
                                          .arg(QString::number(linkValue)));
            }
            ++linkValue;
        }
        setText(numsAtBegining->arg(linkString, linkButtons));
        emit linkPressed(curIndex);
    }
    else
    {
        int linkValue = maxLinkValue - VISIBLE_COUNT_MARKER + 1;
        QString linkString;

        while (linkValue <= maxLinkValue)
        {
            // current link disabled
            if (linkValue == curIndex)
            {
                linkString.append(QString("%1 | ")
                                  .arg(QString::number(linkValue)));
            }
            else
            {
                linkString.append(QString("<a href = \"%1\">%1</a> | ")
                                          .arg(QString::number(linkValue)));
            }
            ++linkValue;
        }
        setText(numsAtEnd->arg(QString::number(minLinkValue), linkString, linkButtons));
        emit linkPressed(curIndex);
    }
}

void LinkLabel::setScrolledLabel_middleRange(int curIndex)
{
    int linkValue = curIndex - NUMS_AT_LEFT;
    int endPoint = curIndex + NUMS_AT_RIGHT;
    QString linkString;

    while (linkValue <= endPoint)
    {
        // if number is pressed disable it
        if (linkValue == curIndex)
        {
            linkString.append(QString("%1 | ")
                                      .arg(QString::number(linkValue)));
        }
        else
        {
            linkString.append(QString("<a href = \"%1\">%1</a> | ")
                                      .arg(QString::number(linkValue)));
        }
        ++linkValue;
    }

    setText(numsAtMiddle->arg(linkString, linkButtons));

    emit linkPressed(curIndex);
}

void LinkLabel::switchLinkButtons(int pressedIndex)
{
    if (pressedIndex == minLinkValue)
    {
        linkButtons = tr("Previous | ") + tr("<a href = \"#NEXT\">Next</a>");
    }
    else if (pressedIndex == maxLinkValue)
    {
        linkButtons = tr("<a href = \"#PREVIOUS\">Previous</a> | ") + tr("Next");
    }
    else
    {
        linkButtons = tr("<a href = \"#PREVIOUS\">Previous</a> | ") +
                tr("<a href = \"#NEXT\">Next</a>");
    }
    return;
}

void LinkLabel::setLinkRange(int min, int max)
{
    minLinkValue = min;
    maxLinkValue = max;
    // set maximum value of link in label
    *numsAtBegining = numsAtBegining->arg("%1", QString::number(max));
    *numsAtMiddle = numsAtMiddle->arg(QString::number(minLinkValue),
                                        "%2", QString::number(max));

    // re-calculate position and visible links in label
    refreshLabel(minLinkValue);
}




