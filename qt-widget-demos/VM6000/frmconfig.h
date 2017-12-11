#ifndef FRMCONFIG_H
#define FRMCONFIG_H

#include <QDialog>

namespace Ui
{
    class frmConfig;
}

class frmConfig : public QDialog
{
    Q_OBJECT

public:
    explicit frmConfig(QWidget *parent = 0);
    ~frmConfig();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void on_btnOk_clicked();
    void on_btnClearNVR_clicked();
    void on_btnClearIPC_clicked();
    void on_btnClearPoll_clicked();
    void on_btnClearAll_clicked();

private:
    Ui::frmConfig *ui;

    QPoint mousePoint;  //����϶��Զ��������ʱ������
    bool mousePressed;  //����Ƿ���
    void InitStyle();   //��ʼ���ޱ߿���
    void InitForm();    //��ʼ����������

};

#endif // FRMCONFIG_H
