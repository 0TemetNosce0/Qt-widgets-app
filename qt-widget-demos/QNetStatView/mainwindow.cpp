#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QScrollBar>
#include <QClipboard>
#include <QHeaderView>
#include <QFileDialog>
#include <QVector>
#include <QMessageBox>
#include <QSettings>
#include <QDir>

Q_DECLARE_METATYPE(QVector<sNetStat>)


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType < QVector<sNetStat> > ("QVector<sNetStat>");

    // date start 19.02.2013
    this->setWindowTitle("QNetStatView  v1.2.0 (20.12.2013)");
    this->setWindowIcon(QIcon(":qnetstatview.ico"));

    // Создание ContextMenu
    initPopupMenu();



    connect(ui->tableWidget->verticalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(tableWidget_sectionVerticalResized(int,int,int)));
    connect(ui->tableWidget->horizontalHeader(),SIGNAL(sectionResized(int,int,int)),this,SLOT(tableWidget_sectionHorizontalResized(int,int,int)));
    connect(ui->tableWidget->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(tableWidget_sectionClicked(int)));
    connect(ui->tableWidget, SIGNAL( customContextMenuRequested( const QPoint & ) ), SLOT( popupCustomMenu( const QPoint & ) ) );

    connect(ui->actionCopy,SIGNAL(triggered()),this,SLOT(CopyToClipboard()));
    connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(CopyToFile()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));

    connect(ui->actionRefresh,SIGNAL(triggered()),this,SLOT(timerUpdate_timeout()));
    connect(ui->actionRestart_as_Root,SIGNAL(triggered()),this,SLOT(restartAsRoot()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));

    connect(ui->actionTCP,SIGNAL(triggered()),this,SLOT(timerUpdate_timeout()));
    connect(ui->actionTCP6,SIGNAL(triggered()),this,SLOT(timerUpdate_timeout()));
    connect(ui->actionUDP,SIGNAL(triggered()),this,SLOT(timerUpdate_timeout()));
    connect(ui->actionUDP6,SIGNAL(triggered()),this,SLOT(timerUpdate_timeout()));

    connect(ui->actionESTABLISHED,SIGNAL(triggered()),this,SLOT(timerUpdate_timeout()));
    connect(ui->actionLISTEN,SIGNAL(triggered()),this,SLOT(timerUpdate_timeout()));
    connect(ui->actionCLOSE,SIGNAL(triggered()),this,SLOT(timerUpdate_timeout()));
    connect(ui->actionAllOther,SIGNAL(triggered()),this,SLOT(timerUpdate_timeout()));

    connect(ui->actionUtilite_for_kill,SIGNAL(triggered()),this,SLOT(showSetupKill()));
    connect(ui->actionResolve_Addresses,SIGNAL(triggered()),this,SLOT(Resolve_Addresses()));

    connect(ui->action1_second,SIGNAL(triggered()),this,SLOT(timer_speed1()));
    connect(ui->action3_second,SIGNAL(triggered()),this,SLOT(timer_speed3()));
    connect(ui->action5_second,SIGNAL(triggered()),this,SLOT(timer_speed5()));
    connect(ui->actionPause,SIGNAL(triggered()),this,SLOT(timer_pause()));


    ui->tableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setContextMenuPolicy( Qt::CustomContextMenu );
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);


    ui->tableWidget->setColumnWidth(1,41);
    ui->tableWidget->setColumnWidth(2,160);
    ui->tableWidget->setColumnWidth(3,160);
    ui->tableWidget->setColumnWidth(5,45);
    ui->tableWidget->setColumnWidth(7,345);
    //ui->tableWidget->horizontalHeader()->setResizeMode(0,QHeaderView::ResizeToContents);
    //ui->tableWidget->horizontalHeader()->setResizeMode(4,QHeaderView::ResizeToContents);
    //ui->tableWidget->horizontalHeader()->setResizeMode(5,QHeaderView::ResizeToContents);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(7,QHeaderView::ResizeToContents);


