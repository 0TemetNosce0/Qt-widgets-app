#include "trackdelegate.h"

#include <QTimeEdit>
#include <QPainter>
#include <QApplication>

#include "trackmodel.h"

const int TrackDelegate::columnNumber = 1;

TrackDelegate::TrackDelegate(QObject* parent) :
    QStyledItemDelegate(parent)
{

}

TrackDelegate::~TrackDelegate()
{

}

QWidget* TrackDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    if (isRightColumn(index, TrackDelegate::columnNumber))
    {
        QTimeEdit *timeEdit = new QTimeEdit(parent);
        timeEdit->setDisplayFormat("hh:mm");
        connect(timeEdit, &QTimeEdit::editingFinished,
                this, &TrackDelegate::commitAndCloseEditor);

        //int secs = index.model()->data(index, Qt::DisplayRole).toInt();
        int secs = index.model()->data(index, Qt::EditRole).toInt();

        QTime time(secs / 60, secs % 60);
        timeEdit->setTime(time);

        return timeEdit;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void TrackDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if ( !index.isValid()) {
        return;
    }

    QTimeEdit* timeEditor = qobject_cast<QTimeEdit*>(editor);

    if ( !timeEditor) {
        return;
    }

    if (isRightColumn(index, TrackDelegate::columnNumber)) {
        int secs = index.model()->data(index, Qt::EditRole).toInt();
        QTime time(secs / 60, secs % 60);
        timeEditor->setTime(time);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void TrackDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    if ( !index.isValid())
    {
        return;
    }

    QTimeEdit* timeEditor = qobject_cast<QTimeEdit*>(editor);

    if ( !timeEditor)
    {
        return;
    }

    if (isRightColumn(index, TrackDelegate::columnNumber))
    {
        QTime time = timeEditor->time();
        int secs = time.hour() * 60 + time.minute();
        //int secs = index.model()->data(index, Qt::EditRole).toInt();
        model->setData(index, secs, Qt::EditRole);
    }
    else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void TrackDelegate::updateEditorGeometry(QWidget *editor,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    Q_UNUSED(index);

    editor->setGeometry(option.rect);
}

void TrackDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    if (isRightColumn(index, TrackDelegate::columnNumber))
    {
        int secs = index.model()->data(index, Qt::EditRole).toInt();
        QString text = QString("%1:%2")
                       .arg(secs / 60, 2, 10, QChar('0'))
                       .arg(secs % 60, 2, 10, QChar('0'));

        //获取项风格设置
        QStyleOptionViewItem myOption = option;
        myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;
        painter->drawText(option.rect, text);
        /*QApplication::style()->drawItemText(painter,
                                            myOption.rect,
                                            myOption.displayAlignment,
                                            QApplication::palette(),
                                            true,
                                            text);*/
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize TrackDelegate::sizeHint(const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    return option.rect.size();
}

void TrackDelegate::commitAndCloseEditor()
{
    QTimeEdit* editor = qobject_cast<QTimeEdit*>(sender());

    emit commitData(editor);
    emit closeEditor(editor);
}

bool TrackDelegate::isRightColumn(const QModelIndex &index,
                                  const int column) const
{
    if ( !index.isValid())
    {
        return false;
    }

    if (index.column() == column)
    {
        return true;
    }
    else
    {
        return false;
    }
}
