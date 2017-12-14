#include "filetreeitemfactory.h"

#include <QUrl>
#include <QFileSystemModel>

QString FileTreeItemFactory::pageHeader()
{
    return QString("<style>.header { font-weight: bold; padding: 10px; } "
                   ".item-text { margin: 5px; text-decoration: none; }</style>");
}

QString FileTreeItemFactory::itemTemplate(const QModelIndex & index)
{
    if (index.column() == 0)
    {
        QUrl url = QUrl::fromLocalFile(index.data(QFileSystemModel::FilePathRole).toString());
        return QString("<a href='%1' class='item-text' data-role='display'></a>").arg(url.toString());
    }
    else
    {
        return QString("<span data-role='display' class='item-text'></span>");
    }
}

int FileTreeItemFactory::itemHeight(const QModelIndex &)
{
    return 20;
}

QStringList FileTreeItemFactory::itemClasses(const QModelIndex &index)
{
    Q_UNUSED(index);
    return QStringList();
}
