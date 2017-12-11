#include "XStyleAgency.h"
#include <QDebug>

XStyleAgency::XStyleAgency(QObject *parent) : QObject(parent)
{
    //qDebug() << "XStyleAgency::XStyleAgency";
    setBackgroundActivatedColor(QColor(255,0,0,255));
}

XStyleAgency::~XStyleAgency()
{

}

void XStyleAgency::onStyleChanged()
{
    //qDebug()<< "XStyleAgency::onStyleChanged";
    emit styleChanged();
    emit styleChanged(getStyleData());
    emit styleChanged(getStylesheet());
}
