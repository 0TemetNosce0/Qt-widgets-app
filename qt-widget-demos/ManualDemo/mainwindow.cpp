#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(QSize(800, 600).expandedTo(this->minimumSizeHint()));//���ó�ʼ���ڴ�С
    this->setWindowIcon(QIcon(":/images/books.png"));//���ñ�����ͼ��
    this->setWindowTitle(QStringLiteral("��е��Ƹ����ֲ�"));//���ñ���������

    if(this->createConnect())
    {
        mainSplitter = new QSplitter(Qt::Horizontal);//�����
        this->createActions();//��������
        this->createMenus();//�����˵���
        this->createToolBars();//����������
        this->createMenuTree();//����Ŀ¼��
        this->createAd();//����������
        this->createTable();//����������
        mainSplitter->setStretchFactor(1,1);//���ñ�����С�Ҵ�
        this->setCentralWidget(mainSplitter);//���������
    }
}

MainWindow::~MainWindow()
{

}

//��������
bool MainWindow::createConnect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");  //ʹ��sqlite���ݿ�����
    db.setDatabaseName("../manual/manualdata.db3");  //����֮ǰ���������ݿ�
    bool connectOK = db.open();  //�����������ݿ�
    if(!connectOK)//�ж������Ƿ�ɹ�
    {
        QMessageBox::critical(0,QStringLiteral("�޷������ݿ�"),db.lastError().databaseText());//����ʧ�ܺ���ʾ��ʾ��
        return false;
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)//�¼����رա�
{
    event->accept();
}

