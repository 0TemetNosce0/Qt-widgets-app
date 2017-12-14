#ifndef XClientPanel_H
#define XClientPanel_H

#include "XFrame.h"

class XClientPanel : public XFrame
{
    Q_OBJECT

private:
    void setStyleSheet(const QString &styleSheet) = delete;

public:
    explicit XClientPanel(QWidget *parent = nullptr);
    ~XClientPanel();

    void setRadius(int ntTopLeft, int ntTopRight, int ntBottomLeft, int ntBottonRight);
    void setBorderWidth(int ntLeft, int ntTop, int ntRight, int ntBottom);
    void setBorderWidth(int ntWidth);

private:
    void refreshRadius();

};

#endif // XClientPanel_H
