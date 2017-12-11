#include "itemwidget.h"
#include "global.h"
#include "ctooltip.h"

#include <QEvent>
#include <QCursor>

ItemWidget::ItemWidget(QWidget *parent)
    : QWidget(parent)
{
    labelIcon = new QLabel(this);
    labelName = new QLabel(this);
    labelName->setStyleSheet("QLabel{color: green; font: 13pt bold;}");
    labelInfo = new QLabel(this);
    labelInfo->setStyleSheet("QLabel{color: gray;}");

    verlayout = new QVBoxLayout();// 此处将参数this添加上和不添加上, 注意查看效果
    verlayout->setContentsMargins(0, 0, 0, 0);
    verlayout->addWidget(labelName);
    verlayout->addWidget(labelInfo);

    horLayout = new QHBoxLayout(this);
    horLayout->setContentsMargins(2, 2, 2, 2);
    horLayout->addWidget(labelIcon, 1, Qt::AlignTop);
    horLayout->addLayout(verlayout, 8);

}

void ItemWidget::setText(QPixmap pixmap, QString name, QString info)
{
    labelIcon->setPixmap(pixmap);
    labelName->setText(name);
    labelInfo->setText(info);
}

// 测试用的
void ItemWidget::setText(QString info)
{
    labelIcon->setText(info);
}

// 鼠标悬停的时候,显示当前用户简要信息
bool ItemWidget::event(QEvent *e)
{
    if (e->type() == QEvent::ToolTip)
    {
        qDebug() << "tool tip show";
        g_toolTip->showMessage(labelIcon->pixmap(),
                               labelName->text(),
                               labelInfo->text(),
                               QCursor::pos());
    }
    else if (e->type() == QEvent::Leave)
    {
        qDebug() << "tool tip leave";
        g_toolTip->hide();
    }

    return QWidget::event(e);
}