#if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
    if (QDir::home().absolutePath()=="/root")
    {
        ui->actionRestart_as_Root->setVisible(false);
    }
#elif defined(Q_OS_WIN)
    ui->actionRestart_as_Root->setVisible(false);
#endif


    netstat = new cNetStat();
    connect(netstat, SIGNAL(endReadStat(QVector<sNetStat>)), this, SLOT(drawTable(QVector<sNetStat>)));

    sortcol = 2;

    // Загрузка services
    QFile file(":services");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QStringList service = in.readLine().split(QRegExp("\\s+"));
            if (service.size() < 2)
            {
                continue;
            }
            ServicesCache[service.at(1).toUpper()]=service.at(0);
        }
        file.close();
    }

    timerUpdate_timeout();
    timerUpdate = new QTimer(this);
    connect (timerUpdate, SIGNAL(timeout()), this, SLOT(timerUpdate_timeout()));
    timerUpdate->start(3000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initPopupMenu()
{
    menu = new QMenu("my", 0);
    menu->addAction(tr("Kill process"), this, SLOT(killProcess()));
    menu->addAction(tr("Close connection"), this, SLOT(closeConnection()));

}
void MainWindow::popupCustomMenu( const QPoint &pos )
{
    menu->popup(ui->tableWidget->mapToGlobal(pos));
}

void MainWindow::killProcess()
{
    Process::killProcess(ui->tableWidget->item(ui->tableWidget->currentRow(),5)->text());
}

void MainWindow::closeConnection()
{
#if defined(Q_OS_WIN) || !defined(USE_LIBNET)
    QMessageBox::critical(0,"closeConnection",tr("Your OS is not support closeConnection"));
    return;
#endif

    if (QDir::home().absolutePath()=="/root")
    {
        if (ui->tableWidget->item(ui->tableWidget->currentRow(),4)->text() == "ESTABLISHED")
        {
            Process::closeConnection(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("/").at(0),ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("/").at(1));
        }
        else
        {
            QMessageBox::critical(0,"closeConnection",tr("Only ESTABLISHED"));
        }
    }
    else
    {
        QMessageBox::critical(0,"closeConnection",tr("Only root can do this"));
    }
}

void MainWindow::tableWidget_sectionClicked(int col)
{
    sortcol=col;
    timerUpdate_timeout();
}

void MainWindow::tableWidget_sectionVerticalResized( int logicalIndex, int oldSize, int newSize)
{
    qDebug() << logicalIndex << oldSize << newSize;
}

void MainWindow::tableWidget_sectionHorizontalResized( int logicalIndex, int oldSize, int newSize)
{
    qDebug() << logicalIndex << oldSize << newSize;
}


void MainWindow::showAbout()
{
    About form;
    form.exec();
}

void MainWindow::CopyToClipboard()
{
    QString buffer = "";
    QClipboard *clipboard = QApplication::clipboard();

    for (int i=0;i<ui->tableWidget->columnCount();i++)
    {
        buffer += ui->tableWidget->item(ui->tableWidget->currentRow(),i)->text() + ";";
    }

    clipboard->setText(buffer);
}

void MainWindow::CopyToFile()
{
    int interval = timerUpdate->interval();
    timerUpdate->stop();
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save to file"), "", tr("All Files (*.*)"));

    if (fileName.size() > 0)
    {
        QFile file(fileName);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);

            for (int r = 0; r < ui->tableWidget->rowCount(); r++)
            {
                for (int i=0;i<ui->tableWidget->columnCount();i++)
                {
                    out << ui->tableWidget->item(r,i)->text() +"\t";
                }
                out << "\n";
            }

            file.close();
        }
    }

    timerUpdate->start(interval);
}

void MainWindow::Resolve_Addresses(){
    timerUpdate_timeout();
}

void MainWindow::lookedUp(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError)
    {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    foreach (const QHostAddress &address, host.addresses())
        DNSCache[address.toString()]=host.hostName();
}

