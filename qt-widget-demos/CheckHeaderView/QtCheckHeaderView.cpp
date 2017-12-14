#include "QtCheckHeaderView.h"

#include <QMouseEvent>
#include <QApplication>
#include <QPainter>
#include <QStyleOptionViewItem>

QRect QtCheckHeaderView::checkRect(const QStyleOptionHeader& option, const QRect& bounding) const
{
    QStyleOptionButton opt;
    opt.QStyleOption::operator=(option);
    opt.rect = bounding;
    QRect cr = style()->subElementRect(QStyle::SE_ViewItemCheckIndicator, &opt);

    if (orientation() == Qt::Horizontal)
    {
        int deltaY = (bounding.height() - cr.height()) / 2;
        return QRect(bounding.left() + 2, bounding.top() + deltaY, cr.width(), cr.height());
    }
    else if (orientation() == Qt::Vertical)
    {
        int deltaX = (bounding.width() - cr.width()) / 2;
        return QRect(bounding.left() + deltaX, bounding.top() + 2, cr.width(), cr.height());
    }
    return QRect();
}

QtCheckHeaderView::QtCheckHeaderView(Qt::Orientation orientation, QWidget *parent)
    :QHeaderView(orientation, parent), blockDataChanged(false)
{

}

QtCheckHeaderView::~QtCheckHeaderView()
{

}

void QtCheckHeaderView::setModel(QAbstractItemModel* model)
{
    mSectionRects.clear();
    QHeaderView::setModel(model);

    foreach(int logicalIndex, mCheckableIndexes)
    {
        updateCheckbox(logicalIndex);
    }
}

void QtCheckHeaderView::dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
    if (blockDataChanged)
        return;

    if (orientation() == Qt::Horizontal)
    {
        for (int i = topLeft.column(); i <= bottomRight.column(); ++i)
        {
            if (mCheckableIndexes.contains(i))
            {
                updateCheckbox(i);
                updateSection(i);
            }
        }
    }
    else if (orientation() == Qt::Vertical)
    {
        for (int i = topLeft.row(); i <= bottomRight.row(); ++i)
        {
            if (mCheckableIndexes.contains(i))
            {
                updateCheckbox(i);
                updateSection(i);
            }
        }
    }
}

void QtCheckHeaderView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        int logicalIndex = logicalIndexAt(event->pos());
        QStyleOptionHeader opt;
        initStyleOption(&opt);
        QRect rect = checkRect(opt, mSectionRects.value(logicalIndex));
        if (rect.contains(event->pos()))
        {
            if (mCheckableIndexes.contains(logicalIndex))
            {
                blockDataChanged = true;
                if (mCheckStates.value(logicalIndex) == Qt::Checked)
                {
                    mCheckStates.insert(logicalIndex, Qt::Unchecked);
                }
                else if (mCheckStates.value(logicalIndex) == Qt::Unchecked)
                {
                    mCheckStates.insert(logicalIndex, Qt::Checked);
                }
                else if (mCheckStates.value(logicalIndex) == Qt::PartiallyChecked)
                {
                    mCheckStates.insert(logicalIndex, Qt::Checked);
                }
                updateModel(logicalIndex);
                blockDataChanged = false;
                updateCheckbox(logicalIndex);
                updateSection(logicalIndex);
                return;
            }
        }
    }

    QHeaderView::mousePressEvent(event);
}

