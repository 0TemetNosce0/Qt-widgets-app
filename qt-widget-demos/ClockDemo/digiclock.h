#ifndef DIGICLOCK_H
#define DIGICLOCK_H

#include <QLCDNumber>

class DigiClock : public QLCDNumber
{
    Q_OBJECT

public:
    DigiClock(QWidget *parent=0);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

public slots:
    void showTime();                 	//��ʾ��ǰ��ʱ��

private:
    QPoint dragPosition;            	//����������Ե���ʱ�Ӵ������Ͻǵ�ƫ��ֵ
    bool showColon;                  	//������ʾʱ��ʱ�Ƿ���ʾ������
};

#endif // DIGICLOCK_H
