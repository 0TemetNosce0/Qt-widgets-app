#include "pricebox.h"

#include <QPainter>
#include <QBrush>
#include <QPushButton>

PriceBox::PriceBox(QWidget *parent)
    : QWidget(parent)
{
    this->init(parent);
}

PriceBox::PriceBox(const QString& text, QWidget *parent)
    : QWidget(parent)
{
    this->init(parent);
    m_Text = text;
}

PriceBox::~PriceBox()
{

}

void PriceBox::paintEvent(QPaintEvent* event)
{
    if(m_ShowWidget)
    {
        QPainter painter(this);
        if(m_ShowFrame)
            painter.setPen(Qt::SolidLine);
        else
            painter.setPen(Qt::DotLine);

        painter.setBrush(QBrush(m_Color));
        int height = m_Size.height();
        int width = m_Size.width();
        float ratio = (float)height/width;
        painter.drawRoundRect(0,0,width-1,height-1,(int)(ratio*m_Radius),m_Radius);

        QFontMetrics fm(this->font());
        int textHeight = fm.height();
        if(!m_Text.isEmpty())
        {
            int textWidth = fm.width(m_Text);
            painter.drawText((m_Size.width() - textWidth ) / 2,(m_Size.height() + textHeight ) / 2,m_Text);
        }
        if(!m_CornerText.isEmpty())
        {
            painter.drawText(m_Size.width()-fm.width(m_CornerText),textHeight,m_CornerText);
        }
    }
    QWidget::paintEvent(event);
}

QSizePolicy	PriceBox::sizePolicy() const
{
    QSizePolicy  sizePolicy;
    sizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    sizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
    return sizePolicy;
}

QSize PriceBox::minimumSizeHint() const
{
    return m_Size;
}

QSize PriceBox::getSize()
{
    return m_Size;
}

void PriceBox::setSize(int width,int height)
{
    m_Size.setWidth(width);
    m_Size.setHeight(height);
    this->resize(m_Size);
}

void PriceBox::setSize(const QSize& size)
{
    m_Size.setWidth(size.width());
    m_Size.setHeight(size.height());
    this->resize(size);
}

void PriceBox::setRadius(int radius)
{
    m_Radius = radius;
}

void PriceBox::setShowWidget(bool bShow)
{
    m_ShowWidget = bShow;
    this->show();
}

bool PriceBox::isShowWidget()
{
    return m_ShowWidget;
}

QColor PriceBox::getBackGroundColor()
{
    return m_Color;
}

void PriceBox::setBackGroundColor(const QColor& color)
{
    m_Color = color;
}

void PriceBox::setText(const QString& text)
{
    m_Text = text;
}

QString PriceBox::getText()
{
    return m_Text;
}

void PriceBox::setShowFrame(bool bShow)
{
    m_ShowFrame = bShow;
}

bool PriceBox::isShowFrame()
{
    return m_ShowFrame;
}

void PriceBox::setCornerText(const QString& text)
{
    m_CornerText = text;
}

QString PriceBox::getCornerText()
{
    return m_CornerText;
}

void PriceBox::setFontSize(int fontSize)
{
    QFont font;
    font.setPixelSize(fontSize);
    this->setFont(font);
}

int PriceBox::getFontSize()
{
    return this->font().pixelSize();
}

void PriceBox::init(QWidget* parent)
{
    m_Size = QSize(50,25);
    m_Radius = 25;
    m_Color = Qt::gray;
    m_ShowWidget = false;
    m_Text = "";
    m_ShowFrame = true;
    m_CornerText = "";
}
