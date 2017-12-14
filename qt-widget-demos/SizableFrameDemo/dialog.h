#ifndef DIALOG_H
#define DIALOG_H

#include <QRect>
#include <QPoint>
#include <QDialog>
#include <QCursor>
#include <QMouseEvent>

#define PADDING 2

namespace Ui {
class Dialog;
}

enum Direction{
    UP = 0,
    DOWN = 1,
    LEFT,
    RIGHT,
    LEFTTOP,
    LEFTBOTTOM,
    RIGHTBOTTOM,
    RIGHTTOP,
    NONE
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    void region(const QPoint &cursorPoint);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    bool isLeftPressDown;
    QPoint dragPosition;
    Direction dir;

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
