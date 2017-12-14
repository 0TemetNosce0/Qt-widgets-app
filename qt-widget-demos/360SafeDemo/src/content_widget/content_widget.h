#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>

class QLabel;
class QSplitter;
class QPushButton;
class QToolButton;
class QProgressBar;

class ContentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContentWidget(QWidget *parent = 0);
    void translateLanguage();

private:
    void initLeft();
    void initRightTop();
    void initRightCenter();
    void initRightCenterFunction();
    void initRightBottom();
    void initRight();

    bool eventFilter(QObject *obj, QEvent *event);

private:
    QSplitter *main_splitter;

    QWidget *left_widget;
    QLabel *label;
    QLabel *suggest_label;
    QLabel *system_safe_label;
    QPushButton *power_button; //立即体检按钮

    QSplitter *right_splitter;
    QWidget *right_widget;
    QWidget *right_top_widget;
    QLabel *name_label;
    QToolButton *menu_button;
    QProgressBar *progress_bar;
    QToolButton *grade_button;

    QPushButton *login_button; //登录我的360帐号
    QLabel *priv_label; //皇砖图标
    QLabel *info_label; //开启炫动卫视图标
    QLabel *privilege_label; //转享特权
    QPushButton *register_button; //10秒免费注册
    QPushButton *safe_button;
    QPushButton *tab_button;
    QPushButton *pet_button;
    QPushButton *lottery_button;
    QPushButton *cloud_five_button;
    QPushButton *caipiao_button;

    QWidget *right_center_widget;
    QToolButton *fireproof_button; //360防火墙
    QToolButton *triggerman_button; //360保镖
    QToolButton *net_shop_button; //网购先赔
    QLabel *line_label_1; //虚线
    QLabel *line_label_2; //虚线

    QWidget *right_center_function_widget;
    QLabel *function_label; //功能大全
    QPushButton *more_button; //更多
    QToolButton *recovery_button; //文件恢复
    QToolButton *mobile_button; //手机助手
    QToolButton *game_box_button; //游戏盒子
    QToolButton *desktop_button; //安全桌面
    QToolButton *net_repair_button; //断网急救箱
    QToolButton *auto_run_button; //开机加速
    QToolButton *net_speed_button; //宽带测速器
    QToolButton *net_pretext_button; //360网盾
    QToolButton *first_add_button; //系统急救箱

    QWidget *right_bottom_widget;
    QLabel *icon_label; //云图标
    QLabel *connect_label; //成功连接云安全
    QLabel *version_label; //版本号
    QPushButton *version_button; //版本升级
};

#endif // CONTENTWIDGET_H
