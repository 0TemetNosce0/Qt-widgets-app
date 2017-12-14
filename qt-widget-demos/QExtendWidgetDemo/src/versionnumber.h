#ifndef VERSIONNUMBER_H
#define VERSIONNUMBER_H

#include <QStringList>
#include <QMetaType>

class VersionNumber
{

public:
    VersionNumber();
    VersionNumber(const VersionNumber & value);
    VersionNumber(const QString & value);
    VersionNumber(const qint64 value);
    virtual ~VersionNumber();
    QString toString() const;
    VersionNumber operator=(const VersionNumber & value);
    VersionNumber operator=(const QString & value);
    VersionNumber operator=(qint64 value);
    bool operator<(const VersionNumber & value) const;
    bool operator<=(const VersionNumber & value) const;
    bool operator>(const VersionNumber & value) const;
    bool operator>=(const VersionNumber & value) const;
    bool operator==(const VersionNumber & value) const;
    bool operator!=(const VersionNumber & value) const;

private:
    typedef QStringList simpleNumber;
    typedef QList< simpleNumber > numberWithPoints;
    typedef QList< numberWithPoints > numberWithPointsAndDashes;

    enum characterType
    {
        letter,
        digit,
        other
    };

    enum type_whichIsBigger
    {
        first_one,
        second_one,
        both_are_equal
    };

    QString theString;

    numberWithPointsAndDashes epoch;

    numberWithPointsAndDashes version_and_release;

    void helper_copyFromHere(const VersionNumber & value);

    void helper_setValue(const QString & value);

    static VersionNumber::characterType helper_characterType(const QChar & value);

    static VersionNumber::simpleNumber helper_createSimpleNumber(const QString & value);

    static VersionNumber::numberWithPoints helper_createNumberWithPoints(const QString & value);

    static VersionNumber::numberWithPointsAndDashes helper_createNumberWithPointsAndDashes(
            const QString & value);

    static VersionNumber::type_whichIsBigger whichIsBigger(
            const VersionNumber & firstValue,
            const VersionNumber & secondValue);

    static VersionNumber::type_whichIsBigger whichIsBigger(
            const numberWithPointsAndDashes & firstValue,
            const numberWithPointsAndDashes & secondValue);

    static VersionNumber::type_whichIsBigger whichIsBigger(
            const numberWithPoints & firstValue,
            const numberWithPoints & secondValue);

    static VersionNumber::type_whichIsBigger whichIsBigger(
            const simpleNumber & firstValue,
            const simpleNumber & secondValue);

    static VersionNumber::type_whichIsBigger whichIsBigger(
            const QString & firstValue,
            const QString & secondValue);

    static VersionNumber::type_whichIsBigger helper_whichNumberIsBigger(
            const QString & firstValue,
            const QString & secondValue);

    static VersionNumber::type_whichIsBigger helper_whichStringIsBigger(
            const QString & firstValue,
            const QString & secondValue);

};

Q_DECLARE_METATYPE(VersionNumber)

#endif
