#include "accessibleclock.h"

AccessibleClock::AccessibleClock(QWidget *widget, Role role, const QString &name)
    : QAccessibleWidget(widget, role, name)
{

}

QAccessible::Role AccessibleClock::role(int child) const
{
    switch (child)
    {
    case ClockSelf:
        return Clock;
    case HourHand:
    case MinuteHand:
        return Slider;
    default:
        ;
    }

    return QAccessibleWidget::role(child);
}

int AccessibleClock::childCount() const
{
    return 2;
}

QRect AccessibleClock::rect(int child) const
{
    QRect rect;
    QPoint topLeft = clock()->mapToGlobal(QPoint(0,0));

    switch (child)
    {
    case ClockSelf:
        rect = clock()->rect();
        break;
    case HourHand:
        rect = clock()->hourHandRect();
        break;
    case MinuteHand:
        rect = clock()->minuteHandRect();
        break;
    default:
        return QAccessibleWidget::rect(child);
    }

    return QRect(topLeft.x() + rect.x(), topLeft.y()
                 + rect.y(), rect.width(), rect.height());
}

QString AccessibleClock::text(Text text, int child) const
{
    if (!widget()->isVisible())
    {
        return QString();
    }

    switch (text)
    {
    case Description:
        switch (child)
        {
        case ClockSelf:
            return "an Analog Clock";
        case HourHand:
            return "a Hour Hand";
        case MinuteHand:
            return "a Minute Hand";
        }
    case Name:
        switch (child)
        {
        case ClockSelf:
            return "Analog Clock";
        case HourHand:
            return "Hour Hand";
        case MinuteHand:
            return "Minute Hand";
        }
    case Value:
        switch (child)
        {
        case ClockSelf:
            return clock()->currentTime.toString();
        case HourHand:
            return QString("%1").arg(clock()->currentTime.hour());
        case MinuteHand:
            return QString("%1").arg(clock()->currentTime.minute());
        }

    default:
        return QString();
    }

    return QString();
}
