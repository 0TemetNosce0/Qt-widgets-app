#include "GLDFileUtils.h"
#include "GLDMaskWidget.h"
#include "GLDNewGuideFacade.h"

#include <QPainter>
#include <QSettings>
#include <QApplication>
#include <QDesktopWidget>

GLDMaskWidget::GLDMaskWidget(GLDNewGuideFacade *facade, QWidget *parent)
    : QWidget(parent)
    , m_pFacade(facade)
    , m_pCurHintWidget(nullptr)
    , m_pNextButton(nullptr)
    , m_pCloseButton(nullptr)
    , m_Step(0)
{
    this->setFixedSize(QApplication::desktop()->width(), QApplication::desktop()->height());

    m_pCurHintWidget = new QWidget(this);
    m_pCurHintWidget->setObjectName("m_pCurHintWidget");
    m_pCurHintWidget->setFixedSize(0, 0);
    m_pCurHintWidget->setAutoFillBackground(true);

    m_pCloseButton = new QPushButton(m_pCurHintWidget);
    m_pCloseButton->setObjectName("m_pCloseButton");
    m_pCloseButton->setGeometry(-1, -1, -1, -1);
    m_pCloseButton->setAutoFillBackground(true);

    connect(m_pCloseButton, &QPushButton::clicked, this, &GLDMaskWidget::closeMaskWidget);

    m_pNextButton = new QPushButton(m_pCurHintWidget);
    m_pNextButton->setObjectName("m_pGuideNextButton");
    m_pNextButton->setGeometry(-1, -1, -1, -1);
    m_pNextButton->setAutoFillBackground(true);

    connect(m_pNextButton, &QPushButton::clicked, this, &GLDMaskWidget::nextButtonClicked);

    setObjectName(c_sNewGuide);
}

GLDMaskWidget::~GLDMaskWidget()
{

}

GLDNewGuideFacade * GLDMaskWidget::getFacade()
{
    return m_pFacade;
}

void GLDMaskWidget::paintEvent(QPaintEvent *event)
{
    //    QPainter painter(this);

    //    QLinearGradient grad(0, 0, rect().width(), rect().height());
    //    {
    //        QGradientStops gs;

    //        gs << QGradientStop(0.0, QColor(0,0,0,100))
    //           << QGradientStop(0.5, QColor(0,0,0,100))
    //           << QGradientStop(1.0, QColor(0,0,0,100));

    //        grad.setStops(gs);
    //    }

    //    painter.fillRect(0, 0, rect().width(), rect().height(), grad);

    QWidget::paintEvent(event);
    QPainter oPainter(this);
    QPainterPath roundPath;
    roundPath.addRect(rect());
    oPainter.setRenderHint(QPainter::Antialiasing);
    oPainter.fillPath(roundPath, QColor(0, 0, 0, 100));
    update();
}

void GLDMaskWidget::init(GLDGuideInfoList guideInfoList)
{
    m_gldGuideInfoList = guideInfoList;
    m_Step = 0;
    setCurrentGuide();
}

void GLDMaskWidget::setCurrentGuide()
{
    GLDGuideInfo guideInfo = m_gldGuideInfoList.at(m_Step);

    if (guideInfo.m_hintWidgetStyle != "")
    {
        m_pCurHintWidget->setStyleSheet(guideInfo.m_hintWidgetStyle);
    }
    else
    {
        m_pCurHintWidget->hide();
    }

    if (guideInfo.m_hintWidgetLeftTopPoint != QPoint(-1, -1))
    {
        m_pCurHintWidget->move(guideInfo.m_hintWidgetLeftTopPoint.x(),
            guideInfo.m_hintWidgetLeftTopPoint.y());
    }

    if ((guideInfo.m_hintWidgetSize != QSize(-1, -1)))
    {
        m_pCurHintWidget->setFixedSize(guideInfo.m_hintWidgetSize.width(),
            guideInfo.m_hintWidgetSize.height());
    }

    // 关闭按钮
    if (guideInfo.m_closeButtonStyle != "")
    {
        m_pCloseButton->setStyleSheet(guideInfo.m_closeButtonStyle);
    }

    if (guideInfo.m_closeButtonLeftTopPoint != QPoint(-1, -1))
    {
        m_pCloseButton->move(guideInfo.m_closeButtonLeftTopPoint.x(),
            guideInfo.m_closeButtonLeftTopPoint.y());
    }

    if ((guideInfo.m_closeButtonSize != QSize(-1, -1)))
    {
        m_pCloseButton->setFixedSize(guideInfo.m_closeButtonSize.width(),
            guideInfo.m_closeButtonSize.height());
    }

    // 下一个按钮
    if (guideInfo.m_nextButtonStyle != "")
    {
        m_pNextButton->setStyleSheet(guideInfo.m_nextButtonStyle);
    }

    if (guideInfo.m_nextButtonLeftTopPoint != QPoint(-1, -1))
    {
        m_pNextButton->move(guideInfo.m_nextButtonLeftTopPoint.x(),
            guideInfo.m_nextButtonLeftTopPoint.y());
    }

    if ((guideInfo.m_nextButtonSize != QSize(-1, -1)))
    {
        m_pNextButton->setFixedSize(guideInfo.m_nextButtonSize.width(),
            guideInfo.m_nextButtonSize.height());
    }
}

void GLDMaskWidget::nextButtonClicked()
{
    m_Step++;

    if (m_Step >= m_gldGuideInfoList.count())
    {
        closeMaskWidget();
    }
    else
    {
        setCurrentGuide();
    }
}

void GLDMaskWidget::closeMaskWidget()
{
    emit closeMask();

    QSettings oInis(exePath() + "/config/NewGuide.ini", QSettings::IniFormat);
    oInis.setValue(m_pFacade->getKeyName(), 1);

    close();
}
