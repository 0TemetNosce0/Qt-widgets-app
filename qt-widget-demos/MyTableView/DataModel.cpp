#include <QSize>
#include "Const.h"
#include "DataModel.h"
#include "DataNode.h"
#include "TableView.h"

DataModel::DataModel(QObject *parent) 
   : QAbstractItemModel(parent)
   , m_rootNode(0)
{
    
}

DataModel::~DataModel()
{

}

QModelIndex DataModel::index(int row, int column,
                      const QModelIndex &parent) const
{
	if (!m_rootNode || row < 0 || column < 0)
	{
		return QModelIndex();
	}

    DataNode *parentNode = nodeFromIndex(parent);
    DataNode *childNode = parentNode->children().value(row);

    if (!childNode)
    {
		return QModelIndex();
	}

    return createIndex(row, column, childNode);
}

QModelIndex DataModel::parent(const QModelIndex &child) const
{
    DataNode *node = nodeFromIndex(child);
    if (!node)
    {
		return QModelIndex();
	}

    DataNode *parentNode = node->parent();
    if (!parentNode)
    {
		return QModelIndex();
	}

    DataNode *grandparentNode = parentNode->parent();
    if (!grandparentNode)
    {
		return QModelIndex();
	}

    int row = grandparentNode->children().indexOf(parentNode);
    return createIndex(row, 0, parentNode);
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
		return 0;
	}

    DataNode *parentNode = nodeFromIndex(parent);
    if (!parentNode)
    {
		return 0;
	}

    return parentNode->children().count();
}

int DataModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
    return COL_NUM;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();
    
	if (role == Qt::TextAlignmentRole)
    {
        if (column != 0)
        {
            return Qt::AlignCenter;
        }
    }

    if (role == Qt::CheckStateRole && (index.column() == 0)) //判断显示的对象是checkbox，并且位于第一列  
    {        
        DataNode *node = nodeFromIndex(index);
        return node->checkState(index.column());
    }  

    if (role == Qt::SizeHintRole)
    {
		//这里可以指定tree每行的高度，通过设置这个值，竖头的高度不会改变，也要相应设置竖头的高度      
        return QSize(60, 30);
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        DataNode *node = nodeFromIndex(index);
        if (!node)
        {
			return QVariant();
		}

        switch (index.column()) 
        {
            case SERIAL_COL:
            {
                return node->serialNo();
            }
            case TYPE_COL:
            {
                DataNode::Type type = node->type();
                if (type == DataNode::Summary)
                {
                    return QStringLiteral("分部");
                }
                else if (type == DataNode::Task)
                {
                    return QStringLiteral("任务");
                }
                else
                {
                    return QStringLiteral("未知");
                }
            }
            case CODE_COL:
            {
                //return QString::number(node->codeNo());
                break;

            }
            case NAME_COL:
            {
                return node->name();
            }
            case PLANBEGINDATE_COL:
            {
                return node->planBeginDate().toString(QStringLiteral("yyyy.MM.dd"));
            }
            case PLANENDDATE:
            {
                return node->planEndDate().toString(QStringLiteral("yyyy.MM.dd"));
            }
            case PLANDAYS_COL:
            {
                return QString::number(node->planDays());
            }
            case REALBEGINDATE_COL:
            {
                return node->realBeginDate().toString(QStringLiteral("yyyy.MM.dd"));
            }
            case REALENDDATE_COL:
            {
                return node->realEndDate().toString(QStringLiteral("yyyy.MM.dd"));
            }
            case REALDAYS_COL:
            {
                return QString::number(node->realDays());
            }
            case TOTALDAYS_COL:
            {
                //return QString::number(node->totalDays());
                //return QVariant((void*)(node->drawGantt()));
                break;
            }
            case MASK_COL:
            {
                return node->mask();
            }    
        }
    }

    return QVariant();
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    if (index.column() == 0)
    {
        return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    if (index.column() == 2)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

DataNode* DataModel::nodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid()) 
    {
        return static_cast<DataNode *>(index.internalPointer());
    } 
    else 
    {
		return m_rootNode;
    }
}

void DataModel::setRootNode(DataNode *node)
{
	delete m_rootNode;
	m_rootNode = node;
    //reset();
	beginResetModel();
	endResetModel();
}
