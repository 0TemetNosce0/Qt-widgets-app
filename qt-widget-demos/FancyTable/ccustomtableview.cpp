#include "ccustomtableview.h"
#include <QDebug>
#include <QHeaderView>
#include <QPainter>
#include "ccustomheadermodel.h"
#include "ccustomheaderview.h"
#include <QPaintEvent>

cCustomTableView::cCustomTableView(QWidget *parent)
    : QTableView(parent)
{
    setMouseTracking(true);
}

void cCustomTableView::columnResized(int column, int oldWidth, int newWidth)
{
    updateGeometries();
    viewport()->update();
}

void cCustomTableView::paintEvent(QPaintEvent *event)
{
    QPainter painter(viewport());

    QHeaderView *_horizontalHeader = horizontalHeader();
    QHeaderView *_verticalHeader = verticalHeader();

    cCustomHeaderView *horizontalHeaderView = 0;

    horizontalHeaderView = qobject_cast<cCustomHeaderView *>(_horizontalHeader);

    cCustomHeaderModel *headerModel = 0;
    QVariant v(model()->data(QModelIndex(), cCustomHeaderView::HorizontalHeaderDataRole));

    if(v.isValid())
    {
        headerModel = qobject_cast<cCustomHeaderModel *>(v.value<QObject*>());
    }

    if(!headerModel)
    {
        qDebug() << "headerModel is zero";
        return;
    }

    int x = 0, y = 0;
    int xpos = 0, ypos = 0;
    int rowSpan, columnSpan;

    int firstVisualColumn = _horizontalHeader->visualIndexAt(0);
    int lastVisualColumn = _horizontalHeader->visualIndexAt(_horizontalHeader->viewport()->width());
    if(lastVisualColumn == -1)
    {
        lastVisualColumn = _horizontalHeader->count();
    }

    int firstVisualRow = qMax(_verticalHeader->visualIndexAt(0),0);
    int lastVisualRow = _verticalHeader->visualIndexAt(_verticalHeader->viewport()->height());
    if(lastVisualRow == -1)
    {
        lastVisualRow = _verticalHeader->count();
    }

    QMultiMap<int, int> blackList; // where not to draw cell

    int tempRow, tempCol;

    qDebug() << "current index" << currentIndex();

    for(int row = 0; row < model()->rowCount(); row++)
    {
        for(int col = 0; col < model()->columnCount(); col++)
        {
            QStyleOptionViewItem opt = viewOptions();
            opt.state |= QStyle::State_Enabled;

            QModelIndex index = model()->index(row, col, rootIndex());

            if(index.isValid())
            {
                if(index == currentIndex())
                {
                    opt.state |= QStyle::State_HasFocus;
                }

                if(state() != EditingState && index == mHover)
                {
                    opt.state |= QStyle::State_MouseOver;
                }

                if(selectionModel() && selectionModel()->isSelected(index))
                {
                    opt.state |= QStyle::State_Selected;
                }
            }

            tempRow = row;
            tempCol = col;
            xpos = x - horizontalOffset();
            ypos = y - verticalOffset();

            sSpan span = headerModel->getSpan(row % headerModel->rowCount(), col);

            rowSpan = span.numRows;
            columnSpan = span.numCols;

            firstVisualRow -= headerModel->rowCount();
            firstVisualRow = qMax(firstVisualRow, 0);

            firstVisualColumn -= headerModel->columnCount();
            firstVisualColumn = qMax(firstVisualColumn, 0);

            if(row >= firstVisualRow && row <= lastVisualRow && col >= firstVisualColumn && col <= lastVisualColumn)
            {
                if(columnSpan > 1 && rowSpan > 1)
                {
                    // draw spanned column and increase the column counter by the span value
                    opt.rect = QRect(xpos - 1, ypos - 1, sectionSizes(_horizontalHeader, col, columnSpan), sectionSizes(_verticalHeader, row, rowSpan));
                    x += sectionSizes(_horizontalHeader, col, columnSpan);
                    col += columnSpan - 1; // skip spanned columns
                }
                else if(columnSpan > 1)
                {
                    // draw spanned column and increase the column counter by the span value
                    opt.rect = QRect(xpos-1, ypos-1, sectionSizes(_horizontalHeader, col, columnSpan), _verticalHeader->sectionSize(row));
                    x += sectionSizes(_horizontalHeader, col, columnSpan);
                    col += columnSpan - 1; // skip spanned columns
                }
                else if(rowSpan > 1)
                {
                    // rows must be handled on a different way. not possible to jump over them, but we can blacklist them to not use later.
                    // draw spanned row and save the covered coordinates to avoid using them later...
                    opt.rect = QRect(xpos-1, ypos-1, _horizontalHeader->sectionSize(col), sectionSizes(_verticalHeader, row, rowSpan));

                    //sSpan span = headerModel->rs(row % headerModel->rowCount(), col);
                    if(span.row != span.top)
                    {
                        blackList.insert(col, row);
                    }
                    x += _horizontalHeader->sectionSize(col);
                }
                else
                {
                    opt.rect = QRect(xpos-1, ypos-1, _horizontalHeader->sectionSize(col), _verticalHeader->sectionSize(row));
                    x += _horizontalHeader->sectionSize(col);
                }

                QMultiMap<int, int>::iterator it = blackList.find(tempCol, tempRow);
                if(it == blackList.end())
                {
                    QModelIndex index = model()->index(tempRow,tempCol);
                    itemDelegate(index)->paint(&painter, opt, index);
                }
            }
            else
            {
                x += _horizontalHeader->sectionSize(col);
            }
        }
        x = 0;

        // todo: make better groupped rows (too much drawing here)
        if(y > 0 && row % headerModel->rowCount() == 0)
        {
            painter.drawLine(0, ypos - 1, viewport()->width(), ypos - 1);
        }

        y += _verticalHeader->sectionSize(row);
    }
}

