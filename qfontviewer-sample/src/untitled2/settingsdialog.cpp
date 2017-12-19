#include "settingsdialog.h"
#include <QSettings>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);

    QSettings s(qApp->applicationName());
    QFont newFont = s.value("fontStyle").value<QFont>();

    QVariant antialias0 = s.value("antialias");
    if (antialias0.isValid())
        antialias->setChecked(antialias0.toBool());

    QVariant autoFontMerge0 = s.value("autoFontMerge");
    if (autoFontMerge0.isValid())
        autoFontMerge->setChecked(autoFontMerge0.toBool());

    QVariant systemColors0 = s.value("systemColors");
    if (systemColors0.isValid())
        systemColors->setChecked(systemColors0.toBool());
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::on_buttonBox_accepted()
{
    QSettings s(qApp->applicationName());

    s.setValue("antialias", antialias->isChecked());
    s.setValue("autoFontMerge", autoFontMerge->isChecked());
    s.setValue("systemColors", systemColors->isChecked());

    s.sync();
    emit accept();
}
