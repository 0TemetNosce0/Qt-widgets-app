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

#include "restclientmainwindow.h"
#include "paramslist.h"
#include "resthistorywidget.h"
#include "requesthistory.h"
#include "responsewidget.h"

#include <QTextEdit>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QToolBar>
#include <QTabWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QMessageBox>
#include <QUrlQuery>
#include <QApplication>
#include <QStatusBar>
#include <QMenuBar>
#include <QSettings>
#include <QProgressDialog>
#include <QCloseEvent>
#include <QShortcut>
#include <QSslConfiguration>

RestClientMainWindow::RestClientMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(1000, 600);
    _gui();

    m_reply = 0;
    m_waitDialog =0;

    m_history = new RequestHistory();
    m_history->init();
    loadHistory();

    QSettings setting("UDL", "qrestclient");
    QByteArray arr = setting.value("gui/state").toByteArray();

    if(!arr.isEmpty())
    {
        restoreState(arr);
    }

    int tab = setting.value("gui/tab_index").toInt();
    m_leftTabWidget->setCurrentIndex(tab);
}

RestClientMainWindow::~RestClientMainWindow()
{
    delete m_history;
}

void RestClientMainWindow::closeEvent(QCloseEvent *event)
{
    QSettings setting("UDL", "qrestclient");
    setting.setValue("gui/state", saveState());
    setting.setValue("gui/tab_index", m_leftTabWidget->currentIndex());

    event->accept();
}

void RestClientMainWindow::_gui()
{
    setWindowTitle("QRestClient");

    QVBoxLayout *l = new QVBoxLayout;

    m_response = new ResponseWidget(this);
    m_response->setMinimumSize(500, 205);
    l->addWidget(m_response);

    m_errorResponse = new QTextEdit();
    m_errorResponse->setText("Error:");
    m_errorResponse->setReadOnly(true);
    m_errorResponse->setAcceptRichText(false);
    m_errorResponse->setMinimumSize(500, 100);
    m_errorResponse->setMaximumHeight(100);
    l->addWidget(m_errorResponse);

    QWidget *main = new QWidget(this);
    main->setLayout(l);
    setCentralWidget(main);

    setupToolBar();
    setupLeftPanel();
    setupRightPanel();
    setupBottomPabel();
    setupMenu();
}

void RestClientMainWindow::setupMenu()
{
    QMenu *view = menuBar()->addMenu("View");

    m_jsonView = new QAction("Json", this);
    m_textView = new QAction("Text", this);
    m_csvView  = new QAction("CSV", this);

    QActionGroup *viewGroup = new QActionGroup(this);
    viewGroup->addAction(m_jsonView);
    viewGroup->addAction(m_textView);
    viewGroup->addAction(m_csvView);

    m_jsonView->setCheckable(true);
    m_textView->setCheckable(true);
    m_csvView->setCheckable(true);

    m_textView->setChecked(true);

    view->addAction(m_jsonView);
    view->addAction(m_textView);
    view->addAction(m_csvView);

    connect(m_jsonView, SIGNAL(triggered()), this, SLOT(slotViewJson()));
    connect(m_textView, SIGNAL(triggered()), this, SLOT(slotViewText()));
    connect(m_csvView,  SIGNAL(triggered()), this, SLOT(slotViewCsv()));

    QAction *a = new QAction("About", this);
    QMenu *m = menuBar()->addMenu("Help");
    m->addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(slotAbout()));
}

void RestClientMainWindow::setupToolBar()
{
    QWidget *tool = new QWidget();
    QHBoxLayout *pHLayout = new QHBoxLayout;

    QLabel *lUrl = new QLabel("URL:");
    m_editURL = new QLineEdit("http://");
    QLabel *lR = new QLabel("Method:");
    m_comboRestMethod = new QComboBox();

    QStringList items;
    items << "GET" << "POST" << "PUT" << "DELETE";
    m_comboRestMethod->addItems(items);

    QPushButton *m_btn = new QPushButton("Send");
    m_btn->setToolTip(tr("To run request Ctrl+R"));
    m_btn->setDefault(true);
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this);


    connect(m_btn, SIGNAL(clicked()), this, SLOT(slotSendRequest()));
    connect(m_editURL, SIGNAL(returnPressed()), this, SLOT(slotSendRequest()));
    connect(shortcut, SIGNAL(activated()), this, SLOT(slotSendRequest()));


    pHLayout->addWidget(lUrl);
    pHLayout->addWidget(m_editURL);
    pHLayout->addWidget(lR);
    pHLayout->addWidget(m_comboRestMethod);
    pHLayout->addWidget(m_btn);
    tool->setLayout(pHLayout);

    QToolBar *toolBar = new QToolBar("restbar", this);
    toolBar->setObjectName("RestToolBar");
    toolBar->addWidget(tool);

    addToolBar(toolBar);
}

