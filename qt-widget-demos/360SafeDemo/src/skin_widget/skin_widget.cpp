#include <QLabel>
#include <QVBoxLayout>
#include <QSignalMapper>

#include "skin_widget.h"
#include "../util/util.h"

SkinWidget::SkinWidget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(620, 445);

    //初始化为未按下鼠标左键
    mouse_press = false;
    skin_name = QString("");
    is_change = false;
    current_page = 1;

    //设置标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->initTitle();
    this->initCenter();
    this->initBottom();

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addLayout(center_layout);
    main_layout->addLayout(bottom_layout);
    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);

    this->translateLanguage();

    this->showSkin(QString::number(current_page, 10));
}

void SkinWidget::initTitle()
{
    title_label = new QLabel();
    title_icon_label = new QLabel();
    close_button = new PushButton();

    QPixmap title_pixmap(":/img/safe");
    title_icon_label->setPixmap(title_pixmap);
    title_icon_label->setFixedSize(16, 16);
    title_icon_label->setScaledContents(true);

    close_button->loadPixmap(":/sysButton/close");
    title_label->setFixedHeight(30);

    title_layout = new QHBoxLayout();
    title_layout->addWidget(title_icon_label, 0, Qt::AlignVCenter);
    title_layout->addWidget(title_label, 0, Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setSpacing(5);
    title_layout->setContentsMargins(10, 0, 5, 0);

    title_label->setStyleSheet("color:white;");
    connect(close_button, SIGNAL(clicked()), this, SLOT(hide()));
}

void SkinWidget::initCenter()
{
    skin_list<<":/skin/0"<<":/skin/1"<<":/skin/2"<<":/skin/3"<<":/skin/4"<<
               ":/skin/5"<<":/skin/6"<<":/skin/7"<<":/skin/8"<<":/skin/9"<<
               ":/skin/10"<<":/skin/11"<<":/skin/12"<<":/skin/13"<<":/skin/14"<<
               ":/skin/15"<<":/skin/16"<<":/skin/17"<<":/skin/18"<<":/skin/19"<<
               ":/skin/20"<<":/skin/21"<<":/skin/22"<<":/skin/23";

    center_layout = new QGridLayout();
    center_layout->setSpacing(5);
    center_layout->setContentsMargins(5, 35, 5, 0);

    change_skin_widget_0 = new ChangeSkinWidget();
    change_skin_widget_1 = new ChangeSkinWidget();
    change_skin_widget_2 = new ChangeSkinWidget();
    change_skin_widget_3 = new ChangeSkinWidget();
    change_skin_widget_4 = new ChangeSkinWidget();
    change_skin_widget_5 = new ChangeSkinWidget();
    change_skin_widget_6 = new ChangeSkinWidget();
    change_skin_widget_7 = new ChangeSkinWidget();

    connect(change_skin_widget_0, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(change_skin_widget_1, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(change_skin_widget_2, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(change_skin_widget_3, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(change_skin_widget_4, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(change_skin_widget_5, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(change_skin_widget_6, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));
    connect(change_skin_widget_7, SIGNAL(changeSkin(QString)), this, SLOT(varyfySkin(QString)));

    center_layout->addWidget(change_skin_widget_0, 0, 0);
    center_layout->addWidget(change_skin_widget_1, 0, 1);
    center_layout->addWidget(change_skin_widget_2, 0, 2);
    center_layout->addWidget(change_skin_widget_3, 0, 3);
    center_layout->addWidget(change_skin_widget_4, 1, 0);
    center_layout->addWidget(change_skin_widget_5, 1, 1);
    center_layout->addWidget(change_skin_widget_6, 1, 2);
    center_layout->addWidget(change_skin_widget_7, 1, 3);

    int skin_list_count = skin_list.size();
    page_count = skin_list_count / 8;
    page_count_point = skin_list_count % 8;
    if(page_count_point > 0)
    {
        page_count = page_count + 1;
    }
}

void SkinWidget::initBottom()
{
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    QList<QPushButton *> *button_list = new QList<QPushButton *>();
    for(int i=0; i<page_count; i++)
    {
        QPushButton *page_button = new QPushButton();
        page_button->setFixedWidth(20);
        page_button->setText(QString::number(i+1, 10));
        page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
        page_button->setCursor(Qt::PointingHandCursor);
        connect(page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(page_button, page_button->text());
        button_list->push_back(page_button);
    }

    first_page_button = new QPushButton();
    previous_page_button = new QPushButton();
    next_page_button = new QPushButton();
    last_page_button = new QPushButton();
    first_page_button->setFixedWidth(50);
    previous_page_button->setFixedWidth(50);
    next_page_button->setFixedWidth(50);
    last_page_button->setFixedWidth(50);
    first_page_button->setCursor(Qt::PointingHandCursor);
    previous_page_button->setCursor(Qt::PointingHandCursor);
    next_page_button->setCursor(Qt::PointingHandCursor);
    last_page_button->setCursor(Qt::PointingHandCursor);
    first_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
    previous_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
    next_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
    last_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");

    first_page_button->setText(tr("first page"));
    previous_page_button->setText(tr("previous page"));
    next_page_button->setText(tr("next page"));
    last_page_button->setText(tr("last page"));

    connect(first_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
    connect(previous_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
    connect(next_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
    connect(last_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
    signal_mapper->setMapping(first_page_button, "first");
    signal_mapper->setMapping(previous_page_button, "previous");
    signal_mapper->setMapping(next_page_button, "next");
    signal_mapper->setMapping(last_page_button, "last");
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(showSkin(QString)));

    bottom_layout = new QHBoxLayout();
    bottom_layout->addStretch();
    bottom_layout->addWidget(first_page_button, 0, Qt::AlignVCenter);
    bottom_layout->addWidget(previous_page_button, 0, Qt::AlignVCenter);
    for(int i=0; i<button_list->count(); i++)
    {
        QPushButton *page_button = button_list->at(i);
        bottom_layout->addWidget(page_button, 0, Qt::AlignVCenter);
    }
    bottom_layout->addWidget(next_page_button, 0, Qt::AlignVCenter);
    bottom_layout->addWidget(last_page_button, 0, Qt::AlignVCenter);
    bottom_layout->addStretch();
    bottom_layout->setSpacing(2);
    bottom_layout->setContentsMargins(0, 10, 0, 0);
}

void SkinWidget::showSkin(QString current_skin)
{
    if(current_skin == "first")
    {
        current_page = 1;
    }
    else if(current_skin == "previous")
    {
        if(current_page > 2)
        {
            current_page = current_page - 1;
        }
    }
    else if(current_skin == "next")
    {
        if(current_page < page_count)
        {
            current_page = current_page + 1;
        }
    }
    else if(current_skin == "last")
    {
        current_page = page_count;
    }
    else
    {
        bool ok;
        current_page = current_skin.toInt(&ok, 10);
    }

    if(current_page == 1)
    {
        next_page_button->show();
        last_page_button->show();
        first_page_button->hide();
        previous_page_button->hide();
    }
    else if(current_page == page_count)
    {
        first_page_button->show();
        previous_page_button->show();
        next_page_button->hide();
        last_page_button->hide();
    }
    else
    {
        first_page_button->hide();
        previous_page_button->show();
        next_page_button->show();
        last_page_button->hide();
    }

    //第一页为0-7 显示至previous_total_page个
    int previous_total_page = (current_page - 1)*8;
    int tip_index = previous_total_page;
    if(previous_total_page > 0)
    {
        tip_index = previous_total_page - 1;
    }
    change_skin_widget_0->changeSkin(":/skin/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    change_skin_widget_1->changeSkin(":/skin/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    change_skin_widget_2->changeSkin(":/skin/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    change_skin_widget_3->changeSkin(":/skin/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    change_skin_widget_4->changeSkin(":/skin/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    change_skin_widget_5->changeSkin(":/skin/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    change_skin_widget_6->changeSkin(":/skin/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
    change_skin_widget_7->changeSkin(":/skin/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++), "11");
}

void SkinWidget::translateLanguage()
{
    title_label->setText(tr("title"));
    close_button->setToolTip(tr("close"));

    tip_list<<tr("profound life")<<tr("blue sea")<<tr("red heart")<<tr("lovely baby")<<tr("transparent water")<<
              tr("flower")<<tr("great sunshine")<<tr("shadow amazement")<<tr("360 pet")<<tr("beautiful stone")<<
              tr("yellow energy")<<tr("magic world")<<tr("intense emotion")<<tr("dream sky")<<tr("angry bird")<<
              tr("graceful jazz")<<tr("card")<<tr("summer cool")<<tr("blue world")<<tr("woodwind")<<
              tr("pink mood")<<tr("across time")<<tr("six year");
}

void SkinWidget::varyfySkin(QString skin_name)
{
    this->skin_name = skin_name;
    is_change = true;
    update();
    emit changeSkin(skin_name);
}

void SkinWidget::paintEvent(QPaintEvent *)
{
    if(!is_change)
    {
        bool is_read = Util::readInit(QString("./user.ini"), QString("skin"), skin_name);
        if(is_read)
        {
            if(skin_name.isEmpty())
            {
                skin_name = QString(":/skin/17_big");
            }
        }
        else
        {
            skin_name = QString(":/skin/17_big");
        }
    }
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(skin_name));

    QPainter painter2(this);
    QLinearGradient linear2(rect().topLeft(), rect().bottomLeft());
    linear2.setColorAt(0, Qt::white);
    linear2.setColorAt(0.5, Qt::white);
    linear2.setColorAt(1, Qt::white);
    painter2.setPen(Qt::white); //设定画笔颜色，到时侯就是边框颜色
    painter2.setBrush(linear2);
    painter2.drawRect(QRect(0, 30, this->width(), this->height()-30));

    QPainter painter3(this);
    painter3.setPen(Qt::gray);
    static const QPointF points[4] = {QPointF(0, 30), QPointF(0, this->height()-1), QPointF(this->width()-1, this->height()-1), QPointF(this->width()-1, 30)};
    painter3.drawPolyline(points, 4);
}

void SkinWidget::mousePressEvent( QMouseEvent * event )
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }

    //窗口移动距离
    move_point = event->globalPos() - pos();
}

void SkinWidget::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void SkinWidget::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}
