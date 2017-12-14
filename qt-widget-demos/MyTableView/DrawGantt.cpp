#include <QFontMetrics>
#include "DrawGantt.h"
#include "NodeManager.h"

#include <QTime>
#include <QMap>

QMap<int, int> RectWidth;

static int randomData(int row)
{
    static int flag = 0;
    if (flag == 0)
    {
        int size = NodeManager::getInstance()->sortMap().size();
    
        static int sincrese = 1;
        for (int i = 0; i < size; ++i)
        {
            int x = 0;
            QTime time;
            time= QTime::currentTime();
            qsrand(time.msec() + time.second() * 1000 + sincrese++);

            x = qrand() % 130 + 50;
        
            RectWidth[i] = x;
        }
    }
    
    flag = 1;

    return RectWidth[row];
}

DrawGantt::DrawGantt()
{

}

void DrawGantt::paintCell(QPainter *painter, const QRect &rect, int row)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    
    QFont font = painter->font();
    font.setPointSize(8);
    painter->setFont(font);
   
    painter->translate(rect.left(), rect.top());
    QString str1 = QStringLiteral("已完预算");

    int xoff = 0;
    int yoff = 2;

    int textYoff = 7;
    painter->drawText(QPoint(xoff, yoff + textYoff), str1);

    QFontMetrics fontMetrics(painter->font());
    int textHeight = fontMetrics.height();

    xoff = fontMetrics.width(str1) + 5;

    painter->setPen(Qt::red);
    painter->setBrush(QColor(Qt::red));

    int rectX = randomData(row);
    painter->drawRect(xoff, yoff, rectX, 10);
    
    painter->setPen(Qt::black);

    xoff = xoff + rectX + 5;
    QString str11 = "7.919";
    painter->drawText(QPoint(xoff, yoff + textYoff), str11);
/////////////////////////////////////////
    xoff = 0;
    yoff = textHeight + 4;
    painter->translate(xoff, yoff);

    yoff = 2;
	QString str2 = QStringLiteral("计划预算");
    painter->drawText(QPoint(xoff, yoff + textYoff), str2);

    xoff = fontMetrics.width(str2) + 5;

    painter->setPen(Qt::green);
    painter->setBrush(QColor(Qt::green));

    int rectX1 = randomData(row);
    painter->drawRect(xoff, yoff, rectX1, 10);
    
    painter->setPen(Qt::black);

    xoff = xoff + rectX1 + 5;
    QString str22 = "7.818";
    painter->drawText(QPoint(xoff, yoff + textYoff), str22);

    painter->restore();
}
