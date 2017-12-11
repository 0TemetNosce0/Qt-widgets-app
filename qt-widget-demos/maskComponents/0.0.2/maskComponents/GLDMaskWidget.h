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

    QString m_hintWidgetStyle;            // Hint图的背景
    QString m_closeButtonStyle;           // 关闭按钮的背景
    QString m_nextButtonStyle;            // 下一步按钮的背景

    QPoint m_hintWidgetLeftTopPoint;      // Hint图的左上点
    QPoint m_closeButtonLeftTopPoint;     // 关闭按钮的左上点
    QPoint m_nextButtonLeftTopPoint;      // 下一步按钮左上上点

    QSize  m_hintWidgetSize;              // Hint图的宽高
    QSize  m_closeButtonSize;             // 关闭按钮的宽高
    QSize  m_nextButtonSize;              // 下一步按钮的宽高
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
