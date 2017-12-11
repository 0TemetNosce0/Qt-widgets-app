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

    //���ʼ��
    int init();
    DataNode* addNode(const TNodeData& data, DataNode* parent = NULL);
    DataNode* RootNode() { return m_rootNode; }

    //���ڵ��˳���ÿһ���ڵ㸳��һ��˳���
    void sortData(DataNode* parent = NULL);

    const QMap<int, DataNode*>& sortMap() { return m_sortMap; }

    //��ȡ�ڵ������е�����ڵ�
    void allChildNode(DataNode* parent, QList<DataNode*>& childList);

    //��ȡ�ڵ����еĸ��ڵ�
    void allParentNode(DataNode* child, QList<DataNode*>& parentList);

	//��ȡnode��Ӧ��˳���
	int serialNoOfNode(DataNode* node);

    //��ȡ��ǰnode�Ĳ㼶���������Ҹ��ڵ�Ĳ���
    int nodeStep(DataNode* node);
private:
    bool isNodeInModel(DataNode* const node);

private:
    NodeManager();
    ~NodeManager();
    static NodeManager* m_instance;

    DataNode* m_rootNode;

    //keyΪnode�����,valueΪnode
    QMap<int, DataNode*> m_sortMap;
    //keyΪnode��valueΪnode�����
    QMap<DataNode*, int> m_serialMap;

    //���浱ǰ��չ��node����Ŀ
    int m_expandedNodeNum;
};

#endif 
