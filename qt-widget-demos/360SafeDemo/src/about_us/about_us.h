#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QDialog>

#include "../push_button/push_button.h"

class QLabel;

class AboutUsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutUsDialog(QWidget *parent = 0);
    ~AboutUsDialog();
    void translateLanguage();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QPoint move_point;        //移动的距离
    bool mouse_press;         //按下鼠标左键
    QLabel *title_label;      //标题
    QLabel *title_icon_label; //标题图标
    QLabel *title_info_label; //360安全卫士
    QLabel *info_label;       //杀木马、防盗号、电脑加速
    QLabel *version_label;    //主程序版本
    QLabel *mummy_label;      //备用木马库
    QLabel *copyright_label;  //版本信息
    QLabel *icon_label;       //图标
    PushButton *close_button; //关闭按钮
    QPushButton *ok_button;   //确定按钮
};

#endif  //ABOUTUS_H
