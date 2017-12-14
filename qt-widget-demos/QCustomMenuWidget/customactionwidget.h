#ifndef CUSTOMACTIONWIDGET_H
#define CUSTOMACTIONWIDGET_H

#include <QPushButton>
#include <QVboxLayout>
#include <QWidget>
#include <qcoreevent.h>

class CustomActionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomActionWidget(QWidget *parent = 0);

signals:
    void hovered();
    void buttonClicked();

protected:
    virtual bool eventFilter(QObject *obj, QEvent *ev);

private:
    QPushButton* buttonOne;
    QPushButton* buttonTwo;
    QVBoxLayout* layout;
};

#endif // CUSTOMACTIONWIDGET_H
