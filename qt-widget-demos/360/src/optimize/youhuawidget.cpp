#include "youhuawidget.h"
#include "common/youhuascanbottom.h"
#include "../common/wenlibackwidget.h"
#include "../common/stackstatuswidget.h"
#include <QVBoxLayout>

YouhuaWidget::YouhuaWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
}

void YouhuaWidget::initUI()
{
    m_topBackWidget = new WenliBackWidget;
    m_stackStatusWidget = new StackStatusWidget;
    m_topBackWidget->insertWidget(m_stackStatusWidget);
    m_topBackWidget->setButtonInfo(":/safe/return");
    m_stackStatusWidget->setStaticIcon(":/youhua/logo");
    m_stackStatusWidget->setNormalButton(":/youhua/start");
    m_stackStatusWidget->setTextInfo("һ���Ż����õ��Կ�������", \
                                         "ȫ���������Կ����ٶȡ�ϵͳ�ٶȡ������ٶȡ�Ӳ���ٶ�");
    m_topBackWidget->setFixedHeight(150);
    connect(m_topBackWidget, SIGNAL(buttonClicked()), this, SIGNAL(goToMain()));
    m_scanBottomWidget = new YouhuaScanBottom;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(m_topBackWidget);
    vLayout->addWidget(m_scanBottomWidget);
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(0,0,0,0);

    this->setLayout(vLayout);
}
