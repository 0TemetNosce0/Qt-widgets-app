#include "mainwindow.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "GSPEngineUtils.h"
#include "GLDFileUtils.h"
#include "GSPActions.h"
#include "GLDTableViewExport.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadUI();
    loadData();
    loadMenu();
    bool bEnableRedo = false;
    GString strLogFile = exePath() + "log.log"; //������־��
    if (fileExists(strLogFile)) //��log�ļ����м�飬������ڵĻ������лָ�
    {
        bEnableRedo = true;
    }
    m_commandLog = new GSPFileCommandLog(exePath() + "Log.log", m_model); //������־�ļ�
    m_model.fetchCommand();//��֮ǰ������ٴ���
    if (bEnableRedo)
    {
        m_model.beginUpdate();//��ʼ���£��ָ����ݱȽϴ�Ļ���ͳһ����
        try
        {
            m_model.beginIgnoreFieldConstraint();//�����ֶ�Լ����飬�ָ�����ټ��
            try
            {
                m_commandLog->redoFromSavePoint();//�ѱ������������������һ�飬ִ�лָ�
            }
            catch (...)
            {
                m_model.cancelIgnoreFieldConstraint();
                throw;
            }
            m_model.endIgnoreFieldConstraint();
        }
        catch (...)
        {
            m_model.cancelUpdate();
            throw;
        }
        m_model.endUpdate();
    }
}

//ִ��detach�¼�
MainWindow::~MainWindow()
{
    m_dataSource->queryCellValueEventList().remove(m_eventHandle);
    m_dataSource->queryCellAttributeEventList().remove(m_eventHandle);
//    freeAndNil(m_eventHandle);

//    if (m_model[0].findTable("Test").tableSchema().recordEventContainer().afterInsertEventList().exist(m_afterInsertRecord))
//    {
//        m_model[0].findTable("Test").tableSchema().recordEventContainer().afterInsertEventList().detach(m_afterInsertRecord);
//    }
//    freeAndNil(m_afterInsertRecord);
    freeAndNil(m_delegate);
    delete ui;
}

//�������ݲ��󶨽���
void MainWindow::loadData()
{
    m_model = gspEngine().createModel(true);//����Ϊtrue,��������������־
    GSPModelPersistent(m_model).loadFromFile(exePath() + "Test1.GSP", false, false);

    GSPViews iViews;
    iViews.push_back(m_model[0].findTable("Test").createView("", NULL));

    m_dataSource = new GSPGridDataSource();
    m_dataSource->setViews(iViews);

    m_dataSourceModel = new GSPGridDataSourceModel(this);
    m_dataSourceModel->setDataSource(m_dataSource);
    m_dataSourceModel->setGridSettingFileName(exePath() + "Test1.GSF");
    buildGridSetting();
    m_dataSourceModel->setActive(true);

    m_tableView->setModel(m_dataSourceModel);

    m_delegate = new MyDelegate();
    m_delegate->setDataSourceModel(m_dataSourceModel);
    m_tableView->setItemDelegate(m_delegate);

    m_eventHandle = new TestEventHandle();
    m_dataSource->queryCellValueEventList().push_back(m_eventHandle);
    m_dataSource->queryCellAttributeEventList().push_back(m_eventHandle);

    //ע�ᴥ����
//    GSPTable iTable = m_model[0].findTable("Test");
//    m_afterInsertRecord = new TestAfterInsertRecord();
//    if (! iTable.tableSchema().recordEventContainer().afterInsertEventList().exist(m_afterInsertRecord))
//    {
//        iTable.tableSchema().recordEventContainer().afterInsertEventList().attach(m_afterInsertRecord, "", false);
//    }
}


void MainWindow::loadUI()
{
    m_tableView = new GSPTableView(ui->centralWidget);
    m_tableView->setGeometry(0, 0, 600, 600);
}

void MainWindow::loadMenu()
{
    GSPDeleteAction *acDeleteAction = new GSPDeleteAction("Del", this);
    acDeleteAction->setDataSource(m_dataSource);
    acDeleteAction->setIsTree(true);
    ui->mainToolBar->addAction(acDeleteAction);

    GSPInsertAction *acInsert = new GSPInsertAction("Insert", this);
    acInsert->setDataSource(m_dataSource);
    acInsert->setBefore(false);
    acInsert->setKind(gikAppend);
    acInsert->setViewIndex(0);
    ui->mainToolBar->addAction(acInsert);

    QAction *acFunction = new QAction("TestFun", this);
    connect(acFunction, SIGNAL(triggered()), this, SLOT(testFunction()));
    ui->mainToolBar->addAction(acFunction);

    QAction *acDebug = new QAction("Debug", this);
    connect(acDebug, SIGNAL(triggered()), this, SLOT(doDebug()));
    ui->mainToolBar->addAction(acDebug);

    QAction *acSave = new QAction("Save", this);
    connect(acSave, SIGNAL(triggered()), this, SLOT(doSave()));
    ui->mainToolBar->addAction(acSave);

    QAction *acUndo = new QAction("Undo", this);
    connect(acUndo, SIGNAL(triggered()), this, SLOT(doUndo()));
    ui->mainToolBar->addAction(acUndo);

    QAction *acRedo = new QAction("Redo", this);
    connect(acRedo, SIGNAL(triggered()), this, SLOT(doRedo()));
    ui->mainToolBar->addAction(acRedo);
}