//��������
void MainWindow::createActions()
{
    //�˳�
    exitAction = new QAction(QStringLiteral("�˳�(&X)"), this);
    exitAction->setShortcut(QStringLiteral("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //�Ի������
    aboutAction = new QAction(QStringLiteral("����(&A)"), this);

    //����
    searchAction = new QAction(QStringLiteral("����(&S)"),this);
    searchAction->setIcon(QIcon(":/images/search.png"));
    searchAction->setStatusTip(QStringLiteral("�����������"));

    //����Ŀ¼����
    goHomeAction = new QAction(QStringLiteral("����Ŀ¼"), this);
    goHomeAction->setIcon(QIcon(":/images/home.png"));
    goHomeAction->setStatusTip(QStringLiteral("����Ŀ¼"));
}

//�����˵���
void MainWindow::createMenus()
{
    //�˵����ļ���
    fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�(&F)"));
    fileMenu->addAction(exitAction);

    //�˵������ߡ�
    toolsMenu = menuBar()->addMenu(QStringLiteral("����(&T)"));

    //�˵���������
    helpMenu = menuBar()->addMenu(QStringLiteral("����(&H)"));
    helpMenu->addAction(aboutAction);
}

//����������
void MainWindow::createToolBars()
{
    mainToolBar = addToolBar(QStringLiteral("����(&S)"));//����������
    searchLabel = new QLabel(QStringLiteral(" ���� "));//����������ǩ
    mainToolBar->addWidget(searchLabel);//�����������
    searchCombo = new QComboBox;//����������
    searchCombo->clear();//���������
    searchCombo->setEditable(true);//����������ɱ༭
    searchCombo->insertItem(0,QStringLiteral(""));//��������ӵ�һ��հ�
    searchCombo->setMinimumWidth(200);//������������С���

    mainToolBar->addWidget(searchCombo);//�����������������
    mainToolBar->addAction(searchAction);//���������������ť
    mainToolBar->addAction(goHomeAction);//������ӷ���Ŀ¼��ť
    mainToolBar->setMovable(false);//��������Ϊ���ɶ�
}

//����Ŀ¼��
void MainWindow::createMenuTree()
{
    QSqlQuery fstMenuQuery;//��firstmenus����
    QSqlQuery secMenuQuery;//��secondmenus����
    QSqlQuery thdMenuQuery;//��thirdmenus����
    if(fstMenuQuery.exec("SELECT menuitem, id FROM firstmenus;"))//�ж��������ݿ���һ��Ŀ¼
    {
        int fstNumRows = 0;//�����������ص�����
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))//�ж������Ƿ����QuerySize
        {
            fstNumRows = fstMenuQuery.size();//�����ص���������fstNumRows
        }
        else
        {
            fstMenuQuery.last();//�������һ��
            fstNumRows = fstMenuQuery.at()+1;//�����ص���������fstNumRows
            fstMenuQuery.seek(-1);//���ص�һ��
        }
        if(fstNumRows>0)//�ж������õ��Ľ���Ƿ����0
        {
            menuTree = new QTreeView();//����Ŀ¼��
            treeModel = new QStandardItemModel(fstNumRows,1);//����Ŀ¼�Ĵ�С
            treeModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("Ŀ¼"));//����Ŀ¼ͷ
            int fstInt = 0;
            while(fstMenuQuery.next())//����һ��Ŀ¼
            {
                QStandardItem *fstItem = new QStandardItem(fstMenuQuery.value(0).toString());//�½�һ��Ŀ¼������
                fstItem->setData(1,Qt::UserRole);//����Ŀ¼����
                treeModel->setItem(fstInt,fstItem);//��һ��Ŀ¼���ص�Ŀ¼����
                fstInt++;//fstInt�Լ�

                if(secMenuQuery.exec("SELECT menuitem, id FROM secondmenus WHERE parentid = "+ fstMenuQuery.value(1).toString()))//�ж��Ƿ��ж���Ŀ¼
                {
                    int secNumRows = 0;//�����������ص�����
                    if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                    {
                        secNumRows = secMenuQuery.size();
                    }
                    else
                    {
                        secMenuQuery.last();
                        secNumRows = secMenuQuery.at()+1;
                        secMenuQuery.seek(-1);
                    }
                    if(secNumRows>0)//�ж������õ��Ľ���Ƿ����0
                    {
                        while(secMenuQuery.next())//���ض���Ŀ¼
                        {
                            QStandardItem *secItem = new QStandardItem(secMenuQuery.value(0).toString());//�½�����Ŀ¼������
                            secItem->setData(2,Qt::UserRole);//����Ŀ¼����Ϊ2
                            fstItem->appendRow(secItem);//���ض���Ŀ¼

                            if(thdMenuQuery.exec("SELECT menuitem, id FROM thirdmenus WHERE parentid = "+ secMenuQuery.value(1).toString()))
                            {
                                int thdNumRows = 0;
                                if(db.driver()->hasFeature(QSqlDriver::QuerySize))
                                {
                                    thdNumRows = thdMenuQuery.size();
                                }
                                else
                                {
                                    thdMenuQuery.last();
                                    thdNumRows = thdMenuQuery.at()+1;
                                    thdMenuQuery.seek(-1);
                                }
                                if(thdNumRows>0)
                                {
                                    while(thdMenuQuery.next())//��������Ŀ¼
                                    {
                                        QStandardItem *thdItem = new QStandardItem(thdMenuQuery.value(0).toString());//�½�����Ŀ¼������
                                        thdItem->setData(3,Qt::UserRole);//����Ŀ¼����Ϊ3
                                        secItem->appendRow(thdItem);//��������Ŀ¼
                                    }
                                }
                            }
                        }
                    }
                }
            }
            menuTree->setModel(treeModel);//����Ŀ¼����MODEL
            menuTree->setEditTriggers(QAbstractItemView::NoEditTriggers);//����Ϊ���ɱ༭
            menuTree->resizeColumnToContents(0);//�������Ŀ��
            mainSplitter->addWidget(menuTree);//��Ŀ¼���ص��������

            connect(menuTree,SIGNAL(clicked(QModelIndex)),this,SLOT(menuTreeClick(QModelIndex)));//���û������Ŀ¼ʱ������menuTreeClick����
        }
    }
}

