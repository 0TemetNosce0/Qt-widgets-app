#include "ItemDelegate.h"

#include <QPainter>
#include <QToolTip>
#include <QMouseEvent>
#include <QApplication>
#include <QStyledItemDelegate>

ItemDelegate::ItemDelegate(QObject * parent)
    : QStyledItemDelegate(parent)
    , m_pixmapHeight(9)
    , m_pixmapWidth(9)
    , m_treeView(NULL)
{
    m_expandIconName = QCoreApplication::applicationDirPath() + "/Resources/Images/arrowBottom.png";
    m_collapseIconName = QCoreApplication::applicationDirPath() + "/Resources/Images/arrowTop.png";
}

void ItemDelegate::setIconSize(QSize size)
{
    m_pixmapHeight = size.height();
    m_pixmapWidth = size.width();
}

void ItemDelegate::setExpandIcon(QString expandIconName)
{
    m_expandIconName = expandIconName;
}

void ItemDelegate::setcollapseIcon(QString collapseIconName)
{
    m_collapseIconName = collapseIconName;
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem  viewOption(option);

    if (viewOption.state & QStyle::State_HasFocus)
    {
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    }

    QStyledItemDelegate::paint(painter, viewOption, index);

    bool bExpanded = false;

    if (m_treeView != NULL)
    {
        const QAbstractItemModel *model = index.model();

        if (!model->hasChildren(index))
        {
            return;
        }
        bExpanded = m_treeView->isExpanded(index);
    }

    int height = (viewOption.rect.height() - m_pixmapWidth) / 2;
    QPixmap pixmap = bExpanded ? QPixmap(m_expandIconName) : QPixmap(m_collapseIconName);
    QRect decorationRect = QRect(viewOption.rect.left() + viewOption.rect.width() - 30, viewOption.rect.top() + height, m_pixmapHeight, m_pixmapWidth);
    painter->drawPixmap(decorationRect, pixmap);
}

bool ItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    int height = (option.rect.height() - m_pixmapWidth) / 2;
    QRect decorationRect = QRect(option.rect.left() + option.rect.width() - 30, option.rect.top() + height, m_pixmapHeight, m_pixmapWidth);

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

    if (event->type() == QEvent::MouseButtonPress && decorationRect.contains(mouseEvent->pos()))
    {
        emit expanded(index);
    }

    if (event->type() == QEvent::MouseMove && decorationRect.contains(mouseEvent->pos()))
    {
        bool bExpanded = false;

        if (m_treeView != NULL)
        {
            const QAbstractItemModel *model = index.model();

            if (!model->hasChildren(index))
            {
                return false;
            }
            bExpanded = m_treeView->isExpanded(index);
        }
        QCursor cursor(Qt::PointingHandCursor);
        QApplication::setOverrideCursor(cursor);
        QString strText = bExpanded ? QStringLiteral("ÕÛµþ") : QStringLiteral("Õ¹¿ª");
        QToolTip::showText(mouseEvent->globalPos(), strText);
    }
    else
    {
        QCursor cursor(Qt::ArrowCursor);
        QApplication::setOverrideCursor(cursor);
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void ItemDelegate::setView(QTreeView *treeView)
{
    m_treeView = treeView;
}
