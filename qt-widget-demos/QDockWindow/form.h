#ifndef FORM_H
#define FORM_H

#include <QWidget>
/*
 made by www.hnmade.com
 */
namespace Ui {
    class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

public:
    QSize sizeHint() const
    {
        qDebug("%d: %d", this->width(), this->height());
        return QSize(this->width(), this->height());
    }

private:
    Ui::Form *ui;
};

#endif // FORM_H
