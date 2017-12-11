

#ifndef PICTUREFLOW_H
#define PICTUREFLOW_H

#include <qwidget.h>

class PictureFlowPrivate;

/*!
  Class PictureFlow implements an image show widget with animation effect 
  like Apple's CoverFlow (in iTunes and iPod). Images are arranged in form 
  of slides, one main slide is shown at the center with few slides on 
  the left and right sides of the center slide. When the next or previous 
  slide is brought to the front, the whole slides flow to the right or 
  the right with smooth animation effect; until the new slide is finally 
  placed at the center.

 */ 
class PictureFlow : public QWidget
{
Q_OBJECT

  Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
  Q_PROPERTY(QSize slideSize READ slideSize WRITE setSlideSize)
  Q_PROPERTY(int slideCount READ slideCount)
  Q_PROPERTY(int centerIndex READ centerIndex WRITE setCenterIndex)

public:

  enum ReflectionEffect
  {
    NoReflection,
    PlainReflection,
    BlurredReflection
  };

  /*!
    Creates a new PictureFlow widget.
  */  
  PictureFlow(QWidget* parent = 0);

  /*!
    Destroys the widget.
  */
  ~PictureFlow();

  /*!
    Returns the background color.
  */
  QColor backgroundColor() const;

  /*!
    Sets the background color. By default it is black.
  */
  void setBackgroundColor(const QColor& c);

  /*!
    Returns the dimension of each slide (in pixels).
  */  
  QSize slideSize() const;

  /*!
    Sets the dimension of each slide (in pixels).
  */  
  void setSlideSize(QSize size);

  /*!
    Returns the total number of slides.
  */
  int slideCount() const;

  /*!
    Returns QImage of specified slide.
  */  
  QImage slide(int index) const;

  /*!
    Returns the index of slide currently shown in the middle of the viewport.
  */  
  int centerIndex() const;

  /*!
    Returns the effect applied to the reflection.
  */  
  ReflectionEffect reflectionEffect() const;

  /*!
    Sets the effect applied to the reflection. The default is PlainReflection.
  */  
  void setReflectionEffect(ReflectionEffect effect);


public slots:

  /*!
    Adds a new slide.
  */  
  void addSlide(const QImage& image);

  /*!
    Adds a new slide.
  */  
  void addSlide(const QPixmap& pixmap);

  /*!
    Sets an image for specified slide. If the slide already exists,
    it will be replaced.
  */  
  void setSlide(int index, const QImage& image);

  /*!
    Sets a pixmap for specified slide. If the slide already exists,
    it will be replaced.
  */  
  void setSlide(int index, const QPixmap& pixmap);

  /*!
    Sets slide to be shown in the middle of the viewport. No animation 
    effect will be produced, unlike using showSlide.
  */  
  void setCenterIndex(int index);

  /*!
    Clears all slides.
  */
  void clear();

  /*!
    Shows previous slide using animation effect.
  */
  void showPrevious();

  /*!
    Shows next slide using animation effect.
  */
  void showNext();

  /*!
    Go to specified slide using animation effect.
  */
  void showSlide(int index);

  /*!
    Rerender the widget. Normally this function will be automatically invoked
    whenever necessary, e.g. during the transition animation.
  */
  void render();

  /*!
    Schedules a rendering update. Unlike render(), this function does not cause
    immediate rendering.
  */  
  void triggerRender();

signals:
  void centerIndexChanged(int index);

protected:
  void paintEvent(QPaintEvent *event);
  void keyPressEvent(QKeyEvent* event);
  void mousePressEvent(QMouseEvent* event);
  void resizeEvent(QResizeEvent* event);

private slots:
  void updateAnimation();

private:
  PictureFlowPrivate* d;
};

#endif // PICTUREFLOW_H