void RestClientMainWindow::setupLeftPanel()
{
    m_params = new ParamsList;
    m_headers = new ParamsList;
    m_contetTypeCombo= new QComboBox();
    m_contentBody = new QTextEdit;
    m_contentBody->setAcceptRichText(false);

    QStringList types;
    types << "application/json" << "text/csv" << "text/plain" << "text/xml";
    m_contetTypeCombo->addItems(types);
    m_contetTypeCombo->setEditable(true);

    QWidget *w = new QWidget;
    QHBoxLayout *ph = new QHBoxLayout;
    QLabel *label = new QLabel("Content Type:");
    ph->addWidget(label);
    ph->addWidget(m_contetTypeCombo);
    QVBoxLayout *pv = new QVBoxLayout;
    pv->addLayout(ph);
    pv->addWidget(m_contentBody);
    w->setLayout(pv);

    m_leftTabWidget = new QTabWidget();
    m_leftTabWidget->addTab(buildParamsWidget(m_params), "Params");
    m_leftTabWidget->addTab(buildParamsWidget(m_headers), "Headers");
    m_leftTabWidget->addTab(w, "Content to Send");

    m_leftTabWidget->setCurrentIndex(0);

    QDockWidget *dock = new QDockWidget(this);
    dock->setObjectName("Left");
    dock->setWidget(m_leftTabWidget);
    dock->setFeatures(QDockWidget::DockWidgetMovable
                      | QDockWidget::DockWidgetFloatable
                      | QDockWidget::DockWidgetVerticalTitleBar);
    dock->setMinimumWidth(450);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
}

