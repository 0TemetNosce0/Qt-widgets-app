#include "ccombobox.h"
#include "accountitem.h"

#include <QDebug>
#include <QListWidgetItem>

CComboBox::CComboBox(QWidget *parent) :
    QComboBox(parent)
{
    m_strText = "";
    connect(this, SIGNAL(currentTextChanged(QString)), this, SLOT(textChanged(QString)));
}

void CComboBox::setItemEnable(QListWidget *list, int index, bool enable) 
{
    QListWidgetItem *item = list->item(index);
    AccountItem *accountItem = (AccountItem *)(list->itemWidget(item));
    // 此处可以用颜色进行区分
    if (enable) 
	{
        // account_item->setStyleSheet("QWidget{background: lightgray;}");
        accountItem->setEnabled(false);
    } 
	else 
	{
        // account_item->setStyleSheet("QWidget{background: yellow;}");
    }
}

void CComboBox::textChanged(QString text) 
{
    qDebug() << text;
    if (text.isEmpty()) 
	{
        this->setEditText(m_strText);
    } 
	else 
	{
        m_strText = text;
    }
}

