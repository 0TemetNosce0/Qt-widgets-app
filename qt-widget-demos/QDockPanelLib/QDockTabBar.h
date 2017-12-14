#ifndef QDOCKTABBAR_H
#define QDOCKTABBAR_H

#include <QTabBar>
#include "IAcceptDrop.h"

class QDockTabBar : public QTabBar, public IAcceptDrop
{
    Q_OBJECT

public:
    QDockTabBar(QWidget* parent);
    ~QDockTabBar();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    bool isLButtonDown_;
    bool sendDragOut_;
    int insertPos_;

signals:
    void dragTabOut(int index);

protected:
    virtual void paintEvent(QPaintEvent *);

    virtual void dragEnter();

    virtual void dragLeave();

    virtual void dragMove(const QPoint& pos);

    virtual void drop(QWidget* from, QPoint pos);

};

#endif // QDOCKTABBAR_H
