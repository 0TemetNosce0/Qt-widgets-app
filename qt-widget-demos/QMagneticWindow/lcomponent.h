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
     * @brief 获取当前容器内的原件列表
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
     * @brief 记录容器内原件的位置
     */
    inline void updateComponentPos();

private slots:
    /**
     * @brief 新建原件按钮槽
     */
    void on_btnNewComponent_clicked();

    /**
     * @brief 隐藏工具栏
     */
    void on_btnHideToolBar_clicked();

    /**
     * @brief 唤出工具栏
     */
    void on_btnCallToolBar_clicked();

    /**
     * @brief 关闭原件响应槽
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
