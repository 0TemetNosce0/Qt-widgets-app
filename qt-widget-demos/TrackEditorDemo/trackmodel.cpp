#include "trackmodel.h"
#include <QTime>

TrackModel::TrackModel(QList<Track> *tracks, QObject* parent) :
    QAbstractTableModel(parent)
{
    this->tracks = tracks;
}

TrackModel::~TrackModel()
{

}

int TrackModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if (tracks)
    {
        return tracks->count();
    }
    else
    {
        return 0;
    }
}

int TrackModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

QVariant TrackModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid())
    {
        return QVariant();
    }

    if (Qt::TextAlignmentRole == role)
    {
        return (int)(Qt::AlignLeft | Qt::AlignVCenter);
    } /*else if (Qt::EditRole == role) {
        if (index.column() == 1) {
            int secs = tracks->at(index.row()).getDuration();
            QTime time(secs / 60, secs % 60);
            return time;
        } else if (0 == index.column()) {
            return tracks->at(index.row()).getTitle();
        }*/
    else if (Qt::DisplayRole == role && index.column() == 0)
    {
        return tracks->at(index.row()).getTitle();
    }
    else if (Qt::EditRole == role && index.column() == 1)
    {
        return tracks->at(index.row()).getDuration();
    }
/*
        switch (index.column()) {
        case 0:
            return tracks->at(index.row()).getTitle();
            break;
        case 1: {
            int secs = tracks->at(index.row()).getDuration();
            QTime time(secs / 60, secs % 60);
            return time;
            break;
        }
        default:
            break;
        }*/
    //}

    return QVariant();
}

bool TrackModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if ( !index.isValid())
    {
        return false;
    }

    if (Qt::EditRole == role)
    {
        if (1 == index.column())
        {
            //int secs = value.toInt();
            int secs = index.model()->data(index, Qt::EditRole).toInt();
            QTime time = index.model()->data(index, Qt::EditRole).toTime();
            //tracks->value(index.row()).setDuration(secs);
            ((*tracks)[index.row()]).setDuration(secs);
            //((*tracks)[index.row()]).setDuration(time.hour() * 60 + time.minute());
            emit dataChanged(index, index);

            return true;
        }
        else
        {
            QAbstractTableModel::setData(index, value, role);
            emit dataChanged(index, index);

            return true;
        }
    }
    else
    {
        QAbstractTableModel::setData(index, value, role);
        emit dataChanged(index, index);

        return true;
    }
}


Qt::ItemFlags TrackModel::flags(const QModelIndex &index) const
{
    if (1 == index.column())
    {
        return (QAbstractTableModel::flags(index) | Qt::ItemIsEditable);
    }
    else
    {
        return QAbstractTableModel::flags(index);
    }
}
