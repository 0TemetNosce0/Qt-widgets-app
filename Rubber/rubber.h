#ifndef RUBBER_H
#define RUBBER_H
#include <QWidget>
#include <QRubberBand>
#include <QPoint>
class Rubber :  public QWidget
{
   Q_OBJECT
public:
   Rubber(QWidget *parent= 0);
   ~Rubber();
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);

private:
  QRubberBand *rubberBand;
  QPoint origin;
};

#endif // RUBBER_H
