#include "labelbtn.h"

#include <QLabel>
#include <QSound>
#include <QPixmap>
#include <QMouseEvent>

LabelBtn::LabelBtn(const QString& pngFile, const QString& soundFile, QWidget *parent)	
	: QLabel(parent)
{
	m_SoundFile = soundFile;
	setCursor(Qt::PointingHandCursor);
	this->setPixmap(QPixmap(pngFile));
	this->resize(QPixmap(pngFile).size());
	this->setAttribute(Qt::WA_TranslucentBackground,true);
    connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
}

LabelBtn::~LabelBtn()
{
	unsetCursor();
}

void LabelBtn::mousePressEvent(QMouseEvent* event)
{
	if(event->button() == Qt::LeftButton)
	{
		QSound::play(m_SoundFile);
		emit clicked();
	}
    QLabel::mousePressEvent(event);
}

void LabelBtn::onClicked()
{

}
