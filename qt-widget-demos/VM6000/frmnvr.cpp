#include "frmnvr.h"
#include "ui_frmnvr.h"
#include "myhelper.h"
#include "iconhelper.h"
#include "myapp.h"
#include "excelhelper.h"

frmNVR::frmNVR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmNVR)
{
    ui->setupUi(this);

    this->InitStyle();
    this->InitForm();
}

frmNVR::~frmNVR()
{
    delete ui;
}

void frmNVR::InitStyle()
{
    this->setProperty("Form", true);
    this->setGeometry(qApp->desktop()->availableGeometry());
    //���ô������������
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint);
    //����ͼ������
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf03d), 11);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    //�����رհ�ť
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
}

void frmNVR::InitForm()
{
    for (int i = 1; i <= 255; i++)
    {
        QString tempNVRID;
        if (i < 10)
        {
            tempNVRID = QString("00000%1").arg(i);
        }
        else if (i < 100)
        {
            tempNVRID = QString("0000%1").arg(i);
        }
        else if (i < 1000)
        {
            tempNVRID = QString("000%1").arg(i);
        }
        ui->cboxNVRID->addItem(tempNVRID);
    }

    QStringList tempNVRType = myApp::NVRType.split(";");
    foreach (QString nvrType, tempNVRType)
    {
        if (nvrType.trimmed() != "")
        {
            ui->cboxNVRType->addItem(nvrType);
        }
    }

    //���һ���Զ����
    ui->tableMain->horizontalHeader()->setStretchLastSection(true);
    //����ż���в�ͬ����ɫ
    ui->tableMain->setAlternatingRowColors(true);
    //ѡ������,ÿ��ֻ����ѡ��һ��
    ui->tableMain->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableMain->setSelectionMode(QAbstractItemView::SingleSelection);

    queryModule = new QSqlQueryModel(this);
    LoadNVRInfo();

    QString columnNames[8]; //��������
    int columnWidths[8];    //�п�����

    //��ʼ������������п�
    columnNames[0] = "���";
    columnNames[1] = "����";
    columnNames[2] = "��ַ";
    columnNames[3] = "IP��ַ";
    columnNames[4] = "����";
    columnNames[5] = "�û���";
    columnNames[6] = "����";
    columnNames[7] = "״̬";

    int width = myApp::DeskWidth - 246;
    columnWidths[0] = width * 0.08;
    columnWidths[1] = width * 0.16;
    columnWidths[2] = width * 0.20;
    columnWidths[3] = width * 0.12;
    columnWidths[4] = width * 0.08;
    columnWidths[5] = width * 0.12;
    columnWidths[6] = width * 0.12;
    columnWidths[7] = width * 0.08;

    //���������б����п�
    for (int i = 0; i < 8; i++) {
        queryModule->setHeaderData(i, Qt::Horizontal, columnNames[i]);
        ui->tableMain->setColumnWidth(i, columnWidths[i]);
    }
}

void frmNVR::LoadNVRInfo()
{
    QString sql = "select * from [NVRInfo] order by [NVRID] asc";
    queryModule->setQuery(sql);
    ui->tableMain->setModel(queryModule);
}

bool frmNVR::IsExistNVRID(QString NVRID)
{
    QSqlQuery query;
    QString sql = "select [NVRID] from [NVRInfo]";
    sql += " where [NVRID]='" + NVRID + "'";
    query.exec(sql);
    return query.next();
}

bool frmNVR::IsExistNVRIP(QString NVRIP)
{
    QSqlQuery query;
    QString sql = "select [NVRIP] from [NVRInfo]";
    sql += " where [NVRIP]='" + NVRIP + "'";
    query.exec(sql);
    return query.next();
}

