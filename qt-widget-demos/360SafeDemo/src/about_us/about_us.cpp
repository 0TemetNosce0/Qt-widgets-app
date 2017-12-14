#include "about_us.h" 
#include "../util/util.h"
#include <QLabel>
#include <QHBoxLayout>

AboutUsDialog::AboutUsDialog(QWidget *parent)
    : QDialog(parent)
{
    this->resize(520, 290);

    //初始化为未按下鼠标左键
    mouse_press = false;

    //设置标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    title_label = new QLabel();
    title_icon_label = new QLabel();
    title_info_label = new QLabel();
    info_label = new QLabel();
    version_label = new QLabel();
    mummy_label = new QLabel();
    copyright_label = new QLabel();
    icon_label = new QLabel();
    close_button = new PushButton();
    ok_button = new QPushButton();

    QPixmap title_pixmap(":/img/safe");
    title_icon_label->setPixmap(title_pixmap);
    title_icon_label->setFixedSize(16, 16);
    title_icon_label->setScaledContents(true);

    close_button->loadPixmap(":/sysButton/close");

    title_label->setFixedHeight(30);
    ok_button->setFixedSize(75, 25);
    QPixmap pixmap(":/img/360safe");
    icon_label->setPixmap(pixmap);
    icon_label->setFixedSize(pixmap.size());

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(title_icon_label, 0, Qt::AlignVCenter);
    title_layout->addWidget(title_label, 0, Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setSpacing(5);
    title_layout->setContentsMargins(10, 0, 5, 0);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addWidget(title_info_label);
    v_layout->addWidget(info_label);
    v_layout->addWidget(version_label);
    v_layout->addWidget(mummy_label);
    v_layout->addWidget(copyright_label);
    v_layout->addStretch();
    v_layout->setSpacing(5);
    v_layout->setContentsMargins(0, 15, 0, 0);
    info_label->setContentsMargins(0, 0, 0, 40);

    QHBoxLayout *bottom_layout = new QHBoxLayout();
    bottom_layout->addStretch();
    bottom_layout->addWidget(ok_button);
    bottom_layout->setSpacing(0);
    bottom_layout->setContentsMargins(0, 0, 30, 20);

    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addLayout(v_layout);
    h_layout->addWidget(icon_label);
    h_layout->setSpacing(0);
    h_layout->setContentsMargins(40, 0, 20, 10);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addStretch();
    main_layout->addLayout(h_layout);
    main_layout->addLayout(bottom_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);

    title_label->setStyleSheet("color:white;");
    copyright_label->setStyleSheet("color:gray;");
    title_info_label->setStyleSheet("color:rgb(30,170,60);");
    info_label->setStyleSheet("color:rgb(30,170,60);");
    ok_button->setStyleSheet("QPushButton{border:1px solid lightgray; background:rgb(230,230,230);}"
                             "QPushButton:hover{border-color:green; background:transparent;}");

    QFont title_info_font("微软雅黑", 14, QFont::Bold, false);
    title_info_label->setFont(title_info_font);

    QFont info_font = info_label->font();
    info_font.setBold(true);
    info_label->setFont(info_font);

    connect(ok_button, SIGNAL(clicked()), this, SLOT(hide()));
    connect(close_button, SIGNAL(clicked()), this, SLOT(hide()));

    this->translateLanguage();
}

void AboutUsDialog::translateLanguage()
{
    title_label->setText(tr("title"));
    title_info_label->setText(tr("360 safe"));
    info_label->setText(tr("info"));
    version_label->setText(tr("version"));
    mummy_label->setText(tr("mummy"));
    copyright_label->setText(tr("copyright"));
    close_button->setToolTip(tr("close"));
    ok_button->setText(tr("ok"));
}

AboutUsDialog::~AboutUsDialog()
{

}

void AboutUsDialog::paintEvent(QPaintEvent *)
{
    QString skin_name;
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

void AboutUsDialog::mousePressEvent( QMouseEvent * event )
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }

    //窗口移动距离
    move_point = event->globalPos() - pos();
}

void AboutUsDialog::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void AboutUsDialog::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}
