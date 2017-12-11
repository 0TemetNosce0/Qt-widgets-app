/* INSTRUCTION
��̬����ԭ��ܼ򵥣�
1. ĳ�ڵ��������ڵ�Ĺ�ϵ������,���ڵ㡢�ӽڵ㡢���ڵ㣻
2. ĳ�ڵ�״̬�仯Ӱ��ķ����и��ڵ㷽���ӽڵ㷽��;
3. ��Ҫע��ݹ���õ�����,��ֹ����������Ӧ����ѭ��.
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
    bool changeDirection;   // Ϊ true ��ʾ������, false ��ʾ�ӷ���
    bool changeByClicked;   // Ϊ true ��ʾ�û����������״̬, false��ʾ�����仯ʱ����ı仯
    void changeParents(QTreeWidgetItem *item);
    void changeChildren(QTreeWidgetItem *item);
};

#endif // Q3TREEWIDGET_H
