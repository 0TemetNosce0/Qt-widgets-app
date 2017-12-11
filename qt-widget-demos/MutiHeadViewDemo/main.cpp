#include <QTableView>
#include <QApplication>

#include "examplemodel.h"
#include "HierarchicalHeaderView.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ExampleModel em;
    QTableView tableView;
    HierarchicalHeaderView* headerViewer = new HierarchicalHeaderView(Qt::Horizontal, &tableView);
    headerViewer->setHighlightSections(true);
    headerViewer->setSectionsClickable(true);
    tableView.setHorizontalHeader(headerViewer);
    headerViewer = new HierarchicalHeaderView(Qt::Vertical, &tableView);
    headerViewer->setHighlightSections(true);
    headerViewer->setSectionsClickable(true);
    tableView.setVerticalHeader(headerViewer);
    tableView.setModel(&em);
    tableView.resizeColumnsToContents();
    tableView.resizeRowsToContents();
    tableView.show();
    tableView.resize(880, 530);
    return app.exec();
}
