#include <QWheelEvent>
#include <QScrollBar>
#include <QPainter>

#include "DataTreeView.h"
#include "TableView.h"
#include "NodeManager.h"
#include "VHeaderView.h"
#include "HHeaderView.h"
#include "DataTreeDelegate.h"
#include "DataModel.h"

DataTreeView* DataTreeView::m_Instance = NULL;

DataTreeView::DataTreeView(QWidget* parent)
    : QTreeView(parent)
{
    m_Instance = this;
    this->setStyleSheet("QTreeView1 { border: none;"
        "background-color: #8EDE21;"
        "selection-background-color: #999}"); 

    connect(this, SIGNAL(collapsed (const QModelIndex&)), this, SLOT(onCollapsed (const QModelIndex&)));
    connect(this, SIGNAL(expanded (const QModelIndex& )), this, SLOT(onExpanded (const QModelIndex&)));

    DataTreeDelegate* delegate = new DataTreeDelegate(this);
    this->setItemDelegate(delegate);

    this->setAlternatingRowColors(true); 
}

DataTreeView::~DataTreeView()
{

}

void DataTreeView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() < 0)
    {
        int value = this->verticalScrollBar()->value();
        this->verticalScrollBar()->setValue(value + 1 * 30);
    }
    else
    {
        int value = this->verticalScrollBar()->value();
        this->verticalScrollBar()->setValue(value - 1 * 30);
    }
}

QModelIndex DataTreeView::rowIndex(int rowNo)
{
    if (rowNo < 0)
    {
		return QModelIndex();
	}

    //��ȡ���ڵ�
    QModelIndex rootIndex = model()->index(0, 0, QModelIndex());
    if (!rootIndex.isValid())
    {
		return QModelIndex();
	}

    QModelIndex resIndex = rootIndex;
    while (rowNo >= 1)
    {
        resIndex = this->indexBelow(resIndex);
        if (!resIndex.isValid())
        {
            break;
        }
        --rowNo;
    }

    return resIndex;
}

int DataTreeView::indexRow(const QModelIndex& index)
{
    if (!index.isValid())
    {
		return -1;
	}

     //��ȡ���ڵ�
    QModelIndex rootIndex = model()->index(0, 0, QModelIndex());
    if (!rootIndex.isValid())
    {
		return -1;
	}

    int rowNo = 0;
    QModelIndex loopIndex = rootIndex;

    DataNode* nodeSrc = static_cast<DataNode*>(index.internalPointer());
    DataNode* nodeDest = static_cast<DataNode*>(loopIndex.internalPointer());
    while (nodeDest != nodeSrc)
    {
        loopIndex = this->indexBelow(loopIndex);
        if (!loopIndex.isValid())
        {
            return -1;
        }

        nodeDest = static_cast<DataNode*>(loopIndex.internalPointer());
        ++rowNo;
    }

    return rowNo;
}

void DataTreeView::onCollapsed ( const QModelIndex &index )
{
    if (!index.isValid())
    {
        return;
    }

    DataNode* parent = static_cast<DataNode*>(index.internalPointer());
    if (NULL == parent)
    {
        return;
    }

    //��ȡ���������е�����ڵ�
    QList<DataNode*> childNodeList;
    NodeManager::getInstance()->allChildNode(parent, childNodeList);

    int size = childNodeList.size();
    for (int i = 0; i < size; ++i)
    {
        int serial = NodeManager::getInstance()->serialNoOfNode(childNodeList.at(i));
        VHeaderView::m_Instance->hideSection(serial);             
    }

    //Ҫ��ˮƽͷ�����һ�н��������С������ˮƽͷ�Լ��ĸ��²������Ӷ�ʹ����������ʾ��ȷ
    HHeaderView::m_Instance->resizeLastSection(true);
}

void DataTreeView::onExpanded ( const QModelIndex & index )
{
    DataNode* parent = static_cast<DataNode*>(index.internalPointer());
    if (NULL == parent)
    {
        return;
    }

    //��ȡ���������е�����ڵ�
    QList<DataNode*> childNodeList;
    NodeManager::getInstance()->allChildNode(parent, childNodeList);

    int size = childNodeList.size();
    for (int i = 0; i < size; ++i)
    {
        int serial = NodeManager::getInstance()->serialNoOfNode(childNodeList.at(i));
        //VHeaderView::m_Instance->showSection(serial);      
    }

    //Ҫ��ˮƽͷ�����һ�н��������С������ˮƽͷ�Լ��ĸ��²������Ӷ�ʹ����������ʾ��ȷ
    HHeaderView::m_Instance->resizeLastSection(false);
}

void DataTreeView::paintEvent(QPaintEvent *event)
{
    QTreeView::paintEvent(event); //ֱ�ӵ���Ĭ�ϴ���������paint��delegate��
}

