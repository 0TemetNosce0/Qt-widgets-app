#include "mainwindow.h"
#include "tagmngrlistmodel.h"
#include "tagmngrlistview.h"
#include <QListView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    TagMngrListView *listView = new TagMngrListView(this);
    listView->resize(800,600);
    this->resize(820,610);

    TagMngrListModel *treem = new TagMngrListModel("One\n Two \n Tree \n Four \n Five");
    listView->setModel(treem);

    listView->setSpacing(3);
    listView->setDragEnabled(true);
    listView->setAcceptDrops(true);
    listView->setDropIndicatorShown(true);
    listView->setDragDropMode(QAbstractItemView::InternalMove);
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

MainWindow::~MainWindow()
{
    
}
