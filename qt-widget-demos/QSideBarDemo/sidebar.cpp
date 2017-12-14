#include "sidebar.h"

int actionHeight = 90;

SideBar::SideBar(QWidget *parent)
    : QWidget(parent)
    , pressedAction(NULL)
    , checkedAction(NULL)
{
    setFixedWidth(90);
}

SideBar::~SideBar()
{

}

void SideBar::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    QFont fontText(p.font());
    fontText.setFamily("Helvetica Neue");
    p.setFont(fontText);

    //Adapter l'adresse de la texture ici
    QImage texture(":/icon/texture.png");
    p.fillRect(event->rect(), QBrush(texture));
    p.setPen(Qt::black);
    p.drawLine(event->rect().topRight(), event->rect().bottomRight());

    int actions_height = m_actionList.size()*actionHeight;

    int action_y = event->rect().height()/2-actions_height/2;
    foreach(QAction *action, m_actionList)
    {
        QRect actionRect(0, action_y, event->rect().width(), actionHeight);

        if(action->isChecked())
        {
            p.setOpacity(0.5);
            p.fillRect(actionRect, QColor(19, 19, 19));
            p.setPen(QColor(9, 9, 9));
            p.drawLine(actionRect.topLeft(), actionRect.topRight());
            p.setOpacity(1);

        }

        if(action == m_actionList.last())
        {
            p.setPen(QColor(15, 15, 15));
            p.drawLine(QPoint(0, actionRect.bottomLeft().y()-1), QPoint(actionRect.width(), actionRect.bottomRight().y()-1));
            p.setPen(QColor(55, 55, 55));
            p.drawLine(actionRect.bottomLeft(), actionRect.bottomRight());

        }

        if(!action->isChecked())
        {
            p.setPen(QColor(15, 15, 15));
            p.drawLine(actionRect.topLeft(), actionRect.topRight());
            p.setPen(QColor(55, 55, 55));
            p.drawLine(QPoint(0, actionRect.topLeft().y()+1), QPoint(actionRect.width(), actionRect.topRight().y()+1));
        }

        QRect actionIconRect(0, action_y, event->rect().width(), actionHeight-20);
        QIcon  actionIcon(action->icon());
        actionIcon.paint(&p, actionIconRect);

        p.setPen(QColor(217, 217, 217));

        if(action->isChecked())
        {
            p.setPen(QColor(255, 255, 255));
        }

        QRect actionTextRect(0, action_y+actionRect.height()-20, event->rect().width(), 15);
        p.drawText(actionTextRect, Qt::AlignCenter, action->text());

        action_y += actionRect.height();
    }

}

QSize SideBar::minimumSizeHint() const
{
    return QSize(90, m_actionList.size()*actionHeight);
}

void SideBar::addAction(QAction *action)
{
    m_actionList.push_back(action);
    action->setCheckable(true);
    update();
    return;
}

QAction *SideBar::addAction(const QString &text, const QIcon &icon)
{
    QAction *action = new QAction(icon, text, this);
    action->setCheckable(true);
    m_actionList.push_back(action);
    update();
    return action;
}

void SideBar::mousePressEvent(QMouseEvent *event)
{
    pressedAction = actionAt(event->pos());

    if(pressedAction == NULL || pressedAction == checkedAction)
    {
        return;
    }

    update();
}

void SideBar::mouseReleaseEvent(QMouseEvent *event)
{
    QAction* tempAction = actionAt(event->pos());

    if(pressedAction != tempAction || tempAction == NULL)
    {
        pressedAction = NULL;
        return;
    }

    if(checkedAction != NULL)
    {
        checkedAction->setChecked(false);
    }

    checkedAction = pressedAction;

    if(checkedAction != NULL)
    {
        checkedAction->setChecked(true);
    }

    update();
    pressedAction = NULL;
}

QAction* SideBar::actionAt(const QPoint &at)
{
    int actionsHeight = m_actionList.size() * actionHeight;

    int actionY = rect().height()/2 - actionsHeight/2;

    foreach(QAction *action, m_actionList)
    {
        QRect actionRect(0, actionY, rect().width(), actionHeight);

        if(actionRect.contains(at))
        {
            return action;
        }

        actionY += actionRect.height();
    }

    return NULL;
}
