/***************************************************************************
 *   Copyright (C) 2007 by Peter Komar                                     *
 *   udldevel@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "querytable.h"

#include <QItemDelegate>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QPainter>
#include <QHeaderView>


const char* date_f = "dd.MM.yyyy";

class SimpleDelegate : public QItemDelegate
{
public:
    SimpleDelegate(QObject*pobj = 0)
        : QItemDelegate(pobj)
    {

    }

    QWidget* createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
    {
        int i = index.column();
        int row = index.row();

        if (!i)
        {
            return NULL;
        }

        if ((i>1) && (row == 2))
        {
            return NULL;
        }

        QString s1 = index.model()->data(index.sibling(index.row(),2), Qt::EditRole).toString();

        //date line
        if (((i == 2) || (i == 4)) && (row == 0))
        {
            if(i ==  4)
            {
                if(s1.isEmpty())
                {
                    return NULL;
                }
            }
            QDateTimeEdit *ed = new QDateTimeEdit(parent);
            ed->setDateTime(QDateTime::currentDateTime());
            ed->setCalendarPopup(true);
            ed->setDisplayFormat(date_f);

            return ed;
        }

        //date line
        if(((i == 2) || (i == 4)) && (row == 1))
        {
            if(i == 4)
            {
                if(s1.isEmpty())
                {
                    return NULL;
                }
            }
            QLineEdit *ed = new QLineEdit(parent);
            QDoubleValidator *valid = new QDoubleValidator(0.00,9999999999999.99,2,0);
            ed->setValidator(valid);

            return ed;
        }

        if(((i == 1) || (i == 3)) && ((row == 0) || (row == 1)))
        {
            QString s = "";

            if(i == 3)
            {
                s = index.model()->data(index.sibling(index.row(),1), Qt::EditRole).toString();
            }

            if((s == ">") || (s == ">="))
            {
                QComboBox *c_box_condition = new QComboBox(parent);
                c_box_condition->setEditable(false);
                QStringList list_types;
                list_types << "" << "<" << "<=";
                c_box_condition->addItems(list_types);

                return c_box_condition;
            }

            if((s == "<") || (s == "<="))
            {
                QComboBox *c_box_condition = new QComboBox(parent);
                c_box_condition->setEditable(false);
                QStringList list_types;
                list_types << "" << ">" << ">=";
                c_box_condition->addItems(list_types);

                return c_box_condition;
            }

            if(s == "=")
            {
                return NULL;
            }

            if(s == "")
            {
                QComboBox *c_box_condition = new QComboBox(parent);
                c_box_condition->setEditable(false);
                QStringList list_types;
                list_types << "=" << ">" << ">=" << "<" << "<=";
                c_box_condition->addItems(list_types);

                return c_box_condition;
            }
        }

        return QItemDelegate::createEditor(parent, option, index );
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        int icolumn = index.column();
        int irow = index.row();

        //date line
        if(((icolumn == 2) || (icolumn == 4)) && (irow == 0))
        {
            QDateTimeEdit *ed = static_cast<QDateTimeEdit*>(editor);
            QString s  = index.model()->data(index, Qt::EditRole).toString();
            QDateTime value = QDateTime::fromString(s,date_f);
            ed->setDateTime(value);
            return;
        }

        if(((icolumn == 1) || (icolumn == 3)) && ((irow == 0) || (irow == 1)))
        {
            QString value = index.model()->data(index, Qt::EditRole).toString();
            QComboBox *c_box_condition = static_cast<QComboBox*>(editor);
            c_box_condition->setCurrentIndex(c_box_condition->findText(value));
            return;
        }

        QItemDelegate::setEditorData(editor, index);

    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        int icolumn = index.column();
        int irow = index.row();
        //date line
        if(((icolumn == 2) || (icolumn == 4)) && (irow == 0))
        {
            QDateTimeEdit *ed = static_cast<QDateTimeEdit*>(editor);
            QString value = ed->dateTime().toString(date_f);
            model->setData(index, value, Qt::EditRole);
            return;
        }

        if(((icolumn == 1) || (icolumn == 3)) && ((irow == 0) || (irow == 1)))
        {
            QComboBox *c_box_condition = static_cast<QComboBox*>(editor);
            QString value = c_box_condition->currentText();
            model->setData(index, value, Qt::EditRole);
            return;
        }

        QItemDelegate::setModelData(editor, model, index);
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex & /*index*/ ) const
    {
        editor->setGeometry(option.rect);
    }

    bool editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* ev = static_cast<QKeyEvent*>(event);

            if(ev->key() == Qt::Key_Delete)
            {
                int icolumn = index.column();
                int irow = index.row();
                //date line
                if(((icolumn >= 2) && ((irow == 0) || (irow == 1)))
                        || ((irow == 2) && (icolumn == 1)))
                {
                    model->setData(index, "", Qt::EditRole);
                    return true;
                }
            }
        }

        return QItemDelegate::editorEvent(event, model, option, index);
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QueryTable::QueryTable(QWidget *parent)
    : QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    setItemDelegate(new SimpleDelegate(this));
}

QueryTable::~QueryTable()
{

}

void QueryTable::drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV3 opt = option;

    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    painter->save();
    painter->setPen(QPen(color));
    painter->drawLine(opt.rect.x(), opt.rect.bottom(), opt.rect.right(), opt.rect.bottom());

    int cs = 0;//draw vertical lines
    for(int i = 0; i<(header()->count()); i++)
    {
        cs += columnWidth(i);
        painter->drawLine(opt.rect.x()+cs,opt.rect.top(), opt.rect.x()+cs, opt.rect.bottom());
    }

    painter->restore();
    QTreeView::drawRow(painter, opt, index);
}

void QueryTable::setSourceModel(QAbstractItemModel *model)
{
    setModel(model);
}
