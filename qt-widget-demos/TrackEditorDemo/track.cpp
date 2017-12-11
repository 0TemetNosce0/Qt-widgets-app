#include "track.h"

#include <QString>

Track::Track(const QString &title, int duration)
{
    this->title = title;
    this->duration = duration;
}

Track::~Track()
{

}

QString Track::getTitle() const
{
    return title;
}

int Track::getDuration() const
{
    return duration;
}

void Track::setTitle(QString title)
{
    this->title = title;
}

void Track::setDuration(int duration)
{
    this->duration = duration;
}
