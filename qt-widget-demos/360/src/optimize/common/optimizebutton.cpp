#include "youhuabutton.h"
#include "../../common/speedoutbutton.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>

OptimizeButton::OptimizeButton(QWidget *parent)
    : QWidget(parent)
    , m_isChecked(true)
{
    this->initUI();
}

void OptimizeButton::initUI()
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    m_speed = new SpeedOutButton;
    m_speed->setAttribute(Qt::WA_TransparentForMouseEvents);

    m_titleLabel = new QLabel;
    m_titleLabel->setObjectName("youhuaTitle");
    m_descriptionLabel = new QLabel;
    m_descriptionLabel->setObjectName("youhuaDesc");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(m_speed, 0, Qt::AlignHCenter);
    vLayout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    vLayout->addWidget(m_descriptionLabel, 0, Qt::AlignHCenter);
    vLayout->setSpacing(5);
    vLayout->setContentsMargins(5, 0, 5, 5);

    this->setLayout(vLayout);
}

void OptimizeButton::setIconInfo(const QString &icon)
{
    m_icon = icon;
    m_speed->setIconsInfo(icon);
}

void OptimizeButton::setTitle(const QString &title)
{
    m_title = title;
    m_titleLabel->setText(title);
}

void OptimizeButton::setDescription(const QString &desc)
{
    m_description = desc;
    m_descriptionLabel->setText(m_description);
}

void OptimizeButton::setCheckedState(bool state)
{
    m_isChecked = state;
    m_speed->setCheckdStatus(m_isChecked);
}

void OptimizeButton::enterEvent(QEvent *)
{
    m_speed->setButtonStatus(BUTTON_ENTER);
}

void OptimizeButton::leaveEvent(QEvent *)
{
    m_speed->setButtonStatus(BUTTON_LEAVE);
}

void OptimizeButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton)
    {
        e->ignore();
        return;
    }
    m_speed->setButtonStatus(BUTTON_PRESSED);
}

void OptimizeButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton)
    {
        e->ignore();
        return;
    }

    if(rect().contains(e->pos()))
    {
        this->setCheckedState((!m_isChecked));
        m_speed->setButtonStatus(BUTTON_ENTER);
        emit checkedChanged(m_isChecked);
        e->accept();
    }
    else
    {
        m_speed->setButtonStatus(BUTTON_LEAVE);
        e->ignore();
    }
}

