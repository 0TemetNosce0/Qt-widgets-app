#include "ColorGrid.h"

#include <QPainter>
#include <QToolTip>
#include <QMouseEvent>

ColorList ColorGrid::s_defaultColors ;
ColorList ColorGrid::s_defaultColors2;
ColorList ColorGrid::s_baseColors;
ColorList ColorGrid::s_namedColors;

ColorGrid::ColorGrid(QWidget *parent)
    : QWidget(parent)
    , m_cellSize(12)
    , m_widthInCells(32)
    , m_idx(-1)
    , m_row(-1)
    , m_col(-1)
    , m_pickDrag(true)
    , m_clickMode(CM_PRESS)
    , m_colors(0)
{
    setScheme(defaultColors());
    setFixedSize(minimumSizeHint());
    setMouseTracking(true);
}

ColorGrid::~ColorGrid()
{

}

QSize ColorGrid::minimumSizeHint() const
{
    return QSize((m_cellSize+1) * m_widthInCells + 4, (m_cellSize+1) * heightInCells() + 4);
}

QSize ColorGrid::sizeHint() const
{
    return minimumSizeHint();
}

int ColorGrid::heightInCells() const
{
    if (!m_colors)
    {
        return 0;
    }
    int d = m_colors->size() / m_widthInCells;
    if (m_colors->size() % m_widthInCells)
    {
        d++;
    }
    return d;
}

void ColorGrid::setCellSize(int size)
{
    if (size < 8)
    {
        size = 8;
    }
    m_cellSize = size;
    setFixedSize(minimumSizeHint());
    redraw();
}

void ColorGrid::setWidthInCells(int width)
{
    if (width < 1)
    {
        width = 1;
    }
    m_widthInCells = width;
    setFixedSize(minimumSizeHint());
    redraw();
}

void ColorGrid::setScheme(ColorList *list)
{
    if (!list)
    {
        return;
    }
    m_colors = list;
    m_idx = -1;
    redraw();
    update();
}

void ColorGrid::redraw()
{
    int rows = heightInCells();

    int c = m_cellSize+1;	// frame
    int h = rows * c;
    int w = m_widthInCells * c;

    m_pix = QPixmap(minimumSizeHint());
    QPainter p(&m_pix);

    p.setBrush(palette().base());
    p.setPen(palette().shadow().color());
    p.drawRect(0,0,w+2,h+2);

    int x = 2, y = 2;
    int idx = 0;
    for (int j = 0; j < rows; j++, y+=c)
    {
        x = 2;
        for (int i = 0; i < m_widthInCells; i++, x+=c)
        {
            if (idx == m_colors->size())
            {
                return;
            }
            p.fillRect(QRect(x,y,m_cellSize,m_cellSize), m_colors->at(idx++));
        }
    }
    
    repaint();
}

int ColorGrid::index() const
{
    int i = m_widthInCells * m_row + m_col;
    if (m_col >= m_widthInCells || i < 0 || i >= m_colors->size())
    {
        i = -1;
    }
    return i;
}

void ColorGrid::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.drawPixmap(0, 0, m_pix);

    m_hlColor = QColor();

    if (m_idx >= 0)
    {
        m_hlColor = m_colors->at(m_idx);

        int c = m_cellSize + 1;
        int x = m_col * c;
        int y = m_row * c;;

        p.setPen(palette().foreground().color());
        p.drawRect(QRect(x + 1, y + 1, c, c));
    }
}

void ColorGrid::mouseMoveEvent(QMouseEvent* event)
{
    //if (!hasFocus()) setFocus();

    QWidget::mouseMoveEvent(event);

    m_pos = event->pos();

    int c = m_cellSize + 1;
    m_row = m_pos.y() / c;
    m_col = m_pos.x() / c;

    int i = index();
    if (i != m_idx)
    {
        m_idx = i;
        repaint();

        QToolTip::hideText();

        if (m_idx != -1)
        {
            emit highlighted(m_hlColor);

            QToolTip::showText(event->globalPos(), m_hlColor.name(), this);

            if (m_pickDrag && event->buttons() & Qt::LeftButton)
            {
                m_selColor = m_hlColor;
                emit picked(m_selColor);
                //emit accepted();
            }
        }
    }

}

void ColorGrid::mousePressEvent(QMouseEvent* event)
{
    if (!hasFocus())
    {
        setFocus();
    }

    if (m_clickMode == CM_PRESS && event->button() == Qt::LeftButton && m_hlColor.isValid())
    {
        m_selColor = m_hlColor;
        emit picked(m_selColor);
        emit accepted();
    }
}

void ColorGrid::mouseReleaseEvent ( QMouseEvent * event )
{
    if (!hasFocus())
    {
        setFocus();
    }

    if (m_clickMode == CM_RELEASE && event->button() == Qt::LeftButton && m_hlColor.isValid())
    {
        m_selColor = m_hlColor;
        emit picked(m_selColor);
        emit accepted();
    }
}

void ColorGrid::leaveEvent(QEvent* event)
{
    Q_UNUSED(event);
    QToolTip::hideText();

    if (m_idx != -1)
    {
        m_idx = -1;
        repaint();
    }
}

bool ColorGrid::event(QEvent* event)
{
    //if (event->type() == QEvent::ToolTip) {
    //    QToolTip::showText(m_pos, "zzz", this);

    //    event->accept();
    //    return true;
    //}

    return QWidget::event(event);
}

