#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "QVBoxLayout"
#include "QSplitter"
#include "QTextBrowser"
#include "QTextEdit"
#include "QKeyEvent"

class QTextBrowser;
class QTextEdit;
class QEvent;

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow();

public:
    bool eventFilter(QObject *watched, QEvent *e);
    void submitChatText();

private:
    Ui::ChatWindow *ui;

    QTextBrowser *conversationView;
    QTextEdit *chatEdit;
};

#endif // CHATWINDOW_H
