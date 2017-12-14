#include "workstation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//#ifdef WIN32
//	QTextCodec *codec = QTextCodec::codecForName("system");
//#else
//	QTextCodec *codec = QTextCodec::codecForName("GBK");
//#endif
//	QTextCodec::setCodecForTr(codec);
//	QTextCodec::setCodecForLocale(codec);
//	QTextCodec::setCodecForCStrings(codec);

	QApplication a(argc, argv);
	WorkStation w;
	int ret = w.createLoginScreen();
	if(ret == QDialog::Accepted)
	{
		w.createShowScreen();
		ret = a.exec();
	}
	return ret;
}
