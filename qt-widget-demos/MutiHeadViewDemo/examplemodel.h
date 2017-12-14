#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include <QStandardItemModel>

class ExampleModel : public QAbstractTableModel
{
public:
    ExampleModel(QObject* parent = 0);

protected:
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;

    QVariant data(const QModelIndex& index, int role) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;

private:
    void fillHeaderModel(QStandardItemModel& headerModel);

private:
    QStandardItemModel _horizontalHeaderModel;
    QStandardItemModel _verticalHeaderModel;
};

#endif // EXAMPLEMODEL_H
