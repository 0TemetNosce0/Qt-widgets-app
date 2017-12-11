#ifndef QDOCKSIDEBAR_H
#define QDOCKSIDEBAR_H

#include <QToolBar>

class QDockSideBar : public QToolBar
{
    Q_OBJECT

public:
    QDockSideBar(QWidget *parent);
    ~QDockSideBar();


private:
    virtual void childEvent(QChildEvent *);

};

#endif // QDOCKSIDEBAR_H
