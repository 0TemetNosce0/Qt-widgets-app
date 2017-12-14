#ifndef SHADOWWIDGET_H
#define SHADOWWIDGET_H

#include <QWidget>
#include <QDialog>

class ShadowWidget : public QDialog
{
    Q_OBJECT
public:
    explicit ShadowWidget(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //������̳�
    virtual void paintEvent(QPaintEvent *event);

private:
    QPoint m_movePoint; //�ƶ��ľ���
    bool m_mousePress; //����������
};

#endif // SHADOWWIDGET_H
