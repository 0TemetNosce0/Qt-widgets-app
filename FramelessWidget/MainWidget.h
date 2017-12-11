#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "XThemeWindow.h"
class QPushButton;

class CMainWidget : public XThemeWindow
{
    Q_OBJECT

public:
    explicit CMainWidget(QWidget *parent = nullptr);

public slots:
    void onBtnSetTheme();

private:
    void initMembers();
    void initContents();
    void initTitleBar();
    void initOutlook();

private:
    QPushButton *mp_btnSetTheme;
};

#endif // MAINWIDGET_H
