#ifndef CUSTOMINDICATOR_H
#define CUSTOMINDICATOR_H

#include <QWidget>

#include "customlcdnumber.h"

const int INDICATOR_COUNT = 3;
const int INDICATOR_PEN_WIDTH = 2;
const QColor INDICATOR_FRAME_COLOR = QColor(255, 170, 0);
const QColor INDICATOR_GRAPH_COLOR = QColor(85, 255, 0);

class CustomIndicator : public QWidget
{
    Q_OBJECT

public:
    explicit CustomIndicator(QWidget *parent = 0);
    void setForeColor(QColor c);

protected:
    QSize sizeHint() const
    {
        return QSize(70,300);
    }

    QSize minimumSizeHint() const
    {
        return QSize(80,200);
    }

    void paintEvent(QPaintEvent *);

private:
    void drawVariables(QPainter* painter);
    void drawBackground(QPainter* painter);
    void drawLCDNums(QPainter* painter);
    void drawRect(QPainter* painter);
    void drawBars(QPainter* painter);
    void drawGraph(QPainter* painter);

private:
    void initVariables();

private:
    CustomLCDNumber* lcd[INDICATOR_COUNT];
    qreal m_leftSpace;
    qreal m_topSpace;
    qreal m_lcdWidth;
    qreal m_lcdHeight;
    int m_value;
    int m_currValue;
    bool m_bReverse;

    QTimer* updateTimer;
    QPointF m_rectTopLeft;
    QPointF m_rectBottomRight;
    QColor forecolor;

private slots:
    void UpdateData();

public slots:
    void setValue(int value);
};

#endif // CUSTOMINDICATOR_H
