#include <QSize>
#include <QDebug>
#include <QPainter>
#include <QTableView>
#include <QPaintEvent>
#include <QModelIndex>
#include <QStyledItemDelegate>

#include "ccustomheaderview.h"
#include "ccustomheadermodel.h"

#include "cheaderitemdelegate.h"

cCustomHeaderView::cCustomHeaderView(QWidget *parent)
    : QHeaderView(Qt::Horizontal, parent)
{
    connect(this, SIGNAL(sectionResized(int, int, int)), this, SLOT(onSectionResized(int, int, int)));

    cHeaderItemDelegate *delegate = new cHeaderItemDelegate;
    setItemDelegate(delegate);
}

void cCustomHeaderView::onSectionResized(int logicalIndex, int oldSize, int newSize)
{
    //todo: do tricks here to simultaneously resize other columns based on hierarchy
    viewport()->update();
}

QSize cCustomHeaderView::sectionSizeFromContents(int logicalIndex) const
{
    QSize size;
    int maxWidth = 0;
    cCustomHeaderModel *headerModel = 0;
    QVariant v(model()->data(QModelIndex(), HorizontalHeaderDataRole));

    if(v.isValid())
    {
        if((headerModel = qobject_cast<cCustomHeaderModel *>(v.value<QObject*>())) !=0)
        {
            for(int i=0; i<headerModel->rowCount(); ++i)
            {
                if(headerModel->item(i, logicalIndex)) // measure only if have valid item on the given coordinates
                {
                    QFont fnt;
                    QStyleOptionHeader opt;
                    initStyleOption(&opt);
                    fnt.setBold(true);
                    opt.text = headerModel->item(i, logicalIndex)->data(Qt::DisplayRole).toString();
                    opt.fontMetrics = QFontMetrics(fnt);
                    size = style()->sizeFromContents(QStyle::CT_HeaderSection, &opt, QSize(), this);
                    maxWidth = qMax(maxWidth, size.width());
                }
            }
            return QSize(maxWidth + minimumSectionSize(), size.height() * headerModel->rowCount());
        }
        else
        {
            return QSize(defaultSectionSize(), 100); // 100 as height, is that good?
        }
    }
    else
    {
        return QHeaderView::sectionSizeFromContents(logicalIndex);
    }
}

QModelIndex cCustomHeaderView::indexAt(const QPoint &pos) const
{
    cCustomHeaderModel *headerModel = 0;
    QVariant v(model()->data(QModelIndex(), HorizontalHeaderDataRole));

    if(v.isValid())
    {
        headerModel = qobject_cast<cCustomHeaderModel *>(v.value<QObject*>());
    }

    if(!headerModel)
    {
        return QModelIndex();
    }

    int x = pos.x();
    int y = pos.y();

    for(QList<cRect>::const_iterator it = m_RectList.begin(); it != m_RectList.end(); ++it)
    {
        cRect r = *it;

        if(x > r.mRect.x() && x < r.mRect.x() + r.mRect.width() &&
                y > r.mRect.y() && y < r.mRect.y() + r.mRect.height())
        {
            return headerModel->index(r.mRow, r.mCol);
        }
    }

    return QModelIndex();
}

bool cCustomHeaderView::event(QEvent *e)
{
    switch(e->type())
    {
        case QEvent::HoverEnter:
            QHoverEvent *he = static_cast<QHoverEvent*>(e);
            qDebug() << "indexat" << indexAt(he->pos());
        break;
    }

    return QHeaderView::event(e);
}

