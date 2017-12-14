#ifndef THUMBNAILPANEL_H
#define THUMBNAILPANEL_H

#include <QObject>
#include <QDockWidget>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QDebug>
#include "thumbnailcanvas.h"

class ThumbnailPanel : public QDockWidget
{
	Q_OBJECT

public:
	ThumbnailPanel(QWidget * parent = 0);
	~ThumbnailPanel();
	ThumbnailCanvas *getThumbnailCanvas();
	void setThumb(QPixmap &p);

public slots:
	void updateZoomLabel(float scaleFactor);
	void updateZoomSlider(float scaleFactor);
	

signals:
	void thumbZoomInSignal();
	void thumbZoomOutSignal();
	void thumbZoom(float scaleFactor);
	
private:
    float PROPOTION1;   // 50/0.875
    float PROPOTION2;   // 50/31;
    float PROPOTION3;   // 0.875/50
    float PROPOTION4;   // 31/50
	QLabel *scaleFactorLabel;
	QLabel *thumbnailLabel;
	ThumbnailCanvas *thumbnailCanvas;
	QPushButton *zoomInBtn;
	QPushButton *zoomOutBtn;
	QSlider *zoomSlider;

private slots:
	void thumbZoomIn();
	void thumbZoomOut();
	void zoomValueChanged(int value);
	
};

#endif // THUMBNAILPANEL_H
