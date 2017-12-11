#include "progressbardelegate.h"

#include <QPainter>
#include <QApplication>

ProgressBarDelegate::ProgressBarDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}


void ProgressBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 1)
    {
        int value = index.model()->data(index).toInt();
        QStyleOptionProgressBarV2 progressBarOption;
        progressBarOption.rect = option.rect.adjusted(4, 4, -4, -4);
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.textAlignment = Qt::AlignRight;
        progressBarOption.textVisible = true;
        progressBarOption.progress = value;
        progressBarOption.text = tr("%1%").arg(progressBarOption.progress);

        painter->save();

        if (option.state & QStyle::State_Selected)
        {
            painter->fillRect(option.rect, option.palette.highlight());
                    painter->setBrush(option.palette.highlightedText());
        }
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);

        painter->restore();

    }
    else
    {
        return QItemDelegate::paint (painter, option, index);
    }
}
