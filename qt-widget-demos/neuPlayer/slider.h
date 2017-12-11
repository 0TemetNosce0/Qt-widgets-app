#ifndef SLIDER_H
#define SLIDER_H

#include <QRect>
#include <QSlider>
#include <QMouseEvent>
#include <QStyleOptionSlider>

/*   Custom class for the typical QSlider
 *   The class is meant to replace the QSlider normal implementation completely
 *   It changes the behaviour of a click on the slider to actually click anywhere to go to a value, not only dragging the handle
 *   Created by Horoneru the 13/04/15
*/

class Slider : public QSlider
{
    Q_OBJECT

public:
    explicit Slider(QWidget *parent = 0);

private:
    void mousePressEvent(QMouseEvent *event);
};

#endif // SLIDER_H
