#include "diagtableheader.h"

#include <math.h>

#include <QPainter>
#include <QTableWidget>
#include <QStylePainter>

DiagTableHeader::DiagTableHeader(QWidget* parent)
    : QHeaderView(Qt::Horizontal, parent)
{

}

int DiagTableHeader::sectionSizeHint(int logicalIndex) const
{
    QSize size = ((QTableWidget*)parentWidget())->horizontalHeaderItem(logicalIndex)->sizeHint();
    int diag = sqrt((double)pow((double)size.height(), 2) + pow((double)size.width(), 2));
    return diag;
}

QSize DiagTableHeader::sizeHint() const
{
    QSize size = QHeaderView::sizeHint();
    int diag = sqrt(pow((double)size.height(), 2) + pow((double)size.width(), 2));
    size.setHeight(diag); // leave the width the same right now
    return size;
}

void DiagTableHeader::paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const
{
    painter->rotate(-45);
    QTableWidgetItem* widget = ((QTableWidget*)parentWidget())->horizontalHeaderItem(logicalIndex);
    QStyleOption opt;
    opt.initFrom(this->viewport());
    QStylePainter sect(this->viewport());
    sect.rotate(-45);
    sect.drawControl(QStyle::CE_HeaderSection, opt); // this doesn't seem to do anything
    if (widget)
    {
        painter->drawText(rect.left(), rect.bottom(), widget->text());
    }
    else
    {
        painter->drawText(rect.left(), rect.bottom(), "123");
    }
}

