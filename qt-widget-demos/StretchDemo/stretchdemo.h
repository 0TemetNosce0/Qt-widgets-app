#ifndef STRETCHDEMO_H
#define STRETCHDEMO_H

#include <QMainWindow>
#include <QPushButton>


namespace Ui {
class StretchDemo;
}

class StretchDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit StretchDemo(QWidget *parent = 0);
    ~StretchDemo();

private:
    Ui::StretchDemo *ui;

    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
};

#endif // STRETCHDEMO_H
