#ifndef DONUT_H
#define DONUT_H

#include "IrregularForm.h"
#include "GLDMask_Global.h"

#include <QLabel>
#include <QSettings>

class QRegion;
class GLDMaskBoxPrivate;

namespace GLDCBB
{
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
}

class GLDMaskBoxParam
{
public:
    GLDMaskBoxParam()
        : m_strTipPath("")
        , m_strBtnPath("")
        , m_maskWidget(nullptr)
    {

    }

    GLDMaskBoxParam& operator=(GLDMaskBoxParam& param)
    {
        m_strTipPath = param.m_strTipPath;
        m_strBtnPath = param.m_strBtnPath;
        m_maskWidget = param.m_maskWidget;
        return *this;
    }

    QString  m_strTipPath;      // ��ʾ��Ϣ
    QString  m_strBtnPath;      // ��ť
    QWidget* m_maskWidget;      // ��Ҫ��ʾ�ɰ��widget
};

class GLDMASKSHARED_EXPORT GLDMaskBox : public QWidget
{
    Q_OBJECT

public:
    enum MASKCOLOR
    {
        GrayColor,      // 128, 128, 128
        GlassColor,     // 201, 120, 12
        CalaeattaColor, // 252, 239, 232
        CreamColor      // 233, 241, 246
    };

public:
    static GLDMaskBox* createMaskFor(QWidget* widget, const QString & tipInfoPath = "", const QString & btnInfoPath = "");

    void setMaskColor(MASKCOLOR maskColor);

    void openIniFile(const QString& filePath);

private:
    void setMaskShow();
    bool getMaskShow(const QString& prefix, const QString& key);

    QString getValue(const QString& prefix, const QString& key);
    void setValue(const QString& prefix, const QString& key);

    QPoint calcPosOfOwner();
    QPoint calcPosOfTipInfo();

private:
    GLDMaskBox(QWidget *parent = nullptr);
    GLDMaskBox(GLDMaskBoxParam& param, QWidget * parent = nullptr);
    virtual ~GLDMaskBox();

Q_SIGNALS:
    void customClicked();

public slots:
    /**
     * @brief �ڲ���ʹ����,ʹ�øú���ȥ�ر�
     */
    void slotClose();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

private:
    void drawMask(QPainter & painter);
    void drawArrow(QPoint &ownerPoint, QPoint &endPoint, QPainter &painter);

private:
    static GLDMaskBox*    m_pMaskBox;

    GLDMaskBox::MASKCOLOR m_maskColor;

    GLDMaskBoxParam       m_oMaskBoxParam;

    QWidget*              m_pClippedWgt;
    QSettings*            m_pSettings;
    IrregularForm*        m_pTipBox;

    bool                  m_bShowMask;
};

#endif // DONUT_H
