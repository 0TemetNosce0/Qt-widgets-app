#include "GLDFileUtils.h"
#include "GLDNewGuideFacade.h"

#include <QSettings>

GLDNewGuideFacade::GLDNewGuideFacade(QWidget *parent)
    : m_parent(parent)
    , m_pMaskWidget(nullptr)
    , m_sKeyName("NewGuideBase")
{
    // 同一个parent不允许同时存在多个新手引导
    GLDMaskWidget *pMaskWidget = m_parent->findChild<GLDMaskWidget*>(c_sNewGuide);

    if (nullptr != pMaskWidget)
    {
        GLDNewGuideFacade *pFacade = pMaskWidget->getFacade();

        if (pFacade != NULL)
        {
            freeAndNil(pFacade);
        }
    }
}

GLDNewGuideFacade::~GLDNewGuideFacade()
{
    freeAndNil(m_pMaskWidget);
}

void GLDNewGuideFacade::init()
{
    if (nullptr == m_pMaskWidget)
    {
        m_pMaskWidget = new GLDMaskWidget(this, m_parent);
    }

    m_guideInfoList.clear();
    registerNewGuideInfo();
    m_pMaskWidget->init(m_guideInfoList);
}

bool GLDNewGuideFacade::show(bool force)
{
    if (!canShow(force))
    {
        return false;
    }

    init();

    m_pMaskWidget->show();

    doAfterShow();

    return true;
}

QString GLDNewGuideFacade::getKeyName() const
{
    return m_sKeyName;
}

bool GLDNewGuideFacade::canShow(bool force)
{
    if (force)
    {
        return true;
    }

    QSettings oInis(exePath()+ "/config/NewGuide.ini", QSettings::IniFormat);

    return oInis.value(m_sKeyName).toInt() == 0;
}

void GLDNewGuideFacade::doAfterShow()
{
    connect(m_pMaskWidget, &GLDMaskWidget::closeMask, this, &GLDNewGuideFacade::deleteLater);
}

void GLDNewGuideFacade::registerNewGuideInfo()
{
    //do nothing
}

void GLDNewGuideFacade::doRegisterGuideInfo(GLDGuideInfo newGuideInfo)
{
    m_guideInfoList.push_back(newGuideInfo);
}
