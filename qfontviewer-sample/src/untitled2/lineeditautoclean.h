#ifndef LINEEDITAUTOCLEAN_H
#define LINEEDITAUTOCLEAN_H

#include <QLineEdit>
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>

class LineEditAutoclean : public QLineEdit
{
    Q_OBJECT

public:
    LineEditAutoclean(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif
