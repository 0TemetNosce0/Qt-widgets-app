#ifndef XCOLORPICKER_H
#define XCOLORPICKER_H

#include <QWidget>
class QTimer;

class XColorPicker : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(XColorPicker)

public:
    explicit XColorPicker(QWidget *parent = nullptr);
    ~XColorPicker();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void colorChanged(QColor color);
    void colorFinished(QColor color);
    void colorChanged();

public slots:
    void pickColor();
    void onTimeout();

private:
    void initMembers();
    void drawMagnifier(QPaintDevice* pPaintDevice, QPointF ptfPos);         // 绘制放大器组件

private:
    QPixmap mo_pxmpScreenSnapshoot;     // 截图
    QImage mo_imgScreenSnapshoot;       // 截图

    QTimer *mp_timer;                   // 定时器
    bool mo_blTransparent;              // Alpha切换标志
    bool mo_blMoved;                    // 鼠标完成第一次移动标志
    QColor mo_color;                    // 颜色
    QSize mo_szScreen;                  // 屏幕尺寸
    QPoint mo_ptCursorPos;              // 光标位置
    QPoint mo_ptPressed;                // 鼠标左按钮按下位置
};

#endif // XCOLORPICKER_H
