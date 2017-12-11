#include "GLDMaskBox.h"
#include "CustomDialog.h"
#include "GLDFileUtils.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDesktopWidget>

#include <QLineEdit>
#include <QTextEdit>


Dialog::Dialog(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    initUI();
    setObjectName("Dialog");
    resize(900, 600);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
}

Dialog::~Dialog()
{

}

void Dialog::initUI()
{
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 4);
    gridLayout->setColumnStretch(2, 1);
    gridLayout->setColumnStretch(3, 1);
    gridLayout->setColumnStretch(4, 4);

    gridLayout->setMargin(15);
    gridLayout->setColumnMinimumWidth(2, 15);

    m_btn1 = new QPushButton(QWidget::tr("First Name:"), this);
    QLineEdit *edit1 = new QLineEdit(this);
    QLabel *lbl2 = new QLabel(QWidget::tr("Last Name:"), this);
    QLineEdit *edit2 = new QLineEdit(this);
    QLabel *lbl3 = new QLabel(QWidget::tr("Sex:"), this);
    QLineEdit *edit3 = new QLineEdit(this);
    QLabel *lbl4 = new QLabel(QWidget::tr("Birthday:"), this);
    QLineEdit *edit4 = new QLineEdit(this);
    QLabel *lbl5 = new QLabel(QWidget::tr("Address:"), this);
    m_textEdt = new QTextEdit(this);

    gridLayout->addWidget(m_btn1, 0, 0);
    gridLayout->addWidget(edit1, 0, 1);
    gridLayout->addWidget(lbl2, 0, 3);
    gridLayout->addWidget(edit2, 0, 4);
    gridLayout->addWidget(lbl3, 1, 0);
    gridLayout->addWidget(edit3, 1, 1);
    gridLayout->addWidget(lbl4, 1, 3);
    gridLayout->addWidget(edit4, 1, 4);
    gridLayout->addWidget(lbl5, 2, 0);
    gridLayout->addWidget(m_textEdt, 3, 0, 2, 5);

    setLayout(gridLayout);

    m_pMask = GLDMaskBox::createMaskFor(m_btn1, exePath() + "/images/Msg/login.png", exePath() + "/images/Msg/know.png");

    connect(m_btn1, &QPushButton::clicked, m_pMask, &GLDMaskBox::customClicked);
    connect(m_pMask, &GLDMaskBox::customClicked, this, &Dialog::showMask);
}

void Dialog::showPosition()
{
    GLDMaskBox::createMaskFor(m_pNextButton, exePath() + "/images/Msg/login.png", exePath() + "/images/Msg/know.png");
}

void Dialog::showMask()
{
    disconnect(m_pMask, &GLDMaskBox::customClicked, this, &Dialog::showMask);
    GLDMaskBox::createMaskFor(m_textEdt, exePath() + "/images/Msg/login.png", exePath() + "/images/Msg/know.png");
}
