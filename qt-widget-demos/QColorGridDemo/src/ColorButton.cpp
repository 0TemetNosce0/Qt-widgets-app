#include "ColorButton.h"
#include "ColorGrid.h"
#include "ColorPopup.h"

#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>

ColorGrid *ColorButton::s_defaultGrid = 0;
ColorPopup *ColorButton::s_popup = 0;

ColorButton::ColorButton(QWidget *parent)
    : QToolButton(parent)
    , m_modeLeft(PM_COLORGRID)
    , m_modeRight(PM_COLORDIALOG)
    , m_grid(0)
{
    setColor(Qt::white);

//    m_menu = new QMenu(this);
//    connect(m_menu, SIGNAL(aboutToShow()), this, SLOT(doShowMenu()));
//    setMenu(m_menu);
}

ColorButton::~ColorButton()
{

}

void ColorButton::setColor(const QColor& color)
{
    m_color = color;

    QPixmap pm(rect().adjusted(3,3,-5,-5).size());
    QPainter p(&pm);
    p.setBrush(color);
    p.setPen(Qt::black);
    p.drawRect(pm.rect().adjusted(0,0,-1,-1));

    setIcon(QIcon(pm));

//    painter.setPen(Qt::black);
//    painter.setBrush(m_color);
//    painter.drawRect(rect().adjusted(4,4,-5,-5));

//    repaint();
}

void ColorButton::setCustomGrid(ColorGrid *grid)
{
    if (m_grid == grid)
    {
        return;
    }

    m_grid = grid;
    if (!m_grid)
    {
        //m_mode = PM_COLORDIALOG;
    }
    else
    {
        //m_mode = PM_COLORGRID;
        m_grid->setPickByDrag(false);
        m_grid->setClickMode(ColorGrid::CM_RELEASE);
    }
}

void ColorButton::setPickModeLeft(const PickMode& mode)
{
    if (m_modeLeft == mode)
    {
        return;
    }

    m_modeLeft = mode;
    if (m_modeLeft == PM_COLORGRID && !m_grid)
    {
        setCustomGrid(defaultGrid());
    }
}

void ColorButton::setPickModeRight(const PickMode& mode)
{
    if (m_modeRight == mode)
    {
        return;
    }

    m_modeRight = mode;
    if (m_modeRight == PM_COLORGRID && !m_grid)
    {
        setCustomGrid(defaultGrid());
    }
}

QSize ColorButton::minimumSizeHint() const
{
    return QSize(24,24);
}

QSize ColorButton::sizeHint() const
{
    return QSize(24,24);
}

void ColorButton::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    setColor(m_color);
}

//void iisColorButton::paintEvent(QPaintEvent* event)
//{
//    QPainter painter(this);
//
//    QStyleOptionButton option;
//    option.initFrom(this);
//
//    style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);
//
//    painter.setPen(Qt::black);
//    painter.setBrush(m_color);
//    painter.drawRect(rect().adjusted(4,4,-5,-5));
//
//    //QStyleOptionSpinBox osb;
//    //osb.initFrom(this);
//    //osb.rect = rect().adjusted(6,6,-6,-6);
//
//    //style()->drawPrimitive(QStyle::PE_IndicatorSpinDown, &osb, &painter, this);
//}

void ColorButton::doShowMenu()
{
    QTimer *pTimer = new QTimer(this);
    pTimer->setInterval(100);
    pTimer->setSingleShot(true);
    connect(pTimer, SIGNAL(timeout()), SLOT(hide()));
    pTimer->start();

    //m_menu->hide();
}

void ColorButton::mousePressEvent(QMouseEvent* event)
{
    QToolButton::mousePressEvent(event);

    event->accept();
    setDown(false);

    int mod;

    switch (event->button())
    {
    case Qt::LeftButton:
        mod = m_modeLeft;
        break;
    case Qt::RightButton:
        mod = m_modeRight;
        break;
    default:
        return;
    }

    switch (mod)
    {
    case PM_COLORDIALOG:
    {
        QColor c = QColorDialog::getColor(m_color, this);
        if (c.isValid())
        {
            setColor(c);
            emit colorChanged(c);
        }
    }
        break;

    case PM_COLORGRID:
    {
        s_popup = new ColorPopup(m_grid ? m_grid : defaultGrid());
        connect(s_popup, SIGNAL(picked(const QColor &)), this, SLOT(setColor(const QColor&)));
        connect(s_popup, SIGNAL(picked(const QColor &)), this, SIGNAL(colorChanged(const QColor&)));
        s_popup->show(mapToGlobal( rect().bottomLeft() ));
    }
        break;

    default:
        ;
    }
}

ColorGrid* ColorButton::defaultGrid()
{
    if (!s_defaultGrid)
    {
        s_defaultGrid = new ColorGrid();
    }

    return s_defaultGrid;
}
