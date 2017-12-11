#include "NodeManager.h"

NodeManager* NodeManager::m_instance = NULL;


NodeManager::NodeManager()
    : m_rootNode(NULL)
{
	//
}

NodeManager::~NodeManager()
{

}

NodeManager* NodeManager::getInstance()
{
    if (NULL == m_instance)
    {
        m_instance = new NodeManager();
    }

    return m_instance;
}

void NodeManager::destroyInstance()
{
    if (NULL != m_instance)
    {
        delete m_instance;
        m_instance = NULL;
    }
}

int NodeManager::init()
{
    m_rootNode = new DataNode();
    m_rootNode->setType(DataNode::Root);

    return 0;
}

DataNode* NodeManager::addNode(const TNodeData& data, DataNode* parent)
{
    if (NULL == parent)
    {
		//加到rootnode下
        DataNode* node = new DataNode();
        node->setParent(m_rootNode);

        node->setType(data.type);
        node->setSerialNo(data.serialNo);
        node->setCodeNo(data.codeNo);
        node->setName(data.name);
        node->setPlanBeginDate(data.planBeginDate);
        node->setPlanEndDate(data.planEndDate);
        node->setPlanDays(data.planDays);
        node->setRealBeginDate(data.realBeginDate);
        node->setRealEndDate(data.planEndDate);
        node->setRealDays(data.realDays);
        node->setTotalDays(data.totalDays);
        node->setMask(data.mask);

        return node;
    }

    //判断parent是否当前rootnode底下的一个子节点
    if (!isNodeInModel(parent))
    {
        return NULL;
    }

    DataNode* node = new DataNode();
    node->setParent(parent);

    node->setType(data.type);
    node->setSerialNo(data.serialNo);
    node->setCodeNo(data.codeNo);
    node->setName(data.name);
    node->setPlanBeginDate(data.planBeginDate);
    node->setPlanEndDate(data.planEndDate);
    node->setPlanDays(data.planDays);
    node->setRealBeginDate(data.realBeginDate);
    node->setRealEndDate(data.planEndDate);
    node->setRealDays(data.realDays);
    node->setTotalDays(data.totalDays);
    node->setMask(data.mask);

    return node;
}

bool NodeManager::isNodeInModel(DataNode* const node)
{
    if (NULL == node) 
    {
        return NULL;
    }

    bool flag = false;
    DataNode* parent = node->parent();
    while (NULL != parent)
    {
        if (m_rootNode == parent)
        {
            flag = true;

            break;
        }

        parent = parent->parent();
    }

    return flag;
}

void NodeManager::sortData(DataNode* parent)
{
    static int SERIALNO = 0;

    if (NULL == parent)
    {
        SERIALNO = 0;
        parent = m_rootNode;
    }
 
    QList<DataNode*> child = parent->children();
    for (int i = 0; i < child.size(); ++i)
    {
        int curNum = SERIALNO++;
        DataNode* node = child.at(i);
        m_sortMap[curNum] = node;

        //再保存多一份数据,方便查找
        m_serialMap[node] = curNum;

        if (!node->children().isEmpty())
        {
            sortData(node);
        }  
    }
}

void NodeManager::allChildNode(DataNode* parent, QList<DataNode*>& childList)
{
    if (NULL == parent)
    {
        parent = m_rootNode;
    }

    QList<DataNode*> child = parent->children();
    for (int i = 0; i < child.size(); ++i)
    {
        DataNode* node = child.at(i);

        if (!node->children().isEmpty())
        {
            allChildNode(node, childList);
        }

        childList.push_back(node);
    }
}

int NodeManager::serialNoOfNode(DataNode* node)
{
    QMap<DataNode*, int>::Iterator iter;

    if (m_serialMap.end() == (iter = m_serialMap.find(node)))
    {
        return -1;
    }

    return iter.value();
}

int NodeManager::nodeStep(DataNode* node)
{
    int step = 0;
    DataNode* parent = node->parent();
    while (parent)
    {
        parent = parent->parent();
        step++;
    }

    return (step - 1);
}

//获取节点所有的父节点
void NodeManager::allParentNode(DataNode* child, QList<DataNode*>& parentList)
{
    DataNode* parent = child->parent();
    while (parent)
    {
        parentList.push_back(parent);
        parent = parent->parent();
    }
}