QString MainWindow::resolve(QString ipaddr,QString prot)
{
    QString result = ipaddr;

    if (ipaddr.split(":").size()<1)
    {
        return ipaddr;
    }

    if (ipaddr=="*")
    {
        return ipaddr;
    }

    if (DNSCache[ipaddr.split(":").at(0)] != "")
    {
        ipaddr = DNSCache[ipaddr.split(":").at(0)] + ":" + ipaddr.split(":").at(1);
    }

    if (ServicesCache[ipaddr.split(":").at(1) + "/" + prot] != "")
    {
        ipaddr = ipaddr.split(":").at(0) + ":" + ServicesCache[ipaddr.split(":").at(1) + "/" + prot];
    }

    return ipaddr;
}

void MainWindow::timer_speed1()
{
    ui->action1_second->setChecked(true);
    ui->action3_second->setChecked(false);
    ui->action5_second->setChecked(false);
    ui->actionPause->setChecked(false);

    timerUpdate_timeout();
    timerUpdate->start(1000);
}
void MainWindow::timer_speed3()
{
    ui->action1_second->setChecked(false);
    ui->action3_second->setChecked(true);
    ui->action5_second->setChecked(false);
    ui->actionPause->setChecked(false);
    timerUpdate_timeout();
    timerUpdate->start(3000);
}

void MainWindow::timer_speed5()
{
    ui->action1_second->setChecked(false);
    ui->action3_second->setChecked(false);
    ui->action5_second->setChecked(true);
    ui->actionPause->setChecked(false);
    timerUpdate_timeout();
    timerUpdate->start(5000);
}

void MainWindow::timer_pause()
{
    ui->action1_second->setChecked(false);
    ui->action3_second->setChecked(false);
    ui->action5_second->setChecked(false);
    ui->actionPause->setChecked(true);

    timerUpdate->stop();
}


void MainWindow::restartAsRoot()
{
    system(QString("kdesu "+QApplication::applicationDirPath()+"/"+qAppName()+" 2> /dev/null &").toStdString().c_str());
    exit(0);
}

