#include "q3treewidget.h"

Q3TreeWidget::Q3TreeWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    changeByClicked = true; // 表示首次变化是由用户点击引起的
    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), SLOT(onItemChanged(QTreeWidgetItem*,int)));
}

void Q3TreeWidget::onItemChanged(QTreeWidgetItem *item, int column)
{
    // 某节点变化后：Qt没有专门的信号去表示某节点的选中状态变化
    // 这些变化都由信号 itemChanged 表示

    // 第 0 列才是树形列表所在的列，我们这里不对别的项变化进行处理
    if (column == 0)
    {
        // 我们说了节点变化会引起两个方向上的状态变化
        // 在完成一个方向上的状态连锁变化后再变另一方向
        // 若先向子节点方向变化，但此方向上结束判断实为不易
        // 所以先向父方向进行连锁变化
        // 只有用户点击引起的变化才会有两个方向，但连锁变化时也会调用这个函数
        // 所以需要区分
        if (changeByClicked)
        {
            // 立即将此标记变为假，因为紧接着后面对此函数的调用均是连锁变化引起的了
            changeByClicked = false;
            changeDirection = true;
            changeParents(item);    // 此函数会引起父节点方向连锁变化
            changeChildren(item);   // 此函数会引起子节点方向连锁变化
            changeByClicked = true; // 为下次点击做准备
        }
        // 后面由连锁变化起码的槽函数调用则均流向此处了
        else
        {
            if (changeDirection)
            {
                changeParents(item);
            }
            else
            {
                changeChildren(item);
            }
        }
    }
}

void Q3TreeWidget::changeParents(QTreeWidgetItem *item)
{
    // 取得当前节点的父节点
    QTreeWidgetItem *p = item->parent();
    // 若父节点存在
    if (p)
    {
        Qt::CheckState checkState = item->checkState(0);
        // 将当前节点与其胞节点进行比较
        int i, childCount = p->childCount();
        for (i = 0; i < childCount; i++)
        {
            QTreeWidgetItem *child;
            child = p->child(i);
            // 若发现与当前节点不相同的胞节点，则退出比较
            if (checkState != child->checkState(0))
            {
                break;
            }
        }
        // 以下条件表示：在对比守所有胞节点前已经发现不同的项
        if (i < childCount)
        {
            checkState = Qt::PartiallyChecked;
        }
        // 此时 checkState 为父节点 p 应当变作的状态
        if (p->checkState(0) != checkState)
        {
            p->setCheckState(0, checkState);
        }
        // 若父节点当前选中状态与其应当变作的状态相同
        // 则父节点方向连锁变化结束
        else
        {
            changeDirection = false;
        }
    }
    // 若父节点不存在，则表示父节点方向的连锁反应已到最顶层节点
    // 此时转为对子节点的连锁反应
    else
    {
        changeDirection = false;
    }
}

void Q3TreeWidget::changeChildren(QTreeWidgetItem *item)
{
    int childCount = item->childCount();
    Qt::CheckState checkState = item->checkState(0);
    // 将每个子节点变作当前节点一样的选中状态
    for (int i = 0; i < childCount; i++)
    {
        QTreeWidgetItem *child;
        child = item->child(i);
        // 只将不同选中状态的子节点进行变化
        // 省得引起多余的连锁变化
        if (checkState != child->checkState(0))
        {
            child->setCheckState(0, checkState);
        }
    }
}

