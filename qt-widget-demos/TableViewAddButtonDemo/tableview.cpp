#include "tableview.h"

#include "tablemodel.h"
#include "buttondelegate.h"

TableView::TableView(QWidget *parent) :
    QTableView(parent)
{
    iniData();
}

TableView::~TableView()
{
    delete m_model;
}

void TableView::iniData()
{
    m_model = new TableModel();
    this->setModel(m_model);
    QStringList headers;
    headers << "Id" << "Progress";
    m_model->setHorizontalHeader(headers);

    QVector<QStringList> data;
    data.append(QStringList() << "1" << "22");
    data.append(QStringList() << "2" << "32");
    data.append(QStringList() << "3" << "2");
    data.append(QStringList() << "4" << "80");
    data.append(QStringList() << "5" << "40");
    m_model->setData(data);

    m_buttonDelegate = new ButtonDelegate(this);
    this->setItemDelegateForColumn(1, m_buttonDelegate);
    emit m_model->layoutChanged();
    this->setColumnWidth(1, 100);
}
