/***************************************************************************
 *   Copyright (C) 2014 by peter komar                                     *
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
#include "requesthistory.h"


RequestHistory::RequestHistory()
{

}

RequestHistory::~RequestHistory()
{
    m_database.close();
}

void RequestHistory::init()
{
    QDir home = QDir::home();

    if(!home.exists(".qrestclient"))
    {
        if( !home.mkdir(".qrestclient"))
        {
            qDebug() << "Fatal create directory";
            return;
        }
    }

    home.cd(".qrestclient");
    QString file = home.absolutePath() + "/history.db";
    bool bNeedToCreate = !QFile::exists(file);
    connect(file);

    if(bNeedToCreate)
    {
        createDataBase();
    }
}

QSqlDatabase& RequestHistory::database()
{
    return m_database;
}

bool RequestHistory::connect(const QString &dbName)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE", dbName);
    m_database.setDatabaseName(dbName);
    m_database.setUserName("");
    m_database.setPassword("");

    if (!m_database.open())
    {
        QSqlDatabase::removeDatabase(dbName);
        qDebug() << "Cant init QSQLITE";
        return false;
    }

    return true;
}

void RequestHistory::createDataBase()
{
    QSqlQuery query(m_database);

    QStringList queries;
    queries
    << "CREATE TABLE requests ("
                "id int,"
                "date datetime,"
                "code int,"
                "type varchar,"
                "url varchar,"
                "response mediumtext,"
                "error varchar,"
                "headers mediumtext"
    ")"
    << "CREATE TABLE requests_params ("
                "request_id int,"
                "name varchar,"
                "value varchar"
    ")"
    << "CREATE TABLE request_headers ("
                "request_id int,"
                "name varchar,"
                "value varchar"
    ")"
    << "CREATE TABLE request_raw ("
                "request_id int,"
                "body varchar,"
                "type_content varchar"
    ")";

    QStringList::const_iterator constIterator;

    for (constIterator = queries.constBegin(); constIterator != queries.constEnd(); ++constIterator)
    {
        if (!query.exec(*constIterator))
        {
          qDebug() << "Failed to execute: " << (*constIterator).toLocal8Bit().constData();
        }
    }
}

int RequestHistory::addRequest(const QString &url, const QString &method, int responseCode,
                               const QString& response,  const QString& error, const QString& headers)
{
    QSqlQuery q(m_database);

    q.prepare("SELECT max(id) FROM requests");

    if(!q.exec())
    {
        qDebug() << "Error execution query: " << q.lastQuery() << " Error: " << q.lastError();
        throw "Error execution query";
    }

    int index = -1;

    if(q.first())
    {
      index = q.value(0).toInt();
    }

    ++index;

    q.prepare(""
     "INSERT INTO requests (id, date, code, type, url, response, error, headers)"
     " VALUES (:id, :date, :code, :type, :url, :response, :error, :headers)"
    );

    q.bindValue(":id", index);
    q.bindValue(":date", QDateTime::currentDateTime().toString());
    q.bindValue(":code", responseCode);
    q.bindValue(":type", method);
    q.bindValue(":url", url);
    q.bindValue(":response", response);
    q.bindValue(":error", error);
    q.bindValue(":headers", headers);

    if(!q.exec())
    {
        qDebug() << "Error execution query: " << q.lastQuery() << " Error: " << q.lastError();
        throw "Error execution query";
    }

    return index;
}

void RequestHistory::addParam(int requestId, const QString &name, const QString &value)
{
    QSqlQuery q(m_database);

    q.prepare(""
     "INSERT INTO requests_params (request_id, name, value)"
     " VALUES (:request_id, :name, :value)"
    );

    q.bindValue(":request_id", requestId);
    q.bindValue(":name", name);
    q.bindValue(":value", value);

    if(!q.exec())
    {
        qDebug() << "Error execution query: " << q.lastQuery() << " Error: " << q.lastError();
        throw "Error execution query";
    }
}

void RequestHistory::addHeader(int requestId, const QString &name, const QString &value)
{
    QSqlQuery q(m_database);

    q.prepare(""
     "INSERT INTO request_headers (request_id, name, value)"
     " VALUES (:request_id, :name, :value)"
    );

    q.bindValue(":request_id", requestId);
    q.bindValue(":name", name);
    q.bindValue(":value", value);

    if(!q.exec())
    {
        qDebug() << "Error execution query: " << q.lastQuery() << " Error: " << q.lastError();
        throw "Error execution query";
    }
}

void RequestHistory::addRaw(int requestId, const QString &contentType, const QString &rawBody)
{
    if(contentType.isEmpty() || rawBody.isEmpty())
    {
        return;
    }

    QSqlQuery q(m_database);

    q.prepare(""
     "INSERT INTO request_raw (request_id, body, type_content)"
     " VALUES (:request_id, :body, :type_content)"
    );

    q.bindValue(":request_id", requestId);
    q.bindValue(":body", rawBody);
    q.bindValue(":type_content", contentType);

    if(!q.exec())
    {
        qDebug() << "Error execution query: " << q.lastQuery() << " Error: " << q.lastError();
        throw "Error execution query";
    }
}

bool RequestHistory::deleteHistory(int requestId)
{
    QSqlQuery query(m_database);

    QStringList queries;
    queries << "DELETE FROM requests WHERE id = :id"
            << "DELETE FROM requests_params WHERE request_id = :id"
            << "DELETE FROM request_headers WHERE request_id = :id"
            << "DELETE FROM request_raw WHERE request_id = :id"
            << "vacuum";

    QStringList::const_iterator constIterator;

    for (constIterator = queries.constBegin(); constIterator != queries.constEnd(); ++constIterator)
    {
        query.prepare(*constIterator);
        query.bindValue(":id", requestId);

        if (!query.exec())
        {
            qDebug() << "Failed to execute: " << (*constIterator).toLocal8Bit().constData();
            return false;
        }
    }

    return true;
}
