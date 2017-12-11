#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QEventLoop>
#include <QTimer>
#include <QPainter>
#include <QList>

// ���Ƶķ���
enum GestureDirect
{
    LEFT = 0,   // ����
    RIGHT = 1,  // ����
    UP = 2,     // ����
    DOWN = 3    // ����
};

// ���嶯��������
enum AnimationType
{
    MOVE = 0,       // �����ƶ�����
    APPEARANCE = 1  // ������ֶ���
};

// �����ṹ��
struct Animation
{
    AnimationType type;     // ��������
    GestureDirect direct;   // ����
    QPointF startPos;       // ��ʼ������ ���ֶ�������ʹ���������
    QPointF endPos;         // ��ֹ������ �ƶ��������յ�����
    int digit;              // ����
    int digit2;             // �ڶ����� ������ܱ��ϲ�
};

// ��Ϸ������ �̳���QWidget
class GameWidget : public QGLWidget
{
    Q_OBJECT
public:
    // ���캯��
    explicit GameWidget(QWidget *parent = 0);

private:
    // ��Ϸ��� �洢ÿ�����ӵ���ֵ
    int board[4][4];
    // ����ĸ��� �洢��ǰ����ϵ����ֵĸ���
    int digitCount;
    // ���� �洢��ǰ�÷�
    int score;
    // ��ʼ������ �洢�����������
    QPoint startPos;
    // �洢������Ҫչ�ֵĶ���
    QList<Animation> animationList;
    // С���ӵĿ�Ⱥ͸߶�
    qreal w, h;
    // ��Ⱥ͸߶ȵ����ű���
    qreal ratioW, ratioH;
    // СԲ�ǵ� x y
    qreal rX, rY;
    // ����ͼ��
    //QImage *cacheImg;
    // �Ƿ��ڲ��Ŷ���Ч��
    bool isAnimating;
    // ��ʱ��
    QTimer timer;

    // ��ʼ����������
    void init2Block();
    // �����Ϸ�Ƿ����
    bool checkGameOver();
    // �����Ϸ�Ƿ��ʤ
    bool checkWin();
    /* ��ȡһ�����ֵĶ�����λ�� ��Ȼ�����ȡ�Ĳ���ȫ�Ƕ�����λ�� ���Ƕ�Ӧ��ɫ������±�
    ���� 2 ��Ӧ 0    8 ��Ӧ 2*/
    int getBitCount(int);
    // ����һ֡����
    bool playAnimation(Animation&, QPainter&);
    // ���ƶ���Ч��
    bool drawAnimation(QPainter&);
    // ��갴�´������¼�
    void mousePressEvent(QMouseEvent *);
    // ����ͷŴ�����ʱ��
    void mouseReleaseEvent(QMouseEvent *);
    // �����¼�
    void paintEvent(QPaintEvent *);
    // ���ڳߴ�ı��¼�
    void resizeEvent(QResizeEvent *);

    // ����ΪһЩ�ź�
signals:
    // �����ƶ��ź�
    void GestureMove(GestureDirect);
    // ���������ź�
    void ScoreInc(int);
    // ��Ϸ�����ź�
    void GameOver();
    // ��Ϸ��ʤ�ź�
    void win();

    // ����ΪһЩ�ۺ���
public slots:
    // ���������ƶ��źŵĲۺ���
    void onGestureMove(GestureDirect);
    // ���¿�ʼ�Ĳۺ���
    void restart();

};

#endif // GAMEWIDGET_H
