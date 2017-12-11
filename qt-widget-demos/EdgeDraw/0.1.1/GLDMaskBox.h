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

class GLDMaskBox : public QWidget
{
    Q_OBJECT

public:
    static GLDMaskBox* showMaskBox(QWidget * wgtOwner);

public:
    GLDMaskBox(const QPoint &pos, float iR, float oR, QWidget *parent = nullptr);
    GLDMaskBox(QWidget* wgtOwner, QWidget *parent = nullptr);

    virtual ~GLDMaskBox();

    void immediateCloseThis();

signals:
    void customClicked();

public slots:
    void slotClose();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *);
    // virtual void mouseMoveEvent(QMouseEvent *);
    // virtual void showEvent(QShowEvent* event);

    QPoint calcPosOfOwner();

private:
    class Impl;

    QScopedPointer<Impl> d;

    QWidget*       m_pWgt;
    QWidget*       m_parent;
    IrregularForm* m_pTipBox;

private:
    static QPointer<GLDMaskBox> m_pMaskBox;
};

#endif // DONUT_H
