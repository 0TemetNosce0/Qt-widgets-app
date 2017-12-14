#ifndef KJMODEL_H
#define KJMODEL_H

#include <QStringList>
#include <QAbstractTableModel>

class KJModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit KJModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void reloadData();
    void addItem();
    void removeItem();

private:
    QStringList m_data;

signals:
    void editCompleted(const QString &);

public slots:
};

#endif // KJMODEL_H
