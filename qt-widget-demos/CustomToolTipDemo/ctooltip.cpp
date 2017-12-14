#include "ctooltip.h"
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

CToolTip::CToolTip(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    this->resize(200, 100); ;

    this->setObjectName("CToolTip");
    this->setStyleSheet("QWidget#CToolTip {border: 2px solid green; background-color: skyblue;}");

    groupBox = new QGroupBox(this);
    groupBox->setGeometry(10, 10, 180, 80);
    groupBox->setTitle(QStringLiteral("�û���Ϣ"));

    labelIcon = new QLabel(groupBox);
    labelName = new QLabel(groupBox);
    labelInfo = new QLabel(groupBox);

    verlayout = new QVBoxLayout();
    verlayout->setContentsMargins(0, 0, 0, 0);
    verlayout->addWidget(labelName);
    verlayout->addWidget(labelInfo);

    horLayout = new QHBoxLayout(groupBox);
    horLayout->setContentsMargins(10, 10, 10, 10);
    horLayout->addWidget(labelIcon, 1, Qt::AlignTop);
    horLayout->addLayout(verlayout, 4);
}

// ��ʾToolTip��Ϣ
void CToolTip::showMessage(const QPixmap *pixmap, QString name, QString info, QPoint point)
{
    labelIcon->setPixmap(*pixmap);
    labelName->setText(name);
    labelInfo->setText(info);

    // ���¶���CToolTip������
    int rectX;
    int rectY;
    if (point.rx() < 200)
    {
        rectX = point.rx() + 10;
    }
    else
    {
        rectX = point.rx() - 240;
    }
    rectY = point.ry();
    move(QPoint(rectX, rectY));
    QWidget::show();
}

// ��ʾToolTip��Ϣ
void CToolTip::showMessage(const QPixmap *pixmap, QPoint point)
{
    labelIcon->setPixmap(*pixmap);

    labelName->setText(QStringLiteral("�Լ���취��ȡ"));
    labelInfo->setText(QStringLiteral("�Լ����֣�������ʳ"));
    // �˴�������ΪQToolTip��ʽ������ʾ
    move(point);
    QWidget::show();
}

// ���������¼�ʱ,�ý������ص�
void CToolTip::hoverEvent(QHoverEvent *)
{
    hide();
}