void frmNVR::on_btnAdd_clicked()
{
    QString NVRID = ui->cboxNVRID->currentText();
    QString NVRName = ui->txtNVRName->text();
    QString NVRAddr = ui->txtNVRAddr->text();
    QString NVRIP = ui->txtNVRIP->text();
    QString NVRType = ui->cboxNVRType->currentText();
    QString NVRUserName = ui->txtNVRUserName->text();
    QString NVRUserPwd = ui->txtNVRUserPwd->text();
    QString NVRUse = ui->cboxNVRUse->currentText();

    if (NVRName == "") {
        myHelper::ShowMessageBoxError("���Ʋ���Ϊ��,��������д!");
        ui->txtNVRName->setFocus();
        return;
    }

    if (NVRIP == "") {
        myHelper::ShowMessageBoxError("IP��ַ����Ϊ��,��������д!");
        ui->txtNVRIP->setFocus();
        return;
    }

    if (!myHelper::IsIP(NVRIP)) {
        myHelper::ShowMessageBoxError("IP��ַ���Ϸ�,��������д!");
        ui->txtNVRIP->setFocus();
        return;
    }

    //����ź�IP�Ƿ�Ψһ
    if (IsExistNVRID(NVRID)) {
        myHelper::ShowMessageBoxError("����Ѿ�����,������ѡ��!");
        return;
    }

    if (IsExistNVRIP(NVRIP)) {
        myHelper::ShowMessageBoxError("IP��ַ�Ѿ�����,��������д!");
        ui->txtNVRIP->setFocus();
        return;
    }

    QSqlQuery query;
    QString sql = "insert into [NVRInfo](";
    sql += "[NVRID],[NVRName],[NVRAddr],[NVRIP],";
    sql += "[NVRType],[NVRUserName],[NVRUserPwd],[NVRUse])";
    sql += "values('";
    sql += NVRID + "','";
    sql += NVRName + "','";
    sql += NVRAddr + "','";
    sql += NVRIP + "','";
    sql += NVRType + "','";
    sql += NVRUserName + "','";
    sql += NVRUserPwd + "','";
    sql += NVRUse + "')";
    query.exec(sql);

    LoadNVRInfo();

    ui->cboxNVRID->setCurrentIndex(ui->cboxNVRID->currentIndex() + 1);
}

void frmNVR::on_btnDelete_clicked()
{
    if (ui->tableMain->currentIndex().row() < 0)
    {
        myHelper::ShowMessageBoxError("��ѡ��Ҫɾ����Ӳ��¼���!");
        return;
    }

    QString tempNVRID = queryModule->record(
                            ui->tableMain->currentIndex().row())
                        .value(0).toString();

    if (tempNVRID == "000255")
    {
        myHelper::ShowMessageBoxError("Ĭ��NVR����ɾ��!");
        return;
    }

    if (myHelper::ShowMessageBoxQuesion("ȷ��Ҫɾ��Ӳ��¼�����?��Ӧ�������ͬ��ɾ��!") == 1)
    {
        QSqlQuery query;
        QString sql = "delete from [NVRInfo] where [NVRID]='" + tempNVRID + "'";
        query.exec(sql);
        myHelper::Sleep(100);

        //ͬ��ɾ����Ӧ�������Ϣ
        sql = "delete from [IPCInfo] where [NVRID]='" + tempNVRID + "'";
        query.exec(sql);
        myHelper::Sleep(100);

        //ͬ��ɾ����Ӧ��ѯ����Ϣ
        sql = "delete from [PollInfo] where [NVRID]='" + tempNVRID + "'";
        query.exec(sql);
        myHelper::Sleep(100);

        LoadNVRInfo();
    }
}