void RestClientMainWindow::setupRightPanel()
{
    m_responseHeaders = new QTextEdit;
    m_responseHeaders->setAcceptRichText(true);
    m_responseHeaders->setReadOnly(true);

    QDockWidget *dock = new QDockWidget(this);
    dock->setObjectName("Right");
    dock->setWindowTitle("Response Headers");
    dock->setWidget(m_responseHeaders);
    dock->setFeatures(QDockWidget::DockWidgetMovable
                      | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
}

void RestClientMainWindow::setupBottomPabel()
{
    m_historyWidget = new RestHistoryWidget;
    connect(m_historyWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(slotHistoryLoad(QTreeWidgetItem*,int)));
    connect(m_historyWidget, SIGNAL(emitRemoveItems()), this, SLOT(slotHistoryRemoveSelected()));
    connect(m_historyWidget, SIGNAL(emitRemoveAllItems()), this, SLOT(slotHistoryClear()));

    QDockWidget *dock = new QDockWidget(this);
    dock->setObjectName("Bottom");
    dock->setWindowTitle("Request History");
    dock->setWidget(m_historyWidget);
    dock->setFeatures(QDockWidget::DockWidgetMovable
                      | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
}

QWidget* RestClientMainWindow::buildParamsWidget(ParamsList *widget)
{
    QWidget *w = new QWidget;
    QHBoxLayout *ph = new QHBoxLayout;

    QPushButton *btnAdd = new QPushButton("Add");
    btnAdd->setProperty("add", true);
    connect(btnAdd, SIGNAL(clicked()), widget, SLOT(slotEditItem()));
    QPushButton *btnEdit = new QPushButton("Edit");
    connect(btnEdit, SIGNAL(clicked()), widget, SLOT(slotEditItem()));
    QPushButton *btnDelete = new QPushButton("Delete");
    connect(btnDelete, SIGNAL(clicked()), widget, SLOT(slotDeleteItem()));

    ph->addStretch(10);
    ph->addWidget(btnAdd);
    ph->addWidget(btnEdit);
    ph->addWidget(btnDelete);

    QVBoxLayout *pv = new QVBoxLayout;
    pv->addLayout(ph);
    pv->addWidget(widget);
    w->setLayout(pv);

    return w;
}

void RestClientMainWindow::saveHistory(int code)
{
    QString url = m_editURL->text();
    if(url.isEmpty() || url.left(4) != "http")
    {
        QMessageBox::critical(this, "Error", "URL is incorrect");
        return;
    }

    int requestId = m_history->addRequest(url,
                                          m_comboRestMethod->currentText(),
                                          code,
                                          m_response->toText(),
                                          m_errorResponse->toPlainText(),
                                          m_responseHeaders->toHtml());

    QTreeWidgetItemIterator it(m_params);
    while(*it)
    {
        m_history->addParam(requestId, (*it)->text(0), (*it)->text(1));
        ++it;
    }

    QTreeWidgetItemIterator it2(m_headers);
    while(*it2)
    {
        m_history->addHeader(requestId, (*it2)->text(0), (*it2)->text(1));
        ++it2;
    }

    m_history->addRaw(requestId, m_contetTypeCombo->currentText(), m_contentBody->toPlainText());
    loadHistory();
}

void RestClientMainWindow::loadHistory()
{
    QSqlQuery q(m_history->database());
    q.prepare("SELECT * FROM requests ORDER By id DESC");
    if(!q.exec())
    {
        throw "Error execute query";
    }

    m_historyWidget->clear();
    while(q.next())
    {
        QTreeWidgetItem *item  = new QTreeWidgetItem(m_historyWidget);
        item->setText(0, q.value(0).toString());
        item->setText(1, q.value(3).toString());
        item->setText(2, q.value(4).toString());
        item->setText(3, q.value(2).toString());
        item->setText(4, q.value(1).toString());
    }
}

void RestClientMainWindow::waitDialog()
{
    m_waitDialog = new QMessageBox(this);
    m_waitDialog->setStandardButtons(QMessageBox::NoButton);
    m_waitDialog->setText("Please wait, sending request ...");
    m_waitDialog->exec();
}

void RestClientMainWindow::releaseReplyResources()
{
    disconnect(m_reply, SIGNAL(readyRead()), this, SLOT(slotReplyResponse()));
    disconnect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this,SLOT(slotReplyError(QNetworkReply::NetworkError)));
    disconnect(m_reply, SIGNAL(finished()), this, SLOT(slotFinishRequest()));

    QNetworkAccessManager *m = m_reply->manager();
    m_reply->deleteLater();
    m->deleteLater();

    m_waitDialog->close();
    delete m_waitDialog;
    m_waitDialog = 0;
}

void RestClientMainWindow::clearItems(QList<QTreeWidgetItem *>& items)
{
    int countItems = items.count();
    QProgressDialog *progress = new QProgressDialog("Removing history...", "", 0, countItems, this);
    progress->setWindowModality(Qt::WindowModal);
    progress->setAutoClose(true);

    QPushButton *btn = new QPushButton("Cancel", progress);
    btn->setDisabled(true);
    progress->setCancelButton(btn);

    int i = 0;
    progress->setValue(i);
    while(!items.isEmpty())
    {
        progress->setValue(++i);
        QTreeWidgetItem *item = (QTreeWidgetItem *)items.takeFirst();
        m_history->deleteHistory(item->text(0).toInt());
        delete item;
    }

    progress->setValue(countItems);
    delete progress;
}

void RestClientMainWindow::parseUrlParams()
{
    QString url = m_editURL->text();
    int pos = url.indexOf("?");

    if(pos == -1)
    {
        return;
    }

    QString queryString = url.mid(pos+1);
    url.remove("?"+queryString);
    m_editURL->setText(url);

    QUrlQuery query(queryString);

    QList<QPair<QString, QString> > items = query.queryItems();

    for( int i= 0; i < items.size(); i++ )
    {
        QPair<QString, QString> pair = items.at(i);
        QList<QTreeWidgetItem *> params = m_params->findItems(pair.first, Qt::MatchFixedString, 0);

        if(params.isEmpty())
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(m_params);
            item->setText(0, pair.first);
            item->setText(1, pair.second);
        }
        else
        {
            QTreeWidgetItem *w = params.takeFirst();
            w->setText(1, pair.second);
        }
    }
}

