#ifndef ADDVALUESDIALOG_H_
#define ADDVALUESDIALOG_H_

#include <QList>
#include <QDialog>
#include "ui_addvaluesdialog.h"

class AddValuesDialog : public QDialog, public Ui::AddValuesDialog
{
    Q_OBJECT

public:
    AddValuesDialog(QWidget *parent = 0, bool batchMode = false);
    QList<int> values();
    bool batchMode();

private slots:
    void on_valuesPlainTextEdit_textChanged();
    void on_batchModeCheckBox_toggled(bool batchMode);

private:
    bool m_batchMode;
    void plainTextValues(QList<int> &list);
};

#endif /* ADDVALUESDIALOG_H_ */
