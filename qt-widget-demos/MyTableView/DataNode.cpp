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
    //�ж��¾ɸ��ڵ��Ƿ����
    if (m_parent != value)
    {
        //�ж��¸��ڵ��Ƿ�ΪNULL
        if (value != NULL)
        {
            if (m_parent != NULL)
            {
                //�ж�ԭ���ڵ�ĺ����б����Ƿ���ڵ�ǰ�ڵ�
                if (m_parent->children().indexOf(this, 0) >= 0)
                {
                    //ԭ���ڵ�͵�ǰ�ڵ�����ϵ
                    m_parent->children().removeOne(this);
                }
            }

            //�����µĸ��ڵ�
            m_parent = value;
            //���¸��ڵ���й���
            if (m_parent->children().indexOf(this, 0) < 0)
            {
                m_parent->children().append(this);
            }
        }
        else
        {
            //�ж�ԭ���ĸ��ڵ��Ƿ�ΪNULL
            if (m_parent != NULL)
            {
                //ԭ���ڵ�͵�ǰ�ڵ�����ϵ
                m_parent->children().removeOne(this);
            }

            //�����¸��ڵ�ΪNULL
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

	//�ж�childԭ���ĸ��ڵ��Ƿ�Ϊnull�������Ϊ��Ҫ���ԭ���Ĺ�ϵ��
	if (child->m_parent != NULL)
	{
		child->setParent(NULL);
	}

	//���õ�ǰ��childe�ĸ��ڵ�Ϊ��ǰ�ڵ�
	child->m_parent = this;

	//���뵽�����б���
	m_children.insert(index, child);
}

DataNode* DataNode::removeChild(int index)
{
    int size = m_children.size();
    if (index > size)
    {
        return NULL;
    }

    //�ҵ���ǰ�Ľڵ�
    DataNode* node = m_children.at(index);

    //�Ӻ��ӽڵ��б���ɾ����ǰ�ڵ�
    m_children.removeAt(index);

    //�Ե�ǰ�ڵ�ĸ��ڵ�����Ϊ��
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