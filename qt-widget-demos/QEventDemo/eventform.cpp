#include "eventform.h"
#include "ui_eventform.h"

EventForm::EventForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EventForm)
{
    ui->setupUi(this);
}

EventForm::~EventForm()
{
    delete ui;
}

void EventForm::on_listWidget_itemClicked(QListWidgetItem *item)
{
    static int offset = 0;
    QWheelEvent wheelEvent(QPoint(),
                           offset--,
                           Qt::MiddleButton,
                           Qt::NoModifier,
                           Qt::Vertical);

    qDebug() << ui->listWidget->focusWidget()->objectName();

    QApplication::sendEvent(ui->listWidget->focusWidget(), &wheelEvent);
}
