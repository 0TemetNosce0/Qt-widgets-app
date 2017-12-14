#ifndef GLDMASKWIDGET_H
#define GLDMASKWIDGET_H

#include <QWidget>
#include <QPushButton>

const QString c_sNewGuide = "NewGuide";

struct GLDGuideInfo
{
    GLDGuideInfo()
        : m_hintWidgetStyle("")
        , m_closeButtonStyle("")
        , m_nextButtonStyle("")
        , m_hintWidgetLeftTopPoint(QPoint(-1, -1))
        , m_closeButtonLeftTopPoint(QPoint(-1, -1))
        , m_nextButtonLeftTopPoint(QPoint(-1, -1))
        , m_hintWidgetSize(QSize(-1, -1))
        , m_closeButtonSize(QSize(-1, -1))
        , m_nextButtonSize(QSize(-1, -1))
    {

    }

    QString m_hintWidgetStyle;            // Hintͼ�ı���
    QString m_closeButtonStyle;           // �رհ�ť�ı���
    QString m_nextButtonStyle;            // ��һ����ť�ı���

    QPoint m_hintWidgetLeftTopPoint;      // Hintͼ�����ϵ�
    QPoint m_closeButtonLeftTopPoint;     // �رհ�ť�����ϵ�
    QPoint m_nextButtonLeftTopPoint;      // ��һ����ť�����ϵ�

    QSize  m_hintWidgetSize;              // Hintͼ�Ŀ��
    QSize  m_closeButtonSize;             // �رհ�ť�Ŀ��
    QSize  m_nextButtonSize;              // ��һ����ť�Ŀ��
};


typedef QList<GLDGuideInfo> GLDGuideInfoList;


class GLDNewGuideFacade;

class GLDMaskWidget : public QWidget
{
    Q_OBJECT

public:
    GLDMaskWidget(GLDNewGuideFacade *facade, QWidget *parent = 0);
    ~GLDMaskWidget();

    GLDNewGuideFacade *getFacade();
    void init(GLDGuideInfoList newGuideInfoList);

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void closeMask();

public slots:
    void closeMaskWidget();

private slots:
    void nextButtonClicked();

private:
    void setCurrentGuide();

private:
    GLDNewGuideFacade*  m_pFacade;
    QWidget*            m_pCurHintWidget;
    QPushButton*        m_pNextButton;
    QPushButton*        m_pCloseButton;
    GLDGuideInfoList    m_gldGuideInfoList;
    int                 m_Step;
};

#endif
