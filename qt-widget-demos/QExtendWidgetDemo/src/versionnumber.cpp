#include "versionnumber.h"

VersionNumber::VersionNumber()
{

}

VersionNumber::VersionNumber(const QString & value)
{
    helper_setValue(value);
}

VersionNumber::VersionNumber(const VersionNumber & value)
{
    helper_copyFromHere(value);
}

VersionNumber::VersionNumber(const qint64 value)
{
    helper_setValue(QString::number(value));
}

VersionNumber::~VersionNumber()
{

}

QString VersionNumber::toString() const
{
    return theString;
}

VersionNumber VersionNumber::operator=(const VersionNumber & value)
{
    helper_copyFromHere(value);
    return *this;
}

VersionNumber VersionNumber::operator=(const QString & value)
{
    helper_setValue(value);
    return *this;
}

VersionNumber VersionNumber::operator=(qint64 value)
{
    helper_setValue(QString::number(value));
    return *this;
}

bool VersionNumber::operator<(const VersionNumber & value) const
{
    return (whichIsBigger(*this, value) == second_one);
}

bool VersionNumber::operator<=(const VersionNumber & value) const
{
    return (! (whichIsBigger(*this, value) == first_one));
}

bool VersionNumber::operator>(const VersionNumber & value) const
{
    return (whichIsBigger(*this, value) == first_one);
}

bool VersionNumber::operator>=(const VersionNumber & value) const
{
    return (!(whichIsBigger(*this, value) == second_one));
}

bool VersionNumber::operator==(const VersionNumber & value) const
{
    return (whichIsBigger(*this, value) == both_are_equal);
}

bool VersionNumber::operator!=(const VersionNumber & value) const
{
    return (!(whichIsBigger(*this, value) == both_are_equal));
}

void VersionNumber::helper_setValue(const QString & value)
{
    theString = value;
    if (value.contains(':'))
    {
        epoch = helper_createNumberWithPointsAndDashes(value.section(':', 0, 0));
        version_and_release = helper_createNumberWithPointsAndDashes(value.section(':', 1));
    }
    else
    {
        epoch = helper_createNumberWithPointsAndDashes(QChar('0'));
        version_and_release = helper_createNumberWithPointsAndDashes(value);
    }
}

VersionNumber::characterType VersionNumber::helper_characterType(const QChar & value)
{
    // variables
    characterType returnValue;

    // code
    if (value.isLetter()) {
        returnValue = letter;
    } else {
        if (value.isDigit()) {
            returnValue = digit;
        } else {
            returnValue = other;
        };
    };
    return returnValue;
}

VersionNumber::simpleNumber VersionNumber::helper_createSimpleNumber(const QString & value)
{
    simpleNumber returnValue;
    int i;
    characterType oldCharacterType;
    characterType newCharacterType;
    QString stack;

    if (value.size() > 0)
    {
        oldCharacterType = helper_characterType(value.at(0)); // works only if the
        for (i=0; i<value.size(); ++i)
        {
            newCharacterType = helper_characterType(value.at(i));
            if (newCharacterType == oldCharacterType)
            {
                stack += value.at(i);
            }
            else
            {
                returnValue.append(stack);
                stack.clear();
                stack += value.at(i);
                oldCharacterType = newCharacterType;
            }
        }
        returnValue.append(stack);
    }
    return returnValue;
}

VersionNumber::numberWithPoints VersionNumber::helper_createNumberWithPoints(
        const QString & value)
{
    numberWithPoints returnValue;
    QStringList m_list;
    int i;

    m_list = value.split('-');
    for (i=0; i<m_list.size(); i++)
    {
        returnValue.append(helper_createSimpleNumber(m_list.at(i)));
    }
    return returnValue;
}

VersionNumber::numberWithPointsAndDashes VersionNumber::helper_createNumberWithPointsAndDashes(
        const QString & value)
{
    numberWithPointsAndDashes returnValue;
    QStringList m_list;
    int i;

    m_list = value.split('-');
    for (i=0; i<m_list.size(); i++)
    {
        returnValue.append(helper_createNumberWithPoints(m_list.at(i)));
    }
    return returnValue;
}

void VersionNumber::helper_copyFromHere(const VersionNumber & value)
{
    theString = value.theString;
    epoch = value.epoch;
    version_and_release = value.version_and_release;
}

VersionNumber::type_whichIsBigger VersionNumber::whichIsBigger(const VersionNumber & firstValue,
                                                               const VersionNumber & secondValue)
{
    type_whichIsBigger temp;
    type_whichIsBigger returnValue;

    temp = whichIsBigger(firstValue.epoch, secondValue.epoch);
    if (temp != both_are_equal)
    {
        returnValue = temp;
    }
    else
    {
        returnValue = whichIsBigger(firstValue.version_and_release, secondValue.version_and_release);
    }
    return returnValue;
}

