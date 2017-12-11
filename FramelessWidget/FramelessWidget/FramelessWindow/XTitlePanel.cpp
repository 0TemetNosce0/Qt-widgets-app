#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QApplication>
#include <QtMath>

#include <QDebug>
#include "XTitlePanel.h"

XTitlePanel::XTitlePanel()
{
    setAttribute(Qt::WA_DeleteOnClose, true);    
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    setObjectName("FrameTitle");
    setMouseTracking(true);

    initStyle();
    setMinimumHeight(30);

    initMembers();
    initControls();
}

/// BEGIN: 公共接口

// 设置按钮类型
void XTitlePanel::setButtonHints(int ntButtonHints)
{
    if(mo_ntButtonHints == ntButtonHints)    return;

    mp_btnMin->setVisible(Q_LIKELY(ntButtonHints&Xc::WindowMinButtonHint));
    mp_btnMax->setVisible(Q_LIKELY(ntButtonHints&Xc::WindowMaxButtonHint));
    mp_btnRes->setVisible(Q_LIKELY(ntButtonHints&Xc::WindowMaxButtonHint));
    mp_btnCls->setVisible(Q_LIKELY(ntButtonHints&Xc::WindowCloseButtonHint));
}

// 设置标题

void XTitlePanel::setTitle(QString strTitle, QString strStylesheet)
{
    mp_labelTitle->setText(strTitle);
    if(!strStylesheet.isEmpty())
        mp_labelTitle->setStyleSheet(strStylesheet);
}

void XTitlePanel::setTitleAlignment(Qt::Alignment align)
{
    mp_labelTitle->setAlignment(align);
}

// 设置图标
void XTitlePanel::setIcon(QString strStylesheet)
{
    //qDebug() << "XTitlePanel::setIcon";
    mp_labelIcon->setStyleSheet(strStylesheet);
}

void XTitlePanel::setIcon(QPixmap pixmap)
{
    mp_labelIcon->setPixmap(pixmap);
}

// 添加部件
void XTitlePanel::addWidget(QWidget *pWgt)
{
    //qDebug() << "XTitlePanel::addWidget";
    mp_layoutBtns->addWidget(pWgt);
    refreshRadius();
}


void XTitlePanel::setRadius(int ntTopLeft, int ntTopRight, int ntBottomLeft, int ntBottonRight)
{
    XStyle::setRadius(ntTopLeft, ntTopRight, ntBottomLeft, ntBottonRight);
    refreshRadius();
}

void XTitlePanel::setBorderWidth(int ntLeft, int ntTop, int ntRight, int ntBottom)
{
    XStyle::setBorderWidth(ntLeft, ntTop, ntRight, ntBottom);
    refreshRadius();
}

void XTitlePanel::setBorderWidth(int ntWidth)
{
    XStyle::setBorderWidth(ntWidth);
    refreshRadius();
}


/// END: 公共接口

/// 私有函数

// 初始化成员
void XTitlePanel::initMembers()
{
    // 部件
    mp_labelIcon = nullptr;          // 窗口图标
    mp_labelTitle = nullptr;         // 窗口标题
    mp_btnMin = nullptr;             // 最小化按钮;
    mp_btnMax = nullptr;             // 最大化按钮;
    mp_btnRes = nullptr;             // 还原按钮;
    mp_btnCls = nullptr;             // 关闭按钮;

    mp_layoutBtns = nullptr;         // 标题栏按钮布局

    // 其他
    mo_ntButtonHints = Xc::WindowMinMaxCloseButtonHint; // 按钮类
}

