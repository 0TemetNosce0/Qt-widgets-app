#include "dialog.h"
#include "widget.h"
#include "ui_dialog.h"
#include "hexspinbox.h"
#include "searchbutton.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>

const int NUMBER = 4;

CustomDialog::CustomDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("网格布局"));
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    QGridLayout *pLayout = new QGridLayout(this);
    pLayout->setObjectName("LiTZ");
    pLayout->setProperty("title",QStringLiteral("标题"));
    pLayout->setProperty("toolTip", "tishi");

    for(int j = 0; j < NUMBER; j++)
    {
//        Widget *pWidget = new Widget(this);
//        pWidget->setObjectName(QStringLiteral("窗体"));
        QPushButton *pButton = new QPushButton(QStringLiteral("测试"), this);
        connect(pButton, SIGNAL(clicked()), this, SLOT(showMessage()));
        pLayout->addWidget(pButton, j/2, j%2);
    }

    // 改变它所在顶级窗口的大小
    setSizeGripEnabled(true);
}

CustomDialog::~CustomDialog()
{
    delete ui;
}

void CustomDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        move(event->globalPos() - m_dragPoint);
        event->accept();
    }
    else
    {
        QDialog::mouseMoveEvent(event);
    }
}

void CustomDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragPoint = event->globalPos() - frameGeometry().topLeft();

        event->accept();
    }
    else
    {
        QDialog::mousePressEvent(event);
    }
}

void CustomDialog::showMessage()
{
    QMessageBox::information(NULL, QStringLiteral("标题"), QStringLiteral("内容"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
