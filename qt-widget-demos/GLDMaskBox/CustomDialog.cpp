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
    m_pPreButton->setText(QStringLiteral("上一步"));

    m_pNextButton = new QPushButton(this);
    m_pNextButton->setText(QStringLiteral("下一步"));

    m_pPreButton->setGeometry(60, 90, 68, 30);
    m_pNextButton->setGeometry(600, 180, 68, 30);

    setObjectName("dsb");

    QString strErrMsg = QStringLiteral("一个保护指针 QPointer,行为类似正常的C++指针，只不过其在引用对象删除之后会自动设置为0. T必须是QObject的子类\
                                        保护指针在你要保存别人创建的QObject对象，且有可能其已经被删除而你仍然持有其引用的时候非常有用。");

    GLDMaskBox::showTipBox(m_pPreButton, QStringLiteral("无所谓"), strErrMsg);


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

