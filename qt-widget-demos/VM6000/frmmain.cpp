#include "frmmain.h"
#include "ui_frmmain.h"
#include "iconhelper.h"
#include "myhelper.h"
#include "myapp.h"
#include "frmconfig.h"
#include "frmnvr.h"
#include "frmipc.h"
#include "frmpollconfig.h"

frmMain::frmMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);

    this->InitStyle();
    this->InitForm();
    this->InitVideo();
    this->LoadVideo();
    this->LoadNVRIPC();
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::InitStyle()
{
    this->setStyleSheet("QGroupBox#gboxMain{border-width:0px;}");
    this->setProperty("Form", true);
    //���ô������������--Qt::WindowStaysOnTopHint |
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint);

    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf03d), 11);
    IconHelper::Instance()->SetIcon(ui->labStyle, QChar(0xf103), 12);
}

void frmMain::change_style()
{
    QAction *action = (QAction *)sender();
    QString style = action->text();
    if (style == "����ɫ")
    {
        myApp::AppStyle = ":/image/blue.css";
    }
    else if (style == "��ɫ")
    {
        myApp::AppStyle = ":/image/dev.css";
    }
    else if (style == "��ɫ")
    {
        myApp::AppStyle = ":/image/gray.css";
    }
    else if (style == "��ɫ")
    {
        myApp::AppStyle = ":/image/black.css";
    }
    else if (style == "�Һ�ɫ")
    {
        myApp::AppStyle = ":/image/brown.css";
    }
    else if (style == "��ɫ")
    {
        myApp::AppStyle = ":/image/white.css";
    }
    else if (style == "��ɫ")
    {
        myApp::AppStyle = ":/image/silvery.css";
    }

    myHelper::SetStyle(myApp::AppStyle);
    myApp::WriteConfig();
}

