/**
* @�ļ���   push_button.h
* @�汾��Ϣ copyright  2012-2013 Sugon. All rights reserved.
* @��������
*           PushButton�������С������󻯡��رա����˵��Ȱ�ť����Ч
* @����     ����<wangliang@sugon.com>
* @����     2012-01-06
*/

#ifndef CS_CSVIEW_PUSHBUTTON_H
#define CS_CSVIEW_PUSHBUTTON_H

#include <QPainter>
#include <QPushButton>
#include <QMouseEvent>

/**
* @��������   ��Ҫ���ð�ť��ʽ����Ч
* @����  ���� <wangliang@sugon.com>
**/

class PushButton : public QPushButton
{
    Q_OBJECT

public:

    /**
    *
    * ����˵��
    *    ���캯��
    *
    * ����˵��
    *     QWidget *parent = 0    ������
    *
    * ����ֵ
    *     ��
    *
    */
    explicit PushButton(QWidget *parent = 0);

    /**
    *
    * ����˵��
    *    ��������
    *
    * ����˵��
    *     ��
    *
    * ����ֵ
    *     ��
    *
    */
    ~PushButton();

    /**
    *
    * ����˵��
    *	 ����ͼ��
    *
    * ����˵��
    *     QString pic_name ͼ������
    *
    * ����ֵ
    *     ��
    *
    */
    void loadPixmap(QString pic_name);

protected:

    /**
    *
    * ����˵��
    *    ����ƽ��¼�
    *
    * ����˵��
    *     QEvent * event    �¼�
    *
    * ����ֵ
    *     ��
    *
    */
    void enterEvent(QEvent *);

    /**
    *
    * ����˵��
    *     ����Ƴ��¼�
    *
    * ����˵��
    *     QEvent * event    �¼�
    *
    * ����ֵ
    *     ��
    *
    */
    void leaveEvent(QEvent *);

    /**
    *
    * ����˵��
    *     ��갴���¼�
    *
    * ����˵��
    *     QMouseEvent *event    ����¼�
    *
    * ����ֵ
    *     ��
    *
    */
    void mousePressEvent(QMouseEvent *event);

    /**
    *
    * ����˵��
    *     ����ͷ��¼�
    *
    * ����˵��
    *     QMouseEvent *event    ����¼�
    *
    * ����ֵ
    *     ��
    *
    */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
    *
    * ����˵��
    *     ��ͼ�¼�
    *
    * ����˵��
    *     QPaintEvent * event    ��ͼ�¼�
    *
    * ����ֵ
    *     ��
    *
    */
    void paintEvent(QPaintEvent *);

private:

    //ö�ٰ�ť�ļ���״̬
    enum ButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS};
    ButtonStatus status;
    QPixmap pixmap;

    int btn_width; //��ť���
    int btn_height; //��ť�߶�
    bool mouse_press; //��ť����Ƿ���
};

#endif //CS_CSVIEW_PUSHBUTTON_H
