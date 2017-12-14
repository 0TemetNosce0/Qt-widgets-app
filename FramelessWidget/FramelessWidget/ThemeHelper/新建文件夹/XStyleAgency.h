#ifndef XSTYLEAGENCY_H
#define XSTYLEAGENCY_H

#include <QObject>
#include "XStyle.h"
class XStyleData;

class XStyleAgency : public QObject, public XStyle
{
    Q_OBJECT

public:
    explicit XStyleAgency(QObject *parent = nullptr);
    ~XStyleAgency();

public:
    void onStyleChanged();

signals:
    void styleChanged();
    void styleChanged(XStyleData* pStyleData);
    void styleChanged(QString strStylesheet);
};

#endif // XSTYLEAGENCY_H
