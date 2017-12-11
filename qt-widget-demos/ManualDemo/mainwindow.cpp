#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(QSize(800, 600).expandedTo(this->minimumSizeHint()));//设置初始窗口大小
    this->setWindowIcon(QIcon(":/images/books.png"));//设置标题栏图标
    this->setWindowTitle(QStringLiteral("机械设计辅助手册"));//设置标题栏标题

    if(this->createConnect())
    {
        mainSplitter = new QSplitter(Qt::Horizontal);//主面板
        this->createActions();//创建动作
        this->createMenus();//创建菜单栏
        this->createToolBars();//创建工具栏
        this->createMenuTree();//创建目录树
        this->createAd();//创建广告面板
        this->createTable();//创建表格面板
        mainSplitter->setStretchFactor(1,1);//设置比例左小右大
        this->setCentralWidget(mainSplitter);//加载主面板
    }
}

MainWindow::~MainWindow()
{

}

//创建连接
bool MainWindow::createConnect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");  //使用sqlite数据库驱动
    db.setDatabaseName("../manual/manualdata.db3");  //我们之前建立的数据库
    bool connectOK = db.open();  //尝试连接数据库
    if(!connectOK)//判断连接是否成功
    {
        QMessageBox::critical(0,QStringLiteral("无法打开数据库"),db.lastError().databaseText());//连接失败后显示提示框
        return false;
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)//事件“关闭”
{
    event->accept();
}

//创建动作
void MainWindow::createActions()
{
    //退出
    exitAction = new QAction(QStringLiteral("退出(&X)"), this);
    exitAction->setShortcut(QStringLiteral("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //对话框关于
    aboutAction = new QAction(QStringLiteral("关于(&A)"), this);

    //搜索
    searchAction = new QAction(QStringLiteral("搜索(&S)"),this);
    searchAction->setIcon(QIcon(":/images/search.png"));
    searchAction->setStatusTip(QStringLiteral("搜索相关内容"));

    //返回目录动作
    goHomeAction = new QAction(QStringLiteral("返回目录"), this);
    goHomeAction->setIcon(QIcon(":/images/home.png"));
    goHomeAction->setStatusTip(QStringLiteral("返回目录"));
}

//创建菜单栏
void MainWindow::createMenus()
{
    //菜单“文件”
    fileMenu = menuBar()->addMenu(QStringLiteral("文件(&F)"));
    fileMenu->addAction(exitAction);

    //菜单“工具”
    toolsMenu = menuBar()->addMenu(QStringLiteral("工具(&T)"));

    //菜单“帮助”
    helpMenu = menuBar()->addMenu(QStringLiteral("帮助(&H)"));
    helpMenu->addAction(aboutAction);
}

//创建工具栏
void MainWindow::createToolBars()
{
    mainToolBar = addToolBar(QStringLiteral("搜索(&S)"));//创建工具条
    searchLabel = new QLabel(QStringLiteral(" 搜索 "));//创建搜索标签
    mainToolBar->addWidget(searchLabel);//添加至工具条
    searchCombo = new QComboBox;//创建搜索框
    searchCombo->clear();//搜索框清空
    searchCombo->setEditable(true);//设置搜索框可编辑
    searchCombo->insertItem(0,QStringLiteral(""));//搜索框添加第一项空白
    searchCombo->setMinimumWidth(200);//设置搜索框最小宽度

    mainToolBar->addWidget(searchCombo);//工具条上添加搜索框
    mainToolBar->addAction(searchAction);//工具条添加搜索按钮
    mainToolBar->addAction(goHomeAction);//工具添加返回目录按钮
    mainToolBar->setMovable(false);//工具设置为不可动
}

//创建目录树
void MainWindow::createMenuTree()
{
    QSqlQuery fstMenuQuery;//对firstmenus搜索
    QSqlQuery secMenuQuery;//对secondmenus搜索
    QSqlQuery thdMenuQuery;//对thirdmenus搜索
    if(fstMenuQuery.exec("SELECT menuitem, id FROM firstmenus;"))//判断搜索数据库中一级目录
    {
        int fstNumRows = 0;//定义搜索返回的行数
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))//判断驱动是否包含QuerySize
        {
            fstNumRows = fstMenuQuery.size();//将返回的行数赋于fstNumRows
        }
        else
        {
            fstMenuQuery.last();//移至最后一行
            fstNumRows = fstMenuQuery.at()+1;//将返回的行数赋于fstNumRows
            fstMenuQuery.seek(-1);//返回第一行
        }
        if(fstNumRows>0)//判断搜索得到的结果是否大于0
        {
            menuTree = new QTreeView();//建立目录树
            treeModel = new QStandardItemModel(fstNumRows,1);//设置目录的大小
            treeModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("目录"));//设置目录头
            int fstInt = 0;
            while(fstMenuQuery.next())//加载一级目录
            {
                QStandardItem *fstItem = new QStandardItem(fstMenuQuery.value(0).toString());//新建一级目录各子项
                fstItem->setData(1,Qt::UserRole);//设置目录阶数
                treeModel->setItem(fstInt,fstItem);//将一级目录加载到目录树中
                fstInt++;//fstInt自加

                if(secMenuQuery.exec("SELECT menuitem, id FROM secondmenus WHERE parentid = "+ fstMenuQuery.value(1).toString()))//判断是否有二级目录
                {
                    int secNumRows = 0;//定义搜索返回的行数
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
                    if(secNumRows>0)//判断搜索得到的结果是否大于0
                    {
                        while(secMenuQuery.next())//加载二级目录
                        {
                            QStandardItem *secItem = new QStandardItem(secMenuQuery.value(0).toString());//新建二级目录各子项
                            secItem->setData(2,Qt::UserRole);//设置目录阶数为2
                            fstItem->appendRow(secItem);//加载二级目录

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
                                    while(thdMenuQuery.next())//加载三级目录
                                    {
                                        QStandardItem *thdItem = new QStandardItem(thdMenuQuery.value(0).toString());//新建三级目录各子项
                                        thdItem->setData(3,Qt::UserRole);//设置目录阶数为3
                                        secItem->appendRow(thdItem);//加载三级目录
                                    }
                                }
                            }
                        }
                    }
                }
            }
            menuTree->setModel(treeModel);//设置目录树的MODEL
            menuTree->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为不可编辑
            menuTree->resizeColumnToContents(0);//设置树的宽度
            mainSplitter->addWidget(menuTree);//将目录加载到主面板中

            connect(menuTree,SIGNAL(clicked(QModelIndex)),this,SLOT(menuTreeClick(QModelIndex)));//当用户点击树目录时，启动menuTreeClick函数
        }
    }
}

