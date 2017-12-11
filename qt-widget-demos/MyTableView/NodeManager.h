#ifndef NODE_MANAGER_H
#define NODE_MANAGER_H

#include <QMap>

#include "DataNode.h"

struct TNodeData
{
    QString serialNo;
    DataNode::Type type;
    float codeNo;
    QString name;

    QDate planBeginDate;
    QDate planEndDate;
    int planDays;

    QDate realBeginDate;
    QDate realEndDate;
    int realDays;

    int totalDays;
    QString mask;

    TNodeData()
    {
        serialNo = "";
        type = DataNode::Unknown;
        codeNo = 0.0;
        name = "";
        planBeginDate = QDate();
        planEndDate = QDate();
        planDays = 0;

        realBeginDate = QDate();
        realEndDate = QDate();
        realDays = 0;

        totalDays = 0;
        mask = "";
    }

    void clear()
    {
        serialNo = "";
        type = DataNode::Unknown;
        codeNo = 0.0;
        name = "";
        planBeginDate = QDate();
        planEndDate = QDate();
        planDays = 0;

        realBeginDate = QDate();
        realEndDate = QDate();
        realDays = 0;

        totalDays = 0;
        mask = "";
    }
};

class NodeManager
{
public:
    static NodeManager* getInstance();
    static void destroyInstance();

    //类初始化
    int init();
    DataNode* addNode(const TNodeData& data, DataNode* parent = NULL);
    DataNode* RootNode() { return m_rootNode; }

    //按节点的顺序给每一个节点赋予一个顺序号
    void sortData(DataNode* parent = NULL);

    const QMap<int, DataNode*>& sortMap() { return m_sortMap; }

    //获取节点下所有的子孙节点
    void allChildNode(DataNode* parent, QList<DataNode*>& childList);

    //获取节点所有的父节点
    void allParentNode(DataNode* child, QList<DataNode*>& parentList);

	//获取node对应的顺序号
	int serialNoOfNode(DataNode* node);

    //获取当前node的层级，即往上找根节点的层数
    int nodeStep(DataNode* node);
private:
    bool isNodeInModel(DataNode* const node);

private:
    NodeManager();
    ~NodeManager();
    static NodeManager* m_instance;

    DataNode* m_rootNode;

    //key为node的序号,value为node
    QMap<int, DataNode*> m_sortMap;
    //key为node，value为node的序号
    QMap<DataNode*, int> m_serialMap;

    //保存当前扩展的node的数目
    int m_expandedNodeNum;
};

#endif 
