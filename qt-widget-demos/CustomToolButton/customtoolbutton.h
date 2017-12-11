#ifndef CUSTOMTOOLBUTTON_H
#define CUSTOMTOOLBUTTON_H

#include <QToolButton>

class CustomToolButton : public QToolButton
{
    Q_OBJECT
public:
    enum TextDirection{None, Down, Left, Right};
    CustomToolButton(QWidget *parent, int iconsize, int btnWidth, int btnHeight, int textsize);
    virtual ~CustomToolButton();

protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

public:
    bool isHover();
    void setTextDirection(TextDirection textDirection);
    void setMouseHoverPixmap(QPixmap mouseHoverPixmap);
    void setMousePressPixmap(QPixmap mousePressPixmap);
    void setNormalPixmap(QPixmap normalPixmap);

private:
    bool m_bHover;
    bool m_bPress;

    int m_iconsize;
    int m_btnWidth;
    int m_btnHeight;
    int m_textsize;

    QRect m_iconrect;
    QRect m_textrect;

    TextDirection m_textDirection;

    QPixmap m_mouseHoverPixmap;
    QPixmap m_mousePressPixmap;
    QPixmap m_normalPixmap;
};

#endif // CUSTOMTOOLBUTTON_H
