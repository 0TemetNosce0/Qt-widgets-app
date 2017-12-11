#ifndef DEMO_H
#define DEMO_H

#include <QWidget>
#include "ui_colorwidget.h"

class ColorWidget : public QWidget
{
    Q_OBJECT

public:
    ColorWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~ColorWidget();

private slots:
    void on_colorWidget_highlighted(const QColor &color);
    void on_colorWidget_picked(const QColor &color);

    void on_slCellSize_valueChanged(int);
    void on_slCellWidth_valueChanged(int);

    void on_cbScheme_activated(int index);

private:
    Ui::ColorWidget* ui;
};

#endif // DEMO_H
