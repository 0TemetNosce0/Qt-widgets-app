#include <QLayout>
#include <QtMath>

#include "XClientPanel.h"

XClientPanel::XClientPanel(QWidget *parent) : XFrame(parent)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setObjectName("FrameClient");
    setMouseTracking(true);

    initStyle();
}

XClientPanel::~XClientPanel()
{

}

void XClientPanel::setRadius(int ntTopLeft, int ntTopRight, int ntBottomLeft, int ntBottonRight)
{
    XStyle::setRadius(ntTopLeft, ntTopRight, ntBottomLeft, ntBottonRight);
    refreshRadius();
}

void XClientPanel::setBorderWidth(int ntLeft, int ntTop, int ntRight, int ntBottom)
{
    XStyle::setBorderWidth(ntLeft, ntTop, ntRight, ntBottom);
    refreshRadius();
}

void XClientPanel::setBorderWidth(int ntWidth)
{
    XStyle::setBorderWidth(ntWidth);
    refreshRadius();
}

void XClientPanel::refreshRadius()
{
    if(layout() == nullptr)    return;

    for(int it=0; it<layout()->count(); it++)
    {
        QLayoutItem *pItem = layout()->itemAt(it);
        QWidget *pWgt = pItem->widget();
        if(Q_LIKELY(pWgt))
        {
            //qDebug() << QString("%1/%2is Widget : ").arg(it).arg(mp_layoutBtns->count()) << pWgt->objectName();
            if(!pWgt->isHidden())
            {
                //qDebug() << "is Widget : " << pWgt->objectName();
                //qDebug() << "Old Stylesheet = " << pWgt->styleSheet();
                QString strStylesheet = pWgt->styleSheet();
                strStylesheet += QString("QPushButton{border-top-right-radius: %2;}")
                                 .arg(getTopRightRadius()-qCeil((getTopBorderWidth()+getRightBorderWidth())/2));
                pWgt->setStyleSheet(strStylesheet);
                //qDebug() << "New Stylesheet = " << pWgt->styleSheet();
                break;
            }
        }
    }
}

