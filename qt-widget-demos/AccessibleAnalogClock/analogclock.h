#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QTime>
#include <QWidget>

class AnalogClock : public QWidget
{
    Q_OBJECT

public:
    AnalogClock(QWidget *parent = 0);
    QRect hourHandRect();
    QRect minuteHandRect();

    QTime currentTime;

public slots:
    void timeout();

private:
    QRect hour_hand_rect;
    QRect minute_hand_rect;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // ANALOGCLOCK_H
