#ifndef HHEADERMODEL_H
#define HHEADERMODEL_H

#include <QAbstractItemModel>


//��Ԫ��ϲ���С
struct CellSpan
{
    CellSpan() : _curRow(-1),_curCol(-1), _rowSpan(-1), _colSpan(-1), _firstRow(-1), _firstCol(-1), _validFlag(false)
    {
    }

    CellSpan(int row, int col, int spanRow, int spanCol, int firstRow, int firstCol) 
    { 
        _curRow = row;
        _curCol = col;
        _rowSpan = spanRow;
        _colSpan = spanCol;
        _firstRow = firstRow;
        _firstCol = firstCol;
        _validFlag = true;
    }

    bool isValid() 
    { 
        return _validFlag; 
    }

    int _curRow;
    int _curCol;
    int _rowSpan;
    int _colSpan;
    int _firstRow;
    int _firstCol;
    bool _validFlag;
};


class HHeaderModel : public QAbstractItemModel
{
    struct ModelData //ģ�����ݽṹ
    {
        QString _text;
     
        ModelData() : _text("")
        {
        }
    };

    Q_OBJECT

public:
    HHeaderModel(QObject *parent = 0);
    ~HHeaderModel();

    void setItem(int row, int col, const QString& text);

    QString item(int row, int col);

    void setSpan(int firstRow, int firstColumn, int rowSpanCount, int columnSpanCount);
    const CellSpan& getSpan(int row, int column);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    //�ҵ���Ӧ��ģ������
    ModelData* modelData(const QModelIndex & index) const;

private:
    //key rowNo,  key colNo
    QMap<int, QMap<int, ModelData*> > m_modelData;
    int m_MaxCol;

    CellSpan m_InvalidCellSpan;
    QList<CellSpan> m_cellSpanList;

};


#endif // HHEADERMODEL_H
