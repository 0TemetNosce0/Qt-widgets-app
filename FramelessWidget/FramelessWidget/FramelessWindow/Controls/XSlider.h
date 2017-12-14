#ifndef XSlider_H
#define XSlider_H

/// C++ 宏定义

// X_ADD_PUBLIC_PROPERTY 宏用于在类申明体内快速添加一个属性到本类. XSlider 中使用了此宏定义。
// 该宏使用参数指定的名称 申明了 属性类型 属性名 属性成员变量,申明并内联实现了 getter setter 方法
// 该宏指定了 属性值改变的 notify 信号名,并且在setter方法中检测并发射该信号.
// Qt 不支持信号槽中使用宏定义的类型, 因此需要手动在类定义体内申明该信号.
// 使用本宏添加属性并且 在类体内申明notify 信号后. 改属性,成员变量,信号以及方法 可以通用使用。

// 使用示例
// 添加属性:
// X_ADD_PUBLIC_PROPERTY(QColor, color, mo_color, color, setColor, colorChanged)
// slots:   void colorChanged(QColor c);
// 使用属性:
// 使用属性方法：pObj->setColor(Qt::red); QColor objCOlor = pObj->color();
// 使用QSS动态修改属性值： pObj->setStylesheet("CObject{ qproperty-color: skyblue; }");
// 常规的属性应用场景都支持...

#define X_ADD_PUBLIC_PROPERTY(type, property, member, getter, setter, notify) 							\
    private:    																						\
        Q_PROPERTY(type property READ getter WRITE setter NOTIFY notify)								\
    private: 																							\
        type member; 																					\
    public: 																							\
        inline type getter() const { return member; } 													\
        inline void setter(const type& var)    															\
        {   																							\
            if(member != var)    																		\
            {   																						\
                member = var;           																\
                emit notify(member);    																\
            }   																						\
        }

// X_ADD_PRIVATE_PROPERTY 宏用于在类申明体内快速添加一个方法为private权限的属性到本类. XSlider 中未此宏定义。
// 除了方法私有外,X_ADD_PRIVATE_PROPERTY 与 X_ADD_PUBLIC_PROPERTY 没有区别。
/*
#define X_ADD_PRIVATE_PROPERTY(type, property, member, getter, setter, notify) 							\
    private:    																						\
        Q_PROPERTY(type property READ getter WRITE setter NOTIFY notify)								\
        type member; 																					\
        inline type getter() const { return member; } 													\
        inline void setter(const type& var)    															\
        {   																							\
            if(member != var)    																		\
            {   																						\
                member = var;           																\
                emit notify(member);    																\
            }   																						\
        }

// X_ADD_PRIVATE_MEMBER 宏用于在类内体快速添加一个成员变量到本类. XSlider 中未使用此宏定义
// 本宏 实现了 用指定类型名 指定成员变量名 指定getter setter方法名 来添加一个成员变量。
// 本宏 无需额外的手动操作,直接使用即可。
#define X_ADD_PRIVATE_MEMBER(type, member, getter, setter)		\
	private:													\
		type member;											\
	public:														\
		inline type& getter() const { return member; }			\
		inline void setter(const type& var) { member = var; }
*/
		
#include <QWidget>

class XSlider : public QWidget
{
    Q_OBJECT

    /// 属性添加 参考 X_ADD_PUBLIC_PROPERTY 宏的定义
    // grooveNormalColor 属性,定义了 滑槽 无Hover时的颜色
    X_ADD_PUBLIC_PROPERTY(QColor, grooveNormalColor, mo_colorGrooveNormal,   grooveNormalColor, setGrooveNormalColor, grooveNormalColorChanged)
    // grooveHoverColor 属性,定义了 滑槽 Hover状态时的颜色
    X_ADD_PUBLIC_PROPERTY(QColor, grooveHoverColor,  mo_colorGrooveHover,    grooveHoverColor,  setGrooveHoverColor,  grooveHoverColorChanged)
    // headleNormalColor 属性,定义了 滑块 无Hover状态时的颜色
    X_ADD_PUBLIC_PROPERTY(QColor, headleNormalColor, mo_colorHeadleNormal,   headleNormalColor, setHeadleNormalColor, headleNormalColorChanged)
    // headleNormalColor 属性,定义了 滑块 Hover状态时的颜色
    X_ADD_PUBLIC_PROPERTY(QColor, headleHoverColor,  mo_colorHeadleHover,    headleHoverColor,  setHeadleHoverColor,  headleHoverColorChanged)
    // grooveDiameter 属性,定义了 滑槽直径所占的百分比
    X_ADD_PUBLIC_PROPERTY(int,    grooveDiameter,    mo_ntGrooveDiameter,    grooveDiameter,    setGrooveDiameter,    grooveDiameterChanged)
    // headleBorderWidth 属性, 定义了滑块边框宽度所占的百分比
    X_ADD_PUBLIC_PROPERTY(int,    headleBorderWidth, mo_ntHeadleBorderWidth, headleBorderWidth, setHeadleBorderWidth, headleBorderWidthChanged)
    // showValueText 属性, 定义了是否限制 当前值文本
    X_ADD_PUBLIC_PROPERTY(bool,   showValueText,     mo_blShowValueText,     showValueText,     setShowValueText,     showValueTextChanged)

public:
    explicit XSlider(QWidget *parent = nullptr);
    ~XSlider();

