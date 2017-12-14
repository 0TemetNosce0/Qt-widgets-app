#include <QCheckBox>
#include <QMouseEvent>
#include <QApplication>
#include "customdelegate.h"

CustomDelegate::CustomDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == index.model()->columnCount() - 1)
    {
        bool checked = index.model()->data(index).toBool();
        QStyleOptionButton* checkBoxOption = new QStyleOptionButton();
        checkBoxOption->state |= QStyle::State_Enabled;

        if (checked)
        {
            checkBoxOption->state |= QStyle::State_On;
        }
        else
        {
            checkBoxOption->state |= QStyle::State_Off;
        }

        checkBoxOption->rect = checkBoxRect(option);
        QApplication::style()->drawControl(QStyle::CE_CheckBox, checkBoxOption, painter);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QRect CustomDelegate::checkBoxRect(const QStyleOptionViewItem &viewItemStyleOptions) const
{
    QStyleOptionButton checkBoxStyleOption;
    QRect rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkBoxStyleOption);
    QPoint point(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - rect.width() / 2,
                 viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - rect.height() / 2);
    return QRect(point, rect.size());
}

bool CustomDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (index.column() == index.model()->columnCount() - 1)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

            if (mouseEvent->button() == Qt::LeftButton && checkBoxRect(option).contains(mouseEvent->pos()))
            {
                bool checked = index.model()->data(index).toBool();
                return model->setData(index, !checked);
            }
        }
    }

    return false;
}
