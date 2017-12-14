// Copyright (c) 2015, Diego Queiroz dos Santos.
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

#include "stdfctl.h"
#include <QProcess>

const QString stdfctl::INI_FILE = "qtconstructor.ini";
const QString stdfctl::LOG_PATH = "output.txt";
const QString stdfctl::SQL_PATH = "QtERP.sql";
const QString stdfctl::SQL_SP_PATH = "QtERP_SPs.sql";
const QString stdfctl::resource_path = ":/new/prefix1/icons/";
const QString stdfctl::bg_red = "color:white; background-color:rgb(141,44,45); border-radius:4px; padding:5px;";
const QString stdfctl::bg_yellow  = "color:black; background-color:#E1C61E; border-radius:4px; padding:5px;";
const QString stdfctl::bg_blue = "color:white; background-color:#607990; border-radius:4px; padding:5px;";
const QString stdfctl::bg_green  = "color:#ffffff; background-color:#495a43; border-radius:4px; padding:5px;";
const QString stdfctl::bg_gray = "color:white; background-color:#8e8f91; border-radius:4px; padding:5px;";

const QString stdfctl::html_style  =  "<style type=\"text/css\">"
                                      ".tg  {border-collapse:collapse;border-spacing:0;border-color:#aabcfe;}"
                                      ".tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:#aabcfe;color:#669;background-color:#e8edff;}"
                                      ".tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:#aabcfe;color:#039;background-color:#b9c9fe;}"
                                      ".tg .tg-s6z2{text-align:center}"
                                      ".tg .tg-vn4c{background-color:#D2E4FC; text-align:center}"
                                      ".tg .tg-0ord{text-align:right}"
                                      ".tg .tg-ifyx{background-color:#D2E4FC;text-align:right}"
                                     " </style>";

const QString stdfctl::table_html_begin  = "<table class=\"tg\" table style=width:100%>";
const QString stdfctl::table_html_end  = "</table>";
const QString stdfctl::row_begin =  "<tr>";
const QString stdfctl::row_end =  "</tr>";
const QString stdfctl::header_cell  = "<th>";
const QString stdfctl::header_cell_end = "</th>";
const QString stdfctl::header_cell_style = " <th class=\"tg-s6z2\" colspan=\"6\">";
const QString stdfctl::header_cell_style_2 = "<th class=\"tg-ifyx\" colspan=\"6\">";
const QString stdfctl::cell_begin = "<td class=\"tg-vn4c\">";
const QString stdfctl::cell_end = "</td>";

qulonglong RANDOM_NUMBER = 0;

stdfctl::stdfctl()
{
    SERIAL_ID = rnd();
}

QString stdfctl::dumpObjects(const int& id)
{
    switch(id)
    {
    case -2:
        return "GERAL";
        break;
    default:
        return int2s(id);
    }
}

void stdfctl::formatFctlLine(const QString& fctl, const int& line, QString& n, QString name)
{
    const char *nbsp = n.toLocal8Bit().constData();
    const QString & id = QString("%1:%2").arg(line,5).arg(fctl);

    if(name.size() > 0)
    {
        qDebug()<< "\/\/" << nbsp<<id.toLocal8Bit().data()<<name;
    }
}

void stdfctl::dumpLocal(const envelope & dados, QString &nbsp, QString fctl, int line, QString name)
{
    qDebug() << "";
    qDebug() << line << fctl.toLocal8Bit().constData()
             << envelope_id(dados).toLocal8Bit().constData();

    if( dados.header.count()>0)
    {
        qDebug() << "    PV r = dados.header; // t=" << dados.header.count();
        dumpLocal( dados.header, nbsp, fctl, 0,name );
    }

    dumpLocal(dados.body, nbsp, fctl, 0,name );
}

void stdfctl::dumpLocal(const QList< QHash<QString,QVariant> > & body,
                              QString & n, QString fctl, int line, QString name )
{
    int t = body.count();
    if(t > 0)
    {
        if(name.size() < 1)
        {
            name = "r";
        }

        qDebug()<< QString("CINT t = "+name+".body.count(); // t=%1").arg(t).toLocal8Bit().constData();
        qDebug()<<"for( int i = 0 ; i < t ; ++ i ){";
        qDebug()<< QString("\tPV r = "+name+".body.at(i);").toLocal8Bit().constData();
        for(int i = 0 ; i < t ; ++i)
        {
            qDebug() << QString("// %2").arg(i).toLocal8Bit().constData();
            dumpLocal( body.at(i), n ,fctl,line,"r");
            qDebug()<<"";
        }
        qDebug()<<"}";
    }
}

