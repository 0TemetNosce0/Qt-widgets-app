#include "imsresoursce.h"

#include <QtCore/QTime>

QIcon CImsResource::stateIconByCode( Ims::ImsState state )
{
	switch(state)
	{
	case Ims::StateOnline://在线
		return QIcon(":/WorkStation/Resources/theme/state/imonline.png");
	case Ims::StateQMy://Q我吧
		return QIcon(":/WorkStation/Resources/theme/state/Qme.png");
	case Ims::StateLeave://离开
		return QIcon(":/WorkStation/Resources/theme/state/away.png");
	case Ims::StateBusy://忙碌
		return QIcon(":/WorkStation/Resources/theme/state/busy.png");
	case Ims::StateNoDisturb://请勿打扰
		return QIcon(":/WorkStation/Resources/theme/state/mute.png");
	case Ims::StateStealth://隐身
		return QIcon(":/WorkStation/Resources/theme/state/invisible.png");
	case Ims::StateOffline://离线
		return QIcon(":/WorkStation/Resources/theme/state/imoffline.png");		
	}
	return QIcon();
}

QIcon CImsResource::trayIconByCode( Ims::ImsState state )
{
	switch(state)
	{
	case Ims::StateOnline://在线
		return QIcon(":/WorkStation/Resources/theme/tray/imonline.ico");
	case Ims::StateQMy://Q我吧
		return QIcon(":/WorkStation/Resources/theme/tray/Qme.ico");
		break;
	case Ims::StateLeave://离开
		return QIcon(":/WorkStation/Resources/theme/tray/away.ico");
		break;
	case Ims::StateBusy://忙碌
		return QIcon(":/WorkStation/Resources/theme/tray/busy.ico");
		break;
	case Ims::StateNoDisturb://请勿打扰
		return QIcon(":/WorkStation/Resources/theme/tray/mute.ico");
		break;
	case Ims::StateStealth://隐身
		return QIcon(":/WorkStation/Resources/theme/tray/invisible.ico");
		break;
	case Ims::StateOffline://离线
		return QIcon(":/WorkStation/Resources/theme/tray/offline.ico");
		break;
	}
	return QIcon();
}

QString CImsResource::mainWindowIcon()
{
	return ":/WorkStation/Resources/theme/qq.ico";
}

QString CImsResource::userHeadImage()
{
	return ":/WorkStation/Resources/theme/head.png";
}

QString CImsResource::loginBackground()
{
	int nCurrentHour = QTime::currentTime().hour();
	if (nCurrentHour >= 7 && nCurrentHour < 9)
		return ":/WorkStation/Resources/theme/login/morning.jpg";
	else if (nCurrentHour >= 9 && nCurrentHour < 18)
		return ":/WorkStation/Resources/theme/login/noon.jpg";
	else if (nCurrentHour >= 18 && nCurrentHour < 19)
		return ":/WorkStation/Resources/theme/login/afternoon.jpg";
	return ":/WorkStation/Resources/theme/login/night.jpg";
}

QString CImsResource::mainAppBackground()
{
	return ":/WorkStation/Resources/theme/interface/default.jpg";
}

QString CImsResource::icomSearchEdit()
{
	return ":/WorkStation/Resources/theme/maintabbar/icon_search_normal.png";
}

QString CImsResource::icomPassWordEdit()
{
	return ":/WorkStation/Resources/theme/login/keyboard.png";
}

QString CImsResource::iconInterManager()
{
	return ":/WorkStation/Resources/theme/interface/AreaPresentMgr_RBMenu.png";
}

QString CImsResource::iconSignatureEdit()
{
	return ":/WorkStation/Resources/theme/interface/autograph.png";
}

QIcon CImsResource::iconMainMenuEnter()
{
	return QIcon(":/WorkStation/Resources/theme/maintool/menu_btn_highlight.png");
}

QIcon CImsResource::iconMainMenuLeave()
{
	return QIcon(":/WorkStation/Resources/theme/maintool/menu_btn_normal.png");
}

QString CImsResource::menuGroupIcon()
{
	return ":/WorkStation/Resources/theme/menu/groupmainpage.png";
}

QString CImsResource::menuContactHeadIcon()
{
	return ":/WorkStation/Resources/theme/menu/modehead.png";
}

QString CImsResource::interfaceCover()
{
	return ":/WorkStation/Resources/theme/interface/fengmian_1.png";
}

QString CImsResource::interfaceClassic()
{
	return ":/WorkStation/Resources/theme/interface/jingdian_2.png";
}
