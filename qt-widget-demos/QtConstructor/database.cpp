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

#include "database.h"
#define DATABASE

database::database(QObject *parent) :
    QObject(parent),
    host(""),
    port(0),
    _database("QtConstructor"),
    user(""),
    pass(""),
    driver("")
{

}

database::~database()
{
    close();
}

bool database::abrir_conexao()
{
    is_valid = false;

    if(!db.isValid())
    {
        if(db.isOpen() && db.isValid())
        {
            is_valid = true;
            return is_valid;
        }
    }

    new_db(driver);
    db.setDatabaseName(_database);
    db.setUserName( user );
    db.setPassword( pass );
    db.setHostName( host );
    db.setPort( port );

    uri = qs( "%1://%2@%3/%4" )
            .arg(driver)
            .arg(user)
            .arg(host)
            .arg(_database);

    if (!db.open())
    {
        send_erro(db.lastError().text());
        return is_valid;
    }

    is_valid = true;
    return is_valid;
}

bool database::conexao_ok()
{
    return db.isValid() && db.open();
}

QSqlQuery database::get_query()
{
    if(conexao_ok())
    {
        return QSqlQuery(db);
    }
    else
    {
        send_erro(db.lastError().text());
    }
    return QSqlQuery();
}

lpv database::get_all(QString str)
{
    lpv tree;
    QSqlQuery q = get_query();    

    if(! q.exec(str))
    {
        on_query_error(q);
        send_erro(db.lastError().text());
        return tree;
    }

    QSqlRecord result_info = q.record();
    const int t = result_info.count();

    while(q.next())
    {
        pv r;

        for( int i = 0 ; i < t ; ++ i )
        {
            const QString & field_name = result_info.fieldName(i);
            const QVariant & column_value = q.value(i);
            r.insert(field_name,column_value);
        }

        tree.append(r);
    }

    return tree;
}

pv database::get_row(QString str)
{
    pv r;
    const lpv tree = get_all(str);
    if(tree.count() == 0) return r;
    return tree.at(0);
}

QString database::getOne(QString str)
{
    QString value;
    PV r = get_row(str);
    QHashIterator<QString,QVariant> i(r);
    while(i.hasNext())
    {
        i.next();
        return i.value().toString();
    }
    return value;
}

bool database::execRow(QString str)
{
    QSqlQuery q = get_query();    
    if(! q.exec(str))
    {
        on_query_error(q);
        send_erro(q.lastError().text());
        return false;
    }
    return true;

}

bool database::on_query_error(QSqlQuery & q)
{
    if(q.lastError().isValid())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void database::new_db(QS driver)
{
    qs id = int2s(rnd());
    db = QSqlDatabase::addDatabase(driver,id);        

}

void database::close()
{
    QS connection = db.connectionName();
    db.close();
    db.removeDatabase(connection);
}

#undef DATABASE

