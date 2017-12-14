/**

@author Calle Laakkonen

@section License

    Copyright (C) 2014 Calle Laakkonen

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Color Widgets.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "hue_slider.hpp"

class HueSlider::Private
{
private:
    HueSlider *w;

public:
    qreal saturation;
    qreal value;

    Private(HueSlider *widget) : w(widget), saturation(1), value(1)
    {
        updateGradient();
    }

    void updateGradient()
    {
        static const double n_colors = 6;
        QGradientStops colors;
        colors.reserve(n_colors+1);
        for(int i=0;i<=n_colors;++i)
        {
            colors.append(QGradientStop(i/n_colors, QColor::fromHsvF(i/n_colors, saturation, value)));
        }
        w->setColors(colors);
    }
};

HueSlider::HueSlider(QWidget *parent)
    : Gradient_Slider(parent)
    , p(new Private(this))
{

}

HueSlider::HueSlider(Qt::Orientation orientation, QWidget *parent)
    : Gradient_Slider(orientation, parent)
    , p(new Private(this))
{

}

HueSlider::~HueSlider()
{
    delete p;
}

qreal HueSlider::colorSaturation() const
{
    return p->saturation;
}

void HueSlider::setColorSaturation(qreal s)
{
    p->saturation = qBound(0.0, s, 1.0);
    p->updateGradient();
}

qreal HueSlider::colorValue() const
{
    return p->value;
}

void HueSlider::setColorValue(qreal v)
{
    p->value = qBound(0.0, v, 1.0);
    p->updateGradient();
}

