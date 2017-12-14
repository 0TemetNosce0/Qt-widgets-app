#include "simplelistwidget.h"
#include "ui_simplelistwidget.h"

#include "simplelistitemfactory.h"

#include <QListView>
#include <QVBoxLayout>
#include <QStringListModel>

SimpleListWidget::SimpleListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleListWidget)
{
    ui->setupUi(this);

    setWindowTitle("Simple List View");

    QStringList list;
    list << "Windows" << "Mac" << "Linux" << "Android" << "Blackberry";

    QStringListModel* model = new QStringListModel(list, this);

    QListView* itemView = new QListView(this);
    WebItemDelegate* delegate = new WebItemDelegate(new SimpleListItemFactory, this);

    itemView->setModel(model);
    delegate->setView(itemView);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(itemView);
}

SimpleListWidget::~SimpleListWidget()
{
    delete ui;
}
