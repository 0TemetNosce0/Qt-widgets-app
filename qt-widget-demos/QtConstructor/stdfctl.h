// This file is part of QtConstructor.
// Copyright (c) 2015, Diego Queiroz dos Santos, drift@linuxmail.com
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//
// * Neither the name of its contributors may be used to endorse or promote
// products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef STDFCTL_H
#define STDFCTL_H

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QDataStream>
#include <QHash>
#include <QHashIterator>
#include <QDateTime>
#include <QTimer>
#include <QFile>
#include <QMessageBox>
#include <QDirIterator>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include "model_template.h"
#include "envelope.h"

#define _D qDebug() << __LINE__ << __FUNCTION__
#define int2s(num) qs("%1").arg(num)

extern qulonglong RANDOM_NUMBER;
typedef const int & CINT;
typedef QList <QPair <QString, QString> > rl;
typedef QHash<QString, QVariant> pv;
typedef  const QHash<QString, QVariant>  & PV;
typedef QList < QHash< QString , QVariant > > lpv;
typedef QString qs;
typedef QStringList qsl;
typedef QString const &  QS;
#define DUMP(arg_hash) {QString s="    "; dumpLocal(arg_hash, s ,__FUNCTION__, __LINE__, #arg_hash); }

class stdfctl
{
public:
    explicit stdfctl();
    int SERIAL_ID;
    uint rnd();    
    QString dumpObjects(const int & id);
    void dumpLocal(const envelope & dados, QString &nbsp, QString fctl, int line, QString name);
    void dumpLocal(const QList< QHash<QString,QVariant> > & body, QString & n, QString fctl, int line, QString name);
    void dumpLocal(const QHash<QString, QVariant>& data, QString & nbsp, QString fctl, int line, QString name);
    QString envelope_id(const envelope & dados);
    void formatFctlLine(const QString & fctl, const int & line, QString & n, QString name);

    QString read_file(QString filename);
    QString base64_encode(QString string);
    QString base64_decode(QString string);

    bool confirmation(QString titulo, QString msg);
    QString escape(QString str);
    QIcon getIcon(qs str);
    QString randomString();

    void logger(const int type, const QString & txt);
    QString returnLogger(const QString & txt);

    void cmd(const qsl args);

    static const int CSS_RED = 0;
    static const int CSS_YELLOW = 1;
    static const int CSS_BLUE = 2;
    static const int CSS_GREEN = 3;
    static const int CSS_GRAY = 4;

    static const int LAYOUT_VERTICAL = 1;
    static const int LAYOUT_HORIZONTAL = 2;
    static const int LAYOUT_FORM = 3;

    // Campos
    static const int CAMPO_QLABEL = 1;
    static const int CAMPO_QLINEEDIT = 2;
    static const int CAMPO_QCOMBOBOX = 3;
    static const int CAMPO_QDATETIMEEDIT = 4;
    static const int CAMPO_QDATEEDIT = 5;
    static const int CAMPO_QCHECKBOX = 6;

    // Tipo de dados
    static const int TIPO_INT = 1;
    static const int TIPO_STRING = 2;
    static const int TIPO_DATE = 3;
    static const int TIPO_DATETIMEEDIT = 4;
    static const int TIPO_BOOL = 5;

    // Widgets
    static const int WDG_PRINCIPAL = 0;
    static const int WDG_ADICIONAR = 1;
    static const int WDG_FINANCEIRO = 2;

    static const int MENU = 1;
    static const int ACTION = 2;
    static const int COMPONENT = 3;

    // LOGGING
    static const QString INI_FILE;
    static const QString LOG_PATH;
    static const int DEBUG_MSG = 0;
    static const int CRITICAL_MSG = 1;
    static const int WARNING_MSG = 2;
    static const int INFO_MSG = 3;

    // BANCO
    static const QString SQL_PATH;
    static const QString SQL_SP_PATH;

    // ICONES
    // Retorna os icones de um qrc
    QStringList getResourceIcons(QString path);

    // Monta uma lista de icones num model
    void getModelIcons(qsl icones, ModelTemplate &model);

    static const QString resource_path;

    // CSS
    static const QString bg_red;
    static const QString bg_yellow;
    static const QString bg_blue;
    static const QString bg_green;
    static const QString bg_gray;

    // Information Time
    static const int INFO_TIME = 10000;

    // HTML
    static const QString html_style;

    static const QString table_html_begin;
    static const QString table_html_end;
    static const QString row_begin;
    static const QString row_end;
    static const QString header_cell;
    static const QString header_cell_end;
    static const QString header_cell_style;
    static const QString header_cell_style_2;
    static const QString cell_begin;
    static const QString cell_end;

    qs title;
    qs header_titles;
    qsl rows;
    qs html_final;       
    qs html_form;
};

#endif // STDFCTL_H