void DataTreeView::mouseReleaseEvent ( QMouseEvent * event )
{
    QModelIndex	index = this->indexAt ( event->pos() );
    if (!index.isValid())
    {
        QTreeView::mouseReleaseEvent(event);
        return;
    }

    DataNode* node = static_cast<DataNode*>(index.internalPointer());

    //��ȡ���ǵڼ���
    int row = indexRow(index);
    //������ͷ�ĺ������������Σ���ʾ����ѡ��
    VHeaderView::m_Instance->selectRow(row);

    //��Ҫ�ж��Ƿ���е�checkbox
    int col = this->columnAt(event->x());
    if (2 == col)
    {
        //��ȡ��ǰ��Ԫ���rect
        QRect rect = this->visualRect(index);

        //��ȡcheckbox�� rect
        QRect checkRect = rect;
        
        int width = rect.width();
        int height = rect.height();
        int left = rect.center().x() - 8;
        int top = rect.center().y() - 8;

        checkRect.setLeft(left);
        checkRect.setTop(top);
        checkRect.setWidth(16);
        checkRect.setHeight(16);

        if (checkRect.contains(event->pos()))
        {
            Qt::CheckState checkState = (node->checkState(col) == Qt::Checked ? Qt::Unchecked : Qt::Checked);
            node->setCheckState(col, checkState);

            HHeaderView::m_Instance->setCheckedState(1, 2, Qt::PartiallyChecked);

            //���̸��½���
            viewport()->update();
            HHeaderView::m_Instance->viewport()->update();
        }
    }
    else if (0 == col)
    {      
        //��ȡ��ǰ�ڵ��Ǹ��ڵ��µĵڼ���
        int step = NodeManager::getInstance()->nodeStep(node);
      
        //��ȡ��ǰ��Ԫ���rect
        QRect rect = this->visualRect(index);

        //��ȡcheckbox�� rect
        QRect checkRect = rect;
        
        int width = rect.width();
        int height = rect.height();
        int left = 25 + 20 * step;
        int top = rect.center().y() - 8;

        checkRect.setLeft(left);
        checkRect.setTop(top);
        checkRect.setWidth(16);
        checkRect.setHeight(16);

        if (checkRect.contains(event->pos()))
        {
            Qt::CheckState checkState = (node->checkState(col) == Qt::Checked ? Qt::Unchecked : Qt::Checked);
            node->setCheckState(col, checkState);

            //��ȡ�����е�����ڵ�
            QList<DataNode*> childList;
            NodeManager::getInstance()->allChildNode(node, childList);
            for (int i = 0; i < childList.size(); ++i)
            {
                childList.at(i)->setCheckState(col, checkState);
            }

            //��ȡ�����еĸ��ڵ�
            QList<DataNode*> parentList;
            NodeManager::getInstance()->allParentNode(node, parentList);
            for (int i = 0; i < parentList.size(); ++i)
            {
                if (checkState == Qt::Unchecked)
                {
                    if (parentList.at(i)->checkState(col) == Qt::Checked)
                    {
                        parentList.at(i)->setCheckState(col, Qt::PartiallyChecked);
                    }
                }
                else
                {
                    parentList.at(i)->setCheckState(col, checkState);
                }
                
                //parentList.at(i)->setCheck(checkState);
            }

            HHeaderView::m_Instance->setCheckedState(1, 1, Qt::PartiallyChecked);

            //���̸��½���
            viewport()->update();
            HHeaderView::m_Instance->viewport()->update();
        }
    }

    QTreeView::mouseReleaseEvent(event);
}

void DataTreeView::mouseMoveEvent ( QMouseEvent * event )
{
    //��Ҫ�ж��Ƿ���е�checkbox
    int col = this->columnAt(event->x());
    if (2 == col)
    {
        QModelIndex	index = this->indexAt ( event->pos() );  
        DataNode* node = static_cast<DataNode*>(index.internalPointer());
        
        //��ȡnode��Ӧ��˳���
        int serial = NodeManager::getInstance()->serialNoOfNode(node);
        //��ȡ��ǰ��Ԫ���rect
        QRect rect = this->visualRect(index);

        //��ȡcheckbox�� rect
        QRect checkRect = rect;
        
        int width = rect.width();
        int height = rect.height();
        int left = rect.center().x() - 8;
        int top = rect.center().y() - 8;

        checkRect.setLeft(left);
        checkRect.setTop(top);
        checkRect.setWidth(16);
        checkRect.setHeight(16);

        if (checkRect.contains(event->pos()))
        {
            static int lastRow = -1;
            if (lastRow == serial)
            {
                QTreeView::mouseMoveEvent(event);
                return;
            }

            lastRow = serial;

             Qt::CheckState checkState = (node->checkState(col) == Qt::Checked ? Qt::Unchecked : Qt::Checked);
            node->setCheckState(col, checkState);

            HHeaderView::m_Instance->setCheckedState(1, 2, Qt::PartiallyChecked);

            //���̸��½���
            viewport()->update();
            HHeaderView::m_Instance->viewport()->update();
        }
    }

    QTreeView::mouseMoveEvent(event);
}

void DataTreeView::updateCheckStateByCol(int col, Qt::CheckState state)
{
    if (2 == col)
    {
        QList<DataNode*> childList;

        NodeManager::getInstance()->allChildNode(NULL, childList);
        int size = childList.size();
        for (int i = 0; i < size; ++i)
        {
            childList.at(i)->setCheckState(col, state);
        }

        viewport()->update();
    }
}

