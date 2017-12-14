#ifndef LCOMPONENT_H
#define LCOMPONENT_H

#include <QPoint>
#include <QWidget>
#include <QMouseEvent>

#include "component.h"
#include "ui_lcomponent.h"

class LComponent : public QWidget
{
    Q_OBJECT

public:
    LComponent(QWidget *parent = 0);
    ~LComponent();

    /**
     * @brief ��ȡ��ǰ�����ڵ�ԭ���б�
     * @return
     */
    inline QList<Component*> getComponentList()
    {
        return m_lComponent;
    }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:

    /**
     * @brief ��¼������ԭ����λ��
     */
    inline void updateComponentPos();

private slots:
    /**
     * @brief �½�ԭ����ť��
     */
    void on_btnNewComponent_clicked();

    /**
     * @brief ���ع�����
     */
    void on_btnHideToolBar_clicked();

    /**
     * @brief ����������
     */
    void on_btnCallToolBar_clicked();

    /**
     * @brief �ر�ԭ����Ӧ��
     * @param nMyComponentId
     */
    void doComponentClose(int nMyComponentId);

private:
    Ui::LComponentClass ui;

    QList<Component*> m_lComponent;
    QList<QPoint*> m_lComponentPos;

    QPoint m_qpMousePressPoint;

    int m_nCurrentComponentId;
};

#endif // LCOMPONENT_H
