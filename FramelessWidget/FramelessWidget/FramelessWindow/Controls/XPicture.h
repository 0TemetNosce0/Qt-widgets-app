#ifndef XPICTURE_H
#define XPICTURE_H

#include <QLabel>

class XPicture : public QLabel
{
    Q_OBJECT

public:
    explicit XPicture(QPixmap pic = QPixmap(), QWidget *parent = nullptr);
    ~XPicture();
    QPixmap pixmap() const;

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void clicked(QPixmap pixmap);
    void doubleClicked();

public slots:

private:
    QPoint mo_ptPressed;
    QPixmap mo_pixmap;
};

#endif // XPICTURE_H
