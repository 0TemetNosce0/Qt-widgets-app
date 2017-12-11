#include "customdelegate.h"
#include <QApplication>

CustomDelegate::CustomDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    if (index.column() == 0)
    {
        bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
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
        checkBoxOption->rect = CheckBoxRect(option);
        QApplication::style()->drawControl(QStyle::CE_CheckBox, checkBoxOption, painter);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QRect CustomDelegate::CheckBoxRect(const QStyleOptionViewItem& viewItemStyleOptions) const
{
    //绘制按钮所需要的参数
    QStyleOptionButton checkBoxStyleOption;
    //按照给定的风格参数 返回元素子区域
    QRect checkBoxRect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &checkBoxStyleOption);
    //返回QCheckBox坐标
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - checkBoxRect.width() / 2,
                         viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - checkBoxRect.height() / 2);
    //返回QCheckBox几何形状
    return QRect(checkBoxPoint, checkBoxRect.size());
}
