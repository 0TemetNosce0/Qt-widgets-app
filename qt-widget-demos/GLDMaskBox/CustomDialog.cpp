#include "GLDMaskBox.h"
#include "CustomDialog.h"

#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDesktopWidget>


Dialog::Dialog(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    m_pPreButton = new QPushButton(this);
    m_pPreButton->setText(QStringLiteral("��һ��"));

    m_pNextButton = new QPushButton(this);
    m_pNextButton->setText(QStringLiteral("��һ��"));

    m_pPreButton->setGeometry(60, 90, 68, 30);
    m_pNextButton->setGeometry(600, 180, 68, 30);

    setObjectName("dsb");

    QString strErrMsg = QStringLiteral("һ������ָ�� QPointer,��Ϊ����������C++ָ�룬ֻ�����������ö���ɾ��֮����Զ�����Ϊ0. T������QObject������\
                                        ����ָ������Ҫ������˴�����QObject�������п������Ѿ���ɾ��������Ȼ���������õ�ʱ��ǳ����á�");

    GLDMaskBox::showTipBox(m_pPreButton, QStringLiteral("����ν"), strErrMsg);


    setWindowFlags(windowFlags() /*| Qt::FramelessWindowHint*/ | Qt::WindowMinMaxButtonsHint);
//     setAttribute(Qt::WA_NoSystemBackground, true);
//     setAttribute(Qt::WA_TranslucentBackground, true);
//     showMaximized();
//     this->setWindowOpacity(0.5);
}

Dialog::~Dialog()
{

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

