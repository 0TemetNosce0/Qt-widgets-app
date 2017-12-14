#pragma once

#include <QDateTime>
#include <QString>

class RandomGenerator {
public:
    QString getRandomCountryCode();
    QString getRandomName();
    QString getRandomSurname();
    QDateTime getRandomBirthDate();
    QString getRandomPassportNumber(const QString& countryCode );
    QString getRandomPhoneNumber(const QString& countryCode );
};