#include "WebItemDelegate.h"

#include <QListView>
#include <QVBoxLayout>
#include <QApplication>
#include <QStringListModel>

class SimpleListItemFactory : public WebItemFactory
{
public:
    virtual QString pageHeader();
    virtual QString itemTemplate(const QModelIndex &index);
    virtual int itemHeight(const QModelIndex &index);
    virtual bool recreateItemOnDataChange(const QModelIndex& index) const;
};

QString SimpleListItemFactory::pageHeader()
{
    return QString();
}

QString SimpleListItemFactory::itemTemplate(const QModelIndex& index)
{
    return index.data(Qt::DisplayRole).toString();
}

int SimpleListItemFactory::itemHeight(const QModelIndex& index)
{
    Q_UNUSED(index);
    return 20;
}

bool SimpleListItemFactory::recreateItemOnDataChange(const QModelIndex&) const
{
    return true;
}

class SimpleListWidget : public QWidget
{
public:
    SimpleListWidget(QWidget* parent = 0);
};

SimpleListWidget::SimpleListWidget(QWidget* parent)
{
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
};

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    SimpleListWidget widget;
    widget.resize(640, 480);
    widget.show();
    return app.exec();
}

