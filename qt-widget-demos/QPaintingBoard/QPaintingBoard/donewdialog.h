#ifndef DONEWDIALOG_H
#define DONEWDIALOG_H

#include <QDialog>

namespace Ui {
    class DoNewDialog;
}

class DoNewDialog : public QDialog {
    Q_OBJECT
public:
    DoNewDialog(QWidget *parent = 0);
    ~DoNewDialog();
    int getWidth();   //���ڷ��ػ����Ŀ�
    int getHeight();   //���ڷ��ػ����ĸ�
    QColor getBackColor();   //���ڷ��ػ����ı���ɫ

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DoNewDialog *ui;
    QColor backColor;   //���ڱ��滭���ı���ɫ

private slots:
    void on_toolButton_clicked();
};

#endif // DONEWDIALOG_H
