#ifndef CUSTOMTOOLBUTTON_H
#define CUSTOMTOOLBUTTON_H

#include <QToolButton>

class CustomToolButton : public QToolButton
{
    Q_OBJECT
public:
    enum TextDirection{None, Down};
    CustomToolButton(QWidget *parent, int iconsize = 10, int btnWidth = 20, int btnHeight = 20, int textsize = 10);
    virtual ~CustomToolButton();

protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    bool isHover();
    void setTextDirection(TextDirection textDirection);
    void setMouseHoverPixmap(QPixmap mouseHoverPixmap);
    void setMousePressPixmap(QPixmap mousePressPixmap);
    void setNormalPixmap(QPixmap normalPixmap);

private:
    bool _bHover;
    bool _bPress;

//    int m_iconsize;
//    int m_btnWidth;
//    int m_btnHeight;
//    int m_textsize;

    QRect _iconrect;
    QRect _textrect;

    TextDirection _textDirection;

    QPixmap _mouseHoverPixmap;
    QPixmap _mousePressPixmap;
    QPixmap _normalPixmap;
};

#endif // CUSTOMTOOLBUTTON_H
