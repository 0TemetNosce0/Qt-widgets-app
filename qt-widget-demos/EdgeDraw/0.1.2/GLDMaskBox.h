#ifndef DONUT_H
#define DONUT_H

#include "irregularform.h"

#include <QLabel>
#include <QFrame>
#include <QPointer>
#include <QScopedPointer>

class QRegion;

static QWidget* topParentWidget(QWidget* pWgt)
{
    if (!pWgt)
    {
        return nullptr;
    }

    QWidget* widget = nullptr;

    for (widget = pWgt; widget != nullptr; widget = widget->parentWidget())
    {
        if (widget->isWindow())
        {
            break;
        }
    }

    return widget;
}


class Impl
{
public:
    explicit Impl(const QPoint &pos, float iR, float oR);
    explicit Impl(QWidget* pWidget, QWidget* parent);

    ~Impl();

public:
    void createMaskImage(QImage&);

    void drawMask(QPainter& painter);

    void drawDonut(QPainter&);
    void drawDonut(QPainter&, QWidget* parent);

public:
    float m_innerRadius;
    float m_outerRadius;

    int m_nClippedWidgetWidth;
    int m_nClippedWidgetHeight;

    QImage m_maskImage;

    QWidget* m_parent;
    QWidget* m_pClippedWgt;

    QPoint m_pos;
    QPoint m_ptGlobalOwnerCenter;

    QSharedPointer<QRegion> m_region;
    QSharedPointer<QRegion> m_innerRegion;

private:
    Q_DISABLE_COPY(Impl)
};

class GLDMaskBox : public QWidget
{
    Q_OBJECT

public:
    static GLDMaskBox* showMaskBox(QWidget * wgtOwner);

private:
    GLDMaskBox(const QPoint &pos, float iR, float oR, QWidget *parent = nullptr);
    GLDMaskBox(QWidget* wgtOwner, QWidget *parent = nullptr);
    virtual ~GLDMaskBox();

public:
    void immediateCloseThis();
    QPoint calcPosOfOwner();

Q_SIGNALS:
    void customClicked();

public slots:
    void slotClose();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

private:
    QScopedPointer<Impl> d;

    QWidget*       m_pWgt;
    QWidget*       m_parent;
    IrregularForm* m_pTipBox;

private:
    static QPointer<GLDMaskBox> m_pMaskBox;
};

#endif // DONUT_H
