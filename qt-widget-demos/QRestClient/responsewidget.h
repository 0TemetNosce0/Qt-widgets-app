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

#ifndef RESPONSEWIDGET_H
#define RESPONSEWIDGET_H

#include <QStackedWidget>

class QTextEdit;
class QJsonView;
class QCsvView;

class ResponseWidget : public QStackedWidget
{
    Q_OBJECT

public:
    enum type
    {
      TYPE_TEXT = 0,
      TYPE_JSON,
      TYPE_CSV,
    };

    explicit ResponseWidget(QWidget *parent = 0);

    void setText(const QString& text);
    void append(const QString& text);
    ResponseWidget::type render(type typeResponse);

    void clear();
    QString toText();

private:
    QTextEdit *m_textView;
    QJsonView *m_jsonView;
    QCsvView  *m_csvView;

    QString m_text;
};

#endif // RESPONSEWIDGET_H