//slots
void RestClientMainWindow::slotSendRequest()
{
    parseUrlParams();
    QString url = m_editURL->text();
    if(url.isEmpty()
            || url.left(4) != "http"
            || url == "http://"
            || url == "https://" )
    {
        QMessageBox::critical(this, "Error", "URL is incorrect");
        return;
    }

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QUrl urlObject(url);
    QUrlQuery query;
    QTreeWidgetItemIterator paramsIterator(m_params);

    while(*paramsIterator)
    {
        query.addQueryItem((*paramsIterator)->text(0), (*paramsIterator)->text(1));
        ++paramsIterator;
    }
    urlObject.setQuery(query);

    QNetworkRequest request(urlObject);

    //Ignore SSL errors
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(conf);

    QTreeWidgetItemIterator headerIterator(m_headers);
    while(*headerIterator)
    {
        request.setRawHeader((*headerIterator)->text(0).toUtf8(), (*headerIterator)->text(1).toUtf8());
        ++headerIterator;
    }

    QByteArray rawBody  = m_contentBody->toPlainText().toUtf8();
    QString contentType = m_contetTypeCombo->currentText();

    if(m_comboRestMethod->currentText() == "GET" )
    {
        m_reply = manager->get(request);
    }
    else if(m_comboRestMethod->currentText() == "POST" )
    {
        if(rawBody.isEmpty())
        {
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
            m_reply = manager->post(request, query.query(QUrl::FullyEncoded).toUtf8());
        }
        else
        {
            QByteArray postDataSize = QByteArray::number(rawBody.size());
            request.setRawHeader("Content-Type", contentType.toLatin1());
            request.setRawHeader("Content-Length", postDataSize);
            m_reply = manager->post(request, rawBody);
        }

    }
    else if( m_comboRestMethod->currentText() == "PUT" )
    {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        m_reply = manager->put(request, query.query(QUrl::FullyEncoded).toUtf8());
    }
    else if( m_comboRestMethod->currentText() == "DELETE" )
    {
        m_reply = manager->deleteResource(request);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Unsupported method");
        return;
    }

    m_time = QTime::currentTime();

    connect(m_reply, SIGNAL(readyRead()), this, SLOT(slotReplyResponse()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this,SLOT(slotReplyError(QNetworkReply::NetworkError)));
    connect(m_reply, SIGNAL(finished()), this, SLOT(slotFinishRequest()));

    m_response->clear();
    m_errorResponse->clear();
    waitDialog();
}

void RestClientMainWindow::slotFinishRequest()
{
    QTime time = QTime::currentTime();
    QList<QByteArray> headers = m_reply->rawHeaderList();
    m_reply->close();

    QString contetType;
    m_responseHeaders->clear();

    for (int i = 0; i < headers.size(); ++i)
    {
        if( headers.at(i).toLower() == "content-type")
        {
            contetType = m_reply->rawHeader(headers.at(i));
        }

        m_responseHeaders->append("<b>"+headers.at(i) + "</b>: " + m_reply->rawHeader(headers.at(i)));
    }

    m_responseHeaders->append("<b>Execute Time</b>: "+QString::number(m_time.msecsTo(time))+" ms");

    saveHistory(200);
    releaseReplyResources();
    renderContentType(contetType);
}

void RestClientMainWindow::slotReplyResponse()
{
    m_response->append(m_reply->readAll());
}

void RestClientMainWindow::slotReplyError(QNetworkReply::NetworkError error)
{
    QString error_string;
    switch(error)
    {
    case QNetworkReply::ConnectionRefusedError :
        error_string += tr("the remote server refused the connection (the server is not accepting requests)");
        break;

    case QNetworkReply::HostNotFoundError :
        error_string += tr("the remote host name was not found (invalid hostname)");
        break;

    default :
        error_string +=  m_reply->errorString();
        break;
    }

    m_errorResponse->setText(error_string);
    releaseReplyResources();

    saveHistory(error);

    renderContentType("");
}


void RestClientMainWindow::slotHistoryLoad(QTreeWidgetItem *item, int)
{
    QSqlQuery q(m_history->database());
    q.prepare("SELECT * FROM requests WHERE id = :id");
    q.bindValue(":id", item->text(0));

    if(!q.exec())
    {
        throw "Error execute query";
    }

    if(!q.first())
    {
        return;
    }

    QString headers = q.value(7).toString();
    QString type = "text";
    int pos = 0;

    if((pos = headers.indexOf("content-type", 0, Qt::CaseInsensitive)) != -1)
    {
        int end = headers.indexOf("<", pos+1);
        type = headers.mid(pos+20, end-pos+5).trimmed();
    }

    m_editURL->setText(q.value(4).toString());
    m_comboRestMethod->setCurrentText(q.value(3).toString());
    m_response->setText(q.value(5).toString());
    m_errorResponse->setText(q.value(6).toString());
    m_responseHeaders->setText(q.value(7).toString());

    renderContentType(type);

    QTreeWidgetItem *i = 0;
    //load params
    q.prepare("SELECT * FROM requests_params WHERE request_id = :id");
    q.bindValue(":id", item->text(0));

    if(!q.exec())
    {
        throw "Error execute query";
    }
    m_params->clear();

    while(q.next())
    {
        i  = new QTreeWidgetItem(m_params);
        i->setText(0, q.value(1).toString());
        i->setText(1, q.value(2).toString());
    }

    //load headers
    q.prepare("SELECT * FROM request_headers WHERE request_id = :id");
    q.bindValue(":id", item->text(0));

    if(!q.exec())
    {
        throw "Error execute query";
    }
    m_headers->clear();

    while (q.next())
    {
        i  = new QTreeWidgetItem(m_headers);
        i->setText(0, q.value(1).toString());
        i->setText(1, q.value(2).toString());
    }

    q.prepare("SELECT * FROM request_raw WHERE request_id = :id");
    q.bindValue(":id", item->text(0));

    if(!q.exec())
    {
        throw "Error execute query";
    }

    m_contentBody->clear();

    if(!q.first())
    {
        return;
    }

    QString s = q.value(2).toString();

    if(m_contetTypeCombo->findText(s) != -1)
    {
        m_contetTypeCombo->setCurrentText(s);
    }
    else
    {
        m_contetTypeCombo->addItem(s);
    }

    m_contentBody->setText(q.value(1).toString());
}

void RestClientMainWindow::slotHistoryRemoveSelected()
{
    QList<QTreeWidgetItem *> list = m_historyWidget->selectedItems();

    if(list.isEmpty())
    {
        return;
    }

    int res = QMessageBox::question(this, "Confirm Remove", "Are you shure to want to remove selected requests?");

    if(res == QMessageBox::Yes)
    {
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        clearItems(list);
        QApplication::restoreOverrideCursor();
    }
}

void RestClientMainWindow::slotHistoryClear()
{
    int res = QMessageBox::question(this, "Confirm Remove", "Are you shure to want to clear request history?");

    if(res != QMessageBox::Yes)
    {
        return;
    }

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    int countItems = m_historyWidget->topLevelItemCount();
    QList<QTreeWidgetItem *> list;

    for(int i = 0; i < countItems; i++)
    {
        list.append(m_historyWidget->topLevelItem(i));
    }

    clearItems(list);

    loadHistory();

    QApplication::restoreOverrideCursor();
}

void RestClientMainWindow::slotViewJson()
{
    ResponseWidget::type type = m_response->render(ResponseWidget::TYPE_JSON);

    if(type != ResponseWidget::TYPE_JSON)
    {
        QMessageBox::critical(this, tr("Error parese"), tr("Error parsing JSON"));
        slotNotifyMenuView(type);
    }
}

void RestClientMainWindow::slotViewText()
{
    ResponseWidget::type type = m_response->render(ResponseWidget::TYPE_TEXT);
    slotNotifyMenuView(type);
}

void RestClientMainWindow::slotViewCsv()
{
    ResponseWidget::type type = m_response->render(ResponseWidget::TYPE_CSV);
    slotNotifyMenuView(type);
}

void RestClientMainWindow::slotNotifyMenuView(int pos)
{
    switch (pos) {
    case ResponseWidget::TYPE_TEXT: m_textView->setChecked(true);
        break;
    case ResponseWidget::TYPE_JSON: m_jsonView->setChecked(true);
    default:
        break;
    }
}

void RestClientMainWindow::renderContentType(const QString &contentType)
{
    int type = 0;
    if( contentType.indexOf("application/json", 0, Qt::CaseInsensitive) != -1) {
        type = m_response->render(ResponseWidget::TYPE_JSON);
    } else {
        type = m_response->render(ResponseWidget::TYPE_TEXT);
    }

    slotNotifyMenuView(type);
}

void RestClientMainWindow::slotAbout()
{
    QMessageBox::about(this, "About", "<b>QRestClient</b> - REST client for WEB services developers.<br/>"
                       "<br/> Supports sending GET, POST, PUT, DELETE requests to URL, managing sending params, heders, contets and logging sended requests.<br/><br/>"
                       "Author <a href=\"http://peter_komar.byethost17.com/\">Peter Komar</a>"
                       "<br/><br/><b>License:</b> GPL v2"
                       "<br/> 2007 - 2014"
                       "<br/><br/><b>Build</b>: " + QString::number(QDateTime::currentMSecsSinceEpoch()));
}