void MainWindow::drawTable(QVector<sNetStat> newNetStat)
{
    QString key = "";
    int listen = 0;
    int established = 0;

    // Сохранение данных
    int saveScroll = ui->tableWidget->verticalScrollBar()->value();
    if (ui->tableWidget->currentRow()>0)
    {
        key = ui->tableWidget->item(ui->tableWidget->currentRow(),2)->text() +"+"+ui->tableWidget->item(ui->tableWidget->currentRow(),3)->text();
    }

    // Удаление старой таблицы
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);


    // Формирование новой таблицы
    ui->tableWidget->verticalHeader()->hide();
    //ui->tableWidget->setRowCount(newNetStat.size());
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->sortByColumn(1);
    ui->tableWidget->setColumnHidden(0,true);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "" << tr("prot") << tr("local address") << tr("rem address") << tr("state") << tr("pid") << tr("program") << tr("cmdline"));

    int row=0;
    for (int i=0;i<newNetStat.size();i++)
    {
        // filter prot
        if (newNetStat.at(i).prot=="TCP")
        {
            if (ui->actionTCP->isChecked()!=true)
                continue;
        }
        else if (newNetStat.at(i).prot=="UDP")
        {
            if (ui->actionUDP->isChecked()!=true)
                continue;
        }
        else if (newNetStat.at(i).prot=="TCP6")
        {
            if (ui->actionTCP6->isChecked()!=true)
                continue;
        }
        else if (newNetStat.at(i).prot=="UDP6")
        {
            if (ui->actionUDP6->isChecked()!=true)
                continue;
        }

        // filter state
        if (newNetStat.at(i).stat=="ESTABLISHED" || newNetStat.at(i).stat=="ESTABLISH")
        {
            if (ui->actionESTABLISHED->isChecked()!= true)
            {
                continue;
            }
        }
        else if(newNetStat.at(i).stat=="LISTEN")
        {
            if (ui->actionLISTEN->isChecked()!= true)
            {
                continue;
            }
        }
        else if(newNetStat.at(i).stat=="CLOSE")
        {
            if (ui->actionCLOSE->isChecked()!= true)
            {
                continue;
            }
        }
        else
        {
            if (ui->actionAllOther->isChecked()!= true)
            {
                continue;
            }
        }

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

        QString local_address = newNetStat.at(i).local_address;
        QString rem_address = newNetStat.at(i).rem_address;


        QTableWidgetItem *itemKey = new QTableWidgetItem(local_address+"/"+rem_address);
        ui->tableWidget->setItem(row, 0, itemKey);

        if (local_address.split(":").at(0) != "*")
        {
            if (DNSCache[local_address.split(":").at(0)] == "")
            {
                QHostInfo::lookupHost(local_address.split(":").at(0),this,SLOT(lookedUp(QHostInfo)));
            }
        }

        if (rem_address != "*")
        {
            if (DNSCache[rem_address.split(":").at(0)] == "")
            {
                QHostInfo::lookupHost(rem_address.split(":").at(0),this,SLOT(lookedUp(QHostInfo)));
            }
        }

        if (ui->actionResolve_Addresses->isChecked()== true)
        {
            local_address=resolve(local_address,newNetStat.at(i).prot);
            rem_address=resolve(rem_address,newNetStat.at(i).prot);
        }

        QTableWidgetItem *itemProt = new QTableWidgetItem(newNetStat.at(i).prot);
        ui->tableWidget->setItem(row, 1, itemProt);

        QTableWidgetItem *itemLocalAddress = new QTableWidgetItem(local_address);
        ui->tableWidget->setItem(row, 2, itemLocalAddress);

        QTableWidgetItem *itemRemoteAddress = new QTableWidgetItem(rem_address);
        ui->tableWidget->setItem(row, 3, itemRemoteAddress);

        QTableWidgetItem *itemStat = new QTableWidgetItem(newNetStat.at(i).stat);
        ui->tableWidget->setItem(row, 4, itemStat);

        QTableWidgetItem *itemPID = new QTableWidgetItem(newNetStat.at(i).process.pid);
        ui->tableWidget->setItem(row, 5, itemPID);

        QTableWidgetItem *itemProg = new QTableWidgetItem(newNetStat.at(i).process.program);
        ui->tableWidget->setItem(row, 6, itemProg);

        QTableWidgetItem *itemCmdLine = new QTableWidgetItem(newNetStat.at(i).process.cmdline);
        ui->tableWidget->setItem(row, 7, itemCmdLine);

        for (int c=1;c<ui->tableWidget->columnCount();c++)
        {
            if (newNetStat.at(i).operation==1)
            {
                ui->tableWidget->item(row,c)->setBackgroundColor(QColor(0,255,0));
            }
            if (newNetStat.at(i).operation==2)
            {
                ui->tableWidget->item(row,c)->setBackgroundColor(QColor(255,0,0));
            }
        }

        if (local_address+"+"+rem_address == key)
        {
            ui->tableWidget->selectRow(row);
        }

        ui->tableWidget->setRowHeight(row,18);

        if (newNetStat.at(i).stat=="LISTEN")
        {
            listen++;
        }

        if (newNetStat.at(i).stat=="ESTABLISHED" || newNetStat.at(i).stat=="ESTABLISH")
        {
            established++;
        }

        row++;
    }

    // Востанавливаем сортировку и позицию курсора
    ui->tableWidget->sortByColumn(sortcol);
    ui->tableWidget->verticalScrollBar()->setValue(saveScroll);

    ui->label->setText(tr("Count connections: ")+QString::number(newNetStat.size()));
    ui->label_2->setText(tr("Count LISTEN: ")+QString::number(listen));
    ui->label_3->setText(tr("Count ESTABLISHED: ")+QString::number(established));


    ui->tableWidget->setColumnWidth(7,345);

}

void MainWindow::timerUpdate_timeout()
{
    netstat->start();
}


void MainWindow::showSetupKill()
{
    setupUtiliteKill frm;
    frm.exec();
}


//TerminateProcess(hProcess, 0)
