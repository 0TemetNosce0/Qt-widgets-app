#ifndef XHLPALETTE_H
#define XHLPALETTE_H

#include <QWidget>
class QPaintEvent;
class QResizeEvent;
class QMouseEvent;

class XHlPalette : public QWidget
{
    Q_OBJECT

public:
    explicit XHlPalette(QWidget *parent = nullptr);
    ~XHlPalette();

    QColor color();                             // 获取颜色值

signals:
    void colorChanged();                        // 无参颜色更新信号
    void colorChanged(QColor color);            // 携参颜色更新信号
    void baseColorChanged(QColor color);        // 通知饱和度控制条更新颜色信号

public slots:
    void setSaturation(double dblsaturation);   // 饱和度修改槽
    void setColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void initMembers();                         // 初始化成员
    void calculateColor(bool blPosChanged);     // 更新颜色值

private:
    QPointF mo_ptfCursorPos;
    QPointF mo_ptfVernierPos;                     // 游标位置
    QPointF mo_ptfVernierPercentPos;            // 游标百分比位置
    QColor mo_color;                            // 颜色
    double mo_dblSaturation;                    // 饱和度
};

#endif // XHLPALETTE_H
