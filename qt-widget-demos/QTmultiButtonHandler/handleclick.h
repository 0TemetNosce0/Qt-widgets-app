#ifndef HANDLECLICK_H
#define HANDLECLICK_H

#include <QObject>

class handleClick : public QObject
{
    Q_OBJECT

public:
    explicit handleClick(QObject *parent = 0);
    void whichPress(const QString &);

signals:

public slots:

};

#endif // HANDLECLICK_H
