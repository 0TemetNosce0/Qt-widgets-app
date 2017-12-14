#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QPaintEvent>

namespace Ui {
class paintWidget;
}

class paintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit paintWidget(QWidget *parent = 0);
    ~paintWidget();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::paintWidget *ui;

    int m_nbMousePressed;
    int m_nInitialX;
    int m_nInitialY;
    int m_nFinalX;
    int m_nFinalY;
    QPixmap *m_nPTargetPixmap;
};

#endif // PAINTWIDGET_H
