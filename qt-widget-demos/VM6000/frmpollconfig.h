#ifndef FRMPOLLCONFIG_H
#define FRMPOLLCONFIG_H

#include <QDialog>

class QSqlQueryModel;
class QModelIndex;

namespace Ui
{
    class frmPollConfig;
}

class frmPollConfig : public QDialog
{
    Q_OBJECT

public:
    explicit frmPollConfig(QWidget *parent = 0);
    ~frmPollConfig();

private slots:
    void on_btnAddOne_clicked();
    void on_btnAddAll_clicked();
    void on_btnRemoveOne_clicked();
    void on_btnRemoveAll_clicked();
    void on_btnExcel_clicked();
    void on_treeMain_doubleClicked(const QModelIndex &index);
    void on_tableMain_doubleClicked(const QModelIndex &index);

private:
    Ui::frmPollConfig *ui;

    QSqlQueryModel *queryModule;

    void InitStyle();   //��ʼ���ޱ߿���
    void InitForm();    //��ʼ����������
    void LoadNVRIPC();  //����NVR��IPC����
    void LoadPollInfo();//������ѯ����

    QString GetNVRID(QString NVRIP);
    bool IsExistIPCID(QString IPCID);

    void GetIPCInfo(QString NVRID, QStringList &IPCID, QStringList &IPCName,
                    QStringList &IPCRtspAddrMain, QStringList &IPCRtspAddrSub);
    void GetIPCInfo(QStringList &IPCID, QStringList &IPCName,
                    QStringList &NVRID, QStringList &NVRName,
                    QStringList &IPCRtspAddrMain, QStringList &IPCRtspAddrSub);
    void GetIPCInfo(QString NVRID, QString IPCID, QString &IPCName,
                    QString &IPCRtspAddrMain, QString &IPCRtspAddrSub);

    void AddPollInfo(QString IPCID, QString IPCName,
                     QString NVRID, QString NVRName,
                     QString IPCRtspAddrMain, QString IPCRtspAddrSub);


};

#endif // FRMPOLLCONFIG_H