void cCustomHeaderView::paintEvent(QPaintEvent *e)
{
    cCustomHeaderModel *headerModel = 0;
    QVariant v(model()->data(QModelIndex(), HorizontalHeaderDataRole));

    if(v.isValid())
    {
        headerModel = qobject_cast<cCustomHeaderModel *>(v.value<QObject*>());
    }

    if(!headerModel)
    {
        return QHeaderView::paintEvent(e);
    }

    int i;

    QPainter painter(viewport());

    QMultiMap<int, int> blackList;

    m_RectList.clear();
    int tempRow, tempCol;

    for(int cr = 0; cr < headerModel->rowCount(); ++cr)
    {
        for(int cc = 0; cc < headerModel->columnCount(); ++cc)
        {
            tempRow = cr;
            tempCol = cc;

            QStyleOptionViewItemV4 opt = viewOptions();

            QStyleOptionHeader header_opt;
            initStyleOption(&header_opt);

            header_opt.textAlignment = Qt::AlignCenter;

            QFont fnt;
            fnt.setBold(true);
            header_opt.fontMetrics = QFontMetrics(fnt);

            opt.fontMetrics = QFontMetrics(fnt);
            QSize size = style()->sizeFromContents(QStyle::CT_HeaderSection, &header_opt, QSize(), this);

            /*
            if (count() == 1)
                header_opt.position = QStyleOptionHeader::OnlyOneSection;
            else if(visualIndex(i) == 0)
                header_opt.position = QStyleOptionHeader::Beginning;
            else if (visualIndex(i) == count() - 1)
                header_opt.position = QStyleOptionHeader::End;
            else
                header_opt.position = QStyleOptionHeader::Middle;
            */

            header_opt.position = QStyleOptionHeader::Middle;

            if(mHover == headerModel->index(cr, cc))
            {
                header_opt.state |= QStyle::State_MouseOver;
            }

            if(headerModel->item(cr, cc))
            {
                opt.text = headerModel->item(cr, cc)->data(Qt::DisplayRole).toString();
                header_opt.text = headerModel->item(cr, cc)->data(Qt::DisplayRole).toString();
            }

            sSpan span = headerModel->getSpan(cr, cc);

            int rowSpan = span.numRows;
            int columnSpan = span.numCols;

            if(columnSpan > 1 && rowSpan > 1)
            {
                // draw spanned column and increase the column counter by the span value
                header_opt.rect = QRect(sectionViewportPosition(logicalIndex(cc)), cr*size.height(), sectionSizes(cc, columnSpan), rowSpan * size.height());
                opt.rect = header_opt.rect;
                cc += columnSpan - 1; // skip spanned columns
            }
            else if(columnSpan > 1)
            {
                // draw spanned column and increase the column counter by the span value
                header_opt.rect = QRect(sectionViewportPosition(logicalIndex(cc)), cr*size.height(), sectionSizes(cc, columnSpan), size.height());
                opt.rect = header_opt.rect;
                cc += columnSpan - 1; // skip spanned columns
            }
            else if(rowSpan > 1)
            {
                // draw spanned row and save the covered coordinates to avoid using them later...
                header_opt.rect = QRect(sectionViewportPosition(logicalIndex(cc)), cr*size.height(), sectionSize(logicalIndex(cc)), size.height() * rowSpan);
                opt.rect = header_opt.rect;
                for(i = cr+1; i<=rowSpan-1; ++i)
                {
                    blackList.insert(i, cc);
                }
            }
            else
            {
                // this is a normal column, just draw it...
                header_opt.rect = QRect(sectionViewportPosition(logicalIndex(cc)), cr*size.height(), sectionSize(logicalIndex(cc)), size.height());
                opt.rect = header_opt.rect;
            }

            opt.state = header_opt.state;

            QMultiMap<int, int>::iterator it = blackList.find(tempRow, tempCol);
            if(it == blackList.end())
            {
                // will be used by indexAt(pos);
                m_RectList.append(cRect(tempRow, tempCol, header_opt.rect));

                //style()->drawControl(QStyle::CE_Header, &header_opt, &painter, this);
                itemDelegate()->paint(&painter, opt, headerModel->index(tempRow, tempCol,QModelIndex()));
            }
        }
    }
}

bool cCustomHeaderView::viewportEvent(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::HoverEnter:
            setHoverIndex(indexAt(static_cast<QHoverEvent*>(event)->pos()));
            break;
        case QEvent::HoverLeave:
            setHoverIndex(QModelIndex());
            break;
        default:
            break;
    }
    return QHeaderView::viewportEvent(event);
}


void cCustomHeaderView::mouseMoveEvent(QMouseEvent *event)
{
    QPersistentModelIndex index = indexAt(event->pos());
    setHoverIndex(index);
    viewport()->update();
    QHeaderView::mouseMoveEvent(event);
}

void cCustomHeaderView::setHoverIndex(const QPersistentModelIndex &index)
{
    if(mHover == index)
    {
        return;
    }
    mHover = index;
}

void cCustomHeaderView::mouseReleaseEvent(QMouseEvent *e)
{
    cCustomHeaderModel *headerModel = 0;
    QVariant v(model()->data(QModelIndex(), HorizontalHeaderDataRole));

    if(v.isValid())
    {
        headerModel = qobject_cast<cCustomHeaderModel *>(v.value<QObject*>());
    }

    if(!headerModel)
    {
        return QHeaderView::mouseReleaseEvent(e);
    }

    QStyleOptionViewItemV4 opt = viewOptions();
    if(e && itemDelegate())
    {
        itemDelegate()->editorEvent(e, headerModel, opt, indexAt(e->pos()));
        viewport()->update();
    }

    qDebug() << indexAt(e->pos());

    /*
    QWidget *w = itemDelegate()->createEditor(this, opt, indexAt(e->pos()));
    w->show();
    w->setFocus();
    */

    return QHeaderView::mouseReleaseEvent(e);
}

int cCustomHeaderView::sectionSizes(int lIndex, int sectionCount)
{
    // todo: check wether section is visible or not
    int width = 0;

    for(int i = lIndex; i < lIndex + sectionCount; ++i)
    {
        width += sectionSize(i);
    }

    return width;
}

int cCustomHeaderView::sectionSizes()
{
    // todo: check wether section is visible or not
    int width = 0;

    for(int i = 0; i < count(); ++i)
    {
        width += sectionSize(i);
    }

    return width;
}
