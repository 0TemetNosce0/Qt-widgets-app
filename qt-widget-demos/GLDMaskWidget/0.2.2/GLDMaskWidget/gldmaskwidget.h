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

    int m_width;               // �ɰ�ͼ�ı���
    int m_height;              // �رհ�ť�ı���
    int m_leftXPos;            // ���Ͻ�X����
    int m_leftYPos;            // ���Ͻ�Y����

    GString m_normalImage;     // ���������ͼƬ
    GString m_hoverImage;      // ��껮��ʱЧ��
    GString m_pressedImage;    // ��갴��ʱЧ��
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

    GLDGuideInfoItem m_maskWidgetItem;    // �ɰ�
    GLDGuideInfoItem m_nextButtonItem;    // ��һ��
    GLDGuideInfoItem m_closeButtonItem;   // �ر�
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
     * @brief ��ʼ���ɰ�������
     */
    void initMaskTitle();

    /**
     * @brief ��ʼ����һ����ť
     */
    void initNextButton();

    /**
     * @brief ��ʼ���رհ�ť
     */
    void initCloseButton();

    /**
     * @brief ��ʼ���ɰ�
     */
    void init();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    /**
     * @brief ���õ�ǰ�ɰ�ҳ��
     */
    void setCurrentGuidePage();

    /**
     * @brief �����ɰ���ʽ
     * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
     */
    void setMaskWidgetStyle(GLDGuideInfo &guideInfo);

    /**
     * @brief ���ùرհ�ť��ʽ
     * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
     */
    void setCloseButtonStyle(GLDGuideInfo &guideInfo);

    /**
     * @brief ������һ����ť��ʽ
     * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
     */
    void setNextButtonStyle(GLDGuideInfo &guideInfo);

    /**
     * @brief ��ȡ�ɰ���ʽ
     * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
     * @return
     */
    GString maskStyleSheet(GLDGuideInfo &guideInfo);

    /**
     * @brief ��ȡ�رհ�ť��ʽ
     * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
     * @return
     */
    GString closeStyleSheet(GLDGuideInfo &guideInfo);

    /**
     * @brief ��ȡ��һ����ť��ʽ
     * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
     * @return
     */
    GString nextStyleSheet(GLDGuideInfo &guideInfo);

    /**
     * @brief ����XML�ļ�
     * @param filename    xml�ļ�·��
     */
    void parseXMl(const GString &filename);

    /**
     * @brief ����guideinfo�е�item
     * @param element     �ĵ�Ԫ��
     * @return            �ɰ���Ϣitem
     */
    GLDGuideInfoItem& parseNodeItem(QDomElement &element);

    /**
     * @brief ע���ɰ���Ϣ
     * @param info    �ɰ���Ϣ
     */
    void doRegisterGuideInfo(GLDGuideInfo info);

private slots:
    /**
     * @brief �ر��ɰ����
     */
    void closeMaskWidget();

    /**
     * @brief ��һ����ť�����
     */
    void nextButtonClicked();

private:
    int                 m_Step;                // ��ǰ����
    QPoint              m_dragPoint;           // ��ק��
    GLDMaskTitle*       m_pMaskTitle;          // �ɰ�ͼƬ
    QPushButton*        m_pNextButton;         // ��һ����ť
    QPushButton*        m_pCloseButton;        // �رհ�ť
    GLDGuideInfoList    m_gldGuideInfoList;    // ��������ɰ���Ϣ���б�
};

class GLDMaskTitle : public QLabel
{
    Q_OBJECT

public:
    explicit GLDMaskTitle(QWidget *parent = 0);
    ~GLDMaskTitle();
};

#endif // GLDMASKWIDGET_H
