#ifndef TOOLLISTWIDGET_H
#define TOOLLISTWIDGET_H

#include <QDebug>
#include <QListWidget>
#include <QWheelEvent>
#include <QApplication>
#include <QListWidgetItem>

class ToolListWidget : public QListWidget
{

public:
    ToolListWidget(QWidget *parent = 0);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
};

#endif // TOOLLISTWIDGET_H
