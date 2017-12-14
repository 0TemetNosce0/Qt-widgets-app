#ifndef IMSDEFINE_H
#define IMSDEFINE_H

#include <stdio.h>
#include <stdlib.h>

namespace Ims{
	//用户状态
	enum ImsState{
		StateUnLogin= 0,//未登录
		StateOnline = 1,//在线      
		StateQMy	= 2,//Q我吧
		StateLeave	= 3,//离开
		StateBusy	= 4,//忙碌
		StateNoDisturb	= 5,//请勿打扰
		StateStealth	= 6,//隐身
		StateOffline	= 7,//离线
	};

	enum ImsTabBar{
		BarContact	 = 1,//联系人
		BarGroup	 = 2,//群/讨论组
		BarZone		 = 3,//空间
		BarBlog		 = 4,//微博
		BarLast		 = 5,//历史记录
	};
};//end namespace Ims

#endif IMSDEFINE_H