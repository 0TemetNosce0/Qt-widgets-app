#ifndef QDOCKARROWS_H
#define QDOCKARROWS_H

#include <QObject>
#include <QWidget>
#include <QPixmap>

#include "QDockCommon.h"

class QArrowWidget;

class QDockArrows : public QObject
{
    Q_OBJECT
public:
    explicit QDockArrows(QWidget *parent = 0);

    void show(int dockArea);

    DockArea getDockAreaByPos(QPoint pos);
private:
    QArrowWidget* leftWid;
    QArrowWidget* topWid;
    QArrowWidget* rightWid;
    QArrowWidget* bottomWid;
    QArrowWidget* centerWid;
    QArrowWidget* centerLeftWid;
    QArrowWidget* centerRightWid;
    QArrowWidget* centerTopWid;
    QArrowWidget* centerBottomWid;

    QWidget* parentWid;
    public slots:

};

#endif // QDOCKARROWS_H