void frmMain::InitForm()
{
    ui->labFull->installEventFilter(this);
    ui->labFull->setProperty("labForm", true);

    ui->labStart->installEventFilter(this);
    ui->labStart->setProperty("labForm", true);

    ui->labNVR->installEventFilter(this);
    ui->labNVR->setProperty("labForm", true);

    ui->labIPC->installEventFilter(this);
    ui->labIPC->setProperty("labForm", true);

    ui->labPollConfig->installEventFilter(this);
    ui->labPollConfig->setProperty("labForm", true);

    ui->labVideoPlayBack->installEventFilter(this);
    ui->labVideoPlayBack->setProperty("labForm", true);

    ui->labConfig->installEventFilter(this);
    ui->labConfig->setProperty("labForm", true);

    ui->labExit->installEventFilter(this);
    ui->labExit->setProperty("labForm", true);

    ui->labStyle->installEventFilter(this);
    ui->labStyle->setProperty("labForm", true);

    menuStyle = new QMenu(this);
    menuStyle->addAction(QStringLiteral("����ɫ"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("��ɫ"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("��ɫ"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("��ɫ"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("�Һ�ɫ"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("��ɫ"), this, SLOT(change_style()));
    menuStyle->addAction(QStringLiteral("��ɫ"), this, SLOT(change_style()));
    menuStyle->setStyleSheet("font: 10pt \"΢���ź�\";");

    ui->lab_Title->setText(myApp::AppTitle);
    this->setWindowTitle(myApp::AppTitle);

    ui->treeMain->header()->setVisible(false);
    ui->treeMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void frmMain::InitVideo()
{
    tempLab = 0;
    video_max = false;

    VideoLab.append(ui->labVideo1);
    VideoLab.append(ui->labVideo2);
    VideoLab.append(ui->labVideo3);
    VideoLab.append(ui->labVideo4);
    VideoLab.append(ui->labVideo5);
    VideoLab.append(ui->labVideo6);
    VideoLab.append(ui->labVideo7);
    VideoLab.append(ui->labVideo8);
    VideoLab.append(ui->labVideo9);
    VideoLab.append(ui->labVideo10);
    VideoLab.append(ui->labVideo11);
    VideoLab.append(ui->labVideo12);
    VideoLab.append(ui->labVideo13);
    VideoLab.append(ui->labVideo14);
    VideoLab.append(ui->labVideo15);
    VideoLab.append(ui->labVideo16);

    VideoLay.append(ui->lay1);
    VideoLay.append(ui->lay2);
    VideoLay.append(ui->lay3);
    VideoLay.append(ui->lay4);

    for (int i = 0; i < 16; i++)
    {
        VideoLab[i]->installEventFilter(this);
        VideoLab[i]->setProperty("labVideo", true);
        VideoLab[i]->setText(QStringLiteral("ͨ��%1").arg(i + 1));
    }

    menu = new QMenu(this);
    menu->setStyleSheet("font: 10pt \"΢���ź�\";");
    menu->addAction(QStringLiteral("ɾ����ǰ��Ƶ"), this, SLOT(delete_video_one()));
    menu->addAction(QStringLiteral("ɾ��������Ƶ"), this, SLOT(delete_video_all()));
    menu->addSeparator();
    menu->addAction(QStringLiteral("��ͼ��ǰ��Ƶ"), this, SLOT(snapshot_video_one()));
    menu->addAction(QStringLiteral("��ͼ������Ƶ"), this, SLOT(snapshot_video_all()));
    menu->addSeparator();

    QMenu *menu1 = menu->addMenu(QStringLiteral("�л���1����"));
    menu1->addAction(QStringLiteral("ͨ��1"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��2"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��3"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��4"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��5"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��6"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��7"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��8"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��9"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��10"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��11"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��12"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��13"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��14"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��15"), this, SLOT(show_video_1()));
    menu1->addAction(QStringLiteral("ͨ��16"), this, SLOT(show_video_1()));

    QMenu *menu4 = menu->addMenu(QStringLiteral("�л���4����"));
    menu4->addAction(QStringLiteral("ͨ��1-ͨ��4"), this, SLOT(show_video_4()));
    menu4->addAction(QStringLiteral("ͨ��5-ͨ��8"), this, SLOT(show_video_4()));
    menu4->addAction(QStringLiteral("ͨ��9-ͨ��12"), this, SLOT(show_video_4()));
    menu4->addAction(QStringLiteral("ͨ��13-ͨ��16"), this, SLOT(show_video_4()));

    QMenu *menu9 = menu->addMenu(QStringLiteral("�л���9����"));
    menu9->addAction(QStringLiteral("ͨ��1-ͨ��9"), this, SLOT(show_video_9()));
    menu9->addAction(QStringLiteral("ͨ��8-ͨ��16"), this, SLOT(show_video_9()));

    menu->addAction(QStringLiteral("�л���16����"), this, SLOT(show_video_16()));
}

void frmMain::LoadVideo()
{
    //�Զ�Ӧ�����һ�εĲ�������
    ChangeVideoLayout();
}

void frmMain::ChangeRtspAddr(int ch, QString rtspAddr)
{
    QStringList rtspAddrs = myApp::RtspAddr16.split("|");
    rtspAddrs[ch] = rtspAddr;

    QString tempRtspAddr16;
    for (int i = 0; i < 16; i++) {
        tempRtspAddr16 += rtspAddrs[i] + "|";
    }
    myApp::RtspAddr16 = tempRtspAddr16.mid(0, tempRtspAddr16.length() - 1);
}

void frmMain::LoadNVRIPC()
{
    ui->treeMain->clear();

    QSqlQuery queryNVR;
    QString sqlNVR = "select [NVRID],[NVRName],[NVRIP] from [NVRInfo] where [NVRUse]='����'";
    queryNVR.exec(sqlNVR);

    while (queryNVR.next())
    {
        QString tempNVRID = queryNVR.value(0).toString();
        QString tempNVRName = queryNVR.value(1).toString();
        QString tempNVRIP = queryNVR.value(2).toString();

        QTreeWidgetItem *itemNVR = new QTreeWidgetItem
                (ui->treeMain, QStringList(tempNVRName + "[" + tempNVRIP + "]"));
        itemNVR->setIcon(0, QIcon(":/image/nvr.png"));

        QSqlQuery queryIPC;
        QString sqlIPC = QString("select [IPCID],[IPCName],[IPCRtspAddrMain] from [IPCInfo] where [NVRID]='%1' and [IPCUse]='����' order by [IPCID] asc").arg(tempNVRID);
        queryIPC.exec(sqlIPC);

        while (queryIPC.next()) {
            QString tempIPCName = queryIPC.value(1).toString();
            QString rtspAddr = queryIPC.value(2).toString();

            QStringList temp = rtspAddr.split("/");
            QString ip = temp[2].split(":")[0];

            QTreeWidgetItem *itemIPC = new QTreeWidgetItem(itemNVR, QStringList(QString(tempIPCName + "[" + ip + "]")));
            itemIPC->setIcon(0, QIcon(":/image/ipc_normal.png"));
            itemNVR->addChild(itemIPC);
        }
    }
    ui->treeMain->expandAll();
}

void frmMain::ChangeVideoLayout()
{
    if (myApp::VideoType == "1_4")
    {
        removelayout();
        change_video_4(0);
    }
    else if (myApp::VideoType == "5_8")
    {
        removelayout();
        change_video_4(4);
    }
    else if (myApp::VideoType == "9_12")
    {
        removelayout();
        change_video_4(8);
    }
    else if (myApp::VideoType == "13_16")
    {
        removelayout();
        change_video_4(12);
    }
    else if (myApp::VideoType == "1_9")
    {
        removelayout();
        change_video_9(0);
    }
    else if (myApp::VideoType == "8_16")
    {
        removelayout();
        change_video_9(7);
    }
    else if (myApp::VideoType == "16")
    {
        removelayout();
        change_video_16(0);
    }
}

void frmMain::keyPressEvent(QKeyEvent *event)
{
    //�ո������ȫ��,esc���˳�ȫ��
    switch(event->key())
    {
    case Qt::Key_F1:
        screen_full();
        break;
    case Qt::Key_Escape:
        screen_normal();
        break;
    default:
        QDialog::keyPressEvent(event);
        break;
    }
}

bool frmMain::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *MouseEvent = static_cast<QMouseEvent *>(event);
    if ((event->type() == QEvent::MouseButtonDblClick) &&
            (MouseEvent->buttons() == Qt::LeftButton))
    {
        QLabel *labDouble = qobject_cast<QLabel *>(obj);
        if (!video_max)
        {
            removelayout();
            video_max = true;
            VideoLay[0]->addWidget(labDouble);
            labDouble->setVisible(true);
        }
        else
        {
            video_max = false;
            ChangeVideoLayout();
        }

        labDouble->setFocus();
        return true;
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        if (obj == ui->labFull)
        {
            screen_full();
            return true;
        }
        else if (obj == ui->labStart)
        {
            if (ui->labStart->text() == "������ѯ")
            {
                ui->labStart->setText("ֹͣ��ѯ");
            }
            else
            {
                ui->labStart->setText("������ѯ");
            }
            return true;
        }
        else if (obj == ui->labNVR)
        {
            frmNVR nvr;
            nvr.exec();
            LoadNVRIPC();
            return true;
        }
        else if (obj == ui->labIPC)
        {
            frmIPC ipc;
            ipc.exec();
            LoadNVRIPC();
            return true;
        }
        else if (obj == ui->labPollConfig)
        {
            frmPollConfig pollConfig;
            pollConfig.exec();
            return true;
        }
        else if (obj == ui->labVideoPlayBack)
        {
            myHelper::ShowMessageBoxError("������δ����!");
            return true;
        }
        else if (obj == ui->labConfig)
        {
            frmConfig config;
            config.exec();
            ui->lab_Title->setText(myApp::AppTitle);
            this->setWindowTitle(myApp::AppTitle);
            return true;
        }
        else if (obj == ui->labExit)
        {
            on_btnMenu_Close_clicked();
            return true;
        }
        else if (obj == ui->labStyle)
        {
            menuStyle->exec(QPoint(myApp::DeskWidth - 135, 31));
            return true;
        }
        else if (MouseEvent->buttons() == Qt::RightButton)
        {
            tempLab = qobject_cast<QLabel *>(obj);
            menu->exec(QCursor::pos());
            return true;
        }
        else
        {
            tempLab = qobject_cast<QLabel *>(obj);
            ui->lab_Title->setText(QString("%1  ��ǰѡ��[%2]").arg(myApp::AppTitle).arg(tempLab->text()));
            return true;
        }
    }

    return QObject::eventFilter(obj, event);
}

void frmMain::on_btnMenu_Close_clicked()
{
    exit(0);
}

void frmMain::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}

void frmMain::delete_video_one()
{

}

void frmMain::delete_video_all()
{

}

void frmMain::snapshot_video_one()
{

}

void frmMain::snapshot_video_all()
{

}

void frmMain::removelayout()
{
    for (int i = 0; i < 4; i++)
    {
        VideoLay[0]->removeWidget(VideoLab[i]);
        VideoLab[i]->setVisible(false);
    }

    for (int i = 4; i < 8; i++)
    {
        VideoLay[1]->removeWidget(VideoLab[i]);
        VideoLab[i]->setVisible(false);
    }

    for (int i = 8; i < 12; i++)
    {
        VideoLay[2]->removeWidget(VideoLab[i]);
        VideoLab[i]->setVisible(false);
    }

    for (int i = 12; i < 16; i++)
    {
        VideoLay[3]->removeWidget(VideoLab[i]);
        VideoLab[i]->setVisible(false);
    }
}

void frmMain::show_video_1()
{
    removelayout();
    myApp::VideoType = "1";
    video_max = true;
    int index = 0;

    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "ͨ��1")
    {
        index = 0;
    }
    else if (name == "ͨ��2")
    {
        index = 1;
    }
    else if (name == "ͨ��3")
    {
        index = 2;
    }
    else if (name == "ͨ��4")
    {
        index = 3;
    }
    else if (name == "ͨ��5")
    {
        index = 4;
    }
    else if (name == "ͨ��6")
    {
        index = 5;
    }
    else if (name == "ͨ��7")
    {
        index = 6;
    }
    else if (name == "ͨ��8")
    {
        index = 7;
    }
    else if (name == "ͨ��9")
    {
        index = 8;
    }
    else if (name == "ͨ��10")
    {
        index = 9;
    }
    else if (name == "ͨ��11")
    {
        index = 10;
    }
    else if (name == "ͨ��12")
    {
        index = 11;
    }
    else if (name == "ͨ��13")
    {
        index = 12;
    }
    else if (name == "ͨ��14")
    {
        index = 13;
    }
    else if (name == "ͨ��15")
    {
        index = 14;
    }
    else if (name == "ͨ��16")
    {
        index = 15;
    }

    change_video_1(index);
    myApp::WriteConfig();
}

void frmMain::change_video_1(int index)
{
    for (int i = (index + 0); i < (index + 1) ; i++)
    {
        VideoLay[0]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }
}

void frmMain::show_video_4()
{
    removelayout();
    video_max = false;
    int index = 0;

    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "ͨ��1-ͨ��4")
    {
        index = 0;
        myApp::VideoType = "1_4";
    }
    else if (name == "ͨ��5-ͨ��8")
    {
        index = 4;
        myApp::VideoType = "5_8";
    }
    else if (name == "ͨ��9-ͨ��12")
    {
        index = 8;
        myApp::VideoType = "9_12";
    }
    else if (name == "ͨ��13-ͨ��16")
    {
        index = 12;
        myApp::VideoType = "13_16";
    }

    change_video_4(index);
    myApp::WriteConfig();
}

void frmMain::change_video_4(int index)
{
    for (int i = (index + 0); i < (index + 2); i++) {
        VideoLay[0]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 2); i < (index + 4); i++) {
        VideoLay[1]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }
}

void frmMain::show_video_9()
{
    removelayout();
    video_max = false;
    int index = 0;

    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "ͨ��1-ͨ��9") {
        index = 0;
        myApp::VideoType = "1_9";
    } else if (name == "ͨ��8-ͨ��16") {
        index = 7;
        myApp::VideoType = "8_16";
    }

    change_video_9(index);
    myApp::WriteConfig();
}

