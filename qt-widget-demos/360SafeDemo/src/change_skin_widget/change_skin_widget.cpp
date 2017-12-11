#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>

#include "change_skin_widget.h"

ChangeSkinWidget::ChangeSkinWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(140, 160);
    mouse_press = false;
    mouse_enter = false;

    skin_label = new QLabel();
    skin_name_label = new QLabel();
    download_count_label = new QLabel();
    use_skin_button = new QPushButton();
    this->setCursor(Qt::PointingHandCursor);

    use_skin_button->setStyleSheet("border-radius:3px; border:1px solid rgb(180, 190, 200); color:rgb(70, 70, 70); background:transparent;");
    skin_label->setScaledContents(true);
    skin_label->setFixedSize(100, 65);
    use_skin_button->setFixedSize(85, 25);

    QVBoxLayout *background_layout = new QVBoxLayout();
    background_layout->addWidget(skin_label, 0, Qt::AlignCenter);
    background_layout->addWidget(skin_name_label, 0, Qt::AlignCenter);
    background_layout->addWidget(download_count_label, 0, Qt::AlignCenter);
    background_layout->addWidget(use_skin_button, 0, Qt::AlignCenter);
    background_layout->setSpacing(5);
    background_layout->setContentsMargins(0, 10, 0, 10);

    this->setLayout(background_layout);

    this->translateLanguage();
}

void ChangeSkinWidget::translateLanguage()
{
    use_skin_button->setText(tr("use skin"));
}

ChangeSkinWidget::~ChangeSkinWidget()
{

}

void ChangeSkinWidget::changeSkin(QString pixmap_name, QString skin_name, QString download_count)
{
    QString background_name = pixmap_name + "_big";
    this->pixmap_name = background_name;

    //更改皮肤背景
    QPixmap pixmap(background_name);
    skin_label->setPixmap(pixmap);

    //更改皮肤名称
    skin_name_label->setText(skin_name);

    //更改下载次数
    download_count_label->setText(tr("download count:") + download_count);
}

void ChangeSkinWidget::paintEvent(QPaintEvent *)
{
    if(mouse_enter)
    {
        //绘制边框
        QPainter painter(this);
        QPen pen(QColor(210, 225, 230));
        painter.setPen(pen);
        painter.drawRoundRect(0,0,this->width()-1, this->height()-1, 5, 5);
    }
}

void ChangeSkinWidget::mousePressEvent(QMouseEvent * event)
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        emit changeSkin(pixmap_name);
    }
}

void ChangeSkinWidget::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void ChangeSkinWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    mouse_enter = true;
    update();
}

void ChangeSkinWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    mouse_enter = false;
    update();
}
