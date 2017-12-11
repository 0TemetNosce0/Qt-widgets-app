#ifndef VINBUTTON_H
#define VINBUTTON_H

#include <QPushButton>

class vinButton : public QPushButton
{
    Q_OBJECT

public:
    explicit vinButton(QWidget *parent = 0);

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // VINBUTTON_H
