#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QLabel;

class Window : public QWidget
{
    Q_OBJECT
    
public:
    Window(QWidget *parent = 0);
    ~Window();
    QLabel *lbl;
};

#endif // WINDOW_H
