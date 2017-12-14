#include <QPainter>
#include <QApplication>
//#include <QSortFilterProxyModel>

#include "DataNode.h"
#include "NodeManager.h"
#include "DataTreeView.h"
#include "DataTreeDelegate.h"

DataTreeDelegate::DataTreeDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

void DataTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //QModelIndex index = ((QSortFilterProxyModel*)(DataTreeView::_Instance->model()))->mapToSource(index1); 
    int row = index.row();
    int column = index.column();
    if (0 == column)
    {
        QStyleOptionViewItem opt(option);
        //先判断是否选中，如果是，则把该列的矩型填充为高亮色
        if (opt.state & QStyle::State_Selected)
        {
            painter->fillRect(opt.rect, opt.palette.highlight());
        }

        DataNode* node = static_cast<DataNode*>(index.internalPointer());
        Qt::CheckState state = node->checkState(column);

        if (Qt::Checked == state)
        {
            opt.state |= QStyle::State_On;
        }
        else if (Qt::PartiallyChecked == state)
        {
            opt.state |= QStyle::State_NoChange;
        }
        else if (Qt::Unchecked == state)
        {
            opt.state |= QStyle::State_Off;
        }

        QStyledItemDelegate::paint(painter, opt, index);
    }
    if (2 == column) 
    {
        painter->save();

        //先要调用默认的paint函数，这样，选中整行时该列才能高亮显示
       // QStyledItemDelegate::paint(painter, option, index); //其实不需这样做，改用下面方法
        QStyleOptionViewItem opt(option);

        //先判断是否选中，如果是，则把该列的矩型填充为高亮色
        if (opt.state & QStyle::State_Selected)
        {
            painter->fillRect(opt.rect, opt.palette.highlight());
        }

        DataNode* node = static_cast<DataNode*>(index.internalPointer());
        Qt::CheckState state = node->checkState(column);

        if (Qt::Checked == state)
        {
            opt.state |= QStyle::State_On;
        }
        else if (Qt::PartiallyChecked == state)
        {
            opt.state |= QStyle::State_NoChange;
        }
        else if (Qt::Unchecked == state)
        {
            opt.state |= QStyle::State_Off;
        }
      
        //QStyledItemDelegate::initStyleOption(&opt, index);

        /*opt.state |= QStyle::State_Selected;
       // opt.palette.setCurrentColorGroup(QPalette::Active);
        opt.palette.setBrush(QPalette::Highlight, QColor(Qt::red));
        opt.palette.setBrush(QPalette::Window, QColor(Qt::red));
        opt.state |= QStyle::State_MouseOver;
        //opt.state &= ~QStyle::State_Enabled;
        opt.state |= QStyle::State_HasFocus;
        opt.state |= QStyle::State_On;*/
        //opt.showDecorationSelected = true;
        
        //画一个checkbox
        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &opt, painter);

        painter->restore();        
    } 
    else if (10 == column) 
    {
		//画图形
        QStyleOptionViewItem opt(option);

        //先判断是否选中，如果是，则把该列的矩型填充为高亮色
        if (opt.state & QStyle::State_Selected)
        {
            painter->fillRect(opt.rect, opt.palette.highlight());
        }
        DataNode* node = static_cast<DataNode*>(index.internalPointer());

        int serial = NodeManager::getInstance()->serialNoOfNode(node);
        node->drawGantt()->paintCell(painter, opt.rect, serial);
    }
    else 
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

/*QSize DataTreeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize();
}
*/
QWidget* DataTreeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return NULL;
}

void DataTreeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void DataTreeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}
