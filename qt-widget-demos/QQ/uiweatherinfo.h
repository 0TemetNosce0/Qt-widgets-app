#ifndef UIWEATHERINFO_H
#define UIWEATHERINFO_H

#include "uiimsbasedialog.h"

#include <QtCore/QTimer>
namespace Ui {class UiWeatherInfo;};

class TiXmlDocument;
class QNetworkReply;
class QNetworkRequest;
class QNetworkAccessManager;
class UiWeatherInfo : public UiImsBaseDialog
{
	Q_OBJECT

public:
	UiWeatherInfo(QWidget *parent = 0);
	~UiWeatherInfo();

	void createWeatherInfo();
	void hideWeatherWidget();
protected:
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);
	virtual void showEvent(QShowEvent *event);
protected:
	void loadCityInfomation();
	QString getCityCodeByName(QString province,QString city);
	QString explainWeatherAttribute(QString title);
	QString explainTemperatureReport(QString title);	
public slots:
	void doShowIpAddr();
	void doShowCityInfo();
	void doTimeOutWeather();
	void doShowCurrWeather();
	void doShowWeatherReport();
	void doShowImageToday();
	void doShowImageTomrrow();
	void doShowImageAfterDay();
private:
	Ui::UiWeatherInfo *ui;
	QTimer				 mTimer;
	QTimer				 mTimerWeather;
	QString				 mTodayImage;
	QString				 mTomrrowImage;
	QString				 mAfterImage;
	QString				 mLocalCityCode;
	QString				 mWeatgerContext;
	TiXmlDocument		 *mXmlDocumentCity;
	QNetworkReply		 *mNetworkReply;
	QNetworkAccessManager*mNetworkAccessManager;
};

#endif // UIWEATHERINFO_H
