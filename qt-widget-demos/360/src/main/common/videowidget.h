#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QDialog>

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
    #include <phonon/mediasource.h>
    #include <phonon/mediaobject.h>
    #include <phonon/AudioOutput>
    #include <phonon/videoplayer.h>
    #include <phonon/VideoWidget>
#define USE_QT4 1
#else
    #include <QVideoWidget>
    #include <QMediaPlayer>
    #include <QMediaPlaylist>
#endif

class QLabel;
class StaticButton;

class VideoWidget : public QDialog
{
    Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = 0);
    void startVideo();

private slots:
    void playFinished();
    void closeWidget();

    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);

private:
    QMediaPlayer    *m_player;
    qint64          m_duration;
    qint64          m_oldPosition;

    StaticButton    *m_close;
    QLabel          *m_startLabel;
    QLabel          *m_endLabel;
    bool            m_isFirst;
};

#endif // VIDEOWIDGET_H
