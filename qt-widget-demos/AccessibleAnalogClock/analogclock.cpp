#include <QtGui>
#include <QRect>
#include <QSize>
#include <QGenericMatrix>
#include "analogclock.h"

AnalogClock::AnalogClock(QWidget *parent)
    : QWidget(parent)
{
    QSize fixedSize(800,800);
    setMinimumSize(fixedSize);
    setMaximumSize(fixedSize);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(1000);

    setWindowTitle(tr("Analog Clock"));
    resize(200, 200);
    timeout();
}

void AnalogClock::timeout()
{
    currentTime = QTime::currentTime();
    QAccessible::updateAccessibility(this, 0, QAccessible::ValueChanged);
    update();
}

QRect AnalogClock::hourHandRect()
{
    return hour_hand_rect;
}

QRect AnalogClock::minuteHandRect()
{
    return minute_hand_rect;
}

void AnalogClock::paintEvent(QPaintEvent *)
{
    float Pi = 3.14159f;
    float angle = 30.0 * (currentTime.hour() + currentTime.minute() / 60.0) / (180 / Pi);
    QPolygon hourHand(3);
    QPolygon minuteHand(3);

    // rotated hourhand
    hourHand.setPoints(3,   (int) (7 * cos(angle) - 8 * sin(angle)), (int) (7 * sin(angle) + 8 * cos(angle)),
                       (int) (-7 * cos(angle) - 8 * sin(angle)), (int) (-7 * sin(angle) + 8 * cos(angle)),
                       (int) (- (-40) * sin(angle)),(int) ((-40) * cos(angle)));

    hour_hand_rect = hourHand.boundingRect();
    hour_hand_rect.translate(width() / 2, height() / 2);

    angle = 6.0 * (currentTime.minute() + currentTime.second() / 60.0) / (180 / Pi);

    // rotated minutehand
    minuteHand.setPoints(3, (int) (7 * cos(angle) - 8 * sin(angle)), (int) (7 * sin(angle) + 8 * cos(angle)),
                         (int) (-7 * cos(angle) - 8 * sin(angle)), (int) (-7 * sin(angle) + 8 * cos(angle)),
                         (int) (- (-70) * sin(angle)),(int) ((-70) * cos(angle)));

    minute_hand_rect = minuteHand.boundingRect();
    minute_hand_rect.translate(width() / 2, height() / 2);

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.drawConvexPolygon(hourHand);
    painter.setPen(minuteColor);

    for (int i = 0; i < 12; ++i)
    {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);
    painter.drawConvexPolygon(minuteHand);
    painter.setPen(hourColor);

    for (int j = 0; j < 60; ++j)
    {
        if ((j % 5) != 0)
        {
            painter.drawLine(92, 0, 96, 0);
        }

        painter.rotate(6.0);
    }

}
