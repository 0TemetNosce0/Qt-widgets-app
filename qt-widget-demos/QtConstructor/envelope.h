#ifndef envelope_H
#define envelope_H
#include <QVariant>
class envelope{
public:
    explicit envelope():object(0){ }

    int object;    

    QHash<QString,QVariant> header;    
    QList< QHash<QString,QVariant> > body;
};


#endif
