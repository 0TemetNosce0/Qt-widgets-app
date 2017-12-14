#include <QPainter>
#include <QRadialGradient>

#include <QDebug>
#include "StatusIndicator.h"

CStatusIndicator::CStatusIndicator(QWidget *parent) : QAbstractButton(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setCheckable(false);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(QSize(16,16));

    initMembers();
}

CStatusIndicator::~CStatusIndicator()
{
}

void CStatusIndicator::setIndicateMode(CStatusIndicator::IndicateMode mode)
{
    mo_mode = mode;
}

void CStatusIndicator::addStatus(QString strStatus, QColor color)
{
    mo_strlstStatus.append(strStatus);
    mo_lstColor.append(color);
}

void CStatusIndicator::setInnerFactor(double factor)
{
    if(mo_dblFactor != factor)
    {
        mo_dblFactor = factor;
        update();
    }
}

void CStatusIndicator::setCheckable(bool)
{

}

void CStatusIndicator::setChecked(bool checked)
{
    mo_blChecked = checked;
}

bool CStatusIndicator::isChecked()
{
    return mo_blChecked;
}

void CStatusIndicator::setCurrentStatus(QString strStatus)
{
    if(!mo_strlstStatus.contains(strStatus))    return;
    if(mo_strCurrentStatus == strStatus)        return;

    mo_strCurrentStatus = strStatus;
    emit statusChanged(mo_strCurrentStatus);
    update();
}

QSize CStatusIndicator::sizeHint()
{
    return QSize(24,24);
}

QSize CStatusIndicator::minimumSizeHint()
{
    return QSize(16, 16);
}


void CStatusIndicator::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);

    double radius = qMin(rect().width(), rect().height())/2.0;
    QColor colorStart, colorFinal;

    if(mo_mode == CheckedMode)
    {
        if(isChecked()){
            colorStart = QColor(255,0,0,255);
            colorFinal = QColor(255,0,0,0);
        }
        else{
            colorStart = QColor(0,0,0,255);
            colorFinal = QColor(0,0,0,0);
        }
    }
    else{
        colorStart = mo_lstColor.at(mo_strlstStatus.indexOf(mo_strCurrentStatus));
        colorStart.setAlpha(255);
        colorFinal = colorStart;
        colorFinal.setAlpha(0);
    }



    QRadialGradient radialGradient(rect().center(),2*radius);
    radialGradient.setColorAt(0.0, colorStart);
    radialGradient.setColorAt(0.5*mo_dblFactor, colorStart);
    radialGradient.setColorAt(0.5, colorFinal);
    painter->setBrush(radialGradient);
    painter->drawEllipse(rect().center(), int(radius), int(radius));

    delete painter;
}

void CStatusIndicator::initMembers()
{
    mo_mode = CheckedMode;
    mo_strCurrentStatus.clear();
    mo_strlstStatus.clear();
    mo_lstColor.clear();
    mo_dblFactor = 0.5;
    //qDebug() << "InitMembers";
}
