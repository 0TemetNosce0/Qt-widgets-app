#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QWidget>

namespace Ui {
class OverlayWidget;
}

class OverlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OverlayWidget(QWidget *parent = 0);
    ~OverlayWidget();

protected:
    //! Catches resize and child events from the parent widget
    bool eventFilter(QObject * obj, QEvent * ev);

    //! Tracks parent widget changes
    bool event(QEvent* ev);

private:
    Ui::OverlayWidget *ui;
};

class ContainerWidget : public QWidget
{
public:
    explicit ContainerWidget(QWidget * parent = 0);

    inline void setSize(QObject * obj)
    {
        if (obj->isWidgetType()) static_cast<QWidget*>(obj)->setGeometry(rect());
    }
protected:
    //! Resizes children to fill the extent of this widget
    bool event(QEvent * ev);
    //! Keeps the children appropriately sized
    void resizeEvent(QResizeEvent *);
};

class LoadingOverlay : public OverlayWidget
{
public:
    LoadingOverlay(QWidget * parent = 0);

protected:
    void paintEvent(QPaintEvent *);

};


#endif // OVERLAYWIDGET_H