void MainWindow::createAd()//创建广告
{
    adView = new AdGraphicsView;//创建视图
    this->readAd(1);//读取id=1的广告
    this->adView->init();//初始化
    mainSplitter->addWidget(this->adView);//加载至主面板
}

void MainWindow::createTable()//创建表格面板
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

void MainWindow::readAd(int adId)//读取广告
{
    QSqlQuery adQuery;//对广告表单搜索
    if(adQuery.exec("SELECT aditem FROM adtable WHERE id = "+QString().setNum(adId)))
    {
        int adNumRows = 0;//定义搜索返回的行数
        if(db.driver()->hasFeature(QSqlDriver::QuerySize))//判断驱动是否包含QuerySize
        {
            adNumRows = adQuery.size();//将返回的行数赋于fstNumRows
        }
        else
        {
            adQuery.last();//移至最后一行
            adNumRows = adQuery.at()+1;//将返回的行数赋于fstNumRows
            adQuery.seek(-1);//返回第一行
        }
        if(adNumRows>0)//判断是否大于0
        {
            while(adQuery.next())
            {
                this->adView->loadMap(adQuery.value(0).toByteArray());//读取广告
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
                int adNumRows = 0;//定义搜索返回的行数
                if(db.driver()->hasFeature(QSqlDriver::QuerySize))//判断驱动是否包含QuerySize
                {
                    adNumRows = rowQuery.size();//将返回的行数赋于adNumRows
                }
                else
                {
                    rowQuery.last();//移至最后一行
                    adNumRows = rowQuery.at()+1;//将返回的行数赋于adNumRows
                    rowQuery.seek(-1);//返回第一行
                }
                if(adNumRows>0)//判断是否大于0
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
                int adNumRows = 0;//定义搜索返回的行数
                if(db.driver()->hasFeature(QSqlDriver::QuerySize))//判断驱动是否包含QuerySize
                {
                    adNumRows = rowQuery.size();//将返回的行数赋于adNumRows
                }
                else
                {
                    rowQuery.last();//移至最后一行
                    adNumRows = rowQuery.at()+1;//将返回的行数赋于adNumRows
                    rowQuery.seek(-1);//返回第一行
                }
                if(adNumRows>0)//判断是否大于0
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
                int adNumRows = 0;//定义搜索返回的行数
                if(db.driver()->hasFeature(QSqlDriver::QuerySize))//判断驱动是否包含QuerySize
                {
                    adNumRows = rowQuery.size();//将返回的行数赋于adNumRows
                }
                else
                {
                    rowQuery.last();//移至最后一行
                    adNumRows = rowQuery.at()+1;//将返回的行数赋于adNumRows
                    rowQuery.seek(-1);//返回第一行
                }
                if(adNumRows>0)//判断是否大于0
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

void MainWindow::readTable(int tableId)//读取表单数据
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
