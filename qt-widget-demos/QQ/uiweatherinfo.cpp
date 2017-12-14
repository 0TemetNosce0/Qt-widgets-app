#include "workstation.h"
#include "uiweatherinfo.h"
#include "ui_uiweatherinfo.h"
#include "tinyxml.h"

#include <QtCore/QUrl>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QTextCodec>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

#define LOGINIPINTER "http://www.3322.org/dyndns/getip"
#define CITYINTER	 "http://www.youdao.com/smartresult-xml/search.s?type=ip&q=" 
#define WEATHERREAL  "http://www.weather.com.cn/data/sk/<%cityid%>.html"
#define WEATHERINTER "http://m.weather.com.cn/data/<%cityid%>.html"
#define WEATHERIMAGE "http://m.weather.com.cn/img/"

UiWeatherInfo::UiWeatherInfo(QWidget *parent)
	: UiImsBaseDialog(parent)
{
	ui = new Ui::UiWeatherInfo();
	ui->setupUi(this);
	mWeatgerContext = "";
	mLocalCityCode	= "";
	mNetworkReply = NULL;
	mNetworkAccessManager = NULL;
	mXmlDocumentCity = NULL;
	connect(&mTimer,SIGNAL(timeout()),this,SLOT(hide()));	
	loadCityInfomation();
}

UiWeatherInfo::~UiWeatherInfo()
{	
	if (mNetworkAccessManager)
		delete mNetworkAccessManager;
	mNetworkAccessManager = NULL;

	if (mXmlDocumentCity)
		delete mXmlDocumentCity;
	mXmlDocumentCity = NULL;
	delete ui;
}

void UiWeatherInfo::enterEvent(QEvent *event)
{
	if(mTimer.isActive())
		mTimer.stop();	
	return UiImsBaseDialog::enterEvent(event);
}

void UiWeatherInfo::leaveEvent(QEvent *event)
{
	hideWeatherWidget();
	return UiImsBaseDialog::leaveEvent(event);
}

void UiWeatherInfo::showEvent(QShowEvent *event)
{
	if(mTimer.isActive())
		mTimer.stop();
	if (!mLocalCityCode.isEmpty())
		doTimeOutWeather();
	return UiImsBaseDialog::showEvent(event);
}

void UiWeatherInfo::hideWeatherWidget()
{
	if (!mTimer.isActive())
		mTimer.start(1000);	
}

void UiWeatherInfo::loadCityInfomation()
{
	QFile file(":/qss/Resources/cityid.xml");
	if(file.open(QIODevice::ReadOnly))
	{
		mXmlDocumentCity = new TiXmlDocument;
		mXmlDocumentCity->Parse(file.readAll().data());
		file.close();
	}	
}

QString UiWeatherInfo::getCityCodeByName(QString province,QString city)
{
	QString sCityId = "";

	if (mXmlDocumentCity == NULL)
    {
        return sCityId;
    }

	if (province.isEmpty())
    {
        province = "直辖市";
    }

    TiXmlElement *pXmlCity = NULL;
	TiXmlElement *pXmlArea = NULL;
	TiXmlElement *pXmlProv = mXmlDocumentCity->RootElement()->FirstChildElement();

	while(pXmlProv)
	{
		if (province == pXmlProv->Attribute("name"))
		{
			pXmlArea = pXmlProv->FirstChildElement();
			break;
		}

		pXmlProv = pXmlProv->NextSiblingElement();
	}

	while(pXmlArea)	
	{
		if (city == pXmlArea->Attribute("name"));
		{
			pXmlCity = pXmlArea->FirstChildElement();
			break;
		}

		pXmlArea = pXmlArea->NextSiblingElement();
	}

	while(pXmlCity)	
	{
		if (city == pXmlCity->Attribute("name"));
		{
			sCityId = pXmlCity->Attribute("id");
			break;
		}

		pXmlCity = pXmlCity->NextSiblingElement();
	}

	return sCityId;
}

void UiWeatherInfo::createWeatherInfo()
{
	if (mNetworkAccessManager == NULL)
    {
        mNetworkAccessManager = new QNetworkAccessManager(this);
    }
    mNetworkReply = mNetworkAccessManager->get(QNetworkRequest(QUrl(LOGINIPINTER)));
	connect(mNetworkReply,SIGNAL(readyRead()),this,SLOT(doShowIpAddr()));
}

void UiWeatherInfo::doShowIpAddr()
{
	QString sIp = mNetworkReply->readAll();
	mNetworkReply->deleteLater();
	qDebug()<<"IP:"<<sIp;
	mNetworkReply = mNetworkAccessManager->get(QNetworkRequest(QUrl(CITYINTER + sIp)));
	connect(mNetworkReply,SIGNAL(readyRead()),this,SLOT(doShowCityInfo()));
}

//江苏省南京市 电信ADSL
void UiWeatherInfo::doShowCityInfo()
{	
	TiXmlDocument doc;
	QString sProvince,sCity = mNetworkReply->readAll();	
	mNetworkReply->deleteLater();
	doc.Parse(sCity.toStdString().c_str());
	TiXmlElement *elem = doc.RootElement()->FirstChildElement("product");

	if (elem)
    {
        elem = elem->FirstChildElement("location");
    }

    if (elem == NULL)
    {
        return;
    }

    sCity = elem->GetText();
	int nPos1 = sCity.indexOf("省");
	int nPos2 = sCity.indexOf("市");
    if (nPos2 == -1)
    {
        return;
    }

	if (nPos1 > 0)
	{
		sProvince = sCity.mid(0,nPos1);
		sCity = sCity.mid(nPos1+1,nPos2 - nPos1 -1);
	}
	else
    {
        sCity = sCity.mid(0,nPos2);
    }
    ui->labelCity->setText(sCity);
	mLocalCityCode = getCityCodeByName(sProvince,sCity);

	if (mLocalCityCode.isEmpty())
	{
        qDebug() << "can not find:" << sProvince << "省" << sCity << "市";
		return;
	}
    qDebug() << mLocalCityCode;
	doTimeOutWeather();
}

