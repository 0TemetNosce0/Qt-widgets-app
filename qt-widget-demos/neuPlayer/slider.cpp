#include "slider.h"

Slider::Slider(QWidget *parent)
    : QSlider(parent)
{

}

void Slider::mousePressEvent(QMouseEvent * event)
{
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

    if (event->button() == (Qt::LeftButton) && !sr.contains(event->pos()))
    {
      int newVal;
      double halfHandleWidth = (0.5 * sr.width()) + 0.5; // Correct rounding
      int adaptedPosX = event->x();

      if (adaptedPosX < halfHandleWidth)
      {
          adaptedPosX = halfHandleWidth;
      }

      if ( adaptedPosX > width() - halfHandleWidth )
      {
          adaptedPosX = width() - halfHandleWidth;
      }
      // get new dimensions accounting for slider handle width
      double newWidth = (width() - halfHandleWidth) - halfHandleWidth;
      double normalizedPosition = (adaptedPosX - halfHandleWidth)  / newWidth ;

      newVal = minimum() + ((maximum()-minimum()) * normalizedPosition);

      if (invertedAppearance())
      {
          setValue( maximum() - newVal );
      }
      else
      {
          setValue(newVal);
      }

      emit sliderMoved(newVal);
      event->accept();
    }

    QSlider::mousePressEvent(event);
}
