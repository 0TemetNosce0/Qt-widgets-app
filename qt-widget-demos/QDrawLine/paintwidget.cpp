#include <QPainter>

#include "paintwidget.h"
#include "ui_paintwidget.h"

paintWidget::paintWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::paintWidget)
{
    ui->setupUi(this);

    m_nInitialX = 0;
    m_nInitialY = 0;
    m_nFinalX = 0;
    m_nFinalY = 0;
    m_nPTargetPixmap = new QPixmap(400,400);
    m_nbMousePressed = false;
}

paintWidget::~paintWidget()
{
    delete ui;
}

void paintWidget::mousePressEvent(QMouseEvent* event)
{
    m_nbMousePressed = true;
    m_nInitialX = event->pos().x();
    m_nInitialY = event->pos().y();
}

void paintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_nbMousePressed = false;
    //update();
}

void paintWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    if(m_nbMousePressed)
    {
        QPainter PixmapPainter(m_nPTargetPixmap);
        QPen pen(Qt::green);
        PixmapPainter.setPen(pen);
        //PixmapPainter.drawLine(m_nInitialX, m_nInitialY, m_nFinalX, m_nFinalY);
    }
    QPainter painter(this);
    painter.drawPixmap(0, 0, *m_nPTargetPixmap);
}

void paintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {
        QPainter PixmapPainter(m_nPTargetPixmap);
        QPen pen(Qt::black);
        PixmapPainter.setPen(pen);
        PixmapPainter.drawLine(m_nInitialX, m_nInitialY, m_nFinalX, m_nFinalY);
        // update your view
        update();
        m_nFinalX = event->pos().x();
        m_nFinalY = event->pos().y();
    }
    // update your view
    update();
}
