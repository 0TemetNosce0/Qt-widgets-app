#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLayout>
#include <QTableView>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked()), SLOT(slotOnButtonAddClicked()));
    connect(ui->btnRemove, SIGNAL(clicked()), SLOT(slotOnButtonRemoveClicked()));

    m_model = new KJModel(0);
    m_styledItemDelegate = new KJStyledItemDelegate(0);
    m_styledItemDelegate->tableView = ui->tableView;
    QList<KJConversationWidget*> widgets = m_styledItemDelegate->widgets;

    ui->tableView->viewport()->setLayout(new QVBoxLayout());

    for (int i = 0; i < widgets.count(); i++)
    {
        ui->tableView->viewport()->layout()->addWidget(widgets.at(i));
    }

    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableView->setItemDelegate(m_styledItemDelegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotOnButtonAddClicked()
{
    int rows = ui->ledRows->text().toInt();

    if (rows < 1)
    {
        rows = 1;
    }

    for (int i = 0; i < rows; i++)
    {
        m_model->addItem();
    }

    if (m_model->rowCount() > 0)
    {
        m_styledItemDelegate->refreshWidgets(false);
    }

    m_model->reloadData();
}

void MainWindow::slotOnButtonRemoveClicked()
{
    int rows = ui->ledRows->text().toInt();

    if (rows < 1)
    {
        rows = 1;
    }

    for (int i = 0; i < rows; i++)
    {
        m_model->removeItem();
    }

    if (m_model->rowCount() == 0)
    {
        m_styledItemDelegate->refreshWidgets(true);
    }

    m_model->reloadData();
}
