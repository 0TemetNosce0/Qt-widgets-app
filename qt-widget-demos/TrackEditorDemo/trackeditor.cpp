#include "trackeditor.h"
#include "ui_trackeditor.h"

#include <QTableView>
#include <QHBoxLayout>
#include <QAbstractTableModel>
#include "trackmodel.h"
#include "trackdelegate.h"

TrackEditor::TrackEditor(QList<Track>* tracks, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrackEditor),
    tableView(new QTableView(this)),
    model(new TrackModel(tracks))
{
    ui->setupUi(this);

    tableView->setModel(model);
    tableView->setItemDelegateForColumn(1, new TrackDelegate());

    QHBoxLayout* mainLayout(new QHBoxLayout(this));
    mainLayout->addWidget(tableView);
    setLayout(mainLayout);
}

TrackEditor::~TrackEditor()
{
    delete ui;
}
