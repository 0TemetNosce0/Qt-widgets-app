#include "waterwavebtn.h"

#include <QMovie>
#include <QLabel>

#include "labelbtn.h"

WaterWaveBtn::WaterWaveBtn(const QString& pngFile, QWidget *parent)
    : QWidget(parent)
{
    m_Movie = new QMovie(":/Resource/waterWave.gif");
	m_Movie->setCacheMode(QMovie::CacheAll);
	QLabel*	waterWaveLabel = new QLabel(this);
	waterWaveLabel->setMovie(m_Movie);
	waterWaveLabel->setAttribute(Qt::WA_TranslucentBackground,true);
	m_Movie->start();
	m_Movie->setPaused(true);
    LabelBtn* labelBtn = new LabelBtn(pngFile,":/Resource/sound.wav",this);
    int size = QPixmap(":/Resource/waterWave.gif").width();
	int gap = (size - labelBtn->width())/2;
	labelBtn->move(gap,gap);
	this->setFixedSize(size,size);

	this->setAttribute(Qt::WA_TranslucentBackground);
//	this->setWindowFlags(Qt::FramelessWindowHint|Qt::Window|Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);

	connect(labelBtn, SIGNAL(clicked()), this, SLOT(showWaterWave()));
}

WaterWaveBtn::~WaterWaveBtn()
{

}

void WaterWaveBtn::showWaterWave()
{
	m_Movie->start();
}
