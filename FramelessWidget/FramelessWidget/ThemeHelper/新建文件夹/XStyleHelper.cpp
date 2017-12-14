#include "XStyleHelper.h"
#include <QDebug>

XStyleHelper::~XStyleHelper()   {   }

XStyleHelper::XStyleHelper(QObject *parent) : QObject(parent)
{
    initStyle();

    connect(&mo_borderStyleAgency, SIGNAL(styleChanged(XStyleData*)), this, SIGNAL(borderStyleChanged(XStyleData*)));
    connect(&mo_titleStyleAgency, SIGNAL(styleChanged(XStyleData*)), this, SIGNAL(titleStyleChanged(XStyleData*)));
    connect(&mo_clientStyleAgency, SIGNAL(styleChanged(XStyleData*)), this, SIGNAL(clientStyleChanged(XStyleData*)));

    initStyle();
}

XStyleHelper &XStyleHelper::getInstance()
{
    static XStyleHelper inst;
    return inst;
}

XStyleAgency &XStyleHelper::borderStyleAgency()
{
    return mo_borderStyleAgency;
}

XStyleAgency &XStyleHelper::titleStyleAgency()
{
    return mo_titleStyleAgency;
}

XStyleAgency &XStyleHelper::clientStyleAgency()
{
    return mo_clientStyleAgency;
}

void XStyleHelper::initStyle()
{
    //qDebug() << "XStyleHelper::initStyle: BorderStyleAgency Dtat = " << mo_titleStyleAgency.getStyleData();
    mo_borderStyleAgency.setBorderWidth(1,1,1,1);
    mo_borderStyleAgency.setRadius(0,0,0,0);
    mo_borderStyleAgency.setBorderActivatedColor(Qt::green);
    mo_borderStyleAgency.setBorderDeactivatedColor(Qt::darkGray);
    mo_borderStyleAgency.setBackgroundActivatedColor(Qt::white);
    mo_borderStyleAgency.setBackgroundDeactivatedColor(Qt::white);
    mo_borderStyleAgency.updateStyle();

    mo_titleStyleAgency.setBorderWidth(0,0,0,0);
    mo_titleStyleAgency.setRadius(0,0,0,0);
    mo_titleStyleAgency.setBorderActivatedColor(Qt::transparent);
    mo_titleStyleAgency.setBorderDeactivatedColor(Qt::transparent);
    mo_titleStyleAgency.setBackgroundActivatedColor(Qt::green);
    mo_titleStyleAgency.setBackgroundDeactivatedColor(Qt::transparent);
    mo_titleStyleAgency.updateStyle();

    mo_clientStyleAgency.setBorderWidth(0,0,0,0);
    mo_clientStyleAgency.setRadius(0,0,0,0);
    mo_clientStyleAgency.setBorderActivatedColor(Qt::transparent);
    mo_clientStyleAgency.setBorderDeactivatedColor(Qt::transparent);
    mo_clientStyleAgency.setBackgroundActivatedColor(Qt::transparent);
    mo_clientStyleAgency.setBackgroundDeactivatedColor(Qt::transparent);
    mo_clientStyleAgency.updateStyle();
}



