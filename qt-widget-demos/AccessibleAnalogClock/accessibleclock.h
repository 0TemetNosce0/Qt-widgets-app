#ifndef ACCESSIBLECLOCK_H
#define ACCESSIBLECLOCK_H

#include <QRect>
#include <QAccessibleWidget>

#include "analogclock.h"

class AccessibleClock : public QAccessibleWidget
{
public:

    enum ClockElements
    {
        ClockSelf = 0,
        HourHand,
        MinuteHand
    };

    AccessibleClock(QWidget *widget, Role role = Client,
                    const QString & name = QString());

    int childCount() const;
    QRect rect(int child) const;
    QString text(Text text, int child) const;
    Role role(int child) const;

private:
    AnalogClock *clock() const
    {
        return qobject_cast<AnalogClock *>(widget());
    }
};

#endif // ACCESSIBLECLOCK_H
