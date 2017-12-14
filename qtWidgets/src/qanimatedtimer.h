#ifndef __qanimatedtimer_h_INCLUDED__
#define __qanimatedtimer_h_INCLUDED__

#include <QObject>
#include <QBasicTimer>
#include <QString>
#include <QWidget>


enum TIMER_STATE
{
    TIMER_STOPPED,
    TIMER_PAUSED,
    TIMER_RUNNING
};

enum FADING_DIRECTION
{
    FADING_NONE,
    FADING_IN,
    FADING_OUT
};

class QAnimatedTimer : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)   // the value of the timer
    Q_PROPERTY(int dots READ dots WRITE setDots)                            // number of dots around the circle
    Q_PROPERTY(bool showCounter READ counterVisible WRITE showCounter)      // are the digits in the middle visible?
    Q_PROPERTY(float yellowThreshold READ yellowThreshold WRITE setYellowThreshold)
    Q_PROPERTY(float redThreshold READ redThreshold WRITE setRedThreshold)

public:
    QAnimatedTimer(QWidget *parent = NULL);

public Q_SLOTS:
    void start();
    void stop();
    void pause();
    void fadeIn(float secDuration = 2.0f);
    void fadeOut(float msDuration = 2.0f);
    void show();                // overloading from QWidget

    unsigned step() const;      // milliseconds between animation frames
    float value() const;
    unsigned dots() const;
    bool counterVisible() const;

    void setValue(float val);
    void setStep(unsigned val);
    void setDots(unsigned val);
    void showCounter(bool visible);

    void setThresholds(unsigned yellow, unsigned red);
    float yellowThreshold();
    void setYellowThreshold(float value);
    float redThreshold();
    void setRedThreshold(float value);

Q_SIGNALS:
    void valueChanged(float);

protected:
    void reset();

    void paintEvent(QPaintEvent *event); // Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event); // Q_DECL_OVERRIDE;

private:
    TIMER_STATE _state;
    FADING_DIRECTION _fading;
    float _opacity;
    float _fadeStep;
    bool _showCounter;
    float _value;
    float _yellowThreshold, _redThreshold;  // negative values mean that the threshold is ignored
    unsigned _msStep;
    unsigned _dots;                         // number of the individual dots around the circle
    QBasicTimer _timer;
};

#endif // __qanimatedtimer_h_INCLUDED__