    // HitTest 鼠标点击区域枚举
    enum HitTest{
        NoHit,      // 空白点击
        HeadleHit,  // 点击滑块
        GrooveHit   // 点击滑槽
    };

    // 鼠标悬浮区域枚举
    enum HoverTest{
        NoHover,        // 空白悬浮
        HeadleHover,    // 悬浮滑块
        GrooveHover     // 悬浮滑槽
    };

    void setOrientation(Qt::Orientation orientation);   // 设置滑动条方向
    void setRange(int ntMinValue, int ntMaxValue);      // 设置取值范围
    void setValue(int ntValue);                         // 设置当前取值
    void setSingleStep(int ntSingleStep);               // 设置滑动间隔
    void setOutlook(QString strStylesheet);             // 设置外观
    int value();

protected:
    bool event(QEvent *event);
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

signals:
    // 属性信号
    void grooveNormalColorChanged(QColor color);
    void grooveHoverColorChanged(QColor color);
    void headleNormalColorChanged(QColor color);
    void headleHoverColorChanged(QColor color);
    void grooveDiameterChanged(int ntDimameter);
    void headleBorderWidthChanged(int ntWidth);
    void showValueTextChanged(bool blShow);
    // 输出信号
    void valueChanged(int ntValue);
    void valueChanged();

public slots:
    void updateColor();                 // 控件颜色改变槽
    void onGrooveDiameterChanged();     // 滑槽直径改变槽

private:
    void initMembers();                                     // 初始化成员变量
    void initPainter(QPainter* pPainter);                   // 初始化Painter
    void drawGroove(QPaintDevice *pPaintDevice);            // 绘制滑槽
    void drawHeadle(QPaintDevice *pPaintDevice);            // 绘制滑块
    bool validateValues();                                  // 验证参数有效性
    void updateValue(QPointF ptfCursor);                    // 更新当前值
    void refreshHeadleRectByCursor(QPointF ptfCursor);      // 刷新滑块滑动位置
    void refreshHeadleRectByValue();                        // 刷新滑块当前值位置

    QPointF worldMap(QPointF ptf);                          // 逻辑坐转换为窗口坐标
    HitTest &hitTest(bool blDebug = false);                 // 点击检测
    HoverTest& hoverTest(bool blDebug = false);             // 悬浮检测

private:
    // 输入参数
    Qt::Orientation mo_orientation; // 滑动条方向
    int mo_ntValue;                 // 当前值
    int mo_ntMinValue;              // 最小值
    int mo_ntMaxValue;              // 最大值
    int mo_ntSingleStep;            // 滑动间隔

    // 内置属性
    QColor mo_colorGroove;          // 滑槽颜色
    QColor mo_colorHeadle;          // 滑块颜色

    // 变量
    QRectF mo_rctfWindow;           // 窗口坐标
    QPointF mo_ptfHeadleBegin;      // 轨道开始点
    QPointF mo_ptfHeadleEnd;        // 轨道结束点
    QSizeF mo_szfHeadle;            // 控制块尺寸

    QPointF mo_ptfCursorTrack;      // 当前光标桌面坐标
    QPointF mo_ptfHeadlePos;        // 当前滑块中心窗口坐标

    QRectF mo_rctfGroove;           // 轨道矩形
    QRectF mo_rctfHeadle;           // 滑块矩形

    bool mo_blIsEnter;              // 鼠标进入状态
    HitTest mo_hitTest;             // 点击测试
    HoverTest mo_hoverTest;         // 悬浮测试
};

#endif // XSlider_H
