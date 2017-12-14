#ifndef GLDNewGUIDEFACADE_H
#define GLDNewGUIDEFACADE_H

#include "GLDMaskWidget.h"

#include <QWidget>

class GLDNewGuideFacade : public QObject
{
    Q_OBJECT

public:
    GLDNewGuideFacade(QWidget *parent = 0);
    virtual ~GLDNewGuideFacade();

public:
    bool show(bool force = false);
    QString getKeyName() const;

protected:
    virtual void registerNewGuideInfo();
    virtual bool canShow(bool force = false);
    // 处理关闭时的对象释放
    virtual void doAfterShow();

protected:
    void init();
    void doRegisterGuideInfo(GLDGuideInfo newGuideInfo);

protected:
    QString           m_sKeyName;
    QWidget*          m_parent;
    GLDMaskWidget*    m_pMaskWidget;
    GLDGuideInfoList  m_guideInfoList;
};

#endif // !1
