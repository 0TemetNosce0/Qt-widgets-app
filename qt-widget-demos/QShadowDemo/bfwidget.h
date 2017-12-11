#ifndef BFWIDGET_H
#define BFWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QResizeEvent>

/**
 * 窗口可以拖动
 * 窗口增加阴影效果
 * @brief The BFWidget class
 */
class BFWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BFWidget(QWidget *parent = 0);

    /**
     * 重写空间排版设置
     * 把空间排版到central_widget上面
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
    //显示内容的区域
    QWidget *central_widget;

    QPoint move_point; //移动的距离
    bool mouse_press; //按下鼠标左键

};

#endif // BFWIDGET_H
