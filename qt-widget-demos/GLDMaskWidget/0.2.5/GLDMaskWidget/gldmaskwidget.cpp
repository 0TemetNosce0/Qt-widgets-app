#include "gldmaskwidget.h"
#include "GLDFileUtils.h"

#include <QFile>
#include <QDomAttr>
#include <QSettings>
#include <QMouseEvent>
#include <QPushButton>
#include <QDomElement>
#include <QDomDocument>
#include <QDesktopWidget>

const GString XMLPath = "/config/GuideInfo.xml";

GLDMaskWidget::GLDMaskWidget(QWidget *parent)
    : QDialog(parent)
    , m_Step(0)
    , m_pMaskTitle(nullptr)
    , m_pNextButton(nullptr)
    , m_pCloseButton(nullptr)
{
    setWindowFlags(Qt::FramelessWindowHint);

    initMaskTitle();

    initNextButton();

    initCloseButton();

    init();
}

GLDMaskWidget::~GLDMaskWidget()
{

}

void GLDMaskWidget::parseXMl(const GString& filename)
{
    if(nullptr == filename)
    {
        return;
    }

    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    QString strError;
    QDomDocument document;
    int errLin = 0, errCol = 0;

    if(!document.setContent(&file, false, &strError, &errLin, &errCol))
    {
        return;
    }

    if(document.isNull())
    {
        return;
    }

    QDomElement root = document.documentElement();
    GString elementTagName = root.firstChildElement().tagName();
    QDomNodeList nodeList = root.elementsByTagName(elementTagName);

    for (int i = 0; i < nodeList.size(); ++i)
    {
        GLDGuideInfo guideInfo;

        QDomElement element = nodeList.item(i).firstChildElement();

        while (!element.isNull())
        {
            GLDGuideInfoItem guideInfoItem = parseNodeItem(element);

            if (element.tagName() == "mask")
            {
                guideInfo.m_maskWidgetItem = guideInfoItem;
            }
            else if (element.tagName() == "close")
            {
                guideInfo.m_closeButtonItem = guideInfoItem;
            }
            else if (element.tagName() == "next")
            {
                guideInfo.m_nextButtonItem = guideInfoItem;
            }

            element = element.nextSiblingElement();
        }

        doRegisterGuideInfo(guideInfo);
    }
}

GLDGuideInfoItem GLDMaskWidget::parseNodeItem(QDomElement &element)
{
    int width, height, leftXpos, leftYpos;
    GString normalImage, hoverImage, pressedImage;

    if (element.hasAttribute("width"))
    {
        width = element.attributeNode("width").value().toInt();
    }

    if (element.hasAttribute("height"))
    {
        height = element.attributeNode("height").value().toInt();
    }

    if (element.hasAttribute("normalimage"))
    {
        normalImage = element.attributeNode("normalimage").value();
    }

    if (element.hasAttribute("hoverimage"))
    {
        hoverImage = element.attributeNode("hoverimage").value();
    }

    if (element.hasAttribute("pressedimage"))
    {
        pressedImage = element.attributeNode("pressedimage").value();
    }

    if (element.hasAttribute("leftXpos"))
    {
        leftXpos = element.attributeNode("leftXpos").value().toInt();
    }

    if (element.hasAttribute("leftYpos"))
    {
        leftYpos = element.attributeNode("leftYpos").value().toInt();
    }

    return GLDGuideInfoItem(width, height, leftXpos, leftYpos, normalImage, hoverImage, pressedImage);
}

void GLDMaskWidget::initMaskTitle()
{
    m_pMaskTitle = new GLDMaskTitle(this);
    m_pMaskTitle->setObjectName("m_pMaskTitle");
    m_pMaskTitle->setGeometry(-1, -1, -1, -1);
    m_pMaskTitle->setAutoFillBackground(true);
}

void GLDMaskWidget::initNextButton()
{
    m_pNextButton = new QPushButton(this);
    m_pNextButton->setObjectName("m_pGuideNextButton");
    m_pNextButton->setGeometry(-1, -1, -1, -1);
    m_pNextButton->setAutoFillBackground(true);

    connect(m_pNextButton, &QPushButton::clicked, this, &GLDMaskWidget::nextButtonClicked);
}

void GLDMaskWidget::initCloseButton()
{
    m_pCloseButton = new QPushButton(this);
    m_pCloseButton->setObjectName("m_pCloseButton");
    m_pCloseButton->setGeometry(-1, -1, -1, -1);
    m_pCloseButton->setAutoFillBackground(true);

    connect(m_pCloseButton, &QPushButton::clicked, this, &GLDMaskWidget::closeMaskWidget);
}

void GLDMaskWidget::init()
{
    m_gldGuideInfoList.clear();
    parseXMl(exePath() + XMLPath);
    m_Step = 0;
    setCurrentGuidePage();
}

void GLDMaskWidget::setCurrentGuidePage()
{
    GLDGuideInfo guideInfo = m_gldGuideInfoList.at(m_Step);

    // 蒙版
    setMaskWidgetStyle(guideInfo);

    // 关闭按钮
    setCloseButtonStyle(guideInfo);

    // 下一个按钮
    setNextButtonStyle(guideInfo);
}

