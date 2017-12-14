#ifndef GLDMASKWIDGET_H
#define GLDMASKWIDGET_H

#include "GLDString.h"

#include <QLabel>
#include <QDialog>

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

    QString m_hintWidgetStyle;            // 蒙版图的背景
    QString m_closeButtonStyle;           // 关闭按钮的背景
    QString m_nextButtonStyle;            // 下一步按钮的背景

    QPoint m_hintWidgetLeftTopPoint;      // 蒙版图的左上点
    QPoint m_closeButtonLeftTopPoint;     // 关闭按钮的左上点
    QPoint m_nextButtonLeftTopPoint;      // 下一步按钮左上上点

    QSize  m_hintWidgetSize;              // 蒙版图的宽高
    QSize  m_closeButtonSize;             // 关闭按钮的宽高
    QSize  m_nextButtonSize;              // 下一步按钮的宽高
};

typedef QList<GLDGuideInfo> GLDGuideInfoList;


class GLDMaskTitle : public QLabel
{
    Q_OBJECT

public:
    explicit GLDMaskTitle(QWidget *parent = 0);
    ~GLDMaskTitle() {}
};

class GLDMaskWidget : public QDialog
{
    Q_OBJECT

public:
    explicit GLDMaskWidget(QWidget *parent = 0);
    ~GLDMaskWidget();

    void initCloseButton();
    void initNextButton();
    void initMaskTitle();
    void init();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void readGuideInfo();
    void setCurrentGuide();
    void parseXMl(const GString &filename);
    void doRegisterGuideInfo(GLDGuideInfo info);

private slots:
    void closeMaskWidget();
    void nextButtonClicked();

private:
    QPoint              m_dragPoint;
    GLDMaskTitle*       m_pMaskTitle;
    QPushButton*        m_pNextButton;
    QPushButton*        m_pCloseButton;
    GLDGuideInfoList    m_gldGuideInfoList;
    int                 m_Step;
};

#endif // GLDMASKWIDGET_H
