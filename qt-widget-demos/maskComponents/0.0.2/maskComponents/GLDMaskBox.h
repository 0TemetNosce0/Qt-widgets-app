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
    GLDMaskBoxParam() :
        //m_sizeMinTipBox(300, 160),
        //m_sizeMaxTipBox(435, 0),
        m_nMaxWidth(435),
        m_nRowHeight(20),
        m_sizeArrow(20, 12),
        m_nTimeFadeOut(2000),
        m_nTimeRemain(8000),
        m_fontBody(QFont(TRANS_STRING("΢���ź�"), 9, QFont::Normal)),
        m_clrBody(QColor("#434343")),
        m_fontTitle(QFont(TRANS_STRING("΢���ź�"), 12, QFont::Bold)),
        m_clrTitle(Qt::blue),
        m_sizeIcon(16, 16),
        m_wgtOwner(NULL),
        m_strIcon(exePath() + "/images/Msg/warring.png"),
        m_strIconClose(exePath() + "/images/Msg/close.png"),
        m_strTitle(TRANS_STRING("��ʾ")),
        m_strBody(TRANS_STRING("��ʾ")),
        m_bIsOverTimeShow(false)
    {

    }

    GLDMaskBoxParam& operator=(GLDMaskBoxParam& param)
    {
        m_strIcon = param.m_strIcon;
        m_strIconClose = param.m_strIconClose;
        m_strTitle = param.m_strTitle;
        m_fontTitle = param.m_fontTitle;
        m_clrTitle = param.m_clrTitle;
        m_nRowHeight = param.m_nRowHeight;
        m_strBody = param.m_strBody;
        m_fontBody = param.m_fontBody;
        m_clrBody = param.m_clrBody;
        m_nTimeRemain = param.m_nTimeRemain;
        m_nTimeFadeOut = param.m_nTimeFadeOut;
        m_sizeArrow = param.m_sizeArrow;
        //m_sizeMinTipBox = param.m_sizeMinTipBox;
        //m_sizeMaxTipBox = param.m_sizeMaxTipBox;
        m_sizeIcon = param.m_sizeIcon;
        //m_bIsWin = param.m_bIsWin;
        m_wgtOwner = param.m_wgtOwner;
        m_bIsOverTimeShow = param.m_bIsOverTimeShow;

        return *this;
    }

    QString m_strIcon;      // ͼ��ȫ·��
    QString m_strIconClose; // �ر�ͼ��·��
    QSize   m_sizeIcon;     // ͼ��Ĵ�С

    QString m_strTitle;     // titile����
    QFont m_fontTitle;      // title��������
    QColor m_clrTitle;      // titile������ɫ

    QString m_strBody;      // ��������
    QFont m_fontBody;       // ������������
    QColor m_clrBody;       // ����������ɫ
    int m_nRowHeight;       // �����и�

    int m_nTimeRemain;      // ͣ��ʱ�䣨milliseconds��
    int m_nTimeFadeOut;     // ����ʱ��(milliseconds)

    QSize m_sizeArrow;      // ��ͷ��С����Ϊ����layout����߾ࣩ
    //QSize m_sizeMinTipBox;  // tipbox�ؼ��Ĵ�С
    //QSize m_sizeMaxTipBox;  // tipbox������С���������ݣ�
    int m_nMaxWidth;        // ����ȣ���������

    //bool m_bIsWin;          // [����]�Ƿ��Ƕ������ڣ�������Χ�����Լ���������false�����Զ���owner�ĸ�����Ϊ����ĸ���
    QWidget * m_wgtOwner;   // ��ָ���widget

    bool m_bIsOverTimeShow; // �Ƿ�ʱ��ʾ��Ĭ��false
};

class GLDMaskBox : public QWidget
{
    Q_OBJECT

public:
    static GLDMaskBox * showTipBox(QWidget * wgtOwner, const QString & strTitle, const QString & strBody);

    static GLDMaskBox * showTipBox(GLDMaskBoxParam * pParam);

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
