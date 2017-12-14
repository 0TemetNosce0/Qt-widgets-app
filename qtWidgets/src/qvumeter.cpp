#include "qvumeter.h"

#include <QPainter>


QVUMeter::QVUMeter(QWidget *parent)
    : QWidget(parent)
{
    init();
}


float QVUMeter::value()
{
    return _value;
}


float QVUMeter::minimum()
{
    return _min;
}


float QVUMeter::maximum()
{
    return _max;
}


float QVUMeter::selection()
{
    return _selection;
}


bool QVUMeter::dimmed()
{
    return _dimmed;
}


void QVUMeter::setValue(float val)
{
    _value = val;
    if (_peak < _value)
    {
        _peak = _value;
    }
    emit valueChanged(val);
    update();
}


void QVUMeter::setMinimum(float m)
{
    _min = m;
    emit rangeChanged(_min, _max);
    update();
}


void QVUMeter::setMaximum(float m)
{
    _max = m;
    emit rangeChanged(_min, _max);
    update();
}


void QVUMeter::setRange(float min, float max)
{
    _min = min;
    _max = max;
    emit rangeChanged(_min, _max);
    update();
}


void QVUMeter::setThresholds(float yellow, float red)
{
    if (_min <= yellow && yellow <= red && red <= _max)
    {
        _yellowStep = yellow;
        _redStep = red;
        emit thresholdsChanged(_yellowStep, _redStep);
        update();
    }
}


void QVUMeter::setSelection(float val)
{
    _selection = val;
    emit selectionChanged(_selection);
    if (_showSelection)
    {
        update();
    }
}


void QVUMeter::setDimmed(bool val)
{
    _dimmed = val;
    update();
}


void QVUMeter::init() {
    _value = _peak = 1.f;
    _selection = 0.f;
    _min = 0.f;
    _yellowStep = 60.f;
    _redStep = 80.f;
    _max = 100.f;
    _tickSize = 10;
    _selectable = true;
    _showSelection = false;
    _dimmed = false;

    _timer.start(100, this);
}


void QVUMeter::mouseMoveEvent(QMouseEvent *pEvent)
{
    if (_showSelection)
    {
        _selection = _max - (_max - _min) * pEvent->y() / height();
        update();
    }
}


void QVUMeter::mousePressEvent(QMouseEvent *pEvent)
{
    if (_selectable)
    {
        _showSelection = true;
        _selection = _max - (_max - _min) * pEvent->y() / height();
        update();
    }
}


void QVUMeter::mouseReleaseEvent(QMouseEvent *pEvent) {
    if (_showSelection)
    {
        _showSelection = false;
        _selection = _max - (_max - _min) * pEvent->y() / height();
        emit selectionChanged(_selection);
        update();
    }
}


void QVUMeter::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    unsigned h = height();
    unsigned leds = h / _tickSize;

    float step = (_max - _min) / leds;
    unsigned iiPeak = (unsigned)((_peak - _min) / step);
    unsigned iiSelection = (unsigned)((_selection - _min) / step);
    QRect rect(2, 0, width() - 4, 0);

    for (unsigned ii = 0; ii < leds; ii++)
    {
        QColor color;
        float yy = _min + ii * step;

        // brush:
        if (_showSelection && ii == iiSelection)
        {
            static bool phase = false;
            phase = !phase;
            color = phase ? QColor(32, 128, 255) : QColor(32, 32, 32);
        }
        else if (yy > _value && ii != iiPeak)
        {
            color = QColor(32, 32, 32, _dimmed ? 72 : 255);
        }
        else if (yy > _redStep)
        {
            color = QColor(255, 32, 32, _dimmed ? 72 : 255);
        }
        else if (yy > _yellowStep)
        {
            color = QColor(255, 255, 32, _dimmed ? 72 : 255);
        }
        else
        {
            color = QColor(32, 255, 32, _dimmed ? 72 : 255);
        }
        painter.setBrush(color);

        // pen:
        if (ii == iiSelection)  // always visualize the selection via hilighted border
        {
            color = QColor(32, 128, 255);
        }
        else
        {
            color.setRed((int) (color.red() * .8));
            color.setGreen((int) (color.green() * .8));
            color.setBlue((int) (color.blue() * .8));
        }
        QPen pen(color);
        pen.setWidthF(1.2f);
        painter.setPen(pen);
        
        rect.setTop(2 + (leds - ii - 1) * _tickSize);
        rect.setBottom(-2 + (leds - ii) * _tickSize);
        painter.drawRoundedRect(rect, 2, 2);
    }
}


void QVUMeter::timerEvent(QTimerEvent * /*event */)
{
    float oldpeak = _peak;
    _peak = std::max(_peak - (_peak - _min) / 30 - (_max - _min) / 80, _min);
    if (oldpeak != _peak || _showSelection)
    {
        update();
    }
}
