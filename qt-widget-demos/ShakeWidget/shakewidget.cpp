#include "shakewidget.h"
#include "ui_shakewidget.h"

#include <QTimer>
#include <QHBoxLayout>
#include <QPushButton>
enum {MaxLimitTimes = 12};
enum {MaxLimitSpace = 5};

ShakeWidget::ShakeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShakeWidget),
    m_timer(new QTimer(this)),
    m_nPosition(0),
    m_curPos(QPoint())
{
    ui->setupUi(this);

    QPushButton* btnTest = new QPushButton(tr("Test"),this);
    bool b = connect(btnTest,SIGNAL(clicked()),this,SLOT(slot_btnTestclicked()));
    Q_ASSERT(b);
    QHBoxLayout* hBox = new QHBoxLayout(this);
    hBox->addWidget(btnTest);
    this->setLayout(hBox);
    // ¼ÆÊ±Æ÷
    b = connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_timerOut()));
    Q_ASSERT(b);
    m_timer->setInterval(40);
}

ShakeWidget::~ShakeWidget()
{
    delete ui;
}

void ShakeWidget::slot_btnTestclicked()
{
    m_nPosition = 0;
    m_curPos = this->pos();
    m_timer->start();
}

void ShakeWidget::slot_timerOut()
{
    m_timer->stop();

    if(m_nPosition < MaxLimitTimes)
    {
        ++m_nPosition;
        switch(m_nPosition%4)
        {
        case 1:
        {
            QPoint tmpPos(m_curPos.x(),m_curPos.y()-MaxLimitSpace);
            this->move(tmpPos);
        }
            break;
        case 2:
        {
            QPoint tmpPos(m_curPos.x()-MaxLimitSpace,m_curPos.y()-MaxLimitSpace);
            this->move(tmpPos);
        }
            break;
        case 3:
        {
            QPoint tmpPos(m_curPos.x()-MaxLimitSpace,m_curPos.y());
            this->move(tmpPos);
        }
            break;
        default:
        case 0:
            this->move(m_curPos);
            break;
        }
        m_timer->start();
    }
}
