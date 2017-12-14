#ifndef BLOCK_H
#define BLOCK_H
#include <QtGui>
#include <QPoint>
#include <QRegExp>
#include <QLineEdit>
#include <QValidator>

class Block : public QWidget
{
    Q_OBJECT

public:
    Block(QWidget *parent=0);
    void changeColor(const QColor &color);
    int data();
    QPoint getPos();
    void setPos(const QPoint &p);
    void setPos(int x, int y);
    void setValue(int a);
    void setEna(bool ok);

private slots:
    void dataChange(const QString & data);

private:
    int da;
    QPoint p;
    QLineEdit *nubEidt;
};

#endif // BLOCK_H
