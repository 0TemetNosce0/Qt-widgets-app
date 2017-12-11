#ifndef INSTALLEDAPPMODEL_H
#define INSTALLEDAPPMODEL_H

#include <QStringList>
#include <QAbstractTableModel>
#include <QItemSelectionModel>

class InstalledAppModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum InstalledAppModelRole
    {
        AppName = Qt::UserRole + 1,
        AppIcon,
        AppLatestVer,
        AppVer,
        AppSize,
        DocSize
    };
    explicit InstalledAppModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    void remove();
    void changeName();
    void changeChecked();
    void setSelectionModel(QItemSelectionModel *model);
signals:

public slots:

private slots:
    void handleSelectionChanged(QItemSelection, QItemSelection);

private:
    QStringList m_name;
    bool m_checked;
    QItemSelectionModel *m_selectionModel;
    int m_rowCount;
};

#endif // INSTALLEDAPPMODEL_H
