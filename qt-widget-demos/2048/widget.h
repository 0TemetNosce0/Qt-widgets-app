#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include "GameWidget.h"

#define LBLSTYLESHEET "QLabel {color: orange;background: #FFFFCC;border: %1px solid orange;border-radius: %2px;}"
#define BTNSTYLESHEET "QPushButton {color: red;background: lightgray;border: %1px solid darkgray;border-radius: %2px;} QPushButton:pressed{color: white;background: orange;border: %1px solid darkgray;border-radius: %2px;}"

// �����ڲ�����
class Widget : public QWidget
{
    Q_OBJECT

public:
    // ����&��������
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    // ��restart����ť
    QPushButton *restartBtn;
    // ��score����ǩ
    QLabel *scoreLbl;
    // ��HightScore����ǩ
    QLabel *highScoreLbl;
    // ��Ϸ����
    GameWidget *gameWidget;
    // ��Ⱥ͸߶ȵ����ű��� ����ʹ���ڲ����������ڵĳߴ�ı���ı�λ����ߴ�
    qreal ratioW, ratioH;
    // ��¼��߷�
    int highScore;

protected:
    // ���ڳߴ�ı䴥�����¼�
    void resizeEvent(QResizeEvent *);

public slots:
    // ������������źŵĲۺ���
    void onScoreInc(int);
    // ������Ϸ�����źŵĲۺ���
    void onGameOver();
    // ������Ϸ��ʤ�źŵĲۺ���
    void onWin();
};

#endif // WIDGET_H
