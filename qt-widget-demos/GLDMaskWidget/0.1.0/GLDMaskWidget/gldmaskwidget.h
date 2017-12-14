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

    QString m_hintWidgetStyle;            // �ɰ�ͼ�ı���
    QString m_closeButtonStyle;           // �رհ�ť�ı���
    QString m_nextButtonStyle;            // ��һ����ť�ı���

    QPoint m_hintWidgetLeftTopPoint;      // �ɰ�ͼ�����ϵ�
    QPoint m_closeButtonLeftTopPoint;     // �رհ�ť�����ϵ�
    QPoint m_nextButtonLeftTopPoint;      // ��һ����ť�����ϵ�

    QSize  m_hintWidgetSize;              // �ɰ�ͼ�Ŀ��
    QSize  m_closeButtonSize;             // �رհ�ť�Ŀ��
    QSize  m_nextButtonSize;              // ��һ����ť�Ŀ��
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