void QtCheckHeaderView::paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const
{
    mSectionRects.insert(logicalIndex, rect);
    if (mCheckableIndexes.contains(logicalIndex))
    {
        painter->save();

        QStyleOptionHeader opt;
        initStyleOption(&opt);
        QStyle::State state = QStyle::State_None;
        if (isEnabled())
            state |= QStyle::State_Enabled;
        if (window()->isActiveWindow())
            state |= QStyle::State_Active;

        QPoint cursorPos = mapFromGlobal(cursor().pos());
        bool containMouse = rect.contains(cursorPos);
        if (this->sectionsClickable())
        {
            if (containMouse)
                state |= QStyle::State_MouseOver;
            if (containMouse && (QApplication::mouseButtons() && (Qt::LeftButton || Qt::RightButton)))
                state |= QStyle::State_Sunken;
            else if (highlightSections())
            {
                if (sectionIntersectsSelection(logicalIndex))
                    state |= QStyle::State_On;
            }
        }

        // setup the style options structure
        QVariant textAlignment = model()->headerData(logicalIndex, orientation(), Qt::TextAlignmentRole);
        opt.rect = rect;
        opt.section = logicalIndex;
        opt.state |= state;
        opt.textAlignment = Qt::Alignment(textAlignment.isValid() ? Qt::Alignment(textAlignment.toInt())
                                                                  : defaultAlignment());

        if (isSortIndicatorShown())
        {
            if (sortIndicatorSection() == logicalIndex)
            {
                if (sortIndicatorOrder() == Qt::AscendingOrder)
                {
                    opt.sortIndicator = QStyleOptionHeader::SortDown;
                }
                else
                {
                    opt.sortIndicator = QStyleOptionHeader::SortUp;
                }
            }
        }
        else
        {
            opt.sortIndicator = QStyleOptionHeader::None;
        }

        opt.iconAlignment = Qt::AlignVCenter;

        QVariant variant = model()->headerData(logicalIndex, orientation(), Qt::DecorationRole);
        opt.icon = qvariant_cast<QIcon> (variant);
        if (opt.icon.isNull())
            opt.icon = qvariant_cast<QPixmap> (variant);
        QVariant foregroundBrush = model()->headerData(logicalIndex, orientation(), Qt::ForegroundRole);
        if (foregroundBrush.canConvert<QBrush>())
            opt.palette.setBrush(QPalette::ButtonText, qvariant_cast<QBrush> (foregroundBrush));

        QVariant backgroundBrush = model()->headerData(logicalIndex, orientation(), Qt::BackgroundRole);
        if (backgroundBrush.canConvert<QBrush>())
        {
            opt.palette.setBrush(QPalette::Button, qvariant_cast<QBrush> (backgroundBrush));
            opt.palette.setBrush(QPalette::Window, qvariant_cast<QBrush> (backgroundBrush));
            painter->setBrushOrigin(opt.rect.topLeft());
        }

        // the section position
        int visual = visualIndex(logicalIndex);
        Q_ASSERT(visual != -1);
        if (count() == 1)
            opt.position = QStyleOptionHeader::OnlyOneSection;
        else if (visual == 0)
            opt.position = QStyleOptionHeader::Beginning;
        else if (visual == count() - 1)
            opt.position = QStyleOptionHeader::End;
        else
            opt.position = QStyleOptionHeader::Middle;
        opt.orientation = orientation();
        // the selected position
        bool previousSelected = sectionIntersectsSelection(this->logicalIndex(visual - 1));
        bool nextSelected = sectionIntersectsSelection(this->logicalIndex(visual + 1));
        if (previousSelected && nextSelected)
            opt.selectedPosition = QStyleOptionHeader::NextAndPreviousAreSelected;
        else if (previousSelected)
            opt.selectedPosition = QStyleOptionHeader::PreviousIsSelected;
        else if (nextSelected)
            opt.selectedPosition = QStyleOptionHeader::NextIsSelected;
        else
            opt.selectedPosition = QStyleOptionHeader::NotAdjacent;
        // draw the section
        style()->drawControl(QStyle::CE_Header, &opt, painter, this);
        painter->restore();

        opt.text = model()->headerData(logicalIndex, orientation(), Qt::DisplayRole).toString();
        if (textElideMode() != Qt::ElideNone)
            opt.text = opt.fontMetrics.elidedText(opt.text, textElideMode(), rect.width() - 4);

        QRect check = checkRect(opt, opt.rect);

        if (orientation() == Qt::Horizontal)
        {
            opt.rect.setLeft(check.right());
        } else if (orientation() == Qt::Vertical)
        {
            opt.rect.setTop(check.bottom());
        }

        style()->drawControl(QStyle::CE_HeaderLabel, &opt, painter, this);


        // ===============================================================
        // Draw checkbox
        QStyleOptionButton option;
        option.QStyleOption::operator =(opt);
        option.rect = checkRect(opt, rect);
        //option.rect = QRect(10, 10, 10, 10);

        switch (mCheckStates.value(logicalIndex))
        {
        case Qt::Checked:
            option.state |= QStyle::State_On;
            break;
        case Qt::Unchecked:
            option.state |= QStyle::State_Off;
            break;
        case Qt::PartiallyChecked:
            option.state |= QStyle::State_NoChange;
            break;
        }
        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);

        // ===============================================================
    }
    else
    {
        QHeaderView::paintSection(painter, rect, logicalIndex);
    }
}

void QtCheckHeaderView::updateCheckbox(int logicalIndex)
{
    bool allchecked = true;
    bool allunchecked = true;

    if (orientation() == Qt::Horizontal)
    {
        for (int i = 0; i < model()->rowCount(rootIndex()); ++i)
        {
            if (model()->index(i, logicalIndex, rootIndex()).data(Qt::CheckStateRole).toInt())
            {
                allunchecked = false;
            }
            else
            {
                allchecked = false;
            }
        }
    }
    else if (orientation() == Qt::Vertical)
    {
        for (int i = 0; i < model()->columnCount(rootIndex()); ++i)
        {
            if (model()->index(logicalIndex, i, rootIndex()).data(Qt::CheckStateRole).toInt())
            {
                allunchecked = false;
            }
            else
            {
                allchecked = false;
            }
        }
    }
    if (allunchecked)
    {
        mCheckStates.insert(logicalIndex, Qt::Unchecked);
    }
    else if (allchecked)
    {
        mCheckStates.insert(logicalIndex, Qt::Checked);
    }
    else
    {
        mCheckStates.insert(logicalIndex, Qt::PartiallyChecked);
    }
}

void QtCheckHeaderView::updateModel(int logicalIndex)
{
    Qt::CheckState checked = mCheckStates.value(logicalIndex);

    if (orientation() == Qt::Horizontal)
    {
        for (int i = 0; i < model()->rowCount(rootIndex()); ++i)
        {
            model()->setData(model()->index(i, logicalIndex, rootIndex()), checked, Qt::CheckStateRole);
        }
    }
    else if (orientation() == Qt::Vertical)
    {
        for (int i = 0; i < model()->columnCount(rootIndex()); ++i)
        {
            model()->setData(model()->index(logicalIndex, i, rootIndex()), checked, Qt::CheckStateRole);
        }
    }
}