void MainWindow::createAd()//�������
{
    adView = new AdGraphicsView;//������ͼ
    this->readAd(1);//��ȡid=1�Ĺ��
    this->adView->init();//��ʼ��
    mainSplitter->addWidget(this->adView);//�����������
}

void MainWindow::createTable()//����������
{
    rightSplitter = new QSplitter(Qt::Vertical);

    QStandardItemModel headerModel;
    this->buildTableHeaderModel(headerModel);

    QStandardItemModel dataModel;
    this->buildTableDataModel(dataModel);

    ProxyModelWithHeaderModels model;
    //model.setModel(&dataModel);
    model.setHorizontalHeaderModel(&headerModel);
    model.setVerticalHeaderModel(&headerModel);

    dataTable = new QTableView;
    HierarchicalHeaderView* hv = new HierarchicalHeaderView(Qt::Horizontal,dataTable);
    dataTable->setHorizontalHeader(hv);
    hv = new HierarchicalHeaderView(Qt::Vertical,dataTable);

    dataTable->setVerticalHeader(hv);
    dataTable->setModel(&model);
    dataTable->resizeColumnsToContents();
    dataTable->resizeRowsToContents();

    rightSplitter->hide();
    rightSplitter->addWidget(dataTable);

    mainSplitter->addWidget(rightSplitter);
}

void MainWindow::readAd(int adId)//��ȡ���
{
    QSqlQuery adQuery;//�Թ�������
    if(adQuery.exec("SELECT aditem FROM adtable WHERE id = "+QString().setNum(adId)))
    {
        int adNumRows = 0;//�����������ص�����
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))//�ж������Ƿ����QuerySize
        {
            adNumRows = adQuery.size();//�����ص���������fstNumRows
        }
        else
        {
            adQuery.last();//�������һ��
            adNumRows = adQuery.at()+1;//�����ص���������fstNumRows
            adQuery.seek(-1);//���ص�һ��
        }
        if(adNumRows>0)//�ж��Ƿ����0
        {
            while(adQuery.next())
            {
                this->adView->loadMap(adQuery.value(0).toByteArray());//��ȡ���
            }
        }
    }
}

