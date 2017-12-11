#include "GLDMaskBox.h"
#include "CustomDialog.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDesktopWidget>


Dialog::Dialog(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    m_pPreButton = new QPushButton(this);
    m_pPreButton->setText(QStringLiteral("上一步"));

    m_pNextButton = new QPushButton(this);
    m_pNextButton->setText(QStringLiteral("下一步"));

    m_pPreButton->setGeometry(60, 90, 68, 30);
    m_pNextButton->setGeometry(500, 180, 68, 30);

    setObjectName("dsb");
    setFixedSize(900, 600);

    setWindowFlags(windowFlags() /*| Qt::FramelessWindowHint*/ | Qt::WindowMinMaxButtonsHint);
    m_mask = GLDMaskBox::showMaskBox(m_pPreButton);
    qDebug() << QStringLiteral("观察这个指针") << m_mask;

//     setAttribute(Qt::WA_NoSystemBackground, true);
//     setAttribute(Qt::WA_TranslucentBackground, true);
//     showMaximized();
//     this->setWindowOpacity(0.5);
}

Dialog::~Dialog()
{

}

void Dialog::showPosition()
{
    GLDMaskBox *b = GLDMaskBox::showMaskBox(m_pNextButton);
    qDebug() << QStringLiteral("观察这个指针") << b;
}

//void Dialog::mousePressEvent(QMouseEvent *mouseEvent)
//{
//    if (mouseEvent->buttons() == Qt::LeftButton)
//    {
//        pPos = mouseEvent->pos();
//    }
//
//    if (mouseEvent->buttons() == Qt::RightButton)
//    {
//        this->close();
//    }
//}
//
//void Dialog::mouseMoveEvent(QMouseEvent *mouseEvent)
//{
//    if (mouseEvent->buttons() == Qt::LeftButton)
//    {
//        move(mouseEvent->globalPos() - pPos);
//    }
//}

