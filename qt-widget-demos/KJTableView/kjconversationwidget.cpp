#include "kjconversationwidget.h"
#include "ui_kjconversationwidget.h"

#include <QDebug>
#include <QMessageBox>

KJConversationWidget::KJConversationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::KJConversationWidget)
{
    ui->setupUi(this);
    connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(slotOnButtonClicked()));
}

KJConversationWidget::~KJConversationWidget()
{
    delete ui;
}

void KJConversationWidget::init(QString title, QString detail, int found)
{
    ui->lblTitle->setText(title);
    ui->lblDetail->setText(detail);
    ui->lblFound->setText(QString("%1").arg(found));
}

void KJConversationWidget::slotOnButtonClicked()
{
    qDebug() << "clicked on:" << ui->lblTitle->text() << "real widgets: " << widgetIndex;
    QString message = QString("You clicked on row: %1 of widget: %2").arg(ui->lblTitle->text()).arg(widgetIndex);
    QMessageBox::warning(this, "Widget", message, QMessageBox::Ok);
}
