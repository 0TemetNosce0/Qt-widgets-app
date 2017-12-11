#ifndef DELEGATEDEMO_H
#define DELEGATEDEMO_H

#include <QMainWindow>
#include <QPushButton>

#include "GSPTableView.h"
#include "GSPGridDataSourceModel.h"
#include "GSPCore.h"
#include "GLDFileUtils.h"
#include "GSPEngineUtils.h"
#include "GLDGridFrame.h"

namespace Ui {
class DelegateDemo;
}

class DelegateDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit DelegateDemo(QWidget *parent = 0);
    ~DelegateDemo();

private:
    void loadData();
    void initTableView();
    void doSomeTest();
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void debug();

private:
    Ui::DelegateDemo *ui;

    GSPModel m_model;
    GSPGridDataSourceModel *m_gridDataSourceModel;
    GSPTableView *m_tableView;
//    GlodonTableView *m_tableView;
    QPushButton *m_debugButton;
};

class TestEventHandler : public GLDGridEventHandler
{
public:
    virtual void onGetDropDownList(
            GSPCustomRowNode *rowNode, int col, GSPField field, GSPRecord record,
            GStrings &items, GStrings &pickResult, unsigned int &dropDownRows,
            bool &handled);
};

class CornerButton : public GTableCornerbutton
{

};

#endif // DELEGATEDEMO_H
