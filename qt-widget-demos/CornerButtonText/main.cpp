#include "mainwindow.h"
#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}



#include <QApplication>

#include <QSplitter>

#include <QTreeView>
#include <QListView>
#include <QTableView>

#include <QStandardItemModel>

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    QTreeView *tree = new QTreeView();
    QListView *list = new QListView();
    QTableView *table = new QTableView();

    QSplitter splitter;
    splitter.addWidget(tree);
    splitter.addWidget(list);
    splitter.addWidget(table);

    QStandardItemModel model( 5, 2 );

    for( int r=0; r<5; r++ )
    {
        for( int c=0; c<2; c++)
        {
            QStandardItem *item = new QStandardItem(QString("Row:%0, Column:%1").arg(r).arg(c));

            if(c == 0)
            {
                for(int i=0; i<3; i++)
                {
                    QStandardItem *child = new QStandardItem(QString("Item %0").arg(i));
                    child->setEditable(false);
                    item->appendRow(child);
                }
            }

            model.setItem(r, c, item);
        }
    }

    model.setHorizontalHeaderItem(0, new QStandardItem("Foo"));
    model.setHorizontalHeaderItem(1, new QStandardItem("Bar-Baz"));

    tree->setModel(&model);
    list->setModel(&model);
    table->setModel(&model);

    list->setSelectionModel(tree->selectionModel());
    table->setSelectionModel(tree->selectionModel());

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    splitter.show();

    MainWindow w;
    w.show();

    return app.exec();
}
