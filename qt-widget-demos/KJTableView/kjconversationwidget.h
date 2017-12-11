#ifndef KJCONVERSATIONWIDGET_H
#define KJCONVERSATIONWIDGET_H

#include <QWidget>

namespace Ui {
class KJConversationWidget;
}

class KJConversationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KJConversationWidget(QWidget *parent = 0);
    ~KJConversationWidget();

    void init(QString title, QString detail, int found);

public:
    int widgetIndex;

private:
    Ui::KJConversationWidget *ui;

private slots:
    void slotOnButtonClicked();
};

#endif // KJCONVERSATIONWIDGET_H
