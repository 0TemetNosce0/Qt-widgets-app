/***************************************************************************
 *   Copyright (C) 2014 by Peter Komar                                     *
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

#include "responsewidget.h"
#include "qjsonview.h"
#include "qcsvview.h"

#include <QTextEdit>
#include <QDebug>

ResponseWidget::ResponseWidget(QWidget *parent)
    : QStackedWidget(parent)
{
    m_textView = new QTextEdit;
    m_textView->setAcceptRichText(false);
    m_textView->setReadOnly(true);
    addWidget(m_textView);

    m_jsonView = new QJsonView;
    addWidget(m_jsonView);

    m_csvView = new QCsvView;
    addWidget(m_csvView);

    setCurrentIndex(0);

    m_text = "";
}

void ResponseWidget::setText(const QString& text)
{   
    m_text = text;
}

void ResponseWidget::append(const QString& text)
{        
    m_text += text;
}

ResponseWidget::type ResponseWidget::render(type typeResponse)
{
    type index = TYPE_TEXT;
    QString body = m_text;
    try{
        switch(typeResponse)
        {

            case TYPE_JSON : body.replace(">", "&gt;").replace("<", "&lt;");
                             m_jsonView->setJson(body);
                             index = TYPE_JSON;
                             break;

            case TYPE_TEXT: index = TYPE_TEXT;
                            m_textView->setText(body);
                            break;
            case TYPE_CSV:  index = TYPE_CSV;
                            m_csvView->setText(body);
                            break;

        }

    }
    catch(...)
    {
        index = TYPE_TEXT;
        m_textView->setText(body);
    }

    setCurrentIndex(index);

    return index;
}

QString ResponseWidget::toText()
{
    return m_text;
}

void ResponseWidget::clear()
{
    m_textView->clear();
    m_jsonView->clear();
    m_text.clear();
}

