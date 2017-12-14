#include "lcomponent.h"
#include <QDebug>

LComponent::LComponent(QWidget *parent)
    : QWidget(parent)
    , m_nCurrentComponentId(0)
{
    ui.setupUi(this);
}

LComponent::~LComponent()
{

}

void LComponent::mousePressEvent(QMouseEvent *event)
{
    m_qpMousePressPoint = event->pos();
    updateComponentPos();

    QWidget::mousePressEvent(event);
}

void LComponent::mouseMoveEvent(QMouseEvent *event)
{
    move(pos() + event->pos() - m_qpMousePressPoint);

    if (m_lComponent.size() != 0)
    {
        for (int i = 0; i < m_lComponent.size(); i++)
        {
            if (m_lComponent[i] != nullptr)
            {
                m_lComponent[i]->move(geometry().topLeft() + *m_lComponentPos[i]
                                      + event->pos() - m_qpMousePressPoint);
            }
        }
    }

    QWidget::mouseMoveEvent(event);
}

void LComponent::updateComponentPos()
{
    for (int i = 0; i < m_lComponent.size(); i++)
    {
        if (m_lComponent[i] != nullptr)
        {
            m_lComponentPos[i]->setX(m_lComponent[i]->geometry().x() - geometry().topLeft().x());
            m_lComponentPos[i]->setY(m_lComponent[i]->geometry().y() - geometry().topLeft().y());
        }
    }
}

void LComponent::on_btnNewComponent_clicked()
{
    Component *pComponent = new Component(m_nCurrentComponentId, this);
    connect(pComponent, SIGNAL(onComponentClose(int)), this, SLOT(doComponentClose(int)));
    pComponent->setToolBarWidth(ui.qwToolBar->width());
    pComponent->setStatusBarHeight(ui.qwStatusBar->height());
    pComponent->show();
    m_lComponent << pComponent;
    QPoint *pPoint = new QPoint(0, 0);
    m_lComponentPos << pPoint;
    m_nCurrentComponentId++;
}

void LComponent::on_btnHideToolBar_clicked()
{
    ui.qwToolBar->setVisible(false);

    for (int i = 0; i < m_lComponent.size(); i++)
    {
        if (m_lComponent[i] != nullptr)
        {
            m_lComponent[i]->setToolBarWidth(0);
        }
    }
}

void LComponent::on_btnCallToolBar_clicked()
{
    ui.qwToolBar->setVisible(true);

    int nLeftLimit = geometry().x() + ui.qwToolBar->width();
    int nRightLimit = geometry().x() + width();

    for (int i = 0; i < m_lComponent.size(); i++)
    {
        if (m_lComponent[i] != nullptr)
        {
            m_lComponent[i]->setToolBarWidth(ui.qwToolBar->width());

            if (m_lComponent[i]->pos().x() < geometry().x() + ui.qwToolBar->width())
            {
                if ((nLeftLimit + m_lComponent[i]->width()) < nRightLimit)
                {
                    m_lComponent[i]->move(nLeftLimit, m_lComponent[i]->pos().y());
                }
                else
                {
                    m_lComponent[i]->setGeometry(nLeftLimit, m_lComponent[i]->pos().y(),
                        nRightLimit - nLeftLimit, 
                        m_lComponent[i]->geometry().height());
                }
            }
        }
    }
}

void LComponent::doComponentClose(int nMyComponentId)
{
    m_lComponent[nMyComponentId] = nullptr;
}
