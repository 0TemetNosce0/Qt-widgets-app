#ifndef TRACKMODEL_H
#define TRACKMODEL_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QList>
#include "track.h"
#include <QObject>

/**
  @brief 继承的模型类。
*/
class TrackModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TrackModel(QList<Track>* tracks, QObject* parent = 0);
    ~TrackModel();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index,
                         const QVariant &value,
                         int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<Track>* tracks;
};

#endif // TRACKMODEL_H
