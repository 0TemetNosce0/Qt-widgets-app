#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
    class Dialog;
}

class cCustomHeaderModel;
class cProxyModelWithHeaderModels;
class cCustomHeaderView;
class cCheckBoxItemDelegate;
class cDefaultItemDelegate;
class QStandardItemModel;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void closeEvent(QCloseEvent *e);

private:
    void initHorizontalHeaderModel(cCustomHeaderModel *horizontalHeaderModel);
    void initProxyModel(cProxyModelWithHeaderModels * pProxyModel, QStandardItemModel * dataModel, 
                         cCustomHeaderModel * horizontalHeaderModel);
    void setUpTableView(cCustomHeaderView * horizontalHeaderView, cProxyModelWithHeaderModels * pProxyModel, 
                        cCheckBoxItemDelegate* checkBoxItemDelegate, cDefaultItemDelegate *defaultItemDelegate);
    void setUpTableWidget(cCheckBoxItemDelegate * checkBoxItemDelegate);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
