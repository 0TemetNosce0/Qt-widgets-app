#ifndef CUSTOMFRAME_H
#define CUSTOMFRAME_H

#include <QFrame>
#include <QMouseEvent>

class CustomFrame : public QFrame
{
    Q_OBJECT

public:
    CustomFrame(QWidget *parent = 0);
    ~CustomFrame();

signals:
    void signalsMousePosition(int ix, int iy);

protected :
    void mouseMoveEvent(QMouseEvent* e);
};

#endif // CUSTOMFRAME_H
