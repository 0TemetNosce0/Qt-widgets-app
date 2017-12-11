#include "imsimagelineedit.h"

#include <QLabel>
#include <QEvent>
#include <QMouseEvent>

ImsImageLineEdit::ImsImageLineEdit(QWidget *parent /* = 0 */)
	: QLineEdit(parent)
{
	mImageLabel = NULL;
	mImagePath = "";
	setAttribute(Qt::WA_TranslucentBackground);	
}

ImsImageLineEdit::ImsImageLineEdit( const QString & contents, QWidget *parent /*= 0*/ )
	: QLineEdit(contents,parent)
{
	mImageLabel = NULL;
	mImagePath = "";
	setAttribute(Qt::WA_TranslucentBackground);
}

ImsImageLineEdit::ImsImageLineEdit( const QString & contents, const QString & pic,QWidget *parent /*= 0*/ )
	: QLineEdit(contents,parent)
{
	mImageLabel = NULL;
	mImagePath = pic;	
	setAttribute(Qt::WA_TranslucentBackground);
	init();
}

ImsImageLineEdit::~ImsImageLineEdit()
{
	if (mImageLabel)
    {
        delete mImageLabel;
    }
    mImageLabel = NULL;
}

void ImsImageLineEdit::setLabelPic( const QString strPic )
{
	mImagePath = strPic;
	init();
}

void ImsImageLineEdit::resizeEvent( QResizeEvent *event )
{
	QLineEdit::resizeEvent(event);  
	changeLabelPosition();  
}

void ImsImageLineEdit::init()
{
	if (mImageLabel == NULL)
	{
		mImageLabel  = new QLabel(this);
		mImageLabel->setScaledContents(true);
		mImageLabel->installEventFilter(this);
		mImageLabel->setCursor(QCursor(Qt::ArrowCursor));
	}	
	changeLabelPosition();
}

void ImsImageLineEdit::changeLabelPosition()
{
	if (mImageLabel == NULL)
    {
        return;
    }
    if (mImagePath.isEmpty())
	{
		mImageLabel->hide();
	}
	else
	{
		int nLabelHeight = height()-4;
		int nLabelWidth  = height()-4;//Ä¬ÈÏÎª22
		mImageLabel->setMaximumSize(nLabelWidth,nLabelHeight);
		mImageLabel->setGeometry(width() - nLabelWidth - 2,(height() - nLabelHeight)/2,
			nLabelWidth,nLabelHeight);
		setTextMargins(QMargins(6,0,nLabelHeight+6,0));
		mImageLabel->setPixmap(QPixmap(mImagePath));
		mImageLabel->show(); 
	}
}

bool ImsImageLineEdit::eventFilter(QObject *obj, QEvent *event)
{
    if (mImageLabel && obj == mImageLabel )
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
			QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

			if (mouseEvent->buttons() & Qt::LeftButton)
			{
				emit imageLabelClicked();
				return true;
			}			
		}
	} 

	return QLineEdit::eventFilter(obj, event);
}
