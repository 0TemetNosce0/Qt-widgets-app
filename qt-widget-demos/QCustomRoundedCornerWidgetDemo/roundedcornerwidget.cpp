#include "roundedcornerwidget.h"

#include <QPainter>
#include <QBrush>
#include <QPushButton>

RoundedCornerWidget::RoundedCornerWidget(QWidget *parent)
    : QWidget(parent)
{
    this->init(parent);
}

RoundedCornerWidget::RoundedCornerWidget(const QString& text, QWidget *parent)
    : QWidget(parent)
{
    this->init(parent);
    m_text = text;
}

RoundedCornerWidget::~RoundedCornerWidget()
{

}

void RoundedCornerWidget::paintEvent(QPaintEvent* event)
{
    if(m_bShowWidget)
    {
        QPainter painter(this);

        if(m_bShowFrame)
        {
            painter.setPen(Qt::SolidLine);
        }
        else
        {
            painter.setPen(Qt::DotLine);
        }

        painter.setBrush(QBrush(m_color));
        int height = m_size.height();
        int width = m_size.width();
        float ratio = (float)height/width;
        painter.drawRoundRect(0, 0, width - 1, height - 1, (int)(ratio * m_radius), m_radius);

        QFontMetrics fm(this->font());
        int textHeight = fm.height();

        if(!m_text.isEmpty())
        {
            int textWidth = fm.width(m_text);
            painter.drawText((m_size.width() - textWidth ) / 2,(m_size.height() + textHeight ) / 2, m_text);
        }

        if(!m_cornerText.isEmpty())
        {
            painter.drawText(m_size.width() - fm.width(m_cornerText), textHeight, m_cornerText);
        }
    }
    QWidget::paintEvent(event);
}

QSizePolicy	RoundedCornerWidget::sizePolicy() const
{
    QSizePolicy  sizePolicy;
    sizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    sizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    return sizePolicy;
}

QSize RoundedCornerWidget::minimumSizeHint() const
{
    return m_size;
}

QSize RoundedCornerWidget::getSize()
{
    return m_size;
}

void RoundedCornerWidget::setSize(int width,int height)
{
    m_size.setWidth(width);
    m_size.setHeight(height);
    this->resize(m_size);
}

void RoundedCornerWidget::setSize(const QSize& size)
{
    m_size.setWidth(size.width());
    m_size.setHeight(size.height());
    this->resize(size);
}

void RoundedCornerWidget::setRadius(int radius)
{
    m_radius = radius;
}

void RoundedCornerWidget::setShowWidget(bool bShow)
{
    m_bShowWidget = bShow;
    this->show();
}

bool RoundedCornerWidget::isShowWidget()
{
    return m_bShowWidget;
}

QColor RoundedCornerWidget::getBackGroundColor()
{
    return m_color;
}

void RoundedCornerWidget::setBackGroundColor(const QColor& color)
{
    m_color = color;
}

void RoundedCornerWidget::setText(const QString& text)
{
    m_text = text;
}

QString RoundedCornerWidget::getText()
{
    return m_text;
}

void RoundedCornerWidget::setShowFrame(bool bShow)
{
    m_bShowFrame = bShow;
}

bool RoundedCornerWidget::isShowFrame()
{
    return m_bShowFrame;
}

void RoundedCornerWidget::setCornerText(const QString& text)
{
    m_cornerText = text;
}

QString RoundedCornerWidget::getCornerText()
{
    return m_cornerText;
}

void RoundedCornerWidget::setFontSize(int fontSize)
{
    QFont font;
    font.setPixelSize(fontSize);
    this->setFont(font);
}

int RoundedCornerWidget::getFontSize()
{
    return this->font().pixelSize();
}

void RoundedCornerWidget::init(QWidget* parent)
{
    m_size = QSize(25,25);
    m_radius = 25;
    m_color = Qt::gray;
    m_bShowWidget = false;
    m_text = "";
    m_bShowFrame = true;
    m_cornerText = "";
}
