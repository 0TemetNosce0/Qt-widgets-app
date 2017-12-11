#ifndef IMSRESOURSCE_H
#define IMSRESOURSCE_H

#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include "imsdefine.h"

class CImsResource
{
public:
	CImsResource();
	~CImsResource();
public:	
	static QIcon stateIconByCode(Ims::ImsState state);
	static QIcon trayIconByCode(Ims::ImsState state);
	static QIcon iconMainMenuEnter();
	static QIcon iconMainMenuLeave();

	static QString mainWindowIcon();
	static QString userHeadImage();
	static QString loginBackground();
	static QString mainAppBackground();
	static QString icomSearchEdit();
	static QString icomPassWordEdit();
	static QString iconInterManager();
	static QString iconSignatureEdit();
	static QString menuGroupIcon();
	static QString menuContactHeadIcon();
	static QString interfaceCover();
	static QString interfaceClassic();
};
#endif //IMSRESOURSCE_H