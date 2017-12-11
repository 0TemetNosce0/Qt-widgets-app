#ifndef BORDERFRAME_H
#define BORDERFRAME_H

#include "XFrame.h"
#include <QVBoxLayout>

class XBorderPanel : public XFrame
{
    Q_OBJECT

private:
    void setStyleSheet(const QString &styleSheet) = delete;

public:
    explicit XBorderPanel(QWidget *parent = 0);
    ~XBorderPanel();

public:      
    void setSizeConstraint(QLayout::SizeConstraint constraint);     // 设置尺寸约束
    void setTitleWidget(QWidget* pWgtTitle);                        // 设置标题栏部件
    void setClientWidget(QWidget* pWgtClient);                      // 设置客户区部件

signals:
    void titleWidgetChanged();                                      // 标题栏部件变更信号
    void clientWidgetChanged();                                     // 客户区部件变更信号

private:
    void initMembers();                                             // 初始化成员
    void initLayout();                                              // 初始化布局
    void reLayout();                                                // 重新布局

private:  
    QVBoxLayout *mp_layout;             // 主布局
    QVBoxLayout *mp_layoutTitle;        // 标题栏布局
    QVBoxLayout *mp_layoutClient;       // 客户区布局

    QWidget *mp_wgtTitle;               // 标题栏部件
    QWidget *mp_wgtClient;              // 客户栏部件
};

#endif // BORDERFRAME_H
