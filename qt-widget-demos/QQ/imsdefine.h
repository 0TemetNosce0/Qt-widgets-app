#ifndef IMSDEFINE_H
#define IMSDEFINE_H

#include <stdio.h>
#include <stdlib.h>

namespace Ims{
	//�û�״̬
	enum ImsState{
		StateUnLogin= 0,//δ��¼
		StateOnline = 1,//����      
		StateQMy	= 2,//Q�Ұ�
		StateLeave	= 3,//�뿪
		StateBusy	= 4,//æµ
		StateNoDisturb	= 5,//�������
		StateStealth	= 6,//����
		StateOffline	= 7,//����
	};

	enum ImsTabBar{
		BarContact	 = 1,//��ϵ��
		BarGroup	 = 2,//Ⱥ/������
		BarZone		 = 3,//�ռ�
		BarBlog		 = 4,//΢��
		BarLast		 = 5,//��ʷ��¼
	};
};//end namespace Ims

#endif IMSDEFINE_H