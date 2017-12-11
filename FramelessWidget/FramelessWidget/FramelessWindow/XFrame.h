#ifndef XFrame_H
#define XFrame_H

#include <QScopedPointer>
#include <QFrame>
#include "XStyle.h"
class XStyleData;


class XFrame : public QFrame, public XStyle
{
    Q_OBJECT

private:    
    void setStyleSheet(const QString &styleSheet) = delete;   // 禁止设置样式表

public:
    explicit XFrame(QWidget *parent = nullptr);
    virtual ~XFrame();
    void switchThemeHelper(bool blOn);          // 启用或者禁用ThemeHelper

    void removeBackgroundImage();

public slots:
    void onStyleChanged(XStyleData *style);
    void onActivationChanged(bool activated);   // 激活改变槽
    void setBackgroundImage(QPixmap pixmap);

protected:
    void paintEvent(QPaintEvent *);
    void onStyleChanged();

private:
    void activatedStyle();                      // 激活状态样式
    void deactivatedStyle();                    // 非激活状态样式

private:
    bool mo_blEnableThemeHelper;
    bool mo_blIsActivated;
    QPixmap *mp_pixmap;
};

#endif // XFrame_H
