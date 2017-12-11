/* INSTRUCTION
三态树的原理很简单：
1. 某节点与其它节点的关系有三种,父节点、子节点、胞节点；
2. 某节点状态变化影响的方向有父节点方向、子节点方向;
3. 需要注意递归调用的问题,防止陷入连锁反应的死循环.
*/

#ifndef Q3TREEWIDGET_H
#define Q3TREEWIDGET_H

#include <QTreeWidget>

class Q3TreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit Q3TreeWidget(QWidget *parent = 0);

private slots:
    void onItemChanged(QTreeWidgetItem *item, int column);

private:
    bool changeDirection;   // 为 true 表示父方向, false 表示子方向
    bool changeByClicked;   // 为 true 表示用户点击产生的状态, false表示连锁变化时引起的变化
    void changeParents(QTreeWidgetItem *item);
    void changeChildren(QTreeWidgetItem *item);
};

#endif // Q3TREEWIDGET_H
