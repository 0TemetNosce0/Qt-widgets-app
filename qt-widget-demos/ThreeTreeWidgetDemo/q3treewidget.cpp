#include "q3treewidget.h"

Q3TreeWidget::Q3TreeWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    changeByClicked = true; // ��ʾ�״α仯�����û���������
    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), SLOT(onItemChanged(QTreeWidgetItem*,int)));
}

void Q3TreeWidget::onItemChanged(QTreeWidgetItem *item, int column)
{
    // ĳ�ڵ�仯��Qtû��ר�ŵ��ź�ȥ��ʾĳ�ڵ��ѡ��״̬�仯
    // ��Щ�仯�����ź� itemChanged ��ʾ

    // �� 0 �в��������б����ڵ��У��������ﲻ�Ա����仯���д���
    if (column == 0)
    {
        // ����˵�˽ڵ�仯���������������ϵ�״̬�仯
        // �����һ�������ϵ�״̬�����仯���ٱ���һ����
        // �������ӽڵ㷽��仯�����˷����Ͻ����ж�ʵΪ����
        // �������򸸷�����������仯
        // ֻ���û��������ı仯�Ż����������򣬵������仯ʱҲ������������
        // ������Ҫ����
        if (changeByClicked)
        {
            // �������˱�Ǳ�Ϊ�٣���Ϊ�����ź���Դ˺����ĵ��þ��������仯�������
            changeByClicked = false;
            changeDirection = true;
            changeParents(item);    // �˺��������𸸽ڵ㷽�������仯
            changeChildren(item);   // �˺����������ӽڵ㷽�������仯
            changeByClicked = true; // Ϊ�´ε����׼��
        }
        // �����������仯����Ĳۺ��������������˴���
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
    // ȡ�õ�ǰ�ڵ�ĸ��ڵ�
    QTreeWidgetItem *p = item->parent();
    // �����ڵ����
    if (p)
    {
        Qt::CheckState checkState = item->checkState(0);
        // ����ǰ�ڵ�������ڵ���бȽ�
        int i, childCount = p->childCount();
        for (i = 0; i < childCount; i++)
        {
            QTreeWidgetItem *child;
            child = p->child(i);
            // �������뵱ǰ�ڵ㲻��ͬ�İ��ڵ㣬���˳��Ƚ�
            if (checkState != child->checkState(0))
            {
                break;
            }
        }
        // ����������ʾ���ڶԱ������а��ڵ�ǰ�Ѿ����ֲ�ͬ����
        if (i < childCount)
        {
            checkState = Qt::PartiallyChecked;
        }
        // ��ʱ checkState Ϊ���ڵ� p Ӧ��������״̬
        if (p->checkState(0) != checkState)
        {
            p->setCheckState(0, checkState);
        }
        // �����ڵ㵱ǰѡ��״̬����Ӧ��������״̬��ͬ
        // �򸸽ڵ㷽�������仯����
        else
        {
            changeDirection = false;
        }
    }
    // �����ڵ㲻���ڣ����ʾ���ڵ㷽���������Ӧ�ѵ����ڵ�
    // ��ʱתΪ���ӽڵ��������Ӧ
    else
    {
        changeDirection = false;
    }
}

void Q3TreeWidget::changeChildren(QTreeWidgetItem *item)
{
    int childCount = item->childCount();
    Qt::CheckState checkState = item->checkState(0);
    // ��ÿ���ӽڵ������ǰ�ڵ�һ����ѡ��״̬
    for (int i = 0; i < childCount; i++)
    {
        QTreeWidgetItem *child;
        child = item->child(i);
        // ֻ����ͬѡ��״̬���ӽڵ���б仯
        // ʡ���������������仯
        if (checkState != child->checkState(0))
        {
            child->setCheckState(0, checkState);
        }
    }
}

