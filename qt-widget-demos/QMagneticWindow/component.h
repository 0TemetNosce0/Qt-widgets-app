#ifndef COMPONENT_1_H
#define COMPONENT_1_H

#include <QDialog>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

#define CM_TITLE_HEIGHT         30             //原件标题栏高度

#define DEFAULT_BORDER_WIDTH    5              //边界宽度
#define DEFAULT_MAGNETIC_OFFSET 20             //磁性效力范围
#define DEFAULT_ERROR_RANGE     6              //脱离磁力误差范围
#define DEFAULT_TOOLBAR_WIDTH   80             //所在容器ToolBar宽度
#define DEFAULT_STATUS_HEIGHT   29             //所在容器StatusBar高度

namespace Ui {
class Component;
}

class Component : public QWidget
{
    Q_OBJECT

public:
    explicit Component(const int nComponentId, QWidget *parent = 0);
    ~Component();

    /**
     * @brief 设置原件的边界宽度
     * @param nBorderWidth
     */
    void setBorderWidth(int nBorderWidth);

    /**
     * @brief 设置磁力效应影响范围
     * @param nMagneticOffset
     */
    void setMagneticOffset(int nMagneticOffset);

    /**
     * @brief 设置磁力效应脱离允许误差范围
     * @param nErrorRange
     */
    void setErrorRange(int nErrorRange);

    /**
     * @brief 设置所在容器ToolBar宽度
     * @param nToolBarWidth
     */
    void setToolBarWidth(int nToolBarWidth);

    /**
     * @brief 设置所在容器StatusBar宽度
     * @param nStatusBarHeight
     */
    void setStatusBarHeight(int nStatusBarHeight);

signals:
    /**
     * @brief 原件关闭信号
     * @param nMyComponentId
     */
    void onComponentClose(int nMyComponentId);

protected:
    bool event(QEvent* evt);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

    /**
     * @brief 设置鼠标resize时的样式
     * @param pt
     */
    void setMouseResizeCursor(const QPoint& pt);

private:

    /**
     * @brief 初始化容器
     */
    inline void initComponent();

    /**
     * @brief 更新鼠标按下需求的相关数据
     * @param event
     */
    inline void updateMousePressedData(QMouseEvent *event);

    /**
     * @brief 更新数据-按在边框
     * @param event
     */
    inline void updateDataOnBorder(QMouseEvent *event);

    /**
     * @brief 更新数据-按在标题栏
     * @param event
     */
    inline void updateDataOnTitleBar(QMouseEvent *event);

    /**
     * @brief 更新鼠标限制移动的区域
     */
    inline void updateMouseLeftLimit();

    /**
     * @brief 限制鼠标移动区域
     */
    inline void limitMouseArea();

    /**
     * @brief 重置拖拽相关
     * @param event
     */
    inline void resetDragData(QMouseEvent *event);

    /**
     * @brief 最小边界的判断与处理---原件
     * @param parentRect
     * @param bechmarkRect
     * @param targetRect
     * @param event
     */
    inline void minBoundaryToComponent(const QRect &parentRect, const QRect &bechmarkRect, const QRect &targetRect, QMouseEvent *event);

    /**
     * @brief 最小边界的判断与处理---容器
     * @param bechmarkRect
     * @param targetRect
     * @param event
     */
    inline void minBoundaryToVessel(const QRect &bechmarkRect, const QRect &targetRect, QMouseEvent *event);

    /**
     * @brief 判断鼠标按下时坐标是否在边框
     * @param pt
     * @return
     */
    inline bool mouseOnWinBorder(const QPoint& pt);

    /**
     * @brief 改变原件大小
     * @param evt
     */
    inline void changeSize(QMouseEvent* evt);

    /**
     * @brief 计算改变的最小宽和高
     * @param sizeHint
     * @param minSizeHint
     * @param minSize
     * @param maxSize
     * @param sizePolicy
     * @return
     */
    inline QSize calcMinSize(const QSize &sizeHint, const QSize &minSizeHint,
        const QSize &minSize, const QSize &maxSize,
        const QSizePolicy &sizePolicy);

    inline QRect leftBorder() const;
    inline QRect rightBorder() const;
    inline QRect topBorder() const;
    inline QRect bottomBorder() const;

private slots:

    /**
     * @brief 关闭原件按钮槽
     */
    void on_btnClose_clicked();

private:
    Ui::Component *ui;

    const int m_nMyComponentId;
    int m_nTitleHeight;              //原件标题栏高度
    int m_nBorderWidth;              //边界宽度
    int m_nMagneticOffset;           //磁性效力范围
    int m_nErrorRange;               //脱离磁力误差范围
    int m_nToolBarWidth;             //所在容器ToolBar宽度
    int m_nStatusBarHeight;          //所在容器StatusBar高度
    int m_nMoveCount;

    bool m_bMousePressedInTitle;
    bool m_bMousePressedInBorder;

    bool m_bHorRelatived;
    bool m_bVerRelatived;

    bool m_bHorStick_s;
    bool m_bVerStick_s;
    bool m_bHorStick_c;
    bool m_bVerStick_c;

    QPoint m_pDragPosition;                 // 在窗口边上鼠标按下时的屏幕坐标位置
    QPoint m_pDragMoveOffset;               // 记录鼠标按下时与窗口右下角的偏移坐标
    QPoint m_qpMousePressPoint;             // 鼠标按下时的位置
    QPoint m_qpDiffPos;                     // 鼠标移动时产生的偏移向量

    QRect m_rParentRect;                    // 所在容器geometry
    QRect m_rMouseLimitRect;                // 鼠标拖拽时限制移动的区域

    QList<Component*> m_lComponent;         // 获取父容器所有的原件视图列表

    enum MousePosition
    {
        mpCenter, mpLeft, mpTop, mpRight, mpBottom,
        mpLeftTop, mpLeftBottom, mpRightTop, mpRightBottom
    };

    MousePosition m_eMousePos;
};

#endif // COMPONENT_1_H
