#ifndef CHANGESKINWIDGET_H
#define CHANGESKINWIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;

class ChangeSkinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeSkinWidget(QWidget *parent = 0);
    ~ChangeSkinWidget();
    void translateLanguage();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    void changeSkin(QString pixmap_name);

public slots:
    void changeSkin(QString pixmap_name, QString skin_name, QString download_count);

private:
    QLabel *skin_label;           //显示皮肤
    QLabel *skin_name_label;      //显示皮肤名称
    QLabel *download_count_label; //显示下载次数
    QPushButton *use_skin_button; //使用此皮肤按钮

    QString pixmap_name;
    bool mouse_press;
    bool mouse_enter;
};

#endif  //CHANGESKINWIDGET_H
