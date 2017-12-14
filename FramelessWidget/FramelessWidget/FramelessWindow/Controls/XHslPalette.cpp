#include <QVBoxLayout>

#include <QDebug>
#include "XHslPalette.h"
#include "XHlPalette.h"
#include "XSaturationPalette.h"

XHslPalette::~XHslPalette(){}


XHslPalette::XHslPalette(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("HSL调色板示例(此窗口可直接做控件)"));
    setWindowFlags(Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose, true);

    initMembers();
    initContents();
}

void XHslPalette::initMembers()
{
    mp_wgtHlPalette = nullptr;
    mp_wgtSaturationIndicator = nullptr;
}

void XHslPalette::initContents()
{
    mp_wgtHlPalette = new XHlPalette;
    mp_wgtSaturationIndicator = new XSaturationPalette;
    connect(mp_wgtHlPalette, SIGNAL(colorChanged(QColor)), mp_wgtSaturationIndicator, SLOT(setBaseColor(QColor)));
    connect(mp_wgtSaturationIndicator, SIGNAL(saturationChanged(double)), mp_wgtHlPalette, SLOT(setSaturation(double)));
    connect(mp_wgtHlPalette, SIGNAL(colorChanged(QColor)), this, SIGNAL(colorChanged(QColor)));

    QVBoxLayout *playout = new QVBoxLayout;
    playout->setMargin(0);
    playout->addWidget(mp_wgtHlPalette);
    playout->addWidget(mp_wgtSaturationIndicator);

    setLayout(playout);
}

void XHslPalette::setColor(QColor color)
{
    //qDebug() << "XHslPalette::setColor";
    if(Q_LIKELY(mp_wgtHlPalette))   mp_wgtHlPalette->setColor(color);
    if(Q_LIKELY(mp_wgtSaturationIndicator)) mp_wgtSaturationIndicator->setColor(color);
}
