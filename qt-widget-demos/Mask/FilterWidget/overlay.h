#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
#include <QPointer>

class OverLay : public QWidget
{
    Q_OBJECT

public:
    explicit OverLay(QWidget * parent = 0);

protected:
    void paintEvent(QPaintEvent *);
};

class Filter : public QObject
{
public:
    Filter(QObject * parent = 0);

protected:
    bool eventFilter(QObject * obj, QEvent * ev);

private:
    QPointer<OverLay> m_overlay;
    QPointer<QWidget> m_overlayOn;
};

#endif // OVERLAY_H
