#ifndef YOUHUASCANBOTTOM_H
#define YOUHUASCANBOTTOM_H

#include "../../common/basestylewidget.h"

class OptimizeButton;

class YouhuaScanBottom : public BaseStyleWidget
{
    Q_OBJECT
public:
    explicit YouhuaScanBottom(QWidget *parent = 0);
private:
    void initUI();
private:
    OptimizeButton    *m_startButton;
    OptimizeButton    *m_sysButton;
    OptimizeButton    *m_netButton;
    OptimizeButton    *m_diskButton;
};

#endif // YOUHUASCANBOTTOM_H
