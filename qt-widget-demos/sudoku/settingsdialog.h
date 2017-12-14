#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QLabel>
#include <QDialog>
#include <QComboBox>

class SettingsDialog :public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget * parent  = 0);
    int solutions() const { return comboBox->currentIndex() + 1; }
    void setSolutions(int num) { comboBox->setCurrentIndex(num - 1); }

private:
    QLabel * label;
    QComboBox * comboBox;
    QPushButton * okButton;
    QPushButton * cancelButton;
};
#endif // !SETTINGSDIALOG_H
