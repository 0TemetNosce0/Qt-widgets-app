#ifndef IRREGULARFORM_H
#define IRREGULARFORM_H

#include <QWidget>

class IrregularForm : public QWidget
{
    Q_OBJECT

public:
    explicit IrregularForm(QWidget *parent = 0);
    ~IrregularForm();

Q_SIGNALS:
    void irregularFormClicked();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

private:
    QPixmap pic;
};

#endif // IRREGULARFORM_H
