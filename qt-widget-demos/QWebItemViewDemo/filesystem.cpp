#include "filesystem.h"

#include "WebItemDelegate.h"
#include "filetreeitemfactory.h"

#include <QApplication>
#include <QStringListModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QFileSystemModel>
#include <QDesktopServices>

#include <QTime>
#include <QUrl>

#include <QDebug>

FileSystemView::FileSystemView(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("File System View");

    QTreeView* itemView = new QTreeView(this);
    itemView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    itemView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QFileSystemModel* model = new QFileSystemModel(this);
    model->setRootPath("/");

    WebItemDelegate* delegate = new WebItemDelegate(new FileTreeItemFactory, this);
    connect(delegate, SIGNAL(linkClicked(QUrl)), this, SLOT(openLink(QUrl)));

    itemView->setModel(model);
    delegate->setView(itemView);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(itemView);
}

FileSystemView::~FileSystemView()
{

}

void FileSystemView::openLink(const QUrl& url)
{
    QDesktopServices::openUrl(url);
}


