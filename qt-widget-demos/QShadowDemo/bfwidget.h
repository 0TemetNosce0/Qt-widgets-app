#ifndef BFWIDGET_H
#define BFWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QResizeEvent>

/**
 * ���ڿ����϶�
 * ����������ӰЧ��
 * @brief The BFWidget class
 */
class BFWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BFWidget(QWidget *parent = 0);

    /**
     * ��д�ռ��Ű�����
     * �ѿռ��Ű浽central_widget����
     * @brief setLayout
     * @param layout
     */
    void setLayout(QLayout * layout);

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //void resizeEvent(QResizeEvent *event);

private:
    //��ʾ���ݵ�����
    QWidget *central_widget;

    QPoint move_point; //�ƶ��ľ���
    bool mouse_press; //����������

};

#endif // BFWIDGET_H
