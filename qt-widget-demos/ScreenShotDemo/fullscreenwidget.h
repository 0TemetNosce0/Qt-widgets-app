#ifndef FULLSCREENWIDGET_H
#define FULLSCREENWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QRect>
#include <QPainter>
#include <QPoint>
#include <QAction>
#include <QMenu>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QContextMenuEvent>

class FullScreenWidget : public QWidget
{
  Q_OBJECT

public:
    FullScreenWidget(); //���캯��

    //���н�����״̬
    enum shotState
    {
        initShot,
        beginShot,
        finishShot,
        endShot,
        beginMoveShot,
        finishMoveShot,
        beginControl,
        finishControl
    };

    //�ƶ�ѡ���е�8�����Ƶ㣬����˳ʱ�뷽������Ͽ��Ƶ㵽���п��Ƶ������Ϊ1��8
    enum controlPointEnum
    {
        moveControl0,
        moveControl1,
        moveControl2,
        moveControl3,
        moveControl4,
        moveControl5,
        moveControl6,
        moveControl7,
        moveControl8
    };

    QPixmap getFullScreenPixmap(); //��ȡȫ����Pixmap

public slots:
    void loadBackgroundPixmap(const QPixmap &bgPixmap);//���ر���Pixmap�ۺ���
    void loadBackgroundPixmap(const QPixmap &bgPixmap, int x, int y, int width, int height); //���ر���pixmap�ۺ���������x,y,width,height
    void cancelSelectedRect(); //ȡ��ѡ������
    void savePixmap(); //��ѡȡ��Ϊ�ķ���

signals:
    void finishPixmap(const QPixmap &finishPixmap); //�����ͼ���ͼƬ,�����źŸ�������

private:
    //ѡ�����8����ѡȡ
    QRect tlRect; //���ϵ�
    QRect trRect; //���ϵ�
    QRect blRect; //���µ�
    QRect brRect; //���µ�
    QRect tcRect; //���е�
    QRect bcRect; //���е�
    QRect lcRect;//���е�
    QRect rcRect; //���е�

    QPainter painter;
    QPoint beginPoint,endPoint,moveBeginPoint,moveEndPoint;
    QRect selectedRect; //ѡ������
    QPixmap loadPixmap,shotPixmap;
    shotState currentShotState; //��ǰ�Ľ���״̬
    controlPointEnum controlValue; //��¼�ƶ����Ƶ��ֵ
    QAction *savePixmapAction; //����ͼƬ��Ϊ
    QAction *cancelAction; //ȡ��ѡȡ��Ϊ
    QAction *quitAction; //�˳�ѡȡ��Ϊ
    QMenu *contextMenu; //ѡ�������Ҽ��˵�
    int screenwidth; //������Ļ�Ŀ��
    int screenheight; //������Ļ�ĸ߶�
    int screenx; //ѡ����X
    int screeny; //ѡ����Y
    int tipWidth,tipHeight,infoWidth,infoHeight; //���س�ʼ��Ŀ�ȣ��߶ȣ���ʾ������Ϣ�Ŀ�ȣ��߶�

    QRect getSelectedRect(); //��ȡѡȡ
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint); //�����������ȡѡȡ����
    void initFullScreenWidget(); //��ʼ��ץȫ������ز���
    bool isInSelectedRect(const QPoint &point); //�жϸõ��Ƿ���ѡ������
    void initSelectedMenu();//��ʼ���Ҽ��˵�
    void drawTipsText(); //����Ļ�ϴ�ӡ��ʾ��Ϣ
    void drawSelectedPixmap(void); //����Ļ�ϻ�ѡȡ����Ļ
    void updateBeginEndPointValue(const QRect &rect);  //���ƶ�ѡȡ�󣬶�beginPoint,endPoint������������޸�
    void checkMoveEndPoint(); //���ƶ���ѡ�������ж�
    void draw8ControlPoint(const QRect &rect);
    void updateMouseShape(const QPoint &point); //�������ĵ�ǰ״̬
    void updateMoveControlMouseShape(controlPointEnum controlValue);
    controlPointEnum getMoveControlState(const QPoint &point); //��ȡ�ƶ����Ƶ�״̬
    QRect getMoveAllSelectedRect(void); //��ȡ�ƶ�����ѡ�е�ѡ��
    QRect getMoveControlSelectedRect(void);//��ȡ�ƶ����Ƶ��ѡ��
    int getMinValue(int num1, int num2);//��ȡ�������е���Сֵ
    void drawXYWHInfo(void); //��ӡѡȡ��x,y,h,wֵ��Ϣ

    //��д���෽��
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
};
#endif // FULLSCREENWIDGET_H
