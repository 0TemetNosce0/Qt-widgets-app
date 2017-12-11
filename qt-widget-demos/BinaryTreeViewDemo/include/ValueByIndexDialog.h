#ifndef VALUEBYINDEXDIALOG_H_
#define VALUEBYINDEXDIALOG_H_

#include <QDialog>
#include "ui_valuebyindexdialog.h"

class ValueByIndexDialog : public QDialog, public Ui::ValueByIndexDialog
{
    Q_OBJECT;

public:
    ValueByIndexDialog(QWidget *parent);
    void setRange(int min, int max);
    int index();
    void setValue(int value);

private slots:
    void askForValue();

signals:
    void indexChanged(int index);
};

#endif /* VALUEBYINDEXDIALOG_H_ */
