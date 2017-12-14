#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QPushButton>

class CustomPushButton : public QPushButton
{
public:
    explicit CustomPushButton(QString imagePath, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap pic;
    QString m_imagePath;
};

#endif // CUSTOMPUSHBUTTON_H
