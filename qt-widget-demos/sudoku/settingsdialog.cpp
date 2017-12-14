#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget * parent)
    : QDialog(parent)
{
    setWindowTitle(QStringLiteral("设置"));
    label = new QLabel(QStringLiteral("题目的解数："), this);
    comboBox = new QComboBox(this);

    for (int i = 1; i <= 10; i++)
    {
        comboBox->addItem(QVariant(i).toString());
    }

    comboBox->setCurrentIndex(0);

    label->setBuddy(comboBox);

    okButton = new QPushButton(tr("OK"), this);
    cancelButton = new QPushButton(tr("Cancel"), this);

    QHBoxLayout * hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(label);
    hLayout1->addWidget(comboBox);

    QHBoxLayout * hLayout2 = new QHBoxLayout;
    hLayout2->addStretch();
    hLayout2->addWidget(okButton);
    hLayout2->addWidget(cancelButton);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);

    setLayout(vLayout);
    setFixedSize(vLayout->sizeHint());

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}
