#ifndef TRACK_H
#define TRACK_H

#include <QString>

/**
  @brief 保存显示数据的类。
*/
class Track
{
public:
    explicit Track(const QString &title = "", int duration = 0);
    ~Track();

    QString getTitle() const;
    int getDuration() const;
    void setTitle(QString title);
    void setDuration(int duration);

private:
    QString title;
    int duration;
};

#endif // TRACK_H
