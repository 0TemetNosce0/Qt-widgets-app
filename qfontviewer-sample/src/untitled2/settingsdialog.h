#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "ui_settingsdialog.h"
#include <QWidget>
#include <QDialog>

class SettingsDialog : public QDialog, Ui::SettingsDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

public slots:
    void on_buttonBox_accepted();
};

#endif
