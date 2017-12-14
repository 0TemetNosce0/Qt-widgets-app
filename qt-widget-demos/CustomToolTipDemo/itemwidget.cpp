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

    verlayout = new QVBoxLayout();// �˴�������this����ϺͲ������, ע��鿴Ч��
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

// �����õ�
void ItemWidget::setText(QString info)
{
    labelIcon->setText(info);
}

// �����ͣ��ʱ��,��ʾ��ǰ�û���Ҫ��Ϣ
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

