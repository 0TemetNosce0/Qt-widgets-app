#ifndef IRREGULARFORM_H
#define IRREGULARFORM_H

#include <QWidget>

class IrregularForm : public QWidget
{
    Q_OBJECT

public:
    explicit IrregularForm(QWidget *parent = 0);
    ~IrregularForm();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap pic;

};

#endif // IRREGULARFORM_H