void MainWindow::menuTreeClick(QModelIndex)
{
    QVariant clickedItem = menuTree->selectionModel()->currentIndex().data(Qt::UserRole);
    int rowId = menuTree->selectionModel()->currentIndex().row()+1;
    QSqlQuery rowQuery;
    switch(clickedItem.toInt())
    {
    case 1:
        {
            if(rowQuery.exec("SELECT tableid, adid FROM firstmenus WHERE id = "+QString().setNum(rowId)))
            {
                int adNumRows = 0;//�����������ص�����
                if(db.driver()->hasFeature(QSqlDriver::QuerySize))//�ж������Ƿ����QuerySize
                {
                    adNumRows = rowQuery.size();//�����ص���������adNumRows
                }
                else
                {
                    rowQuery.last();//�������һ��
                    adNumRows = rowQuery.at()+1;//�����ص���������adNumRows
                    rowQuery.seek(-1);//���ص�һ��
                }
                if(adNumRows>0)//�ж��Ƿ����0
                {
                    rowQuery.next();
                    if(rowQuery.value(0).toInt()==0)
                    {
                        if(this->adView->isHidden())
                        {
                            this->rightSplitter->hide();
                            this->adView->show();
                        }
                        this->readAd(rowQuery.value(1).toInt());
                        this->adView->viewUpdate();
                    }
                    else
                    {
                        if(this->rightSplitter->isHidden())
                        {
                            this->adView->hide();
                            this->rightSplitter->show();
                        }
                        this->readTable(rowQuery.value(0).toInt());
                    }
                }
            }            
        }
        break;

    case 2:
        {
            if(rowQuery.exec("SELECT tableid, adid FROM secondmenus WHERE id = "+QString().setNum(rowId)))
            {
                int adNumRows = 0;//�����������ص�����
                if(db.driver()->hasFeature(QSqlDriver::QuerySize))//�ж������Ƿ����QuerySize
                {
                    adNumRows = rowQuery.size();//�����ص���������adNumRows
                }
                else
                {
                    rowQuery.last();//�������һ��
                    adNumRows = rowQuery.at()+1;//�����ص���������adNumRows
                    rowQuery.seek(-1);//���ص�һ��
                }
                if(adNumRows>0)//�ж��Ƿ����0
                {
                    rowQuery.next();
                    if(rowQuery.value(0).toInt()==0)
                    {
                        if(this->adView->isHidden())
                        {
                            this->rightSplitter->hide();
                            this->adView->show();
                        }
                        this->readAd(rowQuery.value(1).toInt());
                        this->adView->viewUpdate();
                    }
                    else
                    {
                        if(this->rightSplitter->isHidden())
                        {
                            this->adView->hide();
                            this->rightSplitter->show();
                        }
                        this->readTable(rowQuery.value(0).toInt());
                    }
                }
            }
        }
        break;

    case 3:
        {
            if(rowQuery.exec("SELECT tableid, adid FROM thirdmenus WHERE id = "+QString().setNum(rowId)))
            {
                int adNumRows = 0;//�����������ص�����
                if(db.driver()->hasFeature(QSqlDriver::QuerySize))//�ж������Ƿ����QuerySize
                {
                    adNumRows = rowQuery.size();//�����ص���������adNumRows
                }
                else
                {
                    rowQuery.last();//�������һ��
                    adNumRows = rowQuery.at()+1;//�����ص���������adNumRows
                    rowQuery.seek(-1);//���ص�һ��
                }
                if(adNumRows>0)//�ж��Ƿ����0
                {
                    rowQuery.next();
                    if(rowQuery.value(0).toInt()==0)
                    {
                        if(this->adView->isHidden())
                        {
                            this->rightSplitter->hide();
                            this->adView->show();
                        }
                        this->readAd(rowQuery.value(1).toInt());
                        this->adView->viewUpdate();
                    }
                    else
                    {
                        if(this->rightSplitter->isHidden())
                        {
                            this->adView->hide();
                            this->rightSplitter->show();
                        }
                        this->readTable(rowQuery.value(0).toInt());
                    }
                }
            }
        }
        break;

    default:
        break;
    }
}

void MainWindow::readTable(int tableId)//��ȡ������
{

}

void MainWindow::buildTableHeaderModel(QStandardItemModel& headerModel)
{
    QStandardItem* rootItem = new QStandardItem("root");
            QList<QStandardItem*> l;

            QStandardItem* rotatedTextCell=new QStandardItem("Rotated text");
            rotatedTextCell->setData(1, Qt::UserRole);
            l.push_back(rotatedTextCell);
            rootItem->appendColumn(l);

            l.clear();

            QStandardItem* cell=new QStandardItem("level 2");
            l.push_back(cell);
            rootItem->appendColumn(l);

            l.clear();

            l.push_back(new QStandardItem("level 3"));
            cell->appendColumn(l);

            l.clear();

            l.push_back(new QStandardItem("level 3"));
            cell->appendColumn(l);

            l.clear();

            l.push_back(new QStandardItem("level 2"));
            rootItem->appendColumn(l);

            headerModel.setItem(0,0,rootItem);
}

void MainWindow::buildTableDataModel(QStandardItemModel& model)
{
    QString cellText("cell(%1,%2)");
    for(int i=0; i<4; ++i)
    {
        QList<QStandardItem*> l;
        for(int j=0; j<4; ++j)
        {
            QStandardItem* cell = new QStandardItem(cellText.arg(i).arg(j));
            l.push_back(cell);
        }
        model.appendRow(l);
    }
}
