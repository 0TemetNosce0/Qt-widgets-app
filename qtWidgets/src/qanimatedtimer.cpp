#include "qanimatedtimer.h"

#include <math.h>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

#define M_PI 3.1415
QAnimatedTimer::QAnimatedTimer(QWidget *parent)
    : QWidget(parent)
{
    reset();
}


void QAnimatedTimer::start()
{
    if (_state != TIMER_RUNNING)
    {
        if (_state == TIMER_STOPPED)
        {
            _value = 0;
        }
        _state = TIMER_RUNNING;
    }
}


void QAnimatedTimer::stop()
{
    _state = TIMER_STOPPED;
    _value = 0;
}


void QAnimatedTimer::pause()
{
    _state = TIMER_PAUSED;
}


void QAnimatedTimer::fadeIn(float secDuration)
{
    _fading = FADING_IN;
    _opacity = 0.f;
    _fadeStep = ((float)_msStep * .001f) / secDuration;
}


void QAnimatedTimer::fadeOut(float secDuration)
{
    _fading = FADING_OUT;
    _opacity = 1.f;
    _fadeStep = -((float)_msStep * .001f) / secDuration;
}


void QAnimatedTimer::show()
{
    QWidget::show();
    _fading = FADING_NONE;
    _opacity = 1.f;
}


unsigned QAnimatedTimer::step() const
{
    return _msStep;
}


float QAnimatedTimer::value() const
{
    return _value;
}


unsigned QAnimatedTimer::dots() const
{
    return _dots;
}


bool QAnimatedTimer::counterVisible() const
{
    return _showCounter;
}


void QAnimatedTimer::setValue(float val)
{
    _value = val;
    emit valueChanged(val);
    update();
}


void QAnimatedTimer::setStep(unsigned step)
{
    _msStep = step;
    _timer.stop();
    _timer.start(_msStep, this);
}


void QAnimatedTimer::setDots(unsigned val)
{
    _dots = val;
    update();
}


void QAnimatedTimer::showCounter(bool visible)
{
    _showCounter = visible;
    update();
}


void QAnimatedTimer::setThresholds(unsigned yellow, unsigned red)
{
    if (yellow <= red)
    {
        _yellowThreshold = yellow;
        _redThreshold = red;
        update();
    }
}


float QAnimatedTimer::yellowThreshold()
{
    return _yellowThreshold;
}


void QAnimatedTimer::setYellowThreshold(float value)
{
    _yellowThreshold = value;
}


float QAnimatedTimer::redThreshold()
{
    return _redThreshold;
}


void QAnimatedTimer::setRedThreshold(float value)
{
    _redThreshold = value;
}


void QAnimatedTimer::reset()
{
    _state = TIMER_STOPPED;
    _fading = FADING_NONE;
    _showCounter = true;
    _dots = 12;
    _value = 0.f;
    _msStep = 50;
    _redThreshold = 12.f;
    _yellowThreshold = 8.f;
    //_stepsSet = true;
    _opacity = 1.f;

    _timer.start(_msStep, this);
}


void QAnimatedTimer::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    float dxFull = width();
    float dyFull = height();
    float dxHalfDot, dyHalfDot;
    dxHalfDot = dyHalfDot = std::min(dxFull, dyFull) / (_dots * 1.4f);
    float xCenter = dxFull / 2.f;
    float yCenter = dyFull / 2.f;
    float dxUsable = dxFull - 2.5f * dxHalfDot;
    float dyUsable = dyFull - 2.5f * dyHalfDot;

    // 120 (third of 360) below means that we get full rotation in 3 seconds
    unsigned spot = (unsigned)(_value * 120) % 360; // the highlighted dot position, in degrees

    QColor fill(96, 96, 96, _opacity * 255);
    QColor hilight(64, 255, 64, _opacity * 255);
    if (_redThreshold > 0 && _value > _redThreshold)
    {
        hilight = QColor(255, 64, 64, _opacity * 255);
    }
    else if (_yellowThreshold > 0 && _value > _yellowThreshold)
    {
        hilight = QColor(255, 255, 64, _opacity * 255);
    }

    for (unsigned ii = 0; ii < _dots; ii++)
    {
        float brightness = std::max(0.f, 30.f - abs(360.f * ii / _dots - spot)) / 30.f;

        QPointF center((float)(xCenter + dxUsable * .5f * sin(2.f * M_PI * (float)ii/_dots)),
                       (float)(yCenter - dyUsable * .5f * cos(2.f * M_PI * (float)ii/_dots)));
        QRectF rect(center.x() - dxHalfDot - brightness,
                    center.y() - dyHalfDot - brightness,
                    (dxHalfDot + brightness) * 2,
                    (dyHalfDot + brightness) * 2);

        QColor color(fill.red() * (1.f - brightness) + hilight.red() * brightness,
                     fill.green() * (1.f - brightness) + hilight.green() * brightness,
                     fill.blue() * (1.f - brightness) + hilight.blue() * brightness,
                     _opacity * 255);
        painter.setBrush(QBrush(color));
        color.setRed((int)(color.red() * .8));
        color.setGreen((int)(color.green() * .8));
        color.setBlue((int)(color.blue() * .8));
        QPen pen(color);
        pen.setWidthF(1.8f);
        painter.setPen(pen);

        painter.drawRoundedRect(rect, 3 - brightness, 3 - brightness);
    }

    if (_showCounter)
    {
        painter.setBrush(QBrush(hilight));
        painter.setPen(QPen(fill));

        QPainterPath path;
        QFont font;
        font.setPointSize(dyFull / 4.5f);
        font.setStyleHint(QFont::SansSerif);
        font.setWeight(QFont::Black);
        QFontMetrics fm(font);
        QString text;
        text.sprintf("%.1f", _value);    /// TODO: figure out how many digits is needed
        path.addText((dxFull - fm.width(text)) / 2, (dyFull + fm.ascent() - 1) / 2, font, text);
        painter.drawPath(path);
    }
}


void QAnimatedTimer::timerEvent(QTimerEvent * /*event */)
{
    bool toUpdate = false;
    
    if (_state == TIMER_RUNNING)
    {
        _value += _msStep / 1000.f;
        toUpdate = true;
    }
    if (_fading != FADING_NONE)
    {
        _opacity += _fadeStep;
        if (_fading == FADING_OUT && _opacity < 0.f)
        {
            _opacity = 0.f;
            _fading = FADING_NONE;
        }
        else if (_fading == FADING_IN && _opacity > 1.f)
        {
            _opacity = 1.f;
            _fading = FADING_NONE;
        }
        toUpdate = true;
    }

    if (toUpdate)
    {
        update();
    }
}
