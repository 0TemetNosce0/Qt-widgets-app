#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    QSplitter *splitter = new QSplitter(Qt::Vertical, this);
    lay->addWidget(splitter);
    conversationView = new QTextBrowser;
    chatEdit = new QTextEdit;
    splitter->addWidget(conversationView);
    splitter->addWidget(chatEdit);
    chatEdit->installEventFilter(this);
    setWindowTitle(tr("Chat Window"));
    setTabOrder(chatEdit, conversationView);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

bool ChatWindow::eventFilter(QObject *watched, QEvent* e)
{
    if (watched == chatEdit && e->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent*>(e);
        if (ke->key() == Qt::Key_Enter ||
                ke->key() == Qt::Key_Return)
        {
            submitChatText();
            return true;
        }
    }
    return QWidget::eventFilter(watched, e);
}

void ChatWindow::submitChatText()
{
    // append text as new paragraph
    conversationView->append(chatEdit->toPlainText());
    // clear chat window
    chatEdit->setPlainText("");
}
