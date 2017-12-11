#ifndef QSLIDERWIDGET_H
#define QSLIDERWIDGET_H

#include <QWidget>

namespace Ui {
class QSliderWidget;
}

class QSliderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QSliderWidget(QWidget *parent = 0);
    ~QSliderWidget();

private slots:
    void on_btn_clicked();
    void slotsMousePosition(int ix,int iy);

private:
    Ui::QSliderWidget *ui;
};

#endif // QSLIDERWIDGET_H
