#ifndef XTitlePanel_H
#define XTitlePanel_H

#include "XFrame.h"
class QHBoxLayout;
class QLabel;
class QPushButton;

class XTitlePanel : public XFrame
{
    Q_OBJECT

public:
    XTitlePanel();
    void setStyleSheet(const QString &styleSheet) = delete;                     // 禁止设置样式表

public:
    void setButtonHints(int ntButtonHints);                                     // 设置按钮类型
    void setTitle(QString strTitle, QString strStylesheet);                     // 设置标题
    void setTitleAlignment(Qt::Alignment align);                                // 设置标题对齐方式
    void setIcon(QString strStylesheet);                                        // 设置图标
    void setIcon(QPixmap pixmap);                                               // 设置图标
    void addWidget(QWidget *pWgt);                                              // 添加部件

    void setRadius(int ntTopLeft, int ntTopRight, int ntBottomLeft, int ntBottonRight);
    void setBorderWidth(int ntLeft, int ntTop, int ntRight, int ntBottom);
    void setBorderWidth(int ntWidth);

signals:
    void toMinimize();                  // 最小化信号
    void toMaximize();                  // 最大化信号
    void toRestore();                   // 恢复信号
    void toClose();                     // 关闭信号

public slots:
    void onMaximize();                  // 最大化槽
    void onRestore();                   // 恢复槽

private:
    void initMembers();                 // 初始化成员
    void initControls();                // 初始化控件
    void refreshRadius();

private:      
    QLabel *mp_labelIcon;               // 窗口图标
    QLabel *mp_labelTitle;              // 窗口标题
    QPushButton* mp_btnMin;             // 最小化按钮
    QPushButton* mp_btnMax;             // 最大化按钮
    QPushButton* mp_btnRes;             // 还原按钮
    QPushButton* mp_btnCls;             // 关闭按钮

    int mo_ntButtonHints;               // 按钮类型
    QHBoxLayout *mp_layoutBtns;         // 标题栏按钮布局   
};

#endif // XTitlePanel_H
