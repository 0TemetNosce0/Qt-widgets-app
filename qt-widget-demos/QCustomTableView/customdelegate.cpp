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
    //���ư�ť����Ҫ�Ĳ���
    QStyleOptionButton checkBoxStyleOption;
    //���ո����ķ����� ����Ԫ��������
    QRect checkBoxRect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &checkBoxStyleOption);
    //����QCheckBox����
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - checkBoxRect.width() / 2,
                         viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - checkBoxRect.height() / 2);
    //����QCheckBox������״
    return QRect(checkBoxPoint, checkBoxRect.size());
}