void frmNVR::on_btnUpdate_clicked()
{
    if (ui->tableMain->currentIndex().row() < 0)
    {
        myHelper::ShowMessageBoxError("��ѡ��Ҫ�޸ĵ�Ӳ��¼���!");
        return;
    }

    //��ȡԭ��NVRID
    QString tempNVRID = queryModule->record(
                            ui->tableMain->currentIndex().row())
                        .value(0).toString();
    QString tempNVRIP = queryModule->record(
                            ui->tableMain->currentIndex().row())
                        .value(3).toString();

    if (tempNVRID == "000255")
    {
        myHelper::ShowMessageBoxError("Ĭ��NVR�����޸�!");
        return;
    }

    QString NVRID = ui->cboxNVRID->currentText();
    QString NVRName = ui->txtNVRName->text();
    QString NVRAddr = ui->txtNVRAddr->text();
    QString NVRIP = ui->txtNVRIP->text();
    QString NVRType = ui->cboxNVRType->currentText();
    QString NVRUserName = ui->txtNVRUserName->text();
    QString NVRUserPwd = ui->txtNVRUserPwd->text();
    QString NVRUse = ui->cboxNVRUse->currentText();

    if (NVRID != tempNVRID)
    {
        //������Ƿ���Ѿ����ڵĳ��Լ�֮��ı����ͬ
        if (IsExistNVRID(NVRID)) {
            myHelper::ShowMessageBoxError("����Ѿ�����,������ѡ��!");
            return;
        }
    }

    if (NVRIP != tempNVRIP)
    {
        //���IP��ַ�Ƿ���Ѿ����ڵĳ��Լ�֮���IP��ַ��ͬ
        if (IsExistNVRIP(NVRIP)) {
            myHelper::ShowMessageBoxError("IP��ַ�Ѿ�����,��������д!");
            ui->txtNVRIP->setFocus();
            return;
        }
    }

    if (!myHelper::IsIP(NVRIP))
    {
        myHelper::ShowMessageBoxError("IP��ַ���Ϸ�,��������д!");
        ui->txtNVRIP->setFocus();
        return;
    }

    QSqlQuery query;
    QString sql = "update [NVRInfo] set";
    sql += " [NVRID]='" + NVRID;
    sql += "',[NVRName]='" + NVRName;
    sql += "',[NVRAddr]='" + NVRAddr;
    sql += "',[NVRIP]='" + NVRIP;
    sql += "',[NVRType]='" + NVRType;
    sql += "',[NVRUserName]='" + NVRUserName;
    sql += "',[NVRUserPwd]='" + NVRUserPwd;
    sql += "',[NVRUse]='" + NVRUse;
    sql += "' where [NVRID]='" + tempNVRID + "'";
    query.exec(sql);
    myHelper::Sleep(100);

    //ͬ�������������ӦӲ��¼�����Ϣ
    sql = "update [IPCInfo] set";
    sql += " [NVRID]='" + NVRID;
    sql += "',[NVRName]='" + NVRName;
    sql += "' where [NVRID]='" + tempNVRID + "'";
    query.exec(sql);
    myHelper::Sleep(100);

    //ͬ��������ѯ����Ϣ
    sql = "update [PollInfo] set";
    sql += " [NVRID]='" + NVRID;
    sql += "',[NVRName]='" + NVRName;
    sql += "' where [NVRID]='" + tempNVRID + "'";
    query.exec(sql);
    myHelper::Sleep(100);

    LoadNVRInfo();
}

void frmNVR::on_btnExcel_clicked()
{
    QString columnNames[8];
    int columnWidths[8];

    columnNames[0] = "���";
    columnNames[1] = "����";
    columnNames[2] = "��ַ";
    columnNames[3] = "IP��ַ";
    columnNames[4] = "����";
    columnNames[5] = "�û���";
    columnNames[6] = "����";
    columnNames[7] = "״̬";

    columnWidths[0] = 80;
    columnWidths[1] = 120;
    columnWidths[2] = 150;
    columnWidths[3] = 120;
    columnWidths[4] = 60;
    columnWidths[5] = 60;
    columnWidths[6] = 60;
    columnWidths[7] = 60;

    QStringList content;
    QSqlQuery query;
    QString sql = "select * from [NVRInfo] order by [NVRID] asc";
    query.exec(sql);
    int columnCount = query.record().count();

    //ѭ����������,�洢��QStringList��
    while (query.next()) {
        QString temp = "";
        for (int i = 0; i < columnCount; i++) {
            temp += query.value(i).toString() + ";";
        }
        content << temp.mid(0, temp.length() - 1); //ȥ��ĩβ�ķֺ�
    }

    //���õ������ݺ���
    QString title = "Ӳ��¼�����Ϣ";
    ExcelHelper::Instance()->ToExcel(myApp::AppPath + "DB/" + title + ".xls", title, title, columnNames, columnWidths, columnCount, content);

    if (myHelper::ShowMessageBoxQuesion("�������ݵ�Excel�ɹ�,���ھʹ���") == 1) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(myApp::AppPath + "DB/" + title + ".xls"));
    }
}

void frmNVR::on_tableMain_pressed(const QModelIndex &index)
{
    QSqlRecord record = queryModule->record(index.row());
    ui->cboxNVRID->setCurrentIndex(ui->cboxNVRID->findText(record.value(0).toString()));
    ui->txtNVRName->setText(record.value(1).toString());
    ui->txtNVRAddr->setText(record.value(2).toString());
    ui->txtNVRIP->setText(record.value(3).toString());
    ui->cboxNVRType->setCurrentIndex(ui->cboxNVRType->findText(record.value(4).toString()));
    ui->txtNVRUserName->setText(record.value(5).toString());
    ui->txtNVRUserPwd->setText(record.value(6).toString());
    ui->cboxNVRUse->setCurrentIndex(ui->cboxNVRUse->findText(record.value(7).toString()));
}