void frmMain::change_video_9(int index)
{
    for (int i = (index + 0); i < (index + 3); i++) {
        VideoLay[0]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 3); i < (index + 6); i++) {
        VideoLay[1]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 6); i < (index + 9); i++) {
        VideoLay[2]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }
}

void frmMain::show_video_16()
{
    removelayout();
    myApp::VideoType = "16";
    video_max = false;
    int index = 0;
    change_video_16(index);
    myApp::WriteConfig();
}

void frmMain::change_video_16(int index)
{
    for (int i = (index + 0); i < (index + 4); i++)
    {
        VideoLay[0]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 4); i < (index + 8); i++)
    {
        VideoLay[1]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 8); i < (index + 12); i++)
    {
        VideoLay[2]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }

    for (int i = (index + 12); i < (index + 16); i++)
    {
        VideoLay[3]->addWidget(VideoLab[i]);
        VideoLab[i]->setVisible(true);
    }
}

QString frmMain::GetNVRID(QString NVRIP)
{
    QSqlQuery query;
    QString sql = "select [NVRID] from [NVRInfo]";
    sql += " where [NVRIP]='" + NVRIP + "'";
    query.exec(sql);
    query.next();
    return query.value(0).toString();
}

void frmMain::GetRtspAddr(QString NVRID, QString IPCIP, QString &IPCRtspAddrMain, QString &IPCRtspAddrSub)
{
    QSqlQuery query;
    QString sql = "select [IPCRtspAddrMain],[IPCRtspAddrSub] from [IPCInfo] where [IPCUse]='����'";
    sql += " and [NVRID]='" + NVRID + "'";
    query.exec(sql);
    while(query.next())
    {
        //ȡ����������ַ,���Ƿ�IP��ͬ
        QString rtspAddr = query.value(0).toString();
        QStringList temp = rtspAddr.split("/");
        QString ip = temp[2].split(":")[0];
        if (ip == IPCIP)
        {
            IPCRtspAddrMain = query.value(0).toString();
            IPCRtspAddrSub = query.value(1).toString();
            break;
        }
    }
}

