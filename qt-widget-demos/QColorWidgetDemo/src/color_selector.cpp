/**

@author Mattia Basaglia

@section License

    Copyright (C) 2013-2014 Mattia Basaglia

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Color Widgets.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "color_selector.hpp"
#include "color_dialog.hpp"
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>

class ColorSelector::Private
{
public:
    Update_Mode update_mode;
    ColorDialog *dialog;
    QColor old_color;

    Private(QWidget *widget) : dialog(new ColorDialog(widget))
    {}
};

ColorSelector::ColorSelector(QWidget *parent)
    : ColorPreview(parent)
    , p(new Private(this))
{
    setUpdateMode(Continuous);
    p->old_color = color();

    connect(this,SIGNAL(clicked()),this,SLOT(showDialog()));
    connect(this,SIGNAL(colorChanged(QColor)),this,SLOT(updateOldColor(QColor)));
    connect(p->dialog,SIGNAL(rejected()),this,SLOT(rejectDialog()));
    connect(p->dialog,SIGNAL(colorSelected(QColor)), this, SLOT(acceptDialog()));

    setAcceptDrops(true);
}

ColorSelector::~ColorSelector()
{
    delete p;
}

ColorSelector::Update_Mode ColorSelector::updateMode() const
{
    return p->update_mode;
}

void ColorSelector::setUpdateMode(Update_Mode m)
{
    p->update_mode = m;
}

Qt::WindowModality ColorSelector::dialogModality() const
{
    return p->dialog->windowModality();
}

void ColorSelector::setDialogModality(Qt::WindowModality m)
{
    p->dialog->setWindowModality(m);
}

void ColorSelector::showDialog()
{
    p->old_color = color();
    p->dialog->setColor(color());
    connectDialog();
    p->dialog->show();
}

void ColorSelector::connectDialog()
{
    if (p->update_mode == Continuous)
    {
        connect(p->dialog, SIGNAL(colorChanged(QColor)), this, SLOT(setColor(QColor)), Qt::UniqueConnection);
    }
    else
    {
        disconnectDialog();
    }
}

void ColorSelector::disconnectDialog()
{
    disconnect(p->dialog, SIGNAL(colorChanged(QColor)), this, SLOT(setColor(QColor)));
}

void ColorSelector::acceptDialog()
{
    setColor(p->dialog->color());
    p->old_color = color();
}

void ColorSelector::rejectDialog()
{
    setColor(p->old_color);
}

void ColorSelector::updateOldColor(const QColor &c)
{
    if (!p->dialog->isVisible())
    {
        p->old_color = c;
    }
}

void ColorSelector::dragEnterEvent(QDragEnterEvent *event)
{
    if ( event->mimeData()->hasColor() ||
         ( event->mimeData()->hasText() && QColor(event->mimeData()->text()).isValid() ) )
    {
        event->acceptProposedAction();
    }
}


void ColorSelector::dropEvent(QDropEvent *event)
{
    if ( event->mimeData()->hasColor() )
    {
        setColor(event->mimeData()->colorData().value<QColor>());
        event->accept();
    }
    else if ( event->mimeData()->hasText() )
    {
        QColor col(event->mimeData()->text());
        if ( col.isValid() )
        {
            setColor(col);
            event->accept();
        }
    }
}