void UiWeatherInfo::doTimeOutWeather()
{
	QString sUrl = QString(WEATHERREAL).replace("<%cityid%>",mLocalCityCode);
	mNetworkReply = mNetworkAccessManager->get(QNetworkRequest(QUrl(sUrl)));
	connect(mNetworkReply,SIGNAL(readyRead()),this,SLOT(doShowCurrWeather()));
}

void UiWeatherInfo::doShowCurrWeather()
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	mWeatgerContext = codec->toUnicode(mNetworkReply->readAll());
	mNetworkReply->deleteLater();

	ui->labelTemperature->setText(explainWeatherAttribute("temp")+"℃");
	ui->labelWind->setText(explainWeatherAttribute("WD"));

	QString sUrl = QString(WEATHERINTER).replace("<%cityid%>",mLocalCityCode);
	mNetworkReply = mNetworkAccessManager->get(QNetworkRequest(QUrl(sUrl)));
	connect(mNetworkReply,SIGNAL(readyRead()),this,SLOT(doShowWeatherReport()));
}

void UiWeatherInfo::doShowWeatherReport()
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	mWeatgerContext = codec->toUnicode(mNetworkReply->readAll());
	mNetworkReply->deleteLater();

	ui->labelWeather->setText(explainWeatherAttribute("weather1"));
	ui->labelTodayTemp->setText(explainTemperatureReport("temp1"));
	ui->labelTomrrowTemp->setText(explainTemperatureReport("temp2"));
	ui->labelAfterTemp->setText(explainTemperatureReport("temp3"));
    mTodayImage = QString("c%1.gif").arg(explainWeatherAttribute("img1"));

	if (mTodayImage	== "c99.gif")
    {
        mTodayImage	= QString("c%1.gif").arg(explainWeatherAttribute("img2"));
    }
    mTomrrowImage = QString("c%1.gif").arg(explainWeatherAttribute("img3"));

	if (mTomrrowImage == "c99.gif")
    {
        mTomrrowImage = QString("c%1.gif").arg(explainWeatherAttribute("img4"));
    }
    mAfterImage	= QString("c%1.gif").arg(explainWeatherAttribute("img5"));

	if (mAfterImage == "c99.gif")
    {
        mAfterImage = QString("c%1.gif").arg(explainWeatherAttribute("img6"));
    }
    qDebug() << "today:" << mTodayImage << " ;tomorrow:" << mTomrrowImage << " ;after day of tomorrow:" << mAfterImage;
	mNetworkReply = mNetworkAccessManager->get(QNetworkRequest(QUrl(WEATHERIMAGE + mTodayImage)));
	connect(mNetworkReply,SIGNAL(readyRead()),this,SLOT(doShowImageToday()));
}

void UiWeatherInfo::doShowImageToday()
{
	QPixmap pix;
	pix.loadFromData(mNetworkReply->readAll());
	mNetworkReply->deleteLater();
	ui->labelTodayWeather->setPixmap(pix);
	WorkStation::workStation()->setCurrentWeather(pix);

	mNetworkReply = mNetworkAccessManager->get(QNetworkRequest(QUrl(WEATHERIMAGE + mTomrrowImage)));
	connect(mNetworkReply,SIGNAL(readyRead()),this,SLOT(doShowImageTomrrow()));
}

void UiWeatherInfo::doShowImageTomrrow()
{
	QPixmap pix;
	pix.loadFromData(mNetworkReply->readAll());
	mNetworkReply->deleteLater();
	ui->labelTomrrowWeather->setPixmap(pix);

	mNetworkReply = mNetworkAccessManager->get(QNetworkRequest(QUrl(WEATHERIMAGE + mAfterImage)));
	connect(mNetworkReply,SIGNAL(readyRead()),this,SLOT(doShowImageAfterDay()));
}

void UiWeatherInfo::doShowImageAfterDay()
{
	QPixmap pix;
	pix.loadFromData(mNetworkReply->readAll());
	mNetworkReply->deleteLater();
	ui->labelAfterWeather->setPixmap(pix);

// 	if (!isHidden())
// 		QTimer::singleShot(5000,this,SLOT(doTimeOutWeather()));
}

QString UiWeatherInfo::explainWeatherAttribute( QString title )
{
	QString sValue = "";
	int nPos = mWeatgerContext.indexOf(title);		
	if (nPos != -1)
	{
		int nPos1 = mWeatgerContext.indexOf(":\"",nPos);
		int nPos2 = mWeatgerContext.indexOf("\",",nPos);

		if (nPos1 != -1 && nPos2 != -1)
        {
            sValue = mWeatgerContext.mid(nPos1+2,nPos2-nPos1-2);
        }
    }
	return sValue;
}

//30℃~18℃ -->18℃/30℃
QString UiWeatherInfo::explainTemperatureReport( QString title )
{	
	QString sTemp = explainWeatherAttribute(title);
	QStringList list = sTemp.split("~");

	if(list.count() > 1)
	{
		sTemp = list.at(1);
		sTemp.push_back("/");
		sTemp.push_back(list.at(0));
	}

	return sTemp;
}
