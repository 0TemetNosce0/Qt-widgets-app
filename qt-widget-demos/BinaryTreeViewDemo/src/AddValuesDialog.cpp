#include "../include/AddValuesDialog.h"

#include <QDebug>
#include <QTimer>
#include <QPushButton>

AddValuesDialog::AddValuesDialog(QWidget *parent, bool batchMode)
    : QDialog(parent)
{
    setupUi(this);
    verticalLayout->setSizeConstraint(QLayout::SetFixedSize);

    m_batchMode = batchMode;
    batchModeCheckBox->setChecked(m_batchMode);
    valuesPlainTextEdit->setVisible(m_batchMode);
    valueSpinBox->setHidden(m_batchMode);
    if (!m_batchMode)
    {
        QTimer::singleShot(0, valueSpinBox, SLOT(selectAll()));
    }
}

QList<int> AddValuesDialog::values()
{
    QList<int> list;

    if (m_batchMode)
    {
        QRegExp rx("(-?\\d+)");
        QString str = valuesPlainTextEdit->toPlainText();
        int pos = 0;
        while ((pos = rx.indexIn(str, pos)) != -1)
        {
            list << rx.cap(1).toInt();
            pos += rx.matchedLength();
        }
    }
    else
    {
        list << valueSpinBox->value();
    }

    return list;
}

void AddValuesDialog::on_valuesPlainTextEdit_textChanged()
{
    bool notEmpty = !valuesPlainTextEdit->toPlainText().isEmpty();
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(notEmpty);
}

void AddValuesDialog::on_batchModeCheckBox_toggled(bool batchMode)
{
    m_batchMode = batchMode;
    valueSpinBox->setHidden(m_batchMode);
    valuesPlainTextEdit->setVisible(m_batchMode);

    if (m_batchMode)
    {
        bool notEmpty = !valuesPlainTextEdit->toPlainText().isEmpty();
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(notEmpty);
    }
    else
    {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

bool AddValuesDialog::batchMode()
{
    return m_batchMode;
}