QModelIndex cCustomTableView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    cCustomHeaderModel *headerModel = 0;
    QVariant v(model()->data(QModelIndex(), cCustomHeaderView::HorizontalHeaderDataRole));

    if(v.isValid())
    {
        headerModel = qobject_cast<cCustomHeaderModel *>(v.value<QObject*>());
    }

    if(!headerModel)
    {
        qDebug() << "headerModel is zero";
        return QModelIndex();
    }

    QModelIndex ci = currentIndex();
    QModelIndex ni;

    int row, col;
    sSpan span;

    switch(cursorAction)
    {
        case MovePrevious:
        case MoveLeft:
            ni = model()->index(ci.row(), ci.column()-1);

            if(!ni.isValid())
            {
                return ni;
            }

            row = ni.row();
            col = ni.column();

            span = headerModel->getSpan(ni.row() % headerModel->rowCount(), ni.column());
            if(span.isValid())
            {
                if(span.numRows > 1)
                {
                    row -= span.row - span.top;
                }

                if(span.numCols > 1)
                {
                    if(col > span.left)
                    {
                        col = span.left;
                    }
                }
            }
            ni = model()->index(row, col);
            return ni;
        break;
        case MoveNext:
        case MoveRight:
            ni = model()->index(ci.row(), ci.column()+1);
            if(!ni.isValid())
            {
                return ni;
            }
            row = ni.row();
            col = ni.column();
            span = headerModel->getSpan(ni.row() % headerModel->rowCount(), ni.column());

            if(span.isValid())
            {
                if(span.numRows > 1)
                {
                    row -= span.row - span.top;
                }

                if(span.numCols > 1)
                {
                    if(col > span.left)
                    {
                        col = span.left + span.numCols;
                    }
                }
            }
            ni = model()->index(row, col);
            return ni;
        break;
        case MoveDown:
            ni = model()->index(ci.row()+1, ci.column());
            if(!ni.isValid())
                return ni;
            row = ni.row();
            col = ni.column();
            span = headerModel->getSpan(ni.row() % headerModel->rowCount(), ni.column());
            if(span.isValid())
            {
                if(span.numRows > 1)
                    row += span.row-span.top;
                if(span.numCols > 1)
                {
                    if(col > span.left)
                        col = span.left;
                }
            }
            ni = model()->index(row, col);
            return ni;
        break;
        case MoveUp:
            ni = model()->index(ci.row()-1, ci.column());
            if(!ni.isValid())
                return ni;
            row = ni.row();
            col = ni.column();
            span = headerModel->getSpan(ni.row() % headerModel->rowCount(), ni.column());
            if(span.isValid())
            {
                if(span.numRows > 1)
                    row -= span.row-span.top;
                if(span.numCols > 1)
                {
                    if(col > span.left)
                        col = span.left;
                }
            }
            ni = model()->index(row, col);
            return ni;
        break;
        default:break;
    }

    return QModelIndex();
}

