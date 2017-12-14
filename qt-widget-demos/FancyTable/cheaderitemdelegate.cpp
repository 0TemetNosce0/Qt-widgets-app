#include "cheaderitemdelegate.h"
#include <QCheckBox>
#include <QDebug>
#include <QStyleOptionButton>
#include <QStyleOptionViewItem>
#include <QStyleOptionViewItemV4>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QComboBox>

cHeaderItemDelegate::cHeaderItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void cHeaderItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    // actually this one draws the grid
    //painter->setPen(QColor(200,200,200));
    //painter->drawRect(option.rect);

    const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
    /*QRect smallRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                        QSize(option.fontMetrics.width(index.data(Qt::DisplayRole).toString()), option.fontMetrics.height()),
                                        QRect(option.rect.x(), option.rect.y(), option.rect.width(), option.rect.height()));*/

    QRect smallRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                        QSize(option.fontMetrics.width(index.data(Qt::DisplayRole).toString())+30, option.fontMetrics.height()+3),
                                        option.rect);

    // set the correct state in option to display

    QStyleOptionHeader header_opt;
    header_opt.rect = option.rect;
    //header_opt.text = index.data(Qt::DisplayRole).toString();
    header_opt.position = QStyleOptionHeader::Middle;
    header_opt.textAlignment = Qt::AlignCenter;

    header_opt.state = option.state;
    header_opt.state |= QStyle::State_Enabled | QStyle::State_Horizontal | QStyle::State_None | QStyle::State_Raised;

    painter->save();
    QApplication::style()->drawControl(QStyle::CE_Header, &header_opt, painter);
    painter->restore();

    painter->setPen(QColor(100,100,100));

    QStyleOptionViewItemV4 xopt(option);

    xopt.state &= ~QStyle::State_MouseOver;

    xopt.features |= QStyleOptionViewItemV4::HasCheckIndicator;
    xopt.rect = smallRect;

    if(static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt()) == Qt::Checked)
    {
        xopt.state |= QStyle::State_On;
    }

    QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &xopt, painter);

}

bool cHeaderItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    // toggle state
    bool toggle = false;

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
        const Qt::CheckState state = (static_cast<Qt::CheckState>( index.data(Qt::CheckStateRole).toInt() ) == Qt::Checked ? Qt::Unchecked : Qt::Checked);
        return model->setData(index, state, Qt::CheckStateRole);
    }

    return false;
}

QWidget *cHeaderItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox *cb = new QComboBox(parent);
    qDebug() << "not creating editor";
    cb->addItem("asd");
    return cb;
}