// 初始化控件
void XTitlePanel::initControls()
{
    mp_labelIcon = new QLabel(tr("Icon"));
    mp_labelTitle = new QLabel(tr("Unkonw Title"));

    mp_labelTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mp_labelTitle->setAlignment(Qt::AlignLeft);

    mp_btnMin = new QPushButton;
    mp_btnMax = new QPushButton;
    mp_btnRes = new QPushButton;
    mp_btnCls = new QPushButton;

    // 设置部件对象名
    mp_labelIcon->setObjectName("LabelIcon");
    mp_labelTitle->setObjectName("LabelTitle");
    mp_btnMin->setObjectName("BtnMin");
    mp_btnRes->setObjectName("BtnRes");
    mp_btnMax->setObjectName("BtnMax");
    mp_btnCls->setObjectName("BtnCls");

    mp_btnRes->hide();

    /*
    mp_btnMin->setFixedSize(QSize(24, 24));
    mp_btnMax->setFixedSize(QSize(24, 24));
    mp_btnRes->setFixedSize(QSize(24, 24));
    mp_btnCls->setFixedSize(QSize(36, 24));

    mp_btnMin->setText(tr("━"));
    mp_btnMax->setText(tr("✚"));
    mp_btnRes->setText(tr("✚"));
    mp_btnCls->setText(tr("✖"));
    */


    QStyle *style = qApp->style();
    int ntHeight = minimumHeight();
    mp_labelIcon->setPixmap(style->standardPixmap(QStyle::SP_TitleBarMenuButton));

    mp_btnMin->setIcon(style->standardIcon(QStyle::SP_TitleBarMinButton));
    mp_btnMax->setIcon(style->standardIcon(QStyle::SP_TitleBarMaxButton));
    mp_btnRes->setIcon(style->standardIcon(QStyle::SP_TitleBarNormalButton));
    mp_btnCls->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));

    mp_btnMin->setIconSize(QSize(ntHeight,ntHeight));
    mp_btnMax->setIconSize(QSize(ntHeight,ntHeight));
    mp_btnRes->setIconSize(QSize(ntHeight,ntHeight));
    mp_btnCls->setIconSize(QSize(ntHeight*1.5,ntHeight));


    mp_btnMin->setToolTip(tr("最小化"));
    mp_btnMax->setToolTip(tr("最大化"));
    mp_btnRes->setToolTip(tr("恢复"));
    mp_btnCls->setToolTip(tr("关闭"));

    mp_labelIcon->setStyleSheet("QLabel#LabelIcon{border: none;}");
    mp_labelTitle->setStyleSheet("QLabel#LabelTitle{border: none;}");
    mp_btnMin->setStyleSheet(QStringLiteral("QPushButton#BtnMin{border: none;background-color: transparent;color: darkgray;}"
                                            "QPushButton#BtnMin:hover{background-color: rgba(0,0,0,45); color: white}"));
    mp_btnMax->setStyleSheet(QStringLiteral("QPushButton#BtnMax{border: none;background-color: transparent;color: darkgray;}"
                                            "QPushButton#BtnMax:hover{background-color: rgba(0,0,0,45); color: white}"));
    mp_btnRes->setStyleSheet(QStringLiteral("QPushButton#BtnRes{border: none;background-color: transparent;color: darkgray;}"
                                            "QPushButton#BtnRes:hover{background-color: rgba(0,0,0,45); color: white}"));
    mp_btnCls->setStyleSheet(QStringLiteral("QPushButton#BtnCls{border: none; background-color: transparent;color: darkgray;}"
                                            "QPushButton#BtnCls:hover{background-color: red; color: white}"));

    // 设置子部件鼠标跟踪
    mp_labelIcon->setMouseTracking(true);
    mp_labelTitle->setMouseTracking(true);
    mp_btnMin->setMouseTracking(true);
    mp_btnMax->setMouseTracking(true);
    mp_btnRes->setMouseTracking(true);
    mp_btnCls->setMouseTracking(true);

    // 创建子布局
    mp_layoutBtns = new QHBoxLayout;
    mp_layoutBtns->setSizeConstraint(QLayout::SetFixedSize);
    mp_layoutBtns->setDirection(QBoxLayout::RightToLeft);
    mp_layoutBtns->setMargin(0);
    mp_layoutBtns->setSpacing(0);

    // 子布局添加部件
    mp_layoutBtns->addWidget(mp_btnCls);
    mp_layoutBtns->addWidget(mp_btnRes);
    mp_layoutBtns->addWidget(mp_btnMax);
    mp_layoutBtns->addWidget(mp_btnMin);

    // 创建主布局
    QHBoxLayout *playoutMain = new QHBoxLayout;
    playoutMain->setContentsMargins(10,0,0,0);
    playoutMain->setSpacing(5);

    // 主布局添加部件
    playoutMain->addWidget(mp_labelIcon);
    playoutMain->addWidget(mp_labelTitle);
    playoutMain->addLayout(mp_layoutBtns);

    // 主布局设置对齐
    playoutMain->setAlignment(mp_labelTitle,Qt::AlignVCenter);
    playoutMain->setAlignment(mp_layoutBtns,Qt::AlignRight);
    // 设置主布局
    setLayout(playoutMain);

    // 链接信号槽
    connect(mp_btnMin, SIGNAL(clicked()), this, SIGNAL(toMinimize()));
    connect(mp_btnMax, SIGNAL(clicked()), this, SIGNAL(toMaximize()));
    connect(mp_btnRes, SIGNAL(clicked()), this, SIGNAL(toRestore()));
    connect(mp_btnCls, SIGNAL(clicked()), this, SIGNAL(toClose()));

    connect(mp_btnMax, SIGNAL(clicked()), this, SLOT(onMaximize()));
    connect(mp_btnRes, SIGNAL(clicked()), this, SLOT(onRestore()));
}

void XTitlePanel::refreshRadius()
{
    for(int it=0; it<mp_layoutBtns->count(); it++)
    {
        QLayoutItem *pItem = mp_layoutBtns->itemAt(it);
        QWidget *pWgt = pItem->widget();
        if(Q_LIKELY(pWgt))
        {
            //qDebug() << QString("%1/%2is Widget : ").arg(it).arg(mp_layoutBtns->count()) << pWgt->objectName();
            if(!pWgt->isHidden())
            {
                //qDebug() << "is Widget : " << pWgt->objectName();
                //qDebug() << "Old Stylesheet = " << pWgt->styleSheet();
                QString strStylesheet = pWgt->styleSheet();
                strStylesheet += QString("QPushButton{border-top-right-radius: %2;}")
                                 .arg(getTopRightRadius()-qCeil((getTopBorderWidth()+getRightBorderWidth())/2));
                pWgt->setStyleSheet(strStylesheet);
                //qDebug() << "New Stylesheet = " << pWgt->styleSheet();
                break;
            }
        }
    }
}


/// 槽函数
// 最大化槽
void XTitlePanel::onMaximize()
{
    mp_btnMax->hide();
    mp_btnRes->show();
}

// 恢复槽
void XTitlePanel::onRestore()
{
    mp_btnMax->show();
    mp_btnRes->hide();
}