void frmMain::on_treeMain_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    //ѡ�е���NVR�򲻴���
    if (ui->treeMain->currentItem()->parent() == 0)
    {
        return;
    }

    //��ǰ��û��ѡ��ͨ��
    if (tempLab == 0)
    {
        return;
    }

    //ȡ��˫�����������������ַ
    //ȡ��NVR��ż�IPCID
    QString txt = ui->treeMain->currentItem()->parent()->text(0);
    QString NVRIP = txt.split("[")[1].split("]")[0];
    QString NVRID = GetNVRID(NVRIP);
    QString temp = ui->treeMain->currentIndex().data().toString();
    QString IPCIP = temp.split("[")[1].split("]")[0];

    //����NVR��ź�IP��ַ��ѯ�����������������
    QString rtspAddr;
    QString IPCRtspAddrMain;
    QString IPCRtspAddrSub;
    GetRtspAddr(NVRID, IPCIP, IPCRtspAddrMain, IPCRtspAddrSub);
    rtspAddr = (myApp::RtspType == 0 ? IPCRtspAddrMain : IPCRtspAddrSub);

    //����������������
    if (!myHelper::IPCEnable(rtspAddr))
    {
        myHelper::ShowMessageBoxError("�������������!");
        return;
    }

    QString tempCH = tempLab->text();
    for (int i = 0; i < 16; i++)
    {
        if (VideoLab[i]->text() == tempCH)
        {
            ChangeRtspAddr(i, rtspAddr);
            myApp::WriteConfig();
            break;
        }
    }
}

void frmMain::screen_full()
{
    this->setGeometry(qApp->desktop()->geometry());
    this->layout()->setContentsMargins(0, 0, 0, 0);
    ui->widget_main->layout()->setContentsMargins(0, 0, 0, 0);
    ui->widget_title->setVisible(false);
    ui->treeMain->setVisible(false);
}

void frmMain::screen_normal()
{
    this->setGeometry(qApp->desktop()->availableGeometry());
    this->layout()->setContentsMargins(1, 1, 1, 1);
    ui->widget_main->layout()->setContentsMargins(5, 5, 5, 5);
    ui->widget_title->setVisible(true);
    ui->treeMain->setVisible(true);
}

