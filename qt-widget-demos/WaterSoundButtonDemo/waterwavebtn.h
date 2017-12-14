#ifndef WATERWAVEBTN_H
#define WATERWAVEBTN_H

#include <QWidget>

class QMovie;

class WaterWaveBtn : public QWidget
{
	Q_OBJECT

public:
    WaterWaveBtn(const QString& pngFile, QWidget *parent = 0);
	~WaterWaveBtn();

private slots:
	void showWaterWave();

private:
	QMovie*		m_Movie;	
	
};

#endif // WATERWAVEBTN_H
