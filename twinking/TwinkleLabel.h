/*!
 *\file		controls\TwinkleLabel.h
 *\brief	闪烁label头文件. 
*/
#ifndef TWINKLELABEL_H_
#define TWINKLELABEL_H_ 

#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
class QTimer;

/*!
 *\class	CTwinkleLabel
 *\brief	实现图标闪烁的label. 
 *\author	Xl.xu
 *\date		2013/4/10
*/
class CTwinkleLabel : public QLabel
{
	Q_OBJECT
public:
	/*!
	 *\fn		CTwinkleLabel( QWidget* pParent = NULL )
	 *\brief	构造函数. 
	 *\author	Xl.xu
	 *\date		2013/4/10
	 *\param	pParent	父对象指针. 
	*/
	CTwinkleLabel( QWidget* pParent = NULL );
	/*!
	 *\fn		~CTwinkleLabel()
	 *\brief	析构函数. 
	 *\author	Xl.xu
	 *\date		2013/4/10
	*/
	~CTwinkleLabel();
	/*!
	 *\fn		inline bool getTwinkle( )
	 *\brief	获取闪烁状态. 
	 *\author	Xl.xu
	 *\date		2013/4/11
	 *\return	返回闪烁状态. 
	*/
	inline bool getTwinkle( ){  return m_bTwinkle; }
	/*!
	 *\fn		inline void setTwinkle( bool bTwinkle )
	 *\brief	设置是否闪烁. 
	 *\author	Xl.xu
	 *\date		2013/4/10
	 *\param	bTwinkle	true to twinkle. 
	*/
	inline void setTwinkle( bool bTwinkle )
	{ 
        static bool bIsConnected=false;
		if ( NULL == m_pAnimation  )
		{
			initVariable();
		}
		m_bTwinkle = bTwinkle;
        if ( (m_bTwinkle)&&(!bIsConnected) )
		{

			Q_ASSERT( NULL != m_pAnimation );
			bool bRet = connect( m_pAnimation , SIGNAL(finished()), this , SLOT( onTimeoutTwinkle() ));
            connect(m_pTimer,SIGNAL(timeout()),this,SLOT(ChangTextColor()));
            m_pAnimation->start();
            m_pTimer->start(500);
            bIsConnected=true;
		}
		else
		{
            if(bIsConnected)
            {
                disconnect( m_pAnimation , SIGNAL(finished()), this , SLOT( onTimeoutTwinkle() ));
                disconnect(m_pTimer,SIGNAL(timeout()),this,SLOT(ChangTextColor()));
                m_pAnimation->stop();
                m_pTimer->stop();
                bIsConnected=false;
            }
		}
	}
private:
	/*!
	 *\fn		void initVariable()
	 *\brief	初始化成员变量. 
	 *\author	Xl.xu
	 *\date		2013/4/10
	*/
	void initVariable();
private slots:
	void onTimeoutTwinkle( );
    void ChangTextColor();
private:
	//! 是否闪烁. 
	bool m_bTwinkle;
	//! . 
	QPropertyAnimation* m_pAnimation;
    QTimer*             m_pTimer;
    QPalette            m_paRed;
    QPalette            m_paYellow;
};

#endif //TWINKLELABEL_H_
