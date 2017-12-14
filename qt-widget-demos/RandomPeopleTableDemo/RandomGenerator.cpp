#include "RandomGenerator.h"
#include <QMap>

#define SECONDS_PER_YEAR 31557600

QString RandomGenerator::getRandomCountryCode() {
    const char *countries[] = {"at","bg","br","de","es","fr","hu","it","mx","no","po","ru","se","ua","uk","us"};
    int countries_sz = sizeof(countries)/sizeof(countries[0]);
    return QString(countries[qrand()%countries_sz]);
}

QString RandomGenerator::getRandomName() {
    const char *names[] = {
        "Aaron","Abel","Adele","Anna","Alice","Antony","Arnold","Avril","Anders","Adolf","Ardolion",
        "Bob","Boris","Ben","Bella","Beth","Brad","Bruce","Benedict",
        "Charlie","Cristina","Cornelia","Cynthia","Clare","Caren","Adrian","Caroline",
        "Dmitry","Dollie","Dan","Daron","Dizzy","Dixie","Daniel",
        "Eric", "Elena", "Evan", "Eleonora", "Ester", "Eugene",
        "Frank", "Forrest", "Fiona",
        "Gabriel", "Gennadiy", "Gilbert", "Gala", "Gotfried",
        "Howard","Herbert","Helen","Hugh",
        "Ivan","Isabelle","Inna","Irina","Issy","Isaac",
        "Jay","John","Jennie","James","Jennifer","Jose","Jasmine","Julia",
        "Katherine","Kristin","Kirsten",
        "Leonid","Lee","Lewis","Lydia","Liz","Lili","Lev",
        "Morris","Michael","Max","Martin","Mickey",
        "Nickolas","Naomi","Nina","Norah","Nancey",
        "Olga","Olesia","Oleg","Ophra",
        "Peter","Patrick","Patricia","Phil",
        "Queen","Quillon",
        "Ramil","Rachel","Rabi","Ronald","Renny","Rick","Richard",
        "Sarah","Sergei","Sabina","Sally","Sandy","Selena","Shawn","Sean","Sylvester","Steven","Synthia",
        "Ted","Terry","Todd","Tamil","Tina","Tracy","Tyler",
        "Ulf","Ustin","Uri","Uriah",
        "Valencia","Valentina","Valentine","Varvara","Venus","Vitaliy",
        "Will","Witt","Whitney","Woody","Waclaw",
        "Xena","Xavier","Xander","Xerxes",
        "Yvonne", "Yolanda", "Yana",
        "Zak","Zakhar","Zara"
    };
    int names_sz = sizeof(names)/sizeof(names[0]);
    return QString(names[qrand()%names_sz]);
}

QString RandomGenerator::getRandomSurname() {
    const char *surnames[] = {
        "Adams","Anderson","Asher","Ayley","Atkinson","Atkins","Arby",
        "Brown","Bradley","Bloom","Bone","Boon","Bates","Bowers","Bass","Brewer",
        "Crown","Cooper","Clark","Carter","Chase","Crow","Cutts","Cann",
        "Duncan","Donn","Diamond","Dunn","Duval","Dupont","Dickinson",
        "Erics", "Ellis", "Evans", "Eden", "Earl", "Eddison","Everett","Elder",
        "Fox", "Fisher", "Floyd", "Foston", "Flynn",
        "Gill", "Grant", "Garrys", "Gosling", "Griffin",
        "Harris","Higgs","Hitler","Hayes","Howe","Howie","Harold",
        "Irvine","Irving","Ingram","Isaacs","Ivans","Ivanopulo",
        "Jones","Johnson","James","Joseph","Jeffers",
        "Kirkson","King","Keith","Kelly","Kim",
        "Lewis","Lee","Lloyd","Lane","Lynch","Love","Lord",
        "Martin","Morgan","Moore","Maorris","Mitchell","Miller",
        "Nicholson","Newman","Newton","Noorman","Neal","Nixon",
        "Owen","Oliver","O'Neill","O'Leary","O'Connell",
        "Phillips","Peters","Parker","Perry","Pearce","Patton",
        "Quinn","Quirk","Quinton","Quinnell",
        "Roberts","Robinson","Richards","Rogers","Russell","Ripley","Robson",
        "Smith","Scott","Simpson","Sharp","Stone","Stewart","Shaw","Sheppard",
        "Taylor","Thompson","Thorne","Troutman","Timmerman",
        "Utton","Upton","Uttley","Upson",
        "Vincent","Vaughan","Vickers","Ventura","Vinton",
        "Williams","Wilson","Walker","Wood","White","Watson","Ward","Wright","Willis","West",
        "Xaviers","Xanders",
        "Young", "York", "Yards",
        "Zarinson","Zaoui"
    };
    int surnames_sz = sizeof(surnames)/sizeof(surnames[0]);
    return QString(surnames[qrand()%surnames_sz]);
}

QDateTime RandomGenerator::getRandomBirthDate() {
    //1970 + (0-40). random date in 1970-2010 range.
    return QDateTime::fromTime_t( qrand()%(40*SECONDS_PER_YEAR) ); 
}

QString RandomGenerator::getRandomPassportNumber(const QString& countryCode ) {
    QString psn;
    psn.sprintf("%02d%s%04d%04d", qrand()%100, countryCode.toUpper().toUtf8().constData(), qrand()%10000, qrand()%10000 );
    return psn;
}

QString RandomGenerator::getRandomPhoneNumber(const QString& countryCode ) {
    QMap<QString,QString> countryPhonePrefixes;
    countryPhonePrefixes["at"] = "+43";
    countryPhonePrefixes["bg"] = "+35";
    countryPhonePrefixes["br"] = "+55";
    countryPhonePrefixes["de"] = "+49";
    countryPhonePrefixes["es"] = "+34";
    countryPhonePrefixes["fr"] = "+33";
    countryPhonePrefixes["hu"] = "+33";
    countryPhonePrefixes["it"] = "+39";
    countryPhonePrefixes["mx"] = "+52";
    countryPhonePrefixes["no"] = "+47";
    countryPhonePrefixes["po"] = "+48";
    countryPhonePrefixes["ru"] = "+70";
    countryPhonePrefixes["se"] = "+46";
    countryPhonePrefixes["ua"] = "+38";
    countryPhonePrefixes["uk"] = "+44";
    countryPhonePrefixes["us"] = "+10";

    QString phn;
    phn.sprintf(
        "%s(%03d)%03d-%02d-%02d", 
        countryPhonePrefixes[countryCode].toUtf8().constData(), 
        qrand()%1000, qrand()%1000, qrand()%100, qrand()%100 
    );
    return phn;
}
