#include "DataNode.h"

DataNode::DataNode()
{
    m_type = Unknown;

    m_serialNo = "";
    m_codeNo = 0.0;
    m_name = "";
    m_planBeginDate = QDate();
    m_planEndDate = QDate();
    m_planDays = 0;

    m_realBeginDate = QDate();
    m_realEndDate = QDate();
    m_realDays = 0;

    m_totalDays = 0;
    m_mask = "";

    m_parent = NULL;
    m_children.clear();

    m_drawGantt = new DrawGantt();
}

DataNode::~DataNode()
{

}

QString DataNode::serialNo()
{
    return m_serialNo;
}

void DataNode::setSerialNo(const QString& serial)
{
    m_serialNo = serial;
}

float DataNode::codeNo()
{
    return m_codeNo;
}

void DataNode::setCodeNo(float num)
{
    m_codeNo = num;
}

QString DataNode::name()
{
    return m_name;
}

void DataNode::setName(const QString& name)
{
    m_name = name;
}

QDate DataNode::planBeginDate()
{
    return m_planBeginDate;
}

void DataNode::setPlanBeginDate(const QDate& date)
{
    m_planBeginDate = date;
}

QDate DataNode::planEndDate()
{
    return m_planEndDate;
}

void DataNode::setPlanEndDate(const QDate& date)
{
    m_planEndDate = date;
}

int DataNode::planDays()
{
    return m_planDays;
}

void DataNode::setPlanDays(int days)
{
    m_planDays = days;
}

QDate DataNode::realBeginDate()
{
    return m_realBeginDate;
}

void DataNode::setRealBeginDate(const QDate& date)
{
    m_realBeginDate = date;
}

QDate DataNode::realEndDate()
{
    return m_realEndDate;
}

void DataNode::setRealEndDate(const QDate& date)
{
    m_realEndDate = date;
}

int DataNode::realDays()
{
    return m_realDays;
}

void DataNode::setRealDays(int days)
{
    m_realDays = days;
}

int DataNode::totalDays()
{
    return m_totalDays;
}

void DataNode::setTotalDays(int days)
{
    m_totalDays = days;
}

QString DataNode::mask()
{
    return m_mask;
}

void DataNode::setMask(const QString& mask)
{
    m_mask = mask;
}

DataNode* DataNode::parent() 
{
    return m_parent;
}

DataNode& DataNode::setParent(DataNode* value)
{
    //判断新旧父节点是否相等
    if (m_parent != value)
    {
        //判断新父节点是否为NULL
        if (value != NULL)
        {
            if (m_parent != NULL)
            {
                //判断原父节点的孩子列表中是否存在当前节点
                if (m_parent->children().indexOf(this, 0) >= 0)
                {
                    //原父节点和当前节点解除关系
                    m_parent->children().removeOne(this);
                }
            }

            //设置新的父节点
            m_parent = value;
            //和新父节点进行关联
            if (m_parent->children().indexOf(this, 0) < 0)
            {
                m_parent->children().append(this);
            }
        }
        else
        {
            //判断原来的父节点是否为NULL
            if (m_parent != NULL)
            {
                //原父节点和当前节点解除关系
                m_parent->children().removeOne(this);
            }

            //设置新父节点为NULL
            m_parent = NULL;
        }
    }

    return *this;
}

QList<DataNode*>& DataNode::children() 
{
    return m_children;
}

void DataNode::insertChild(int index, DataNode* child)
{
	int size = m_children.size();
	if (index > size)
	{
		return;
	}

	//判断child原来的父节点是否为null，如果不为需要解除原来的关系先
	if (child->m_parent != NULL)
	{
		child->setParent(NULL);
	}

	//设置当前的childe的父节点为当前节点
	child->m_parent = this;

	//插入到孩子列表中
	m_children.insert(index, child);
}

DataNode* DataNode::removeChild(int index)
{
    int size = m_children.size();
    if (index > size)
    {
        return NULL;
    }

    //找到当前的节点
    DataNode* node = m_children.at(index);

    //从孩子节点列表中删除当前节点
    m_children.removeAt(index);

    //对当前节点的父节点设置为空
    node->m_parent = NULL;
    
    return node;
}

Qt::CheckState DataNode::checkState(int col)
{
    return m_stateMap[col];
}

void DataNode::setCheckState(int col, Qt::CheckState state)
{
    m_stateMap[col] = state;
}