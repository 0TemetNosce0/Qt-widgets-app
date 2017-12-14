#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpData(const QList<Student>& list)
{
    m_model = new CustomModel(this);
    m_model->setStudenetList(list);

    m_delegate = new CustomDelegate(this);

    ui->tableView->setModel(m_model);
    ui->tableView->setItemDelegate(m_delegate);
}

void MainWindow::on_insertButton_clicked()
{
    m_insertWidget = new InsertWidget;
    int result = m_insertWidget->exec();
    if (result == QDialog::Accepted)
    {
        m_model->insertRows(0, 1);
        QModelIndex index1 = m_model->index(0, 0);
        m_model->setData(index1, m_insertWidget->num());

        QModelIndex index2 = m_model->index(0, 1);
        m_model->setData(index2, m_insertWidget->name());

        QModelIndex index3 = m_model->index(0, 2);
        m_model->setData(index3, m_insertWidget->id());

        QModelIndex index4 = m_model->index(0, 3);
        m_model->setData(index4, m_insertWidget->phone());

        QModelIndex index5 = m_model->index(0, 4);
        m_model->setData(index5, m_insertWidget->level());

        QModelIndex index6 = m_model->index(0, 5);
        m_model->setData(index6, m_insertWidget->desc());

        QModelIndex index7 = m_model->index(0, 6);
        m_model->setData(index7, false);
    }

    m_insertWidget->deleteLater();
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    m_model->removeRows(index.row(), 1);
}

void MainWindow::on_selectAllButton_clicked()
{
    m_model->selectAll();
}

void MainWindow::on_unselectAllButton_clicked()
{
    m_model->unselect();
}
