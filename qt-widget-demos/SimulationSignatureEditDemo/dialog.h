#ifndef DIALOG_H
#define DIALOG_H

#include "qslineedit.h"

#include <QDialog>
#include <QString>
#include <QMouseEvent>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

signals:

protected slots:
    void mousePressEvent(QMouseEvent *e);

private:
    QSLineEdit *leEdit;
    QSLineEdit *leEdit2;
    QLineEdit *edit;

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
