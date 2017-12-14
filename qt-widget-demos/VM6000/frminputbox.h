#ifndef FRMINPUTBOX_H
#define FRMINPUTBOX_H

#include <QDialog>

namespace Ui
{
    class frmInputBox;
}

class frmInputBox : public QDialog
{
    Q_OBJECT

public:
    explicit frmInputBox(QWidget *parent = 0);
    ~frmInputBox();

    void SetMessage(QString title);
    QString GetValue()const {
        return value;
    }

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_btnOk_clicked();

private:
    Ui::frmInputBox *ui;

    QPoint mousePoint;  //����϶��Զ��������ʱ������
    bool mousePressed;  //����Ƿ���
    void InitStyle();   //��ʼ���ޱ߿���

    QString value;
};

#endif // FRMINPUTBOX_H
