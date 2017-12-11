/*!
 *\file		controls\TwinkleLabel.h
 *\brief	��˸labelͷ�ļ�. 
*/
#ifndef TWINKLELABEL_H_
#define TWINKLELABEL_H_ 

#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
class QTimer;

/*!
 *\class	CTwinkleLabel
 *\brief	ʵ��ͼ����˸��label. 
 *\author	Xl.xu
 *\date		2013/4/10
*/
class CTwinkleLabel : public QLabel
{
	Q_OBJECT
public:
	/*!
	 *\fn		CTwinkleLabel( QWidget* pParent = NULL )
	 *\brief	���캯��. 
	 *\author	Xl.xu
	 *\date		2013/4/10
	 *\param	pParent	������ָ��. 
	*/
	CTwinkleLabel( QWidget* pParent = NULL );
	/*!
	 *\fn		~CTwinkleLabel()
	 *\brief	��������. 
	 *\author	Xl.xu
	 *\date		2013/4/10
	*/
	~CTwinkleLabel();
	/*!
	 *\fn		inline bool getTwinkle( )
	 *\brief	��ȡ��˸״̬. 
	 *\author	Xl.xu
	 *\date		2013/4/11
	 *\return	������˸״̬. 
	*/
	inline bool getTwinkle( ){  return m_bTwinkle; }
	/*!
	 *\fn		inline void setTwinkle( bool bTwinkle )
	 *\brief	�����Ƿ���˸. 
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
	 *\brief	��ʼ����Ա����. 
	 *\author	Xl.xu
	 *\date		2013/4/10
	*/
	void initVariable();
private slots:
	void onTimeoutTwinkle( );
    void ChangTextColor();
private:
	//! �Ƿ���˸. 
	bool m_bTwinkle;
	//! . 
	QPropertyAnimation* m_pAnimation;
    QTimer*             m_pTimer;
    QPalette            m_paRed;
    QPalette            m_paYellow;
};

#endif //TWINKLELABEL_H_
