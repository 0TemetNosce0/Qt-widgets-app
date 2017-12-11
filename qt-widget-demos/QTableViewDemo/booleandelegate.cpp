#include <QStyle>
#include <QApplication>

#include "booleandelegate.h"


BooleanDelegate::BooleanDelegate(QObject *parent, bool defaultValue)
    : QStyledItemDelegate(parent)
    , defaultValue(defaultValue)
{

}

void BooleanDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
{
    QVariant value = index.data();

    if (!value.isValid() || value.canConvert<bool>())
    {
        bool boolVal = value.isValid() ? value.toBool() : defaultValue;
        QStyle *style = qApp->style();
        QRect checkBoxRect = style->subElementRect(QStyle::SE_CheckBoxIndicator, &option);
        int chkWidth = checkBoxRect.width();
        int chkHeight = checkBoxRect.height();

        int centerX = option.rect.left() + qMax(option.rect.width()/2-chkWidth/2, 0);
        int centerY = option.rect.top() + qMax(option.rect.height()/2-chkHeight/2, 0);
        QStyleOptionViewItem modifiedOption(option);
        modifiedOption.rect.moveTo(centerX, centerY);
        modifiedOption.rect.setSize(QSize(chkWidth, chkHeight));

        if(boolVal)
        {
            modifiedOption.state |= QStyle::State_On;
        }

        style->drawPrimitive(QStyle::PE_IndicatorItemViewItemCheck, &modifiedOption, painter);
    }

    return QStyledItemDelegate::paint(painter, option, index);
}

QWidget *BooleanDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &/* index */) const
{
    CenteredCheckBoxWidget *editor = new CenteredCheckBoxWidget(parent);
    editor->checkBox()->setChecked(defaultValue);

    return editor;
}

void BooleanDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QVariant data = index.model()->data(index, Qt::EditRole);
    bool value;

    if(!data.isNull())
    {
        value = data.toBool();
    }
    else
    {
        value = defaultValue;
    }

    CenteredCheckBoxWidget *checkBoxWidget = static_cast<CenteredCheckBoxWidget*>(editor);
    checkBoxWidget->checkBox()->setChecked(value);
}

void BooleanDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    CenteredCheckBoxWidget *checkBoxWidget = static_cast<CenteredCheckBoxWidget*>(editor);

    bool value = checkBoxWidget->checkBox()->isChecked();

    model->setData(index, value, Qt::EditRole);
}

void BooleanDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    CenteredCheckBoxWidget *checkBoxWidget = static_cast<CenteredCheckBoxWidget*>(editor);

    QSize size = checkBoxWidget->sizeHint();
    editor->setMinimumHeight(size.height());
    editor->setMinimumWidth(size.width());
    editor->setGeometry(option.rect);
}
