#include "ccheckboxitemdelegate.h"
#include <QCheckBox>
#include <QDebug>
#include <QStyleOptionButton>
#include <QStyleOptionViewItem>
#include <QStyleOptionViewItemV4>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

cCheckBoxItemDelegate::cCheckBoxItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void cCheckBoxItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    // actually this one draws the grid
    painter->setPen(QColor(200, 200, 200));
    painter->drawRect(option.rect);

    const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
    QRect newRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                        QSize(option.decorationSize.width(), option.decorationSize.height()),
                                        QRect(option.rect.x() + textMargin, option.rect.y(),
                                              option.rect.width() - (2 * textMargin), option.rect.height()));

    QStyleOptionButton opt;
    opt.rect = newRect;
    qDebug() << opt.rect.width();

    // set the correct state in option to display
    static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt()) == Qt::Checked ? opt.state = QStyle::State_On : opt.state = QStyle::State_Off;

    // will draw background for hover
    QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &option, painter);
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &opt, painter);
    //QApplication::style()->drawControl(QStyle::CE_CheckBoxLabel, &opt, painter);
}

bool cCheckBoxItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    // toggle state
    bool toggle = false;
    qDebug() << event->type();

    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *e = static_cast<QKeyEvent *>(event);

        if(e->key() == Qt::Key_Space)
        {
            toggle = true;
        }
    }

    if(toggle || event->type() == QEvent::MouseButtonRelease)
    {
        qDebug() << "xxx";
        const Qt::CheckState state = (static_cast<Qt::CheckState>( index.data(Qt::CheckStateRole).toInt() ) == Qt::Checked ? Qt::Unchecked : Qt::Checked);
        return model->setData(index, state, Qt::CheckStateRole);
    }

    return false;
}

QWidget *cCheckBoxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);
    qDebug() << "not creating editor";
    return 0;
}
