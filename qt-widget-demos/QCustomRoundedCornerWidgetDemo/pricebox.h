#ifndef PRICEBOX_H
#define PRICEBOX_H

#include <QSize>
#include <QWidget>

class PriceBox : public QWidget
{
    Q_OBJECT

public:
    PriceBox(QWidget *parent=0);
    PriceBox(const QString& text,QWidget *parent=0);
    ~PriceBox();

protected:
    void paintEvent(QPaintEvent* event);
    QSizePolicy	sizePolicy() const;
    QSize	minimumSizeHint() const;

public:
    QSize getSize();
    void  setSize(int width,int height);
    void  setSize(const QSize& size);
    void  setRadius(int radius);
    void  setShowWidget(bool bShow);
    bool  isShowWidget();
    QColor getBackGroundColor();
    void  setBackGroundColor(const QColor& color);
    void  setText(const QString& text);
    QString getText();
    void  setShowFrame(bool bShow);
    bool  isShowFrame();
    void  setCornerText(const QString& text);
    QString getCornerText();
    void  setFontSize(int fontSize);
    int   getFontSize();

private:
    void init(QWidget* parent);

private:
    int		m_Radius;	//Բ�ǰ뾶;
    QSize	m_Size;
    QColor  m_Color;
    bool    m_ShowWidget;
    QString m_Text;
    bool    m_ShowFrame;
    QString m_CornerText;
};


#endif // PRICEBOX_H
