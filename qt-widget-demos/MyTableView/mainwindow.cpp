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
    horizontalHeaderModel->setItem(0,0, QStringLiteral("�����ֽ�ṹ"));
    horizontalHeaderModel->setItem(0,4, QStringLiteral("�ƻ�����"));
    horizontalHeaderModel->setItem(0,7, QStringLiteral("ʵ�ʽ���"));
    horizontalHeaderModel->setItem(0,10, QStringLiteral("����"));
    horizontalHeaderModel->setItem(0,11, QStringLiteral("��ע"));

    horizontalHeaderModel->setItem(1,0, QStringLiteral("���"));
    horizontalHeaderModel->setItem(1,1, QStringLiteral("����"));
    horizontalHeaderModel->setItem(1,2, QStringLiteral("��������"));
    horizontalHeaderModel->setItem(1,3, QStringLiteral("��������"));
    horizontalHeaderModel->setItem(1,4, QStringLiteral("��ʼʱ��"));
    horizontalHeaderModel->setItem(1,5, QStringLiteral("����ʱ��"));
    horizontalHeaderModel->setItem(1,6, QStringLiteral("����"));
    horizontalHeaderModel->setItem(1,7, QStringLiteral("��ʼʱ��"));
    horizontalHeaderModel->setItem(1,8, QStringLiteral("����ʱ��"));
    horizontalHeaderModel->setItem(1,9, QStringLiteral("����"));

    horizontalHeaderModel->setSpan(0,0,1,4);
    horizontalHeaderModel->setSpan(0,4,1,3);
    horizontalHeaderModel->setSpan(0,7,1,3);

    horizontalHeaderModel->setSpan(0,10,2,1);
    horizontalHeaderModel->setSpan(0,11,2,1); //��֧�ֿ�Խ���ж��е����
}

void MainWindow::InitDataModel()
{
    TNodeData tData;
    tData.serialNo = QStringLiteral("��λ����");
    tData.type = DataNode::Root;

    DataNode* rootNode = NodeManager::getInstance()->addNode(tData);

    tData.clear();

    int max = 5;
    for (int i = 0; i < max; i++)
    {
        tData.serialNo = QStringLiteral("1���ӽڵ�A") + "_" + QString::number(i);
        tData.type = DataNode::Summary;
        tData.codeNo = 1;
        tData.name = QStringLiteral("����ʩ��");
        tData.planBeginDate = QDate::fromString("2012-11-08", "yyyy-MM-dd");
        tData.planEndDate = QDate::fromString("2012-12-08", "yyyy-MM-dd");
        tData.planDays = 30;
        tData.realBeginDate = QDate::fromString("2012-11-08", "yyyy-MM-dd");
        tData.realEndDate = QDate::fromString("2012-12-08", "yyyy-MM-dd");
        tData.realDays = 30;
        tData.totalDays = 30;
        tData.mask = QStringLiteral("��ʱ�깤");

        DataNode* nodeA = NodeManager::getInstance()->addNode(tData, rootNode);
        tData.serialNo = QStringLiteral("A1") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.1;
        tData.name = QStringLiteral("��������");

        DataNode* nodeA1 = NodeManager::getInstance()->addNode(tData, nodeA);

        tData.serialNo = QStringLiteral("A2") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.2;
        tData.name = QStringLiteral("һ׮��̨����");

        DataNode* nodeA2 = NodeManager::getInstance()->addNode(tData, nodeA);

        tData.serialNo = QStringLiteral("A3") + "_" + QString::number(i);
        tData.type = DataNode::Summary;
        tData.codeNo = 1.3;
        tData.name = QStringLiteral("��׮��̨����");

        DataNode* nodeA3 = NodeManager::getInstance()->addNode(tData, nodeA);

        tData.serialNo = QStringLiteral("A31") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.31;
        tData.name = QStringLiteral("����1");

        DataNode* nodeA31 = NodeManager::getInstance()->addNode(tData, nodeA3);

        tData.serialNo = QStringLiteral("A32") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.32;
        tData.name = QStringLiteral("����2");

        DataNode* nodeA32 = NodeManager::getInstance()->addNode(tData, nodeA3);

        tData.serialNo = QStringLiteral("A4") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.4;
        tData.name = QStringLiteral("��׮��̨����");

        DataNode* nodeA4 = NodeManager::getInstance()->addNode(tData, nodeA);

        tData.serialNo = QStringLiteral("A5") + "_" + QString::number(i);
        tData.type = DataNode::Task;
        tData.codeNo = 1.4;
        tData.name = QStringLiteral("���彽��");

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
