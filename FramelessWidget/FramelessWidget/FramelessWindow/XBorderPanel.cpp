#include <QDebug>
#include "XBorderPanel.h"

// 析构函数
XBorderPanel::~XBorderPanel()
{

}

/// 构造函数
XBorderPanel::XBorderPanel(QWidget *parent) : XFrame(parent)
{
    setAttribute(Qt::WA_DeleteOnClose, true);        
    setObjectName("FrameBorder");
    setMouseTracking(true);

    initStyle();
    initMembers();
    initLayout();

    reLayout();   
}

/// 公有接口
// 设置尺寸约束
void XBorderPanel::setSizeConstraint(QLayout::SizeConstraint constraint)
{
    mp_layout->setSizeConstraint(constraint);
}

// 设置标题栏部件
void XBorderPanel::setTitleWidget(QWidget *pWgtTitle)
{
    if(mp_wgtTitle != pWgtTitle)
    {
        mp_wgtTitle = pWgtTitle;
        reLayout();
    }
}

// 设置客户区部件
void XBorderPanel::setClientWidget(QWidget *pWgtClient)
{
    if(mp_wgtClient != pWgtClient)
    {
        mp_wgtClient = pWgtClient;
        reLayout();
    }
}

/// 私有函数
// 初始化成员
void XBorderPanel::initMembers()
{
    // 布局成员
    mp_layout = nullptr;
    mp_layoutTitle = nullptr;                      // 标题栏布局
    mp_layoutClient = nullptr;                     // 客户区布局

    // 部件成员
    mp_wgtTitle = nullptr;                         // 标题栏
    mp_wgtClient = nullptr;                        // 客户区
}

// 创建布局
void XBorderPanel::initLayout()
{
    mp_layoutTitle = new QVBoxLayout;        // 标题栏布局
    mp_layoutClient = new QVBoxLayout;       // 客户区布局

    // 设置主布局
    mp_layout = new QVBoxLayout;
    mp_layout->setContentsMargins(0,0,0,0);
    mp_layout->setSpacing(0);
    mp_layout->addLayout(mp_layoutTitle);
    //mp_layout->addStretch();
    mp_layout->addLayout(mp_layoutClient);
    //mp_layout->addStretch();
    //mp_layout->setAlignment(mp_layoutTitle, Qt::AlignTop);
    setLayout(mp_layout);
}

void XBorderPanel::reLayout()
{
    if(mp_wgtTitle != NULL)
    {
        mp_layoutTitle->addWidget(mp_wgtTitle,Qt::AlignTop);
    }

    if(mp_wgtClient != NULL)
    {
        mp_layoutClient->addWidget(mp_wgtClient);
    }
}
