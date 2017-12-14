#pragma once
#include <QWidget>
#include <QPoint>

class IAcceptDrop
{
public:
    IAcceptDrop();
    virtual ~IAcceptDrop();
    virtual void dragEnter() = 0;
    virtual void dragLeave() = 0;
    virtual void dragMove(const QPoint& pos) = 0;
    virtual void drop(QWidget* from,QPoint pos) = 0;
};

