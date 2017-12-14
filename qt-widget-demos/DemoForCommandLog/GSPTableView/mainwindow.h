#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GSPGridDataSource.h"
#include "GSPGridDataSourceModel.h"
#include "GSPTableView.h"
#include "GSPCore.h"
#include "GSPDefaultItemDelegate.h"
#include "GSPDataSourceEvent.h"
#include "GEPCustomFunction.h"
#include "GSPCommandLog.h"

namespace Ui {
class MainWindow;
}

class MyDelegate;
class TestEventHandle;
class TestAfterInsertRecord;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
    void loadData();
    void loadUI();
    void loadMenu();
    void buildGridSetting();
private slots:
    void testFunction();
    void doDebug();
    void doSave();
    void doUndo();
    void doRedo();

private:
    Ui::MainWindow *ui;
    GSPTableView *m_tableView;
    GSPGridDataSource *m_dataSource;
    GSPGridDataSourceModel *m_dataSourceModel;
    GSPModel m_model;
    MyDelegate *m_delegate;
    TestEventHandle *m_eventHandle;
    TestAfterInsertRecord *m_afterInsertRecord;
    GSPFileCommandLog *m_commandLog;
};

class MyDelegate : public GSPDefaultItemDelegate
{
public:
    GEditStyle editStyle(GSPCustomRowNode *rowNode, int dataCol, bool &readOnly) const;
};

class TestEventHandle : public GSPQueryCellValueEvent, public GSPQueryCellAttributeEvent
{
public:
    void onQueryCellValue(GSPCustomRowNode *rowNode, int col, GSPField field,
                          GSPRecord record, GVariant &value, bool &handled);
    void onQueryCellAttribute(GSPCustomRowNode *rowNode, int col, GSPField field,
                              GSPRecord record, int role, GVariant &attribute, bool &handled);
};

class TestAfterInsertRecord : public GSPAfterInsertRecordImpl
{
public:
    void afterInsertRecord(GSPRecord &record);
};

class MyFunction : public CGEPCustomFunction
{
public:
    GString GSPMETHODCALLTYPE name();
    GEPDataType GSPMETHODCALLTYPE resultDataType();
    GEPDataMatchType GSPMETHODCALLTYPE matchParam(long paramCount, IGEPNodeList * params);
    void GSPMETHODCALLTYPE execute(long paramCount, IGEPNodeList *params, IGEPData *result);
};
#endif // MAINWINDOW_H
