#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QToolButton>

class ColorGrid;
class ColorPopup;

class ColorButton : public QToolButton
{
	Q_OBJECT

public:
    enum PickMode {PM_NONE, PM_COLORDIALOG, PM_COLORGRID};

    ColorButton(QWidget *parent);
    ~ColorButton();

	virtual QSize minimumSizeHint() const;
    virtual QSize sizeHint() const;

    inline const QColor& color() const { return m_color; }

    inline const PickMode& pickModeLeft() const { return m_modeLeft; }
	inline const PickMode& pickModeRight() const { return m_modeRight; }

    inline ColorGrid* customGrid() const { return m_grid; }


    static ColorGrid* defaultGrid();

public slots:
    void setColor(const QColor& color);
    
    void setPickModeLeft(const PickMode& mode);
	void setPickModeRight(const PickMode& mode);

    void setCustomGrid(ColorGrid *grid);

	void doShowMenu();

signals:
	void colorChanged(const QColor &color);

protected:
//    virtual void paintEvent(QPaintEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);

    QColor m_color;
    PickMode m_modeLeft;
    PickMode m_modeRight;
    ColorGrid *m_grid;
	QMenu *m_menu;

    static ColorGrid *s_defaultGrid;
    static ColorPopup *s_popup;
};

#endif // COLORBUTTON_H
