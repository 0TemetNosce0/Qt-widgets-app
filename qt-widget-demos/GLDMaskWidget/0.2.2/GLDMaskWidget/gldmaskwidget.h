#ifndef GLDMASKWIDGET_H
#define GLDMASKWIDGET_H

#include "GLDString.h"

#include <QLabel>
#include <QDialog>
#include <QDomElement>

struct GLDGuideInfoItem
{
    GLDGuideInfoItem(int width = -1, int height = -1, int leftXPos = -1, int leftYPos = -1,
                     GString normalImage = "", GString hoverImage = "", GString pressedImage = "")
        : m_width(width)
        , m_height(height)
        , m_leftXPos(leftXPos)
        , m_leftYPos(leftYPos)
        , m_normalImage(normalImage)
        , m_hoverImage(hoverImage)
        , m_pressedImage(pressedImage)
    {

    }

    int m_width;               // 蒙版图的背景
    int m_height;              // 关闭按钮的背景
    int m_leftXPos;            // 左上角X坐标
    int m_leftYPos;            // 左上角Y坐标

    GString m_normalImage;     // 正常情况下图片
    GString m_hoverImage;      // 鼠标划过时效果
    GString m_pressedImage;    // 鼠标按下时效果
};

struct GLDGuideInfo
{
    GLDGuideInfo()
    {

    }

    GLDGuideInfo(GLDGuideInfoItem maskWidgetItem, GLDGuideInfoItem nextButtonItem,
                 GLDGuideInfoItem closeButtonItem)
        : m_maskWidgetItem(maskWidgetItem)
        , m_nextButtonItem(nextButtonItem)
        , m_closeButtonItem(closeButtonItem)
    {

    }

    GLDGuideInfoItem m_maskWidgetItem;    // 蒙版
    GLDGuideInfoItem m_nextButtonItem;    // 下一步
    GLDGuideInfoItem m_closeButtonItem;   // 关闭
};

class GLDMaskTitle;
typedef QList<GLDGuideInfo> GLDGuideInfoList;

class GLDMaskWidget : public QDialog
{
    Q_OBJECT

public:
    explicit GLDMaskWidget(QWidget *parent = 0);
    ~GLDMaskWidget();

    /**
     * @brief 初始化蒙版主界面
     */
    void initMaskTitle();

    /**
     * @brief 初始化下一步按钮
     */
    void initNextButton();

    /**
     * @brief 初始化关闭按钮
     */
    void initCloseButton();

    /**
     * @brief 初始化蒙版
     */
    void init();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    /**
     * @brief 设置当前蒙版页面
     */
    void setCurrentGuidePage();

    /**
     * @brief 设置蒙版样式
     * @param guideInfo    当前蒙版页信息
     */
    void setMaskWidgetStyle(GLDGuideInfo &guideInfo);

    /**
     * @brief 设置关闭按钮样式
     * @param guideInfo    当前蒙版页信息
     */
    void setCloseButtonStyle(GLDGuideInfo &guideInfo);

    /**
     * @brief 设置下一步按钮样式
     * @param guideInfo    当前蒙版页信息
     */
    void setNextButtonStyle(GLDGuideInfo &guideInfo);

    /**
     * @brief 获取蒙版样式
     * @param guideInfo    当前蒙版页信息
     * @return
     */
    GString maskStyleSheet(GLDGuideInfo &guideInfo);

    /**
     * @brief 获取关闭按钮样式
     * @param guideInfo    当前蒙版页信息
     * @return
     */
    GString closeStyleSheet(GLDGuideInfo &guideInfo);

    /**
     * @brief 获取下一步按钮样式
     * @param guideInfo    当前蒙版页信息
     * @return
     */
    GString nextStyleSheet(GLDGuideInfo &guideInfo);

    /**
     * @brief 解析XML文件
     * @param filename    xml文件路径
     */
    void parseXMl(const GString &filename);

    /**
     * @brief 解释guideinfo中的item
     * @param element     文档元素
     * @return            蒙版信息item
     */
    GLDGuideInfoItem& parseNodeItem(QDomElement &element);

    /**
     * @brief 注册蒙版信息
     * @param info    蒙版信息
     */
    void doRegisterGuideInfo(GLDGuideInfo info);

private slots:
    /**
     * @brief 关闭蒙版界面
     */
    void closeMaskWidget();

    /**
     * @brief 下一步按钮被点击
     */
    void nextButtonClicked();

private:
    int                 m_Step;                // 当前步数
    QPoint              m_dragPoint;           // 拖拽点
    GLDMaskTitle*       m_pMaskTitle;          // 蒙版图片
    QPushButton*        m_pNextButton;         // 下一步按钮
    QPushButton*        m_pCloseButton;        // 关闭按钮
    GLDGuideInfoList    m_gldGuideInfoList;    // 存放所有蒙版信息的列表
};

class GLDMaskTitle : public QLabel
{
    Q_OBJECT

public:
    explicit GLDMaskTitle(QWidget *parent = 0);
    ~GLDMaskTitle();
};

#endif // GLDMASKWIDGET_H
