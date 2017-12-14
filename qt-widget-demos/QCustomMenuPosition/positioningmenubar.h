#ifndef POSITIONINGMENUBAR_H
#define POSITIONINGMENUBAR_H

#include <QMenuBar>

class PositioningMenuBar : public QMenuBar
{
    Q_OBJECT

public:
    explicit PositioningMenuBar(QMenuBar *parent = 0);

private:
    bool eventFilter(QObject *obj, QEvent *ev);
};

#endif // POSITIONINGMENUBAR_H
