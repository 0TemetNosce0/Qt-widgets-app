#ifndef CLABEL_H
#define CLABEL_H

#include <QLabel>

class CLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CLabel(QWidget *parent = 0);

signals:
    void signalClicked();

public slots:

protected:
    bool m_bPressed;
    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // CLABEL_H
