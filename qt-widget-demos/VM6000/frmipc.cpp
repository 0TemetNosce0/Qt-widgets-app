#include "frmipc.h"
#include "ui_frmipc.h"
#include "myhelper.h"
#include "iconhelper.h"
#include "myapp.h"
#include "excelhelper.h"

frmIPC::frmIPC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmIPC)
{
    ui->setupUi(this);

    this->InitStyle();
    this->InitForm();
    this->BindNVRID();
}

frmIPC::~frmIPC()
{
    delete ui;
}

void frmIPC::InitStyle()
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

void frmIPC::InitForm()
{
    for (int i = 1; i <= 500; i++)
    {
        QString tempIPCID;
        if (i < 10)
        {
            tempIPCID = QString("00%1").arg(i);
        }
        else if (i < 100)
        {
            tempIPCID = QString("0%1").arg(i);
        }
        else if (i < 1000)
        {
            tempIPCID = QString("%1").arg(i);
        }
        ui->cboxIPCID->addItem(tempIPCID);
    }

    QStringList tempIPCType = myApp::IPCType.split(";");
    foreach (QString ipcType, tempIPCType) {
        if (ipcType.trimmed() != "") {
            ui->cboxIPCType->addItem(ipcType);
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
    LoadIPCInfo();

    QString columnNames[10]; //��������
    int columnWidths[10];    //�п�����

    //��ʼ������������п�
    columnNames[0] = "���";
    columnNames[1] = "����";
    columnNames[2] = "NVR���";
    columnNames[3] = "NVR����";
    columnNames[4] = "����";
    columnNames[5] = "��������ַ";
    columnNames[6] = "��������ַ";
    columnNames[7] = "�û���";
    columnNames[8] = "����";
    columnNames[9] = "״̬";

    int width = myApp::DeskWidth - 246;
    columnWidths[0] = width * 0.06;
    columnWidths[1] = width * 0.08;
    columnWidths[2] = width * 0.08;
    columnWidths[3] = width * 0.12;
    columnWidths[4] = width * 0.06;
    columnWidths[5] = width * 0.19;
    columnWidths[6] = width * 0.19;
    columnWidths[7] = width * 0.07;
    columnWidths[8] = width * 0.07;
    columnWidths[9] = width * 0.05;

    //���������б����п�
    for (int i = 0; i < 10; i++)
    {
        queryModule->setHeaderData(i, Qt::Horizontal, columnNames[i]);
        ui->tableMain->setColumnWidth(i, columnWidths[i]);
    }
}

void frmIPC::LoadIPCInfo()
{
    QString sql = "select * from [IPCInfo] order by [IPCID] asc";
    queryModule->setQuery(sql);
    ui->tableMain->setModel(queryModule);
}

void frmIPC::BindNVRID()
{
    ui->cboxNVRID->clear();
    QSqlQuery query;
    QString sql = "select [NVRID] from [NVRInfo]";
    query.exec(sql);
    while(query.next())
    {
        ui->cboxNVRID->addItem(query.value(0).toString());
    }
}

bool frmIPC::IsExistIPCID(QString NVRID, QString IPCID)
{
    QSqlQuery query;
    QString sql = "select [IPCID] from [IPCInfo]";
    sql += " where [IPCID]='" + IPCID ;
    sql += "' and [NVRID]='" + NVRID + "'";
    query.exec(sql);
    return query.next();
}

QString frmIPC::GetNVRName(QString NVRID)
{
    QSqlQuery query;
    QString sql = "select [NVRName] from [NVRInfo]";
    sql += " where [NVRID]='" + NVRID + "'";
    query.exec(sql);
    query.next();
    return query.value(0).toString();
}

void frmIPC::on_btnAdd_clicked()
{
    QString IPCID = ui->cboxIPCID->currentText();
    QString IPCName = ui->txtIPCName->text();
    QString NVRID = ui->cboxNVRID->currentText();
    QString NVRName = ui->cboxNVRName->currentText();
    QString IPCType = ui->cboxIPCType->currentText();
    QString IPCRtspAddrMain = ui->txtIPCRtspAddrMain->text();
    QString IPCRtspAddrSub = ui->txtIPCRtspAddrSub->text();
    QString IPCUserName = ui->txtIPCUserName->text();
    QString IPCUserPwd = ui->txtIPCUserPwd->text();
    QString IPCUse = ui->cboxIPCUse->currentText();

    if (IPCName == "") {
        myHelper::ShowMessageBoxError(QStringLiteral("���Ʋ���Ϊ��,��������д!"));
        ui->txtIPCName->setFocus();
        return;
    }

    if (NVRName == "") {
        myHelper::ShowMessageBoxError(QStringLiteral("NVR���Ʋ���Ϊ��,������Ӻ�NVR!"));
        return;
    }

    if (IPCRtspAddrMain == "") {
        myHelper::ShowMessageBoxError(QStringLiteral("��������ַ����Ϊ��,��������д!"));
        ui->txtIPCRtspAddrMain->setFocus();
        return;
    }

    if (IPCRtspAddrSub == "") {
        myHelper::ShowMessageBoxError(QStringLiteral("��������ַ����Ϊ��,��������д!"));
        ui->txtIPCRtspAddrSub->setFocus();
        return;
    }

    //������Ƿ�Ψһ
    if (IsExistIPCID(NVRID, IPCID)) {
        myHelper::ShowMessageBoxError(QStringLiteral("����Ѿ�����,������ѡ��!"));
        return;
    }

    QSqlQuery query;
    QString sql = "insert into [IPCInfo](";
    sql += "[IPCID],[IPCName],[NVRID],[NVRName],";
    sql += "[IPCType],[IPCRtspAddrMain],[IPCRtspAddrSub],";
    sql += "[IPCUserName],[IPCUserPwd],[IPCUse])";
    sql += "values('";
    sql += IPCID + "','";
    sql += IPCName + "','";
    sql += NVRID + "','";
    sql += NVRName + "','";
    sql += IPCType + "','";
    sql += IPCRtspAddrMain + "','";
    sql += IPCRtspAddrSub + "','";
    sql += IPCUserName + "','";
    sql += IPCUserPwd + "','";
    sql += IPCUse + "')";
    query.exec(sql);

    LoadIPCInfo();

    ui->cboxIPCID->setCurrentIndex(ui->cboxIPCID->currentIndex() + 1);
    ui->txtIPCName->setText(QStringLiteral("�����%1").arg(ui->cboxIPCID->currentText()));
}

void frmIPC::on_btnDelete_clicked()
{
    if (ui->tableMain->currentIndex().row() < 0) {
        myHelper::ShowMessageBoxError(QStringLiteral("��ѡ��Ҫɾ���������!"));
        return;
    }

    QString tempIPCID = queryModule->record(
                            ui->tableMain->currentIndex().row())
                        .value(0).toString();

    if (myHelper::ShowMessageBoxQuesion(QStringLiteral("ȷ��Ҫɾ���������?")) == 1) {
        QSqlQuery query;
        QString sql = "delete from [IPCInfo] where [IPCID]='" + tempIPCID + "'";
        query.exec(sql);
        myHelper::Sleep(100);

        //ͬ��ɾ����ѯ���е��������Ϣ
        sql = "delete from [PollInfo] where [IPCID]='" + tempIPCID + "'";
        query.exec(sql);
        myHelper::Sleep(100);

        LoadIPCInfo();
    }
}

void frmIPC::on_btnUpdate_clicked()
{
    if (ui->tableMain->currentIndex().row() < 0) {
        myHelper::ShowMessageBoxError(QStringLiteral("��ѡ��Ҫ�޸ĵ������!"));
        return;
    }

    QString tempIPCID = queryModule->record(
                            ui->tableMain->currentIndex().row())
                        .value(0).toString();

    QString IPCID = ui->cboxIPCID->currentText();
    QString IPCName = ui->txtIPCName->text();
    QString NVRID = ui->cboxNVRID->currentText();
    QString NVRName = ui->cboxNVRName->currentText();
    QString IPCType = ui->cboxIPCType->currentText();
    QString IPCRtspAddrMain = ui->txtIPCRtspAddrMain->text();
    QString IPCRtspAddrSub = ui->txtIPCRtspAddrSub->text();
    QString IPCUserName = ui->txtIPCUserName->text();
    QString IPCUserPwd = ui->txtIPCUserPwd->text();
    QString IPCUse = ui->cboxIPCUse->currentText();

    if (IPCID != tempIPCID) {
        //������Ƿ���Ѿ����ڵĳ��Լ�֮��ı����ͬ
        if (IsExistIPCID(NVRID, IPCID)) {
            myHelper::ShowMessageBoxError(QStringLiteral("����Ѿ�����,������ѡ��!"));
            return;
        }
    }

    QSqlQuery query;
    QString sql = "update [IPCInfo] set";
    sql += " [IPCID]='" + IPCID;
    sql += "',[IPCName]='" + IPCName;
    sql += "',[NVRID]='" + NVRID;
    sql += "',[NVRName]='" + NVRName;
    sql += "',[IPCType]='" + IPCType;
    sql += "',[IPCRtspAddrMain]='" + IPCRtspAddrMain;
    sql += "',[IPCRtspAddrSub]='" + IPCRtspAddrSub;
    sql += "',[IPCUserName]='" + IPCUserName;
    sql += "',[IPCUserPwd]='" + IPCUserPwd;
    sql += "',[IPCUse]='" + IPCUse;
    sql += "' where [IPCID]='" + tempIPCID + "'";
    query.exec(sql);
    myHelper::Sleep(100);

    //ͬ���޸���ѯ�����Ϣ
    sql = "update [PollInfo] set";
    sql += " [IPCID]='" + IPCID;
    sql += "',[IPCName]='" + IPCName;
    sql += "',[NVRID]='" + NVRID;
    sql += "',[NVRName]='" + NVRName;
    sql += "',[IPCRtspAddrMain]='" + IPCRtspAddrMain;
    sql += "',[IPCRtspAddrSub]='" + IPCRtspAddrSub;
    sql += "' where [IPCID]='" + tempIPCID + "'";
    query.exec(sql);
    myHelper::Sleep(100);

    LoadIPCInfo();
}

void frmIPC::on_btnExcel_clicked()
{
    QString columnNames[10];
    int columnWidths[10];

    columnNames[0] = "���";
    columnNames[1] = "����";
    columnNames[2] = "NVR���";
    columnNames[3] = "NVR����";
    columnNames[4] = "����";
    columnNames[5] = "��������ַ";
    columnNames[6] = "��������ַ";
    columnNames[7] = "�û���";
    columnNames[8] = "����";
    columnNames[9] = "״̬";

    columnWidths[0] = 60;
    columnWidths[1] = 80;
    columnWidths[2] = 70;
    columnWidths[3] = 100;
    columnWidths[4] = 60;
    columnWidths[5] = 200;
    columnWidths[6] = 200;
    columnWidths[7] = 60;
    columnWidths[8] = 60;
    columnWidths[9] = 60;

    QStringList content;
    QSqlQuery query;
    QString sql = "select * from [IPCInfo] order by [IPCID] asc";
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
    QString title = "�������Ϣ";
    ExcelHelper::Instance()->ToExcel(myApp::AppPath + "DB/" + title + ".xls", title, title, columnNames, columnWidths, columnCount, content);

    if (myHelper::ShowMessageBoxQuesion(QStringLiteral("�������ݵ�Excel�ɹ�,���ھʹ���")) == 1) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(myApp::AppPath + "DB/" + title + ".xls"));
    }
}

