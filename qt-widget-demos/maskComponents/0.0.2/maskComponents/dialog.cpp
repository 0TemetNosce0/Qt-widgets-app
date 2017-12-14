#include "dialog.h"
#include "ui_dialog.h"
#include "GLDMaskWidget.h"
#include "CustomNewGuideFacade.h"

#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDesktopWidget>

Dialog::Dialog(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_pPreButton = new QPushButton(this);
    m_pPreButton->setText(QStringLiteral("上一步"));

    m_pNextButton = new QPushButton(this);
    m_pNextButton->setText(QStringLiteral("下一步"));

    m_pPreButton->setGeometry(60, 90, 68, 30);
    m_pNextButton->setGeometry(600, 180, 68, 30);

    // setWindowFlags(Qt::FramelessWindowHint);
    // setAttribute(Qt::WA_NoSystemBackground, true);
    // setAttribute(Qt::WA_TranslucentBackground, true);
    // showMaximized();
    // this->setWindowOpacity(0.5);
    // ui->label->move((QApplication::desktop()->width() - ui->label->width())/2,(QApplication::desktop()->height() - ui->label->height())/2);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton)
    {
        pPos = mouseEvent->pos();
    }

    if (mouseEvent->buttons() == Qt::RightButton)
    {
        this->close();
    }
}

void Dialog::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton)
    {
        move(mouseEvent->globalPos() - pPos);
    }
}
