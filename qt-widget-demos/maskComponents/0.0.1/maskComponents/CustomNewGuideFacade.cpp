#include "GLDFileUtils.h"
#include "CustomNewGuideFacade.h"
#include <windows.h>

#include <QSettings>
#include <QEventLoop>

CustomNewGuideFacade::CustomNewGuideFacade(QWidget *parent)
    : GLDNewGuideFacade(parent)
{
    m_sKeyName = "CustomNewCreateGuide";
}

CustomNewGuideFacade::~CustomNewGuideFacade()
{

}

void CustomNewGuideFacade::execute(QWidget *parent)
{
    CustomNewGuideFacade* pCustomModeGuideFacade = new CustomNewGuideFacade(parent);
    pCustomModeGuideFacade->show();
}

void CustomNewGuideFacade::registerNewGuideInfo()
{
    //GLDGuideInfo newGuideInfo;

    //newGuideInfo.m_hintWidgetStyle = "QWidget#m_pCurHintWidget{border-image: url(:/mask/images/target.png);}";
    //newGuideInfo.m_hintWidgetLeftTopPoint = QPoint(24, 86);
    //newGuideInfo.m_hintWidgetSize = QSize(305, 511);

    //newGuideInfo.m_closeButtonLeftTopPoint = QPoint(255, 255);
    //newGuideInfo.m_closeButtonSize = QSize(30, 30);
    //newGuideInfo.m_closeButtonStyle = "QPushButton#m_pCloseButton"
    //    "{"
    //    "border-image: url(:/mask/images/close-normal.png);"
    //    "}"
    //    "QPushButton#m_pCloseButton:hover"
    //    "{"
    //    "border-image: url(:/mask/images/close-hover.png);"
    //    "}"
    //    "QPushButton#m_pCloseButton:pressed"
    //    "{"
    //    "border-image: url(:/mask/images/close-pressed.png);"
    //    "}"
    //    ;

    //newGuideInfo.m_nextButtonLeftTopPoint = QPoint(90, 450);
    //newGuideInfo.m_nextButtonSize = QSize(128, 38);
    //newGuideInfo.m_nextButtonStyle = "QPushButton#m_pGuideNextButton"
    //    "{"
    //    "border-image: url(:/mask/images/next-normal.png);"
    //    "}"
    //    "QPushButton#m_pGuideNextButton:hover"
    //    "{"
    //    "border-image: url(:/mask/images/next-hover.png);"
    //    "}"
    //    "QPushButton#m_pGuideNextButton:pressed"
    //    "{"
    //    "border-image: url(:/mask/images/next-pressed.png);"
    //    "}"
    //    ;

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
        newGuideInfo.m_hintWidgetStyle = "QWidget#m_pCurHintWidget{border-image: url("+ hintWidgetStyle + ");}";

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

void CustomNewGuideFacade::doAfterShow()
{
    //QEventLoop oEventLoop;
    //connect(m_pMaskWidget, &GLDMaskWidget::signal_Close, &oEventLoop, &QEventLoop::quit);
    //oEventLoop.exec();
}
