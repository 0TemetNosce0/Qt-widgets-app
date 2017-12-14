#include "GTableWidget.h"

#include <QEvent>
#include <QHeaderView>
#include <QApplication>
#include <QStylePainter>
#include <QAbstractButton>

TableWidget::TableWidget(int rows, int cols, QWidget *parent)
    : QTableWidget(rows, cols, parent)
{
    QAbstractButton* btn = findChild<QAbstractButton*>();

    if (btn)
    {
        btn->setText(QStringLiteral("½ÇÂä°´Å¥"));
        btn->installEventFilter(this);

        // adjust the width of the vertical header to match the preferred corner button width

        // (unfortunately QAbstractButton doesn't implement any size hinting functionality)

        QStyleOptionHeader opt;
        opt.text = btn->text();
        QSize s = (btn->style()->sizeFromContents(QStyle::CT_HeaderSection, &opt, QSize(), btn).
                   expandedTo(QApplication::globalStrut()));

        if (s.isValid())
        {
            verticalHeader()->setMinimumWidth(s.width());
        }
    }
}


bool TableWidget::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::Paint)
    {
        QAbstractButton* btn = qobject_cast<QAbstractButton*>(o);

        if (btn)
        {
            // paint by hand (borrowed from QTableCornerButton)

            QStyleOptionHeader opt;
            opt.init(btn);
            QStyle::State state = QStyle::State_None;

            if (btn->isEnabled())
            {
                state |= QStyle::State_Enabled;
            }

            if (btn->isActiveWindow())
            {
                state |= QStyle::State_Active;
            }

            if (btn->isDown())
            {
                state |= QStyle::State_Sunken;
            }

            opt.state = state;
            opt.rect = btn->rect();
            opt.text = btn->text(); // this line is the only difference to QTableCornerButton

            opt.position = QStyleOptionHeader::OnlyOneSection;
            QStylePainter painter(btn);
            painter.drawControl(QStyle::CE_Header, opt);
            return true; // eat event
        }
    }

    return false;
}
