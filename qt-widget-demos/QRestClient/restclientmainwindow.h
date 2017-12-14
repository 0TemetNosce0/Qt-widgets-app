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

#ifndef RESTCLIENTMAINWINDOW_H
#define RESTCLIENTMAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QTime>

class QTextEdit;
class RequestHistory;
class QLineEdit;
class QComboBox;
class ParamsList;
class RestHistoryWidget;
class RequestHistory;
class QTreeWidgetItem;
class QMessageBox;
class QTabWidget;
class ResponseWidget;

class RestClientMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit RestClientMainWindow(QWidget *parent = 0);
    ~RestClientMainWindow();

signals:

public slots:
     //Requests slots
    void slotFinishRequest();
    void slotSendRequest();
    void slotReplyResponse();
    void slotReplyError(QNetworkReply::NetworkError error);

    void slotHistoryLoad(QTreeWidgetItem*,int);
    void slotHistoryRemoveSelected();
    void slotHistoryClear();

    void slotViewJson();
    void slotViewText();
    void slotViewCsv();
    void slotAbout();

    void slotNotifyMenuView(int pos);

protected:
    void closeEvent(QCloseEvent *event);


private:
    QMessageBox *m_waitDialog;

    ResponseWidget *m_response;
    QTextEdit *m_errorResponse;
    QLineEdit *m_editURL;
    QComboBox *m_comboRestMethod;
    ParamsList *m_params;
    ParamsList *m_headers;
    QComboBox *m_contetTypeCombo;
    QTextEdit *m_contentBody;
    QTextEdit *m_responseHeaders;
    RestHistoryWidget *m_historyWidget;
    QTabWidget *m_leftTabWidget;

    RequestHistory *m_history;
    QNetworkReply *m_reply;

    QTime m_time;

    QAction *m_jsonView;
    QAction *m_textView;
    QAction *m_csvView;


    void loadHistory();
    void saveHistory(int resposeCode);

    void releaseReplyResources();
    void waitDialog();

    void _gui();
    void setupToolBar();
    void setupLeftPanel();
    void setupRightPanel();
    void setupBottomPabel();
    void setupMenu();

    QWidget* buildParamsWidget(ParamsList *);

    void clearItems(QList<QTreeWidgetItem*>& items);
    void parseUrlParams();

    void renderContentType(const QString& contentType);
};

#endif // RESTCLIENTMAINWINDOW_H
