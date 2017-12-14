#ifndef GLDTIPBOX_H
#define GLDTIPBOX_H

#include "GLDFileUtils.h"

#include <QWidget>

class QLabel;
class QPushButton;
class QPropertyAnimation;
class QGraphicsOpacityEffect;

static QWidget* topParentWidget(QWidget* pWgt)
{
    if (!pWgt)
    {
        return nullptr;
    }

    QWidget* widget = nullptr;

    for (widget = pWgt; widget != nullptr; widget = widget->parentWidget())
    {
        if (widget->isWindow())
        {
            break;
        }
    }

    return widget;
}

// ���ݲ�����
// ע�⣺���������Ҫ�������ӣ�����ѭhtml�Ķ��壬���磺<a href=\"http://www.baidu.com/\">title</a>
class GLDMaskBoxParam
{
public:
    GLDMaskBoxParam()
         //, m_sizeMinTipBox(300, 160)
         //, m_sizeMaxTipBox(435, 0)
        : m_strWarnIcon(exePath() + "/images/Msg/warring.png")
        , m_strCloseIcon(exePath() + "/images/Msg/close.png")
        , m_sizeIcon(16, 16)
        , m_strTitle(TRANS_STRING("��ʾ"))
        , m_titleFont(QFont(TRANS_STRING("΢���ź�"), 12, QFont::Bold))
        , m_titleColor(Qt::blue)
        , m_strBody(TRANS_STRING("��ʾ"))
        , m_bodyFont(QFont(TRANS_STRING("΢���ź�"), 9, QFont::Normal))
        , m_bodyColor(QColor("#434343"))
        , m_nRowHeight(20)
        , m_nTimeRemain(8000)
        , m_nTimeFadeOut(2000)
        , m_nMaxWidth(435)
        , m_arrowSize(20, 12)
        , m_wgtOwner(NULL)
        , m_bIsOverTimeShow(true)
    {

    }

    GLDMaskBoxParam& operator=(GLDMaskBoxParam& param)
    {
        m_strWarnIcon = param.m_strWarnIcon;
        m_strCloseIcon = param.m_strCloseIcon;
        m_strTitle = param.m_strTitle;
        m_titleFont = param.m_titleFont;
        m_titleColor = param.m_titleColor;
        m_nRowHeight = param.m_nRowHeight;
        m_strBody = param.m_strBody;
        m_bodyFont = param.m_bodyFont;
        m_bodyColor = param.m_bodyColor;
        m_nTimeRemain = param.m_nTimeRemain;
        m_nTimeFadeOut = param.m_nTimeFadeOut;
        m_arrowSize = param.m_arrowSize;
        //m_sizeMinTipBox = param.m_sizeMinTipBox;
        //m_sizeMaxTipBox = param.m_sizeMaxTipBox;
        m_sizeIcon = param.m_sizeIcon;
        //m_bIsWin = param.m_bIsWin;
        m_wgtOwner = param.m_wgtOwner;
        m_bIsOverTimeShow = param.m_bIsOverTimeShow;

        return *this;
    }

    QString  m_strWarnIcon;      // ͼ��ȫ·��
    QString  m_strCloseIcon;     // �ر�ͼ��·��
    QSize    m_sizeIcon;         // ͼ��Ĵ�С

    QString  m_strTitle;         // titile����
    QFont    m_titleFont;        // title��������
    QColor   m_titleColor;       // titile������ɫ

    QString  m_strBody;          // ��������
    QFont    m_bodyFont;         // ������������
    QColor   m_bodyColor;        // ����������ɫ
    int      m_nRowHeight;       // �����и�

    int      m_nTimeRemain;      // ͣ��ʱ��(milliseconds)
    int      m_nTimeFadeOut;     // ����ʱ��(milliseconds)

    //QSize m_sizeMinTipBox;     // tipbox�ؼ��Ĵ�С
    //QSize m_sizeMaxTipBox;     // tipbox������С���������ݣ�

    //bool m_bIsWin;             // [����]�Ƿ��Ƕ�������(������Χ�����Լ���������false�����Զ���owner�ĸ�����Ϊ����ĸ�)

    int      m_nMaxWidth;        // �����,��������
    QSize    m_arrowSize;        // ��ͷ��С(��Ϊ����layout����߾�)

    QWidget* m_wgtOwner;         // ��ָ���widget

    bool     m_bIsOverTimeShow;  // �Ƿ�ʱ��ʾ,Ĭ��false

};

class GLDMaskBox : public QWidget
{
    Q_OBJECT

public:
    static GLDMaskBox* showTipBox(QWidget * wgtOwner, const QString & strTitle, const QString & strBody);

    static GLDMaskBox* showTipBox(GLDMaskBoxParam * pParam);

    static void closeThis();

    QString objectName() const
    {
        return QString("QTipBox");
    }

public:
    GLDMaskBoxParam& tipBoxParam();

    /**
     * @brief �����ر�,������
     */
    virtual void immediateCloseThis();

    virtual QSize sizeHint() const;

protected:
    virtual void showEvent(QShowEvent * event);

    virtual void paintEvent(QPaintEvent * event);

    virtual void mousePressEvent(QMouseEvent *e);

    virtual bool eventFilter(QObject *obj, QEvent *ev);

    /**
     * @brief ����Բ�Ǿ��ε�tip path
     * @return
     */
    virtual QPainterPath buildPathRoundRectTip();

    virtual QPoint calcPosOfOwner();


    GLDMaskBoxParam          m_oTipBoxParam;

    QLabel*                 m_labelIco;                       // ͼ��
    QLabel*                 m_labelTextTitle;                 // ����������
    QLabel*                 m_labelTextBody;                  // ����������
    QTimer*                 m_timerClose;                     // �رն�ʱ��
    QPushButton*            m_btnClose;                       // �رհ�ť
    QPropertyAnimation*     m_animFadeOut;                    // ����Ч������
    QGraphicsOpacityEffect* m_effectOpacity;                  // ����Ч��

private:
    explicit GLDMaskBox(GLDMaskBoxParam & oTipBoxParam, QWidget *parent = 0);

    static QPointer<GLDMaskBox> m_pTipBox;

public slots:
    void slotClose();

protected slots:
    void slotCloseTimer();
    void slotFadeout();
};

#endif // GLDTIPBOX_H
