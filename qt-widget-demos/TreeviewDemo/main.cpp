#include <QApplication>
#include <QHeaderView>
#include "treeview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TreeView view;

    view.setEditTriggers(QAbstractItemView::NoEditTriggers);

    view.resize(300,280);

    view.iterateOverItems();

    view.setWindowTitle(QStringLiteral("Linux 服务管理"));

    view.show();

    return app.exec();
}