void GLDMaskWidget::setMaskWidgetStyle(GLDGuideInfo &guideInfo)
{
    if (guideInfo.m_maskWidgetItem.m_normalImage != "")
    {
        const GString strMaskStyle = maskStyleSheet(guideInfo);
        m_pMaskTitle->setStyleSheet(strMaskStyle);
    }
    else
    {
        hide();
    }

    if (guideInfo.m_maskWidgetItem.m_leftXPos != -1 && guideInfo.m_maskWidgetItem.m_leftYPos != -1)
    {
        m_pMaskTitle->move(0, 0);
    }

    if (guideInfo.m_maskWidgetItem.m_width != -1 && guideInfo.m_maskWidgetItem.m_height != -1)
    {
        this->setFixedSize(guideInfo.m_maskWidgetItem.m_width, guideInfo.m_maskWidgetItem.m_height);
        m_pMaskTitle->setFixedSize(guideInfo.m_maskWidgetItem.m_width, guideInfo.m_maskWidgetItem.m_height);
    }
}

void GLDMaskWidget::setCloseButtonStyle(GLDGuideInfo &guideInfo)
{
    if (guideInfo.m_closeButtonItem.m_normalImage != "")
    {
        const GString strCloseStyle = closeStyleSheet(guideInfo);
        m_pCloseButton->setStyleSheet(strCloseStyle);
    }

    if (guideInfo.m_closeButtonItem.m_leftXPos != -1 && guideInfo.m_closeButtonItem.m_leftYPos != -1)
    {
        m_pCloseButton->move(guideInfo.m_closeButtonItem.m_leftXPos,
            guideInfo.m_closeButtonItem.m_leftYPos);
    }

    if (guideInfo.m_closeButtonItem.m_width != -1 && guideInfo.m_closeButtonItem.m_height != -1)
    {
        m_pCloseButton->setFixedSize(guideInfo.m_closeButtonItem.m_width,
            guideInfo.m_closeButtonItem.m_height);
    }
}

void GLDMaskWidget::setNextButtonStyle(GLDGuideInfo &guideInfo)
{
    if (guideInfo.m_nextButtonItem.m_normalImage != "")
    {
        const GString strNextStyle = nextStyleSheet(guideInfo);
        m_pNextButton->setStyleSheet(strNextStyle);
    }

    if (guideInfo.m_nextButtonItem.m_leftXPos != -1 && guideInfo.m_nextButtonItem.m_leftYPos != -1)
    {
        m_pNextButton->move(guideInfo.m_nextButtonItem.m_leftXPos,
            guideInfo.m_nextButtonItem.m_leftYPos);
    }

    if (guideInfo.m_nextButtonItem.m_width != -1 && guideInfo.m_nextButtonItem.m_height != -1)
    {
        m_pNextButton->setFixedSize(guideInfo.m_nextButtonItem.m_width,
            guideInfo.m_nextButtonItem.m_height);
    }
}

GString GLDMaskWidget::maskStyleSheet(GLDGuideInfo &guideInfo)
{
    return GString("QLabel#m_pMaskTitle"
        "{"
        "border-image: url(" + guideInfo.m_maskWidgetItem.m_normalImage + ");"
        "}"
        "QLabel#m_pMaskTitle:hover"
        "{"
        "border-image: url(" + guideInfo.m_maskWidgetItem.m_hoverImage + ");"
        "}"
        "QLabel#m_pMaskTitle:pressed"
        "{"
        "border-image: url(" + guideInfo.m_maskWidgetItem.m_pressedImage + ");"
        "}");
}

GString GLDMaskWidget::closeStyleSheet(GLDGuideInfo &guideInfo)
{
    return GString("QPushButton#m_pCloseButton"
        "{"
        "border-image: url(" + guideInfo.m_closeButtonItem.m_normalImage + ");"
        "}"
        "QPushButton#m_pCloseButton:hover"
        "{"
        "border-image: url(" + guideInfo.m_closeButtonItem.m_hoverImage + ");"
        "}"
        "QPushButton#m_pCloseButton:pressed"
        "{"
        "border-image: url(" + guideInfo.m_closeButtonItem.m_pressedImage + ");"
        "}");
}

GString GLDMaskWidget::nextStyleSheet(GLDGuideInfo &guideInfo)
{
    return GString("QPushButton#m_pGuideNextButton"
        "{"
        "border-image: url(" + guideInfo.m_nextButtonItem.m_normalImage + ");"
        "}"
        "QPushButton#m_pGuideNextButton:hover"
        "{"
        "border-image: url(" + guideInfo.m_nextButtonItem.m_hoverImage + ");"
        "}"
        "QPushButton#m_pGuideNextButton:pressed"
        "{"
        "border-image: url(" + guideInfo.m_nextButtonItem.m_pressedImage + ");"
        "}");
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
        setCurrentGuidePage();
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

GLDMaskTitle::~GLDMaskTitle()
{

}
