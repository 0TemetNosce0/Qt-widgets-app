#ifndef PRICEBOX_H
#define PRICEBOX_H

#include <QSize>
#include <QWidget>

class RoundedCornerWidget : public QWidget
{
    Q_OBJECT

public:
    RoundedCornerWidget(QWidget *parent=0);
    RoundedCornerWidget(const QString& text, QWidget *parent=0);
    ~RoundedCornerWidget();

protected:
    void paintEvent(QPaintEvent* event);
    QSizePolicy	sizePolicy() const;
    QSize minimumSizeHint() const;

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
    int		m_radius;	//Բ�ǰ뾶;
    QSize	m_size;
    QColor  m_color;
    bool    m_bShowWidget;
    QString m_text;
    bool    m_bShowFrame;
    QString m_cornerText;
};


#endif // PRICEBOX_H
