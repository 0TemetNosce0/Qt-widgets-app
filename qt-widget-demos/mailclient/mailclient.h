#ifndef MAILCLIENT_H
#define MAILCLIENT_H

#include <QMainWindow>
#include <QSplitter>
#include <QTreeWidget>
#include <QTextEdit>

namespace Ui {
class mailclient;
}

class mailclient : public QMainWindow
{
    Q_OBJECT

public:
    explicit mailclient(QWidget *parent = 0);
    ~mailclient();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::mailclient *ui;

    void addFolder(const QIcon &icon, const QString &name);
    void addMessage(const QString &subject, const QString &from,
                    const QString &date);
    void readSettings();
    void writeSettings();

    QSplitter *mainSplitter;
    QSplitter *rightSplitter;
    QTreeWidget *foldersTreeWidget;
    QTreeWidget *messagesTreeWidget;
    QTextEdit *textEdit;
};

#endif // MAILCLIENT_H