VersionNumber::type_whichIsBigger VersionNumber::whichIsBigger(
        const numberWithPointsAndDashes & firstValue,
        const numberWithPointsAndDashes & secondValue)
{
    type_whichIsBigger temp;
    bool abort;
    int i;

    i = 0;
    abort = false;
    while (abort == false)
    {
        if (firstValue.size() > i)
        {
            if (secondValue.size() > i)
            {
                temp = whichIsBigger(firstValue.at(i), secondValue.at(i));
                if (temp != both_are_equal)
                {
                    abort = true;
                }
            }
            else
            {
                temp = first_one;
                abort = true;
            }
        }
        else
        {

            if (secondValue.size() > i)
            {
                temp = second_one;
                abort = true;
            }
            else
            {
                temp = both_are_equal;
                abort = true;
            }
        }
        i = i+1;
    }
    return temp;
}

VersionNumber::type_whichIsBigger VersionNumber::whichIsBigger(
        const numberWithPoints & firstValue,
        const numberWithPoints & secondValue)
{
    type_whichIsBigger temp;
    bool abort;
    int i;

    i = 0;
    abort = false;
    while (abort == false)
    {
        if (firstValue.size() > i)
        {

            if (secondValue.size() > i)
            {
                temp = whichIsBigger(firstValue.at(i), secondValue.at(i));
                if (temp != both_are_equal)
                {
                    abort = true;
                }
            }
            else
            {
                temp = first_one;
                abort = true;
            }
        }
        else
        {

            if (secondValue.size() > i)
            {
                temp = second_one;
                abort = true;
            }
            else
            {
                temp = both_are_equal;
                abort = true;
            }
        }
        i = i+1;
    }
    return temp;
}

VersionNumber::type_whichIsBigger VersionNumber::whichIsBigger(const simpleNumber & firstValue,
                                                               const simpleNumber & secondValue)
{
    type_whichIsBigger temp;
    bool abort;
    int i;

    i = 0;
    abort = false;
    while (abort == false)
    {
        if (firstValue.size() > i)
        {

            if (secondValue.size() > i)
            {
                temp = whichIsBigger(firstValue.at(i), secondValue.at(i));
                if (temp != both_are_equal)
                {
                    abort = true;
                }
            }
            else
            {
                temp = first_one;
                abort = true;
            }
        }
        else
        {
            if (secondValue.size() > i)
            {
                temp = second_one;
                abort = true;
            }
            else
            {
                temp = both_are_equal;
                abort = true;
            }
        }
        i = i+1;
    }
    return temp;
}

VersionNumber::type_whichIsBigger VersionNumber::helper_whichNumberIsBigger(
        const QString & firstValue,
        const QString & secondValue)
{
    quint64 m_firstNumber;
    quint64 m_secondNumber;
    quint64 m_firstStringSize;
    quint64 m_secondStringSize;
    type_whichIsBigger returnValue;

    m_firstNumber = firstValue.toULongLong();
    m_secondNumber = secondValue.toULongLong();
    if (m_firstNumber > m_secondNumber)
    {
        returnValue = first_one;
    }
    else if (m_firstNumber < m_secondNumber)
    {
        returnValue = second_one;
    }
    else
    {
        m_firstStringSize = firstValue.size();
        m_secondStringSize = secondValue.size();
        if (m_firstStringSize > m_secondStringSize)
        {
            returnValue = first_one;
        }
        else if (m_firstStringSize < m_secondStringSize)
        {
            returnValue = second_one;
        }
        else
        {
            returnValue = both_are_equal;
        }
    }
    return returnValue;
}

VersionNumber::type_whichIsBigger VersionNumber::helper_whichStringIsBigger(
        const QString & firstValue,
        const QString & secondValue)
{
    type_whichIsBigger returnValue;

    if (firstValue > secondValue)
    {
        returnValue = first_one;
    }
    else if (firstValue < secondValue)
    {
        returnValue = second_one;
    }
    else
    {
        returnValue = both_are_equal;
    }
    return returnValue;
}

VersionNumber::type_whichIsBigger VersionNumber::whichIsBigger(const QString & firstValue,
                                                               const QString & secondValue)
{
    type_whichIsBigger returnValue;

    if (firstValue.at(0).isDigit() && secondValue.at(0).isDigit())
    {
        returnValue = helper_whichNumberIsBigger(firstValue, secondValue);
    }
    else
    {
        returnValue = helper_whichStringIsBigger(firstValue, secondValue);
    }
    return returnValue;
}
