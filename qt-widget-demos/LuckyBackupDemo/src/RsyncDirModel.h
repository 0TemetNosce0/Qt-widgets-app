/****************************************************************************
    Copyright (C) VCreate Logic Private Limited, Bangalore
    Contact: info@vcreatelogic.com
    
    This file is developed by VCreate Logic Private Limited and used as part of the "luckyBackup" project
    It is distributed under the terms of the GNU General Public License
    It is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    It is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the luckyBackup project.  If not, see <http://www.gnu.org/licenses/>.

****************************************************************************/

#ifndef Rsync_DIR_MODEL_H
#define Rsync_DIR_MODEL_H

#include <QAbstractItemModel>
//#include <QAuthenticator>
#include <QUrl>

class RsyncEntry;

struct RsyncDirModelData;
class RsyncDirModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    RsyncDirModel(QObject* parent=0);
    ~RsyncDirModel();

    void setUrl(const QUrl& url);
    void setUrl(const QUrl& url,const QString& cpath);
    void setUrl(const QUrl& url,const QString& cpath, const QStringList& cargs);

    QUrl url() const;

//    void setLogin(const QString& user,
//                  const QString& password);
//    QString user() const;
//    QString password() const;

    QUrl url(const QModelIndex& index) const;
    QString path(const QModelIndex& index) const;
    QModelIndex index(const QString& path) const;


public slots:
    void refresh(const QModelIndex& index=QModelIndex());

signals:
    void listingDone(RsyncEntry*);
//    void loginParamsRequest(QAuthenticator* auth);

protected:
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QModelIndex index(int row, int col, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex& index) const;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;

    QModelIndex index(RsyncEntry* entry) const;
    bool list() const;
    bool list(RsyncEntry* entry) const;

private slots:
    void slotListingDone(RsyncEntry* entry);

private:
    RsyncDirModelData* d;

};

#endif // Rsync_DIR_MODEL_H

 