void frmIPC::on_tableMain_pressed(const QModelIndex &index)
{
    QSqlRecord record = queryModule->record(index.row());
    ui->cboxIPCID->setCurrentIndex(ui->cboxIPCID->findText(record.value(0).toString()));
    ui->txtIPCName->setText(record.value(1).toString());
    ui->cboxNVRID->setCurrentIndex(ui->cboxNVRID->findText(record.value(2).toString()));
    on_cboxNVRID_activated(record.value(2).toString());
    ui->cboxIPCType->setCurrentIndex(ui->cboxIPCType->findText(record.value(4).toString()));
    ui->txtIPCRtspAddrMain->setText(record.value(5).toString());
    ui->txtIPCRtspAddrSub->setText(record.value(6).toString());
    ui->txtIPCUserName->setText(record.value(7).toString());
    ui->txtIPCUserPwd->setText(record.value(8).toString());
    ui->cboxIPCUse->setCurrentIndex(ui->cboxIPCUse->findText(record.value(9).toString()));

    ui->txtIPCRtspAddrMain->setCursorPosition(0);
    ui->txtIPCRtspAddrSub->setCursorPosition(0);
}

void frmIPC::on_cboxNVRID_activated(const QString &arg1)
{
    ui->cboxNVRName->clear();
    ui->cboxNVRName->addItem(GetNVRName(arg1));
}

void frmIPC::on_txtIPCRtspAddrMain_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    QString rtspMain = ui->txtIPCRtspAddrMain->text();
    if (rtspMain.length() < 7)
    {
        return;
    }

    QStringList tempMain = rtspMain.split("/");
    QString ipMain = tempMain[2].split(":")[0];

    QString rtspSub = ui->txtIPCRtspAddrSub->text();
    if (rtspSub.length() < 7)
    {
        return;
    }

    QStringList tempSub = rtspSub.split("/");
    int len = tempSub[2].split(":")[0].length();

    rtspSub = rtspSub.replace(7, len, ipMain);
    ui->txtIPCRtspAddrSub->setText(rtspSub);
}

void frmIPC::on_cboxIPCID_activated(const QString &arg1)
{
    ui->txtIPCName->setText(QStringLiteral("�����%1").arg(arg1));
}

