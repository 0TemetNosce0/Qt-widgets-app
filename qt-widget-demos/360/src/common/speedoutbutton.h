#ifndef SPEEDOUTBUTTON_H
#define SPEEDOUTBUTTON_H

#include "common.h"

#include <QWidget>

class SpeedOutButton : public QWidget
{
    Q_OBJECT

public:
    explicit SpeedOutButton(QWidget *parent = 0);
    void setIconsInfo(const QString &icon);
    void setButtonStatus(BUTTONSTATUS status);
    void setCheckdStatus(bool checked);

signals:
    void checkedChanged(bool);

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    bool           m_isChecked;
    QRect          m_checkRect;
    QPixmap        m_normalHover;
    QPixmap        m_grayHover;
    QPixmap        m_checkPix;
    QPixmap        m_uncheckPix;
    BUTTONSTATUS   m_status;
    QList<QPixmap> m_checkList;
};

#endif // SPEEDOUTBUTTON_H
