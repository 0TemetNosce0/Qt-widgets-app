#include "accountitem.h"
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>

AccountItem::AccountItem(QWidget *parent)
    : QWidget(parent)
{
    // 大小 样式 自己设定，此处只用于演示用
    mouse_press = false;
    m_label = new QLabel();
    deleteButton = new QPushButton();

    QPixmap pixmap(":/res/del.png");
    deleteButton->setIcon(pixmap);
    deleteButton->setIconSize(pixmap.size());
    deleteButton->setStyleSheet("background:transparent;");
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(removeAccount()));

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(m_label);
    mainLayout->addStretch();
    mainLayout->addWidget(deleteButton);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);
    this->setLayout(mainLayout);
}

AccountItem::~AccountItem()
{

}

void AccountItem::setAccountNumber(QString accountText)
{
    m_label->setText(accountText);
}

QString AccountItem::getAccountNumber()
{
    QString accountNumberText = m_label->text();

    return accountNumberText;
}

void AccountItem::removeAccount()
{
    QString accountNumberText = m_label->text();
    emit removeAccount(accountNumberText);
}

void AccountItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }
}

void AccountItem::mouseReleaseEvent(QMouseEvent *)
{
    if(mouse_press)
    {
        emit showAccount(m_label->text());
        mouse_press = false;
    }
}
