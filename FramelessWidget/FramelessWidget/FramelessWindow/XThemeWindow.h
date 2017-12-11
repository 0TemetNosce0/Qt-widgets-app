#ifndef XThemeWindow_H
#define XThemeWindow_H

#include "XWindow.h"
#include "XThemeHelper.h"

class XThemeWindow : public XWindow
{
    Q_OBJECT
public:
    explicit XThemeWindow(QWidget *parent = nullptr);
    virtual ~XThemeWindow();
    void setThemeHelperEnable(bool blEnable);

signals:

public slots:
    void onThemeColorChanged(QColor color);
    void onThemeAlphaChanged(int ntAlpha);
    void onBackgroundImageChanged(QPixmap pixmap);

private:
    void initMembers();

private:
    bool mo_blThemehelper;
};

#endif // XThemeWindow_H
