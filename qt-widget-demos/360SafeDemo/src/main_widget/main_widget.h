#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "../about_us/about_us.h"
#include "../main_menu/main_menu.h"
#include "../skin_widget/skin_widget.h"
#include "../system_tray/system_tray.h"
#include "../title_widget/title_widget.h"
#include "../setting_dialog/setting_dialog.h"
#include "../content_widget/content_widget.h"
#include "../character_widget/character_widget.h"

#include <QSystemTrayIcon>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void showWidget();

private slots:
    void showMax();
    void showSkinWidget();
    void showMainMenu();
    void showSettingDialog();
    void showAboutUs();
    void showNewCharacter();
    void changeSkin(QString skin_name);
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);

private:
    QRect location;
    TitleWidget *title_widget; //������
    ContentWidget *content_widget; //����������
    SystemTray *system_tray; //������
    SettingDialog *setting_dialog; //���ý���
    CharacterWidget *character_widget; //�°����Խ���
    AboutUsDialog *about_us_dialog; //�������ǽ���
    QString skin_name;//�����ڱ���ͼƬ������
    MainMenu *main_menu; //���˵�
    SkinWidget *skin_widget; //��ʾƤ������

};

#endif // MAINWIDGET_H
