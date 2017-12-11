#include <QtGui>
#include "../include/ValueByIndexDialog.h"
#include <QDebug>
#include <QPushButton>
#include <QTimer>

ValueByIndexDialog::ValueByIndexDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    buttonBox->button(QDialogButtonBox::Cancel)->setDefault(false);
    buttonBox->button(QDialogButtonBox::Cancel)->setAutoDefault(false);
    indexSpinBox->setValue(1);
    connect(indexSpinBox, SIGNAL(editingFinished()), this, SLOT(askForValue()));
    QTimer::singleShot(0, indexSpinBox, SLOT(selectAll()));
}

void ValueByIndexDialog::setRange(int min, int max)
{
    indexSpinBox->setMinimum(min);
    indexSpinBox->setMaximum(max);
}

void ValueByIndexDialog::setValue(int value)
{
    valueLineEdit->setText(QString::number(value));
}

void ValueByIndexDialog::askForValue()
{
    emit indexChanged(indexSpinBox->value());
}

int ValueByIndexDialog::index()
{
    return indexSpinBox->value();
}