//��̬�޸�GSF
void MainWindow::buildGridSetting()
{
    GSPGridSetting *oGridSetting = m_dataSourceModel->gridDataSource()->gridSetting();
    oGridSetting->setDesignState(true);
    try
    {
        GSPColSetting *oColSetting = dynamic_cast<GSPColSetting *>(oGridSetting->colSettings()->insert());
        int nIndex = oGridSetting->colSettings()->indexOf(oColSetting);
        oColSetting->setDisplayWidth(80);
        oGridSetting->titleRows()->items(0)->cells(nIndex)->setCaption("home");
        oGridSetting->tableSettings()->items(0)->fieldSettings()->items(nIndex)->setEditFieldName("home");
    }
    catch (...)
    {
        oGridSetting->setDesignState(false);
    }
    oGridSetting->setDesignState(false);
}

//�Զ��庯��ִ��
void MainWindow::testFunction()
{
    MyFunction *oFun = new MyFunction();
    m_model.gepEngine().functionCenter().Register((IGEPFunction *)oFun);

    GEPParser iParser = m_model.gepEngine().createParser();
    iParser.setExpression("aaa()");
    iParser.evaluate();
    GString strValue = iParser.result().asString();
    QMessageBox::information(NULL, "Result", strValue, QMessageBox::Ok);
}

//����һ������
void MainWindow::doDebug()
{
    GSPTable iTable = m_model[0].findTable("Test");
    GSPRecord iRecord = iTable.newRecord();
    iTable.append(iRecord);
    m_commandLog->logCommand(m_model.fetchCommand());//����Ӧ�ĵط�д������
}

void MainWindow::doSave()
{
    m_commandLog->markSavePoint();//�����ȷ���������ļ��󣬿��Ե�һ����������´λָ���ʱ��ʹ����￪ʼ�ָ�
}

void MainWindow::doUndo()
{
    if (m_commandLog->undoEnabled())
    {
        m_commandLog->undo();
    }
}

void MainWindow::doRedo()
{
    if (m_commandLog->redoEnabled())
    {
        m_commandLog->redoEnabled();
    }
}

//���ñ༭��ʽ
GEditStyle MyDelegate::editStyle(GSPCustomRowNode *rowNode, int dataCol, bool &readOnly) const
{
    if (3 == dataCol)
    {
        return esDropDown;
    }
    else
    {
        return GSPDefaultItemDelegate::editStyle(rowNode, dataCol, readOnly);
    }
}

//queryCell�ı�ֵ
void TestEventHandle::onQueryCellValue(GSPCustomRowNode *rowNode, int col, GSPField field, GSPRecord record, GVariant &value, bool &handled)
{
    G_UNUSED(handled);
    G_UNUSED(record);
    G_UNUSED(field);
    if ((4 == col) && (2 == rowNode->rowNo()))
    {
        QImage oImage = QImage(":/res/res/Add16.png");
        oImage.setText("Image", "..\\bin\\Add16.png");
        value = oImage;
    }
    else if ((4 == col) && (1 == rowNode->rowNo()))
    {
        QImage oImage = QImage(":/res/res/back.png");
        oImage.setText("Image", "..\\bin\\back.png");
        value = oImage;
    }
}

//����queryCellAttribute
void TestEventHandle::onQueryCellAttribute(GSPCustomRowNode *rowNode, int col, GSPField field, GSPRecord record, int role, GVariant &attribute, bool &handled)
{
    G_UNUSED(handled);
    G_UNUSED(rowNode);
    if (3 == col)
    {
        if (role == Qt::BackgroundColorRole)
        {
            attribute = QColor(0xFF, 0xFF, 0xC8);
        }
    }
    else if (4 == col)
    {
        if (Qt::TextAlignmentRole == role)
        {
            attribute = Qt::AlignHCenter;
        }
    }
}

//����󴥷�������¼�
void TestAfterInsertRecord::afterInsertRecord(GSPRecord &record)
{
    G_UNUSED(record);
    QMessageBox::information(NULL, "Test", "Insert Ok", QMessageBox::Ok);
}

GString MyFunction::name()
{
    return "aaa";
}

GEPDataType MyFunction::resultDataType()
{
    return edtString;
}

GEPDataMatchType MyFunction::matchParam(long paramCount, IGEPNodeList *params)
{
    G_UNUSED(paramCount);
    G_UNUSED(params);
    return dmtExact;
}

void MyFunction::execute(long paramCount, IGEPNodeList *params, IGEPData *result)
{
    G_UNUSED(paramCount);
    G_UNUSED(params);
    result->setAsString("bbb");
}