QRect cCustomTableView::visualRect(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return QRect();
    }

    cCustomHeaderModel *headerModel = 0;
    QVariant v(model()->data(QModelIndex(), cCustomHeaderView::HorizontalHeaderDataRole));
    if(v.isValid())
    {
        headerModel = qobject_cast<cCustomHeaderModel *>(v.value<QObject*>());
    }

    if(!headerModel)
    {
        qDebug() << "headerModel is zero";
        return QRect();
    }

    int row = index.row();
    int col = index.column();
    int spanHeight=1, spanWidth=1;
    sSpan span = headerModel->getSpan(row % headerModel->rowCount(), col);

    if(span.isValid() && span.numRows > 1 || span.numCols > 1)
    {
        spanHeight = sectionSizes(verticalHeader(), span.top, span.numRows);
        spanWidth = sectionSizes(horizontalHeader(), span.left, span.numCols);
    }
    else
    {
        return QTableView::visualRect(index);
    }

    return QRect(horizontalHeader()->sectionViewportPosition(index.column()), verticalHeader()->sectionViewportPosition(index.row()), spanWidth, spanHeight);
}

void cCustomTableView::setHoverIndex(const QPersistentModelIndex &index)
{
    if(mHover == index)
    {
        return;
    }
    mHover = index;
}

void cCustomTableView::mouseMoveEvent(QMouseEvent *event)
{
    QPersistentModelIndex index = indexAt(event->pos());
    setHoverIndex(index);
    QTableView::mouseMoveEvent(event);
}

bool cCustomTableView::viewportEvent(QEvent *event)
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
    return QTableView::viewportEvent(event);
}

QModelIndex cCustomTableView::indexAt(const QPoint &pos) const
{
    if(!model())
    {
        return QModelIndex();
    }

    cCustomHeaderModel *headerModel = 0;
    QVariant v(model()->data(QModelIndex(), cCustomHeaderView::HorizontalHeaderDataRole));

    if(v.isValid())
    {
        headerModel = qobject_cast<cCustomHeaderModel *>(v.value<QObject*>());
    }

    if(!headerModel)
    {
        qDebug() << "headerModel is zero";
        return QModelIndex();
    }

    int r = rowAt(pos.y());
    int c = columnAt(pos.x());

    if(r >= 0 && c >= 0)
    {
        sSpan span = headerModel->getSpan(r % headerModel->rowCount(), c);

        if(!span.isValid())
        {
            return QTableView::indexAt(pos);
        }

        if(span.numRows > 1)
        {
            r -= span.row-span.top;
        }

        if(span.numCols > 1)
        {
            c = span.left;
        }

        return model()->index(r, c, rootIndex()); // returns an index
    }

    return QModelIndex();
}

int cCustomTableView::sectionSizes(QHeaderView *hv, int col, int span) const
{
    int total=0;

    for(int i=col; i<col+span; i++)
    {
        total += hv->sectionSize(i);
    }

    return total;
}
