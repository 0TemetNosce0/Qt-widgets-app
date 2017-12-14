#ifndef IISCOLORGRID_H
#define IISCOLORGRID_H

#include <QWidget>

typedef QList<QColor> ColorList;


class ColorGrid : public QWidget
{
    Q_OBJECT

public:
    enum ClickMode
    {
        CM_PRESS,
        CM_RELEASE
    };

    ColorGrid(QWidget *parent = 0);
    ~ColorGrid();

	virtual QSize minimumSizeHint() const;
    virtual QSize sizeHint() const;

	inline int cellSize() const { return m_cellSize; }
	void setCellSize(int size);

	inline int widthInCells() const { return m_widthInCells; }
	void setWidthInCells(int width);

    int heightInCells() const;

    inline const QColor &lastHighlighted() const { return m_hlColor; }
    inline const QColor &lastPicked() const { return m_selColor; }

    inline bool pickByDrag() const { return m_pickDrag; }
    inline void setPickByDrag(bool set) { m_pickDrag = set; }

    inline ClickMode clickMode() const { return m_clickMode; }
    inline void setClickMode(ClickMode mode) { m_clickMode = mode; }

    inline ColorList* scheme() const { return m_colors; }
    void setScheme(ColorList *list);


    static ColorList* defaultColors();
    static ColorList* defaultColors2();
    static ColorList* baseColors();
    static ColorList* namedColors();

signals:
    void highlighted(const QColor &color);
    void picked(const QColor &color);
    void accepted();
    void rejected();

protected slots:


protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual bool event(QEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void leaveEvent(QEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);

    void redraw();

    int index() const;

	int m_cellSize;
	int m_widthInCells;
    int m_row, m_col, m_idx;
    QPixmap m_pix;
    bool m_pickDrag;
    ClickMode m_clickMode;
    QPoint m_pos;

    QColor m_hlColor;
    QColor m_selColor;

    ColorList *m_colors;

    static ColorList s_defaultColors;
    static ColorList s_defaultColors2;
    static ColorList s_baseColors;
    static ColorList s_namedColors;
};

#endif // IISCOLORGRID_H
