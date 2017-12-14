#ifndef IISCOLORPOPUP_H
#define IISCOLORPOPUP_H

#include <QFrame>
#include <QVBoxLayout>

class ColorGrid;

class ColorPopup : public QFrame
{
	Q_OBJECT

public:
    ColorPopup(ColorGrid *grid);
    virtual ~ColorPopup();

public slots:
    void show(const QPoint &point);

signals:
    void picked(const QColor &color);

private:
    ColorGrid *m_grid;
    QVBoxLayout *m_vbl;
    QWidget *m_oldParent;
};

#endif // IISCOLORPOPUP_H
