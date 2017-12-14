#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QList>
#include <QRect>
#include <QWidget>
#include <QPainterPath>

#define DEF_CODECOUNT       4            // 验证码默认位数

#define DEF_NOISYPOINTCOUNT 60           // 噪点数量
#define DEF_CONVERSEROTATE  10           // 转换角度范围
#define DEF_CONVERSESCALE   15           // 转换大小范围

class CodeArea : public QWidget
{
    Q_OBJECT

public:
    CodeArea(QWidget *parent = 0);
    ~CodeArea();

    /**
     * @brief 更换验证码图片
     */
    void replaceCodePic();

    /**
     * @brief 设置验证码位数
     * @param nCodeCount
     */
    void setCodeCount(int nCodeCount);

    /**
     * @brief 设置噪点数量
     * @param nNoisyPointCount
     */
    void setNoisyPointCount(int nNoisyPointCount);

    /**
     * @brief 检验验证码
     * @param sCode
     * @return
     */
    bool checkCode(QString sCode);

protected:
    void paintEvent(QPaintEvent *event);

private:

    /**
     * @brief 初始化验证码范围
     */
    inline void initCodeRange();

    /**
     * @brief 初始化验证码可用颜色列表
     */
    inline void initCodeColorList();

    /**
     * @brief 更新验证码
     */
    inline void updateLoginCode();

    /**
     * @brief 更新验证码图片
     */
    inline void updateCodePic();

    /**
     * @brief 更新用于与用户输入的验证码做比较的码
     */
    inline void updateCode();

    /**
     * @brief 绘制边缘虚线框
     * @param painter
     */
    inline void drawOutline(QPainter &painter);

    /**
     * @brief 绘制验证码
     * @param painter
     * @param nCodeIndex
     */
    inline void drawCode(QPainter &painter, int nCodeIndex);

    /**
     * @brief 绘制噪点
     * @param painter
     */
    inline void drawNoisyPoint(QPainter &painter);

    /**
     * @brief 做验证码形态转换
     * @param painter
     */
    inline void drawConversion(QPainter &painter);

    /**
     * @brief 设置验证码图片
     * @param lCodePic
     */
    inline void setCodePic(const QList<QPainterPath *> &lCodePic);

private:
    QString m_sCode;                            // 用于与用户输入的验证码做比较的码
    QStringList m_slCodeRange;                  // 验证码生成范围
    QStringList m_slLoginCode;                  // 验证码列表，用于生成验证码图片
    QPainterPath *m_pCodePic;                   // 单个位的验证码图片
    QList<QPainterPath *> m_lCodePic;           // 验证码图片
    QList<Qt::GlobalColor> m_lCodeColor;        // 验证码可用颜色列表

    int m_nNoisyPointCount;
    int m_nConverseRotate;
    int m_nConverseScale;
    int m_nCodeCount;
};

#endif // RENDERAREA_H
