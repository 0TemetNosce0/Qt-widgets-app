#ifndef DATANODE_H
#define DATANODE_H

#include <QMap>
#include <QList>
#include <QDate>
#include <QString>
#include <QStringList>

#include "DrawGantt.h"

class DataNode
{
public:
    enum Type{Root, Summary, Task, Unknown};
    DataNode();
    ~DataNode();

    Type type() {return m_type;}
    void setType(Type type) { m_type = type;}

    QString serialNo();
    void setSerialNo(const QString& serial);

    Qt::CheckState checkState(int col);
    void setCheckState(int col, Qt::CheckState state);

    float codeNo();
    void setCodeNo(float num);

    QString name();
    void setName(const QString& name);

    QDate planBeginDate();
    void setPlanBeginDate(const QDate& date);

    QDate planEndDate();
    void setPlanEndDate(const QDate& date);

    int planDays();
    void setPlanDays(int days);

    QDate realBeginDate();
    void setRealBeginDate(const QDate& date);

    QDate realEndDate();
    void setRealEndDate(const QDate& date);

    int realDays();
    void setRealDays(int days);

    int totalDays();
    void setTotalDays(int days);

    QString mask();
    void setMask(const QString& mask);

    DrawGantt* drawGantt() { return m_drawGantt; }

public:
    DataNode* parent();
    DataNode& setParent(DataNode* value);
    QList<DataNode*>& children();
    void insertChild(int index, DataNode* child);
    DataNode* removeChild(int index);
    
private:
    DataNode* m_parent;
    QList<DataNode*> m_children;

private:
	QString m_serialNo;
	Type m_type;

    //keyÎªÁÐºÅ
    QMap<int, Qt::CheckState> m_stateMap;

    float m_codeNo;
    QString m_name;

    QDate m_planBeginDate;
    QDate m_planEndDate;
    int m_planDays;

    QDate m_realBeginDate;
    QDate m_realEndDate;
    int m_realDays;

    int m_totalDays;
    QString m_mask;

    DrawGantt* m_drawGantt;
};

#endif // DATANODE_H