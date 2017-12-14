#ifndef CUSTOMLCDNUMBER_H
#define CUSTOMLCDNUMBER_H

#define LCDNUMBER_SPACE 2

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class CustomLCDNumber : public QWidget
{
    Q_OBJECT

public:
    explicit CustomLCDNumber(QWidget *parent = 0);

signals:

public slots:
    void setNumber(int num);

protected:
    QSize sizeHint() const
    {
        return QSize(20,30);
    }

    QSize minimumSizeHint() const
    {
        return QSize(10,15);
    }

    void paintEvent(QPaintEvent *);

private:
    void drawVariables(QPainter* painter);
    void drawBackground(QPainter* painter);
    void drawNumber(QPainter* painter);

private:
    int m_nNum;
    qreal m_min;
    qreal m_rectWidth;
    QPointF m_center;
    void initVariables();
};

#endif // CUSTOMLCDNUMBER_H
