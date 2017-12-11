#include "TwinkleLabel.h"
CTwinkleLabel::CTwinkleLabel( QWidget* pParent /* = NULL */ ):QLabel(pParent)
{
	m_pAnimation = NULL;
	m_bTwinkle = false;

    setFont(QFont("simsun",50));


    m_paRed.setColor(QPalette::WindowText,Qt::red);
    m_paYellow.setColor(QPalette::WindowText,Qt::yellow);
    setPalette(m_paRed);

    m_pTimer=new QTimer;


//	initVariable();
}

CTwinkleLabel::~CTwinkleLabel( )
{
	if ( NULL != m_pAnimation )
	{
		m_pAnimation->deleteLater();
		m_pAnimation = NULL;
	}

}

void CTwinkleLabel::ChangTextColor()
{
    static int a=0;
    if(a++%2==0)
        setPalette(m_paRed);
    else
        setPalette(m_paYellow);
}

void CTwinkleLabel::initVariable( )
{
	m_pAnimation = new QPropertyAnimation( this , "geometry" );
	QRect geo = geometry();
	m_pAnimation->setDuration(1000);
	m_pAnimation->setKeyValueAt(0.0,QRect(geo.x(),geo.y(),width(),height()));
	m_pAnimation->setKeyValueAt(0.25,QRect(geo.x()-2,geo.y()+2,width(),height()));
	m_pAnimation->setKeyValueAt(0.5,QRect(geo.x(),geo.y(),width(),height()));
	m_pAnimation->setKeyValueAt(0.75,QRect(geo.x()+2,geo.y()+2,width(),height()));
	m_pAnimation->setKeyValueAt(1.0,QRect(geo.x(),geo.y(),width(),height()));
}

void CTwinkleLabel::onTimeoutTwinkle( )
{
	if ( getTwinkle() )
	{
		if ( NULL != m_pAnimation )
		{
			m_pAnimation->start();
		}
	}
}
