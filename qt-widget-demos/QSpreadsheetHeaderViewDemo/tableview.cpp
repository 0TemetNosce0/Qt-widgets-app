#include "tableview.h"
#include <QFile>

TableView::TableView(QWidget *parent)
    : QTableView(parent)
{
    loadStyleSheet();
}

void TableView::loadStyleSheet(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly))
    {
        return;
    }

    this->setStyleSheet(file.readAll());
    file.close();
}
