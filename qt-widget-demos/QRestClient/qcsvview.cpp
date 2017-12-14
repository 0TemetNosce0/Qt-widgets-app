#include "qcsvview.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>
#include <QTreeView>
#include <QStatusBar>

#include <QDebug>

QCsvView::QCsvView(QWidget *parent)
    : QWidget(parent)
{

    m_Delimeter = ";";
    m_Enclosure = "\"";
    m_Text = "";
    m_firstRowHeader = true;

    QFormLayout *form = new QFormLayout();
    QLineEdit *txtDelimeter = new QLineEdit(m_Delimeter);
    QLineEdit *txtEnclosure = new QLineEdit(m_Enclosure);

    QCheckBox *chkFirstRowHeader = new QCheckBox("First row is header");
    chkFirstRowHeader->setChecked(true);

    form->addRow("Delimeter:", txtDelimeter);
    form->addRow("Enclosure:", txtEnclosure);
    form->addRow("", chkFirstRowHeader);

    m_csvBody = new QTreeView;

    lblCountColumns = new QLabel();
    lblCountRows = new QLabel();

    QStatusBar *statusBar = new QStatusBar();
    statusBar->addWidget(new QLabel("Line:"));
    statusBar->addWidget(lblCountRows);
    statusBar->addWidget(new QLabel("Col:"));
    statusBar->addWidget(lblCountColumns);

    QVBoxLayout *lyt = new QVBoxLayout(this);
    lyt->addLayout(form);
    lyt->addWidget(m_csvBody);
    lyt->addWidget(statusBar);

    connect(txtDelimeter,SIGNAL(textChanged(QString)),this,SLOT(slotChangeDelimeter(QString)));
    connect(txtEnclosure,SIGNAL(textChanged(QString)),this,SLOT(slotChangeEnclosure(QString)));
    connect(chkFirstRowHeader,SIGNAL(toggled(bool)),this,SLOT(slotFirstRowHeader(bool)));
}

void QCsvView::setText(const QString &text)
{
    m_Text = text;
    renderCsv();
}

void QCsvView::renderCsv()
{
    QRegExp regEnclosure("^\\" + m_Enclosure + "{1}|\\" + m_Enclosure + "{1}$");

    QRegExp regRow("\n|\r|\n\r|\r\n");
    QRegExp regColumn(m_Delimeter + "|" + m_Delimeter + m_Enclosure+"|" + m_Enclosure + m_Delimeter + "|" + m_Enclosure + m_Delimeter + m_Enclosure);

    QStringList rows = m_Text.split(regRow);

    QStringList headerColumns = rows.first().split(regColumn);
    int countColumns = headerColumns.size();

    QStandardItemModel *model = new QStandardItemModel(0, countColumns, this);

    if(m_firstRowHeader)
    {
        rows.removeFirst();

        for(int i = 0; i < countColumns; i++)
        {
            QString text = QString(headerColumns.at(i).toLocal8Bit().constData()).replace(regEnclosure, "");
            model->setHeaderData(i, Qt::Horizontal, text);
        }

    }
    else
    {
        for(int i = 0; i < countColumns; i++)
        {
            model->setHeaderData(i, Qt::Horizontal, QString::number(i));
        }
    }

    for(int i = 0; i < rows.size(); i++)
    {
        QStringList columns = rows.at(i).split(regColumn);

        for(int y = 0; y < columns.size(); y++)
        {
            QString text = QString(columns.at(y).toLocal8Bit().constData()).replace(regEnclosure, "");
            QStandardItem* item = new QStandardItem(text);
            model->setItem(i,y,item);
        }
    }

    m_csvBody->setModel(model);
    m_csvBody->setAlternatingRowColors(true);

    m_csvBody->header()->setStretchLastSection(true);
    lblCountColumns->setText(QString::number(countColumns));
    lblCountRows->setText(QString::number(rows.size()));
}

void QCsvView::slotChangeDelimeter(QString text)
{
    m_Delimeter = text;
    renderCsv();
}

void QCsvView::slotChangeEnclosure(QString text)
{
    m_Enclosure = text;
    renderCsv();
}

void QCsvView::slotFirstRowHeader(bool checked)
{
    m_firstRowHeader = checked;
    renderCsv();
}
