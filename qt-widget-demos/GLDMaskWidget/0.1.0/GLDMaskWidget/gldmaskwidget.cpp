#include "gldmaskwidget.h"
#include "GLDFileUtils.h"

#include <QSettings>
#include <QMouseEvent>
#include <QPushButton>
#include <QDesktopWidget>

GLDMaskWidget::GLDMaskWidget(QWidget *parent)
    : QDialog(parent)
    , m_pNextButton(nullptr)
    , m_pCloseButton(nullptr)
    , m_Step(0)
{
    initMaskTitle();

    initCloseButton();

    initNextButton();

    init();

    setWindowFlags(Qt::FramelessWindowHint);
}

GLDMaskWidget::~GLDMaskWidget()
{

}

void GLDMaskWidget::readGuideInfo()
{
    QSettings setting(exePath()+ "/config/GuideInfo.ini", QSettings::IniFormat);

    QStringList oGroups = setting.childGroups();

    for (int i = 0; i < oGroups.size(); ++i)
    {
        setting.beginGroup(oGroups.at(i));

        QString hintWidgetStyle = setting.value("HintWidgetStyle").toString();
        QStringList hintWidgetLeftTopPoint = setting.value("HintWidgetLeftTopPoint").toString().split(" ");
        QStringList hintWidgetSize = setting.value("HintWidgetSize").toString().split(" ");

        QString closeButtonStyleNormal = setting.value("CloseButtonStyleNormal").toString();
        QString closeButtonStyleHover  = setting.value("CloseButtonStyleHover").toString();
        QString closeButtonStylePressed = setting.value("CloseButtonStylePressed").toString();
        QStringList closeButtonLeftTopPoint = setting.value("CloseButtonLeftTopPoint").toString().split(" ");
        QStringList closeButtonSize = setting.value("CloseButtonSize").toString().split(" ");

        QString nextButtonStyleNormal = setting.value("NextButtonStyleNormal").toString();
        QString nextButtonStyleHover  = setting.value("NextButtonStyleHover").toString();
        QString nextButtonStylePressed = setting.value("NextButtonStylePressed").toString();
        QStringList nextButtonLeftTopPoint = setting.value("NextButtonLeftTopPoint").toString().split(" ");
        QStringList nextButtonSize = setting.value("NextButtonSize").toString().split(" ");

        GLDGuideInfo newGuideInfo;

        newGuideInfo.m_hintWidgetLeftTopPoint = QPoint(hintWidgetLeftTopPoint.at(0).toInt(), hintWidgetLeftTopPoint.at(1).toInt());
        newGuideInfo.m_hintWidgetSize = QSize(hintWidgetSize.at(0).toInt(), hintWidgetSize.at(1).toInt());
        newGuideInfo.m_hintWidgetStyle = "QLabel#m_pMaskTitle{border-image: url("+ hintWidgetStyle + ");}";

        newGuideInfo.m_closeButtonLeftTopPoint = QPoint(closeButtonLeftTopPoint.at(0).toInt(), closeButtonLeftTopPoint.at(1).toInt());
        newGuideInfo.m_closeButtonSize = QSize(closeButtonSize.at(0).toInt(), closeButtonSize.at(1).toInt());
        newGuideInfo.m_closeButtonStyle = "QPushButton#m_pCloseButton"
            "{"
                "border-image: url("+ closeButtonStyleNormal + ");"
            "}"
            "QPushButton#m_pCloseButton:hover"
            "{"
                "border-image: url("+ closeButtonStyleHover + ");"
            "}"
            "QPushButton#m_pCloseButton:pressed"
            "{"
                "border-image: url("+ closeButtonStylePressed + ");"
            "}"
            ;

        newGuideInfo.m_nextButtonLeftTopPoint = QPoint(nextButtonLeftTopPoint.at(0).toInt(), nextButtonLeftTopPoint.at(1).toInt());;
        newGuideInfo.m_nextButtonSize = QSize(nextButtonSize.at(0).toInt(), nextButtonSize.at(1).toInt());
        newGuideInfo.m_nextButtonStyle = "QPushButton#m_pGuideNextButton"
            "{"
                "border-image: url(" + nextButtonStyleNormal + ");"
            "}"
            "QPushButton#m_pGuideNextButton:hover"
            "{"
            "border-image: url(" + nextButtonStyleHover + ");"
            "}"
            "QPushButton#m_pGuideNextButton:pressed"
            "{"
            "border-image: url(" + nextButtonStylePressed + ");"
            "}"
            ;

        doRegisterGuideInfo(newGuideInfo);

        setting.endGroup();
    }
}

void GLDMaskWidget::initCloseButton()
{
    m_pCloseButton = new QPushButton(this);
    m_pCloseButton->setObjectName("m_pCloseButton");
    m_pCloseButton->setGeometry(-1, -1, -1, -1);
    m_pCloseButton->setAutoFillBackground(true);

    connect(m_pCloseButton, &QPushButton::clicked, this, &GLDMaskWidget::closeMaskWidget);
}

void GLDMaskWidget::initNextButton()
{
    m_pNextButton = new QPushButton(this);
    m_pNextButton->setObjectName("m_pGuideNextButton");
    m_pNextButton->setGeometry(-1, -1, -1, -1);
    m_pNextButton->setAutoFillBackground(true);

    connect(m_pNextButton, &QPushButton::clicked, this, &GLDMaskWidget::nextButtonClicked);
}

void GLDMaskWidget::initMaskTitle()
{
    m_pMaskTitle = new GLDMaskTitle(this);
    m_pMaskTitle->setObjectName("m_pMaskTitle");
    m_pMaskTitle->setGeometry(-1, -1, -1, -1);
    m_pMaskTitle->setAutoFillBackground(true);
}

void GLDMaskWidget::init()
{
    m_gldGuideInfoList.clear();
    readGuideInfo();
    m_Step = 0;
    setCurrentGuide();
}

void GLDMaskWidget::setCurrentGuide()
{
    GLDGuideInfo guideInfo = m_gldGuideInfoList.at(m_Step);

    if (guideInfo.m_hintWidgetStyle != "")
    {
        m_pMaskTitle->setStyleSheet(guideInfo.m_hintWidgetStyle);
    }
    else
    {
        hide();
    }

    if (guideInfo.m_hintWidgetLeftTopPoint != QPoint(-1, -1))
    {
        m_pMaskTitle->move(0, 0);
    }

    if ((guideInfo.m_hintWidgetSize != QSize(-1, -1)))
    {
        this->setFixedSize(guideInfo.m_hintWidgetSize.width(), guideInfo.m_hintWidgetSize.height());
        m_pMaskTitle->setFixedSize(guideInfo.m_hintWidgetSize.width(), guideInfo.m_hintWidgetSize.height());
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
    QSettings oInis(exePath() + "/config/NewGuide.ini", QSettings::IniFormat);
    oInis.setValue("GLDMaskWidget", 1);

    close();
}

void GLDMaskWidget::doRegisterGuideInfo(GLDGuideInfo info)
{
     m_gldGuideInfoList.append(info);
}

void GLDMaskWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        move(event->globalPos() - m_dragPoint);
        event->accept();
    }
    else
    {
        QDialog::mouseMoveEvent(event);
    }
}

void GLDMaskWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragPoint = event->globalPos() - frameGeometry().topLeft();

        event->accept();
    }
    else
    {
        QDialog::mousePressEvent(event);
    }
}

GLDMaskTitle::GLDMaskTitle(QWidget *parent)
    : QLabel(parent)
{

}
