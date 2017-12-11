#ifndef SKINWIDGET_H
#define SKINWIDGET_H

#include <QWidget>

class skinWidget : public QWidget
{
    Q_OBJECT
public:
    explicit skinWidget(QString picName,QWidget *parent = 0);

signals:
    void changeSkin(QString);

private slots:
    void setSkin(QString);

protected:
    void paintEvent(QPaintEvent *);

private:
    QString bkPicName;

};

#endif // SKINWIDGET_H

/*
Æ¤·ô´°¿Ú
*/
