#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

//class CLabel;

class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(QWidget *parent = 0);
    void setText(QPixmap pixmap, QString name, QString info);
    void setText(QString info);

signals:

public slots:

private:
    QLabel *labelIcon;
    QLabel *labelName;
    QLabel *labelInfo;

    QHBoxLayout *horLayout;
    QVBoxLayout *verlayout;

protected:
    bool event(QEvent *e);
};

#endif // ITEMWIDGET_H