void stdfctl::dumpLocal(const QHash<QString, QVariant>& data, QString & nbsp,
                         QString fctl, int line, QString name)
{
    if(line != 0) formatFctlLine(fctl, line,nbsp,name);
    if(name.size() < 1) name = "r";
    QHashIterator < QString, QVariant > i(data);
    QList<QString> keys = data.keys();
    CINT ct = keys.count();
    int k_max = 0;
    for(int i = 0 ; i < ct ; ++ i)
    {
        if(keys.at(i).size() > k_max)
        {
            k_max = keys.at(i).size();
        }
    }
    k_max += 2;
    qs tpl;
    while(i.hasNext())
    {
        i.next();
        const QVariant & v = i.value();

        QS key = "\""+i.key()+"\"";;
        qs key_var = i.key();
           key_var.replace(QRegExp("[^a-zA-Z0-9_]"),"_");

        QS v_str = v.toString().mid(0,60).trimmed();
        QS v_type = v.typeName();

        if( v.type() == QVariant::Int )
        {
            tpl = "%1CINT %2 = %3.value(%4).toInt(); // %5: %6";
        }
        else if( v.type() == QVariant::Bool )
        {
            tpl = "%1const bool & %2 = %3.value(%4).toBool(); // %5: %6";
        }
        else
        {
            tpl = "%1QS %2 = %3.value(%4).toString(); // %5: %6";
        }

        QS line = QString(tpl.toLocal8Bit().constData())
                    .arg(nbsp).arg(key_var).arg(name).arg(key).arg(v_type).arg(v_str);
        qDebug() << line.toLocal8Bit().data();
    }
}

QString stdfctl::envelope_id(const envelope & dados)
{
    qsl args;
    QString t = "TCP";
    args << t;

    if(dados.object != 0)
    {
        args << "object=" + dumpObjects(dados.object);
    }
    return args.join(",")+" ";
}

uint stdfctl::rnd()
{
    ++RANDOM_NUMBER;
    return RANDOM_NUMBER;
}

QString stdfctl::read_file(QString filename)
{
    QFile file(filename);
    QString lines;

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        lines = in.readAll();
        return lines;
    }
    return lines;
}

QString stdfctl::base64_encode(QString string)
{
    QByteArray ba;
    ba.append(string);
    return ba.toBase64();
}

QString stdfctl::base64_decode(QString string)
{
    QByteArray ba;
    ba.append(string);
    return QByteArray::fromBase64(ba);
}

bool stdfctl::confirmation(QString titulo, QString msg)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(0 , titulo, msg, QMessageBox::Yes | QMessageBox::No);

      if (reply == QMessageBox::Yes)
      {
        return true;
      }

      return false;
}

QString stdfctl::escape(QString str)
{
    return "'"+str.replace("'","\\'")+"'";
}

// ICONES
QStringList stdfctl::getResourceIcons(QString path)
{
    QStringList icones;
    QDirIterator it(path.toUtf8().constData(), QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        icones << it.next();
    }
    return icones;
}

void stdfctl::getModelIcons(qsl icones, ModelTemplate & model)
{
    CINT total = icones.count();
    for(int i = 0; i < total; ++i)
    {
        QString nome_icone =  icones.at(i);
        QStandardItem *item = new QStandardItem(QIcon(nome_icone), nome_icone);
        item->setData(nome_icone);
        model.insertRow(i, item);
    }
}

QIcon stdfctl::getIcon(qs str)
{
    return QIcon(resource_path + str);
}

QString stdfctl::randomString()
{
   QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   int randomStringLength = 12;

   QString randomString;

   for(int i = 0; i < randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }

   return randomString;
}

void stdfctl::logger(const int type, const QString & txt)
{
    QString f = LOG_PATH;
    QByteArray date = QDateTime::currentDateTime().toString("dd.MM.yyyy h:m:s").toUtf8();
    QFile fl(f);
    fl.open(QIODevice::WriteOnly | QIODevice::Append);
    switch (type)
    {
    case DEBUG_MSG:
        fl.write("[" +date + "]" + " DEBUG: " + txt.toUtf8() + "\n");
        break;
    case CRITICAL_MSG:
        fl.write("[" +date + "]" + " CRITICAL: " + txt.toUtf8() + "\n");
        break;
    case WARNING_MSG:
        fl.write("[" +date + "]" + " WARNING: " + txt.toUtf8() + "\n");
        break;
    case INFO_MSG:
        fl.write("[" +date + "]" + " INFO: " + txt.toUtf8() + "\n");
        break;
    }

    fl.close();
}

QString stdfctl::returnLogger(const QString & txt)
{
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy h:m:s");
    QString text = "[" +date +    "]" + txt + "\n";
    return text;
}

void stdfctl::cmd(const qsl args)
{
    if(args.count() > 0)
    {
        qsl tmp = args;
        qs cmd = tmp.at(0);
        tmp.removeAt(0);
        QProcess::startDetached(cmd,tmp);
    }
    else
    {
        QProcess::startDetached("/usr/bin/sudo", args);
    }
}