void ColorGrid::keyPressEvent(QKeyEvent* event)
{
    QToolTip::hideText();

    switch (event->key())
    {

    case Qt::Key_Right:
        if (m_idx == -1)
        {
            m_row = m_col = 0;
            m_idx = 0;
        }
        else
        {
            if (++m_col == m_widthInCells)
            {
                m_col = 0; m_row++;
            }
            m_idx = index();

            if (m_idx == -1)
            {
                m_row = m_col = 0;
                m_idx = 0;
            }
        }
        repaint();
        m_hlColor = m_colors->at(m_idx);
        emit highlighted(m_hlColor);
        event->accept();
        return;

    case Qt::Key_Left:
        if (m_idx == -1)
        {
            m_row = m_col = 0;
            m_idx = 0;
        }
        else
        {
            if (--m_col < 0)
            {
                m_col = m_widthInCells-1;
                m_row--;
            }
            m_idx = index();

            if (m_idx == -1)
            {
                m_row = heightInCells()-1;
                m_idx = m_colors->size()-1;
                m_col = m_idx % m_widthInCells;
            }
        }
        repaint();
        m_hlColor = m_colors->at(m_idx);
        emit highlighted(m_hlColor);
        event->accept();
        return;

    case Qt::Key_Up:
        if (m_idx == -1)
        {
            m_row = m_col = 0;
            m_idx = 0;
        }
        else
        {
            int h = heightInCells()-1;
            if (--m_row < 0)
            {
                m_row = h;
                if (--m_col < 0)
                {
                    m_row = h;
                    m_idx = m_colors->size()-1;
                    m_col = m_idx % m_widthInCells;
                }
            }
            m_idx = index();
            if (m_idx == -1 && m_row == h)
            {
                m_row--;
                m_idx = index();
            }
            if (m_idx == -1)
            {
                m_row = h;
                m_idx = m_colors->size()-1;
                m_col = m_idx % m_widthInCells;
            }
        }
        repaint();
        m_hlColor = m_colors->at(m_idx);
        emit highlighted(m_hlColor);
        event->accept();
        return;

    case Qt::Key_Down:
        if (m_idx == -1)
        {
            m_row = m_col = 0;
            m_idx = 0;
        }
        else
        {
            int h = heightInCells()-1;
            if (++m_row > h)
            {
                m_row = 0; m_col++;
            }
            m_idx = index();
            if (m_idx == -1 && m_row == h)
            {
                m_row = 0; m_col++;
                m_idx = index();
            }
            if (m_idx == -1)
            {
                m_row = m_col = 0;
                m_idx = 0;
            }
        }
        repaint();
        m_hlColor = m_colors->at(m_idx);
        emit highlighted(m_hlColor);
        event->accept();
        return;

    case Qt::Key_Return:
        if (m_idx != -1)
        {
            emit picked(m_selColor = m_hlColor);
            emit accepted();
        }
        event->accept();
        return;

    case Qt::Key_Escape:
        emit rejected();
        event->accept();
        return;

    default:
        event->ignore();
    }

    return QWidget::keyPressEvent(event);
}

ColorList* ColorGrid::defaultColors()
{
    const int step = 32;

    if (!s_defaultColors.isEmpty())
    {
        return &s_defaultColors;
    }

    for (int b = 0; b <= 256; b += 16)
    {
        if (b == 256)
        {
            b = 255;
        }
        s_defaultColors.append(QColor(b, b, b));
    }

    for (int r = 0; r <= 256; r += step)
    {
        if (r == 256)
        {
            r = 255;
        }
        for (int g = 0; g <= 256; g += step)
        {
            if (g == 256)
            {
                g = 255;
            }
            for (int b = 0; b <= 256; b += step)
            {
                if (b == 256)
                {
                    b = 255;
                }
                s_defaultColors.append(QColor(r,g,b));
            }
        }
    }

    return &s_defaultColors;
}

ColorList* ColorGrid::defaultColors2()
{
    const int step = 64;

    if (!s_defaultColors2.isEmpty())
    {
        return &s_defaultColors2;
    }

    for (int b = 0; b <= 256; b += 16)
    {
        if (b == 256)
        {
            b = 255;
        }
        s_defaultColors2.append(QColor(b,b,b));
    }

    for (int r = 0; r <= 256; r += step)
    {
        if (r == 256)
        {
            r = 255;
        }
        for (int g = 0; g <= 256; g += step)
        {
            if (g == 256)
            {
                g = 255;
            }
            for (int b = 0; b <= 256; b += step)
            {
                if (b == 256)
                {
                    b = 255;
                }
                s_defaultColors2.append(QColor(r,g,b));
            }
        }
    }

    return &s_defaultColors2;
}

ColorList* ColorGrid::baseColors()
{
    if (!s_baseColors.isEmpty())
    {
        return &s_baseColors;
    }

    for (int i = Qt::black; i <= Qt::darkYellow; i++)
    {
        s_baseColors.append((Qt::GlobalColor)i);
    }

    return &s_baseColors;
}

ColorList* ColorGrid::namedColors()
{
    if (!s_namedColors.isEmpty())
    {
        return &s_namedColors;
    }

    QStringList names = QColor::colorNames();
    for (int i = 0; i < names.size(); i++)
    {
        s_namedColors.append(QColor(names.at(i)));
    }

    return &s_namedColors;
}


