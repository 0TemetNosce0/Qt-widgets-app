#include "PeopleDialog.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QCoreApplication>
#include <QApplication>
#include <QDesktopServices>
#include <QMenu>
#include <QScrollBar>
#include <QSqlError>
#include <QDesktopServices>

PeopleDialog::PeopleDialog(QWidget *parent) : QDialog(parent)
{
    createLayouts();
    initHeader();
    initDataSource();
    initTable();
    fillLayouts();
    connectSignalsToSlots();
}

void PeopleDialog::createLayouts()
{
    mVLayout = new QVBoxLayout(this);
    mBottomBtnLayout = new QHBoxLayout(this);
}

void PeopleDialog::initHeader()
{
    QString headerText("<h1>Random people table</h1>");
    headerText += "<br>Click column headers to sort asc/desc.";
    headerText += "<br>Select row(s), right-click and choose \"Delete rows\" to delete data.";
    headerText += "<br>Right-click and choose \"Add row\" to add new record.<br>";
    mTopLabel = new QLabel(this);
    mTopLabel->setText(headerText);
}

void PeopleDialog::initDataSource()
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    QString dbDir = QStandardPaths::standardLocations (QStandardPaths::DocumentsLocation).join("");
    dbase.setDatabaseName(dbDir + "/people_db.sqlite");

    if (!dbase.open())
    {
        QMessageBox::information(this, "Error", "Couldn't reach database! Quitting app. "+ dbDir + " "+ dbase.lastError().text());
        QApplication::quit();
    }

    mDataModel = new PeopleDataModel(this, dbase);
}

void PeopleDialog::initTable()
{
    mTableView = new PeopleTableView(this);
    mTableView->setModel(mDataModel);
    mTableView->setContextMenuPolicy(Qt::CustomContextMenu);    
    mTableView->setSelectionMode(QTableView::ContiguousSelection);
    mTableView->setSelectionBehavior(QTableView::SelectRows);
    mTableView->verticalHeader()->hide();
    mTableView->setEditTriggers(QTableView::NoEditTriggers);
    sortByColumn(0);
}

void PeopleDialog::fillLayouts()
{
    mVLayout->addWidget(mTopLabel);
    mVLayout->addWidget(mTableView);
    mVLayout->addLayout(mBottomBtnLayout);
}

void PeopleDialog::connectSignalsToSlots()
{
    connect(this, SIGNAL(finished(int)), this, SLOT(finished(int)));
    QHeaderView *horizHeader = mTableView->horizontalHeader();
    connect(horizHeader, SIGNAL(sectionClicked(int)), this, SLOT(sectionClicked(int)));
    connect(mTableView, SIGNAL(customContextMenuRequested(QPoint)),SLOT(customMenuRequested(QPoint)));
    QScrollBar *vertScrollBar = mTableView->verticalScrollBar();
    connect(vertScrollBar, SIGNAL(sliderReleased()), this, SLOT(scrollingEnded()));
}

void PeopleDialog::finished(int result)
{
    (void)result;
}

void PeopleDialog::sortByColumn(int col)
{
    mDataModel->sortByColumn(col);
    mTableView->sortByColumn(col, mDataModel->getCurrentSortOrder());
    mTableView->resizeColumnsToContents();
}

void PeopleDialog::sectionClicked(int section)
{
    this->sortByColumn(section);    
}

void PeopleDialog::resizeEvent(QResizeEvent *event)
{
    (void)event;
    mTableView->resizeColumnsToContents();
}

void PeopleDialog::customMenuRequested(QPoint pos)
{
    QModelIndex idx = mTableView->indexAt(pos);
    QMenu *menu = new QMenu(this);

    QAction *deleteRowAction = new QAction("Delete rows", this);
    QAction *addRowAction = new QAction("Add row", this);
    connect( deleteRowAction, SIGNAL(triggered()), this, SLOT(deleteCurrentRows()) );
    connect( addRowAction, SIGNAL(triggered()), this, SLOT(addRow()) );

    menu->addAction(deleteRowAction);
    menu->addAction(addRowAction);
    menu->popup(mTableView->viewport()->mapToGlobal(pos));
}

void PeopleDialog::deleteCurrentRows()
{
    QModelIndexList il = mTableView->selectionModel()->selectedRows();

    for ( int i=0; i<il.length(); ++i ) {
        int row = il.at(i).row();
        mDataModel->removeRows(row, 1);
    }
    
    mDataModel->select();
}

void PeopleDialog::addRow()
{
    mDataModel->addRecord();
}

void PeopleDialog::scrollingEnded()
{
    mTableView->resizeColumnsToContents();
}
