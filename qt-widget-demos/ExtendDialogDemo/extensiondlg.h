#ifndef EXTENSIONDLG_H
#define EXTENSIONDLG_H

#include <QDialog>

namespace Ui {
class extensiondlg;
}

class extensiondlg : public QDialog
{
    Q_OBJECT

public:
    explicit extensiondlg(QWidget *parent = 0);
    ~extensiondlg();

private slots:
    void showDetailInfo();

private:
    Ui::extensiondlg *ui;
    void createBaseInfo();           	//ʵ�ֻ����Ի����岿��
    void createDetailInfo();            //ʵ����չ���岿��
    QWidget *baseWidget;                //�����Ի����岿��
    QWidget *detailWidget;            	//��չ���岿��
};

#endif // EXTENSIONDLG_H
