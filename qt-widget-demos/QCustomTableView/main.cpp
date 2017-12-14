#include "widget.h"
#include "custommodel.h"
#include "customdelegate.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList<bool> datas;
    datas << false << true << true << false << true;

    CustomModel* model = new CustomModel;
    model->setModel(datas);

    CustomDelegate* delegate = new CustomDelegate;

    Widget w;
    w.setModel(model);
    w.setItemDelegate(delegate);

    w.show();

    return a.exec();
}
