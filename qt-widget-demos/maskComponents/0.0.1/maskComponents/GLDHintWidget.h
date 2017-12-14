#ifndef GLDHINTWIDGET_H
#define GLDHINTWIDGET_H

#include <QWidget>

class GLDHintWidget : public QWidget
{
    Q_OBJECT

public:
    GLDHintWidget(QWidget *parent = 0);
    virtual ~GLDHintWidget();

protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif

