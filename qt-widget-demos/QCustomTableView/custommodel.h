#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <QAbstractTableModel>

class CustomModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CustomModel(QObject *parent = 0);
    void setModel(const QList<bool>& list);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

signals:

public slots:

private:
    QList<bool> list;
};

#endif // CUSTOMMODEL_H
