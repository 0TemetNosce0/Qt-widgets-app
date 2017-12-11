#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

#include <QFrame>
#include <QLayout>
#include <QEventLoop>

#include "XBorderPanel.h"
#include "XTitlePanel.h"
#include "XClientPanel.h"
class QHBoxLayout;
class QMenuBar;
class QToolBar;
class QStatusBar;



class XWindow : public QFrame
{
    Q_OBJECT

public:
    XWindow(QWidget *parent = 0);
    virtual ~XWindow();
    // 鼠标碰撞类型枚举
    enum HitSection
    {
        NoSection = 0,
        MoveSection = 1,
        TopLeftSection = 2,
        TopSection = 3,
        TopRightSection = 4,
        LeftSection = 5,
        RightSection = 6,
        BottomLeftSection = 7,
        BottomSection = 8,
        BottomRightSection = 9,
    };

public:
    // 框架窗口接口
    void initTheme();
    QColor themeColor();
    void setHitRadius(int ntLeftWidth, int ntTopWidth,
                      int ntRightWidth, int ntBottomWidth);                 // 设置碰撞半径
    void setShadowRadius(int ntRadius);                                     // 设置阴影半径
    void setShadowColor(QColor color);                                      // 设置阴影颜色
    void setRadius(int ntTopRadius, int ntBottomRadius);                    // 设置窗口圆角半径      
    void setSizeConstraint(QLayout::SizeConstraint constraint);             // 设置尺寸约束
    void setFixedSize(int w, int h);
    void setFixedSize(const QSize & size);
    void exec();                                                            // 模态显示
    // 边框接口
    XBorderPanel* borderFrame();
    // 标题栏接口
    void setTitleWidget(QWidget *pWgt);                                     // 设置部件为标题栏
    XTitlePanel *titleBar();                                                  // 获取标题栏
    void showTileBar(bool exist);                                           // 隐藏/显示标题栏
    void setTitleButtonHints(int ntButtonHints);                            // 设置按钮类型
    void setWindowTitle(QString strTitle,QString strStylesheet = "");       // 设置标题
    void setTitleAlignment(Qt::Alignment align);                            // 设置标题对齐方式
    void setWindowIcon(QString strStylesheet);                              // 设置图标
    void addWidgetTotitleBar(QWidget *pWgt);                                // 添加部件到标题栏

    // 客户区接口
    XClientPanel *clientFrame();                                            // 获取客户区指针
    void setLayout(QLayout *pLayout);                                       // 设置布局

signals:
    void toClose();                                     // 关闭信号
    void activationChanged(bool activated);             // 激活状态改变信号

public slots:
    void onMinimize();                                  // 最小化窗口
    void onMaximize();                                  // 最大化窗口
    void onRestore();                                   // 恢复窗口
    void onClose();                                     // 关闭窗口
    void onActivationChanged(bool activated);           // 激活状态响应槽
    void setThemeColor(QColor color);                                  // 设置背景颜色
    void setBackgroundImage(QPixmap pixmap);                          // 设置背景图片
    void setThemeAlpha(int ntAlpha);

protected:
    bool event(QEvent *event);                          // 事件处理
    void keyPressEvent(QKeyEvent *event);               // 按键按下事件
    void mousePressEvent(QMouseEvent *event);           // 鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event);         // 鼠标抬起事件
    void mouseMoveEvent(QMouseEvent *event);            // 鼠标移动事件
    void closeEvent(QCloseEvent *);
    void resizeEvent(QResizeEvent *event);              // 尺寸事件
    void moveEvent(QMoveEvent *event);                  // 移动事件

private:
    void initMembers();                     // 初始化成员
    void initControls();                    // 初始化子控件
    void createTitleBar();                  // 创建标题栏
    void createClientFrame();               // 创建客户区
    void reLayout();
    void moveWindow();                      // 移动窗口
    void resizeWindow();                    // 改变窗口尺寸
    void hitTest();                         // 碰撞检测

private:
    XBorderPanel *mp_frameBorder;       // 边框Frame
    XTitlePanel *mp_frameTitle;           // 标题栏
    XClientPanel *mp_frameClient;       // 客户区
    QHBoxLayout *mp_layoutMain;         // 主布局
    QEventLoop mo_evenLoop;             // 事件循环

    QColor mo_colorTheme;

    // 标志成员
    bool mo_blMovable;              // 可移动标志
    bool mo_blResizable;            // 尺寸可变标志
    bool mo_blMaximised;            // 最大化标志
    bool mo_blPressed;              // 鼠标左键按下状态

    // 位置信息
    QPoint mo_ptPressedOffset;      // 鼠标按下相对位置
    QPoint mo_ptOffset;             // 鼠标相对位置
    QPoint mo_ptPos;                // 鼠标绝对位置
    QPoint mo_ptLastPos;            // 鼠标上一次绝对位置
    QRect mo_rctResPos;             // 窗口恢复位置
    QPainterPath mo_moveArea;       // 移动区域路径

    // 尺寸框
    HitSection mo_hitSection;           // 点击区域
    int mo_ntLeftHitWidth;              // 左尺寸框宽度
    int mo_ntTopHitWidth;               // 上尺寸框宽度
    int mo_ntRightHitWidth;             // 右尺寸框宽度
    int mo_ntBottomHitWidth;            // 下尺寸框宽度

    // 阴影
    int mo_ntShadowWidth;               // 阴影宽度
    int mo_ntRtmShaowWidth;             // 实时阴影宽度
    QColor mo_colorShadow;              // 框架颜色
};

#endif // FRAMELESSWIDGET_H
