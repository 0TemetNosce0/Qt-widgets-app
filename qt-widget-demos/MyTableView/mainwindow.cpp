#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitSetting();

	resize(1690, 1000);

	QVBoxLayout *pLayout = new QVBoxLayout(this);
	pLayout->addWidget(ptableView);

	centralWidget()->setLayout(pLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitHHeaderModel(HHeaderModel *horizontalHeaderModel)
{
    horizontalHeaderModel->setItem(0,0, QStringLiteral("工作分解结构"));
    horizontalHeaderModel->setItem(0,4, QStringLiteral("计划进度"));
    horizontalHeaderModel->setItem(0,7, QStringLiteral("实际进度"));
    horizontalHeaderModel->setItem(0,10, QStringLiteral("工期"));
    horizontalHeaderModel->setItem(0,11, QStringLiteral("备注"));

    horizontalHeaderModel->setItem(1,0, QStringLiteral("序号"));
    horizontalHeaderModel->setItem(1,1, QStringLiteral("类型"));
    horizontalHeaderModel->setItem(1,2, QStringLiteral("工作编码"));
    horizontalHeaderModel->setItem(1,3, QStringLiteral("工作名称"));
    horizontalHeaderModel->setItem(1,4, QStringLiteral("开始时间"));
    horizontalHeaderModel->setItem(1,5, QStringLiteral("结束时间"));
    horizontalHeaderModel->setItem(1,6, QStringLiteral("工日"));
    horizontalHeaderModel->setItem(1,7, QStringLiteral("开始时间"));
    horizontalHeaderModel->setItem(1,8, QStringLiteral("结束时间"));
    horizontalHeaderModel->setItem(1,9, QStringLiteral("工日"));

    horizontalHeaderModel->setSpan(0,0,1,4);
    horizontalHeaderModel->setSpan(0,4,1,3);
    horizontalHeaderModel->setSpan(0,7,1,3);

    horizontalHeaderModel->setSpan(0,10,2,1);
    horizontalHeaderModel->setSpan(0,11,2,1); //不支持跨越多行多列的情况
}

void MainWindow::InitDataModel()
{
    TNodeData tData;
    tData.serialNo = QStringLiteral("单位工程");
    tData.type = DataNode::Root;

    DataNode* rootNode = NodeManager::getInstance()->addNode(tData);

    tData.clear();

    int max = 5;
    for (int i = 0; i < max; i++)
    {
        tData.serialNo = QStringLiteral("1级子节点A") + "_" + QString::number(i);
        tData.type = DataNode::Summary;
        tData.codeNo = 1;
        tData.name = QStringLiteral("基础施工");
        tData.planBeginDate = QDate::fromString("2012-11-08", "yyyy-MM-dd");
        tData.planEndDate = QDate::fromString("2012-12-08", "yyyy-MM-dd");
        tData.planDays = 30;
        tData.realBeginDate = QDate::fromString("2012-11-08", "yyyy-MM-dd");
        tData.realEndDate = QDate::fromString("2012-12-08", "yyyy-MM-dd");
        tData.realDays = 30;
        tData.totalDays = 30;
        tData.mask = QStringLiteral("按时完工");

        DataNode* nodeA = NodeManager::getInstance()->addNode(tData, rootNode);
        tData.serialNo = QStringLiteral("A1") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.1;
        tData.name = QStringLiteral("基础开挖");

        DataNode* nodeA1 = NodeManager::getInstance()->addNode(tData, nodeA);

        tData.serialNo = QStringLiteral("A2") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.2;
        tData.name = QStringLiteral("一桩承台浇筑");

        DataNode* nodeA2 = NodeManager::getInstance()->addNode(tData, nodeA);

        tData.serialNo = QStringLiteral("A3") + "_" + QString::number(i);
        tData.type = DataNode::Summary;
        tData.codeNo = 1.3;
        tData.name = QStringLiteral("二桩承台浇筑");

        DataNode* nodeA3 = NodeManager::getInstance()->addNode(tData, nodeA);

        tData.serialNo = QStringLiteral("A31") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.31;
        tData.name = QStringLiteral("浇筑1");

        DataNode* nodeA31 = NodeManager::getInstance()->addNode(tData, nodeA3);

        tData.serialNo = QStringLiteral("A32") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.32;
        tData.name = QStringLiteral("浇筑2");

        DataNode* nodeA32 = NodeManager::getInstance()->addNode(tData, nodeA3);

        tData.serialNo = QStringLiteral("A4") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.4;
        tData.name = QStringLiteral("三桩承台浇筑");

        DataNode* nodeA4 = NodeManager::getInstance()->addNode(tData, nodeA);

        tData.serialNo = QStringLiteral("A5") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.4;
        tData.name = QStringLiteral("伐板浇筑");

        DataNode* nodeA5 = NodeManager::getInstance()->addNode(tData, nodeA);
    }
}

void MainWindow::InitSetting()
{
    HHeaderView* headerView = new HHeaderView(Qt::Horizontal);
    HHeaderModel* horizontalHeaderModel = new HHeaderModel();

    InitHHeaderModel(horizontalHeaderModel);

    headerView->setModel(horizontalHeaderModel);

    headerView->setCheckedEnable(1, 0, true);
    headerView->setCheckedEnable(1, 2, true);

    headerView->setSortedEnable(1, 4);
    headerView->setSortedEnable(1, 5);
    headerView->setSortedEnable(1, 7);
    headerView->setSortedEnable(1,8);

    headerView->setCustomMenuEnbale(1,1);
    headerView->setCustomMenuEnbale(1,2);
    headerView->setCustomMenuEnbale(1,3);
    headerView->setCustomMenuEnbale(1,10);
    headerView->setCustomMenuEnbale(1,11);

    NodeManager::getInstance()->init();

    InitDataModel();

    NodeManager::getInstance()->sortData();

    DataModel* dataModel = new DataModel();
    dataModel->setRootNode(NodeManager::getInstance()->RootNode());


    //TableView ptableView;

    /*QSortFilterProxyModel* sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(dataModel);
    w.setModel(sortModel);*/
	ptableView = new TableView();
	ptableView->setModel(dataModel);
	ptableView->setHorizontalHeader(headerView);
	ptableView->m_dataTree->setHeader(headerView);
	ptableView->m_dataTree->expandAll();



    VHeaderView* vHeaderView = new VHeaderView(Qt::Vertical);
    VHeaderModel* vHeaderModel = new VHeaderModel();

    vHeaderView->setModel(vHeaderModel);
	ptableView->setVerticalHeader(vHeaderView);
    /*QTreeView w;
    w.setModel(dataModel);
    w.setHeader(headerView);
    w.expandAll();*/

    //w.resize(1200,800);
	ptableView->showMaximized();

	ptableView->setColumnWidth(0, 180);
	ptableView->setColumnWidth(1, 80);
	ptableView->setColumnWidth(2, 80);
	ptableView->setColumnWidth(3, 120);
	ptableView->setColumnWidth(4, 120);
	ptableView->setColumnWidth(5, 120);
	ptableView->setColumnWidth(6, 60);
	ptableView->setColumnWidth(7, 120);
	ptableView->setColumnWidth(8, 120);
	ptableView->setColumnWidth(9, 60);
	ptableView->setColumnWidth(10, 270);
	ptableView->setColumnWidth(11, 60);
}
