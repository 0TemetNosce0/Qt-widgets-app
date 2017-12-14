#ifndef RUBBER_H
#define RUBBER_H

#include <QWidget>
#include <QRubberBand>

namespace Ui {
class Rubber;
}

class Rubber : public QWidget
{
    Q_OBJECT

public:
    explicit Rubber(QWidget *parent = 0);
    ~Rubber();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    QRubberBand *rubberBand;
    QPoint origin;

private:
    Ui::Rubber *ui;
};

#endif // RUBBER_H
