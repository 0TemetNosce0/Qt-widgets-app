#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
   virtual void contextMenuEvent(QContextMenuEvent* event);

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
