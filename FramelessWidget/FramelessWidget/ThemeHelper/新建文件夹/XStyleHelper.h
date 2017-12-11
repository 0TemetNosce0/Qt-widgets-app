#ifndef XSTYLEHELPER_H
#define XSTYLEHELPER_H

#include <QObject>
#include "XStyleAgency.h"

#define go_styleHelper XStyleHelper::getInstance()

class XStyleHelper : public QObject
{
    Q_OBJECT

// BEGIN: 单例

private:
    XStyleHelper(QObject *parent = nullptr);
    XStyleHelper(const XStyleHelper&) = delete;
    XStyleHelper& operator = (const XStyleHelper&) = delete;

public:
    ~XStyleHelper();
    static XStyleHelper& getInstance();

    XStyleAgency& borderStyleAgency();
    XStyleAgency& titleStyleAgency();
    XStyleAgency& clientStyleAgency();

// End: 单例

protected:
    void initStyle();

signals:
    void borderStyleChanged(XStyleData *styleData);        // 边框样式改变
    void titleStyleChanged(XStyleData *styleData);         // 标题栏样式改变
    void clientStyleChanged(XStyleData *styleData);        // 客户区样式改变
    void themeColorChaned(QColor color);                   // 主题样式改变

private:
    XStyleAgency mo_borderStyleAgency;
    XStyleAgency mo_titleStyleAgency;
    XStyleAgency mo_clientStyleAgency;
};

#endif // XSTYLEHELPER_H
