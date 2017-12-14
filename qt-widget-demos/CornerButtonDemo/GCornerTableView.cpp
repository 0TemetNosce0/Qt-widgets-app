#include "gcornertableview.h"

#include <QHeaderView>
#include <QFontMetrics>
#include <private/qtableview_p.h>

GCornerTableView::GCornerTableView(QWidget *parent)
    : QTableView(parent)
{
    Q_D(QTableView);

    disconnect(d->cornerWidget, SIGNAL(clicked()), this, SLOT(selectAll()));
    delete d->cornerWidget;
    GTableCornerButton *btn = new GTableCornerButton(this);
    btn->setAlignment(Qt::AlignCenter);
    d->cornerWidget = btn;
    d->cornerWidget->setFocusPolicy(Qt::NoFocus);
    d->cornerWidget->setFont(d->verticalHeader->font());//cornerbutton used for verticalheader
//    QObject::connect(d->cornerWidget, SIGNAL(clicked()), this, SLOT(selectAll()));
}

void GCornerTableView::setCornerButtonText(const QString &text)
{
    Q_D(QTableView);

    m_cornerButtonText = text;
    GTableCornerButton *btn = static_cast<GTableCornerButton *>(d->cornerWidget);
    Q_ASSERT(btn);
    btn->setText(m_cornerButtonText);

    QFontMetrics metrics(btn->font());
    int width = metrics.width(m_cornerButtonText);
    int height = metrics.height();
    d->verticalHeader->setMinimumWidth(width + metrics.maxWidth());
    d->verticalHeader->setMinimumHeight(height + metrics.maxWidth());
    d->verticalHeader->setDefaultAlignment(Qt::AlignCenter);
}

void GCornerTableView::setCornerTextAlignment(Qt::Alignment align)
{
    Q_D(QTableView);

    GTableCornerButton *btn = static_cast<GTableCornerButton *>(d->cornerWidget);
    Q_ASSERT(btn);
    btn->setAlignment(align);
    btn->repaint();
}
