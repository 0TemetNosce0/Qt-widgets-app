#include "medalwallwidget.h"

#include <QPainter>

MedalWallWidget::MedalWallWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    this->setFixedSize(700, 475);
    ismousePress = false;

    closeButton = new QPushButton();
//    closeButton->setPicName(QString(":/sysButton/close"));

    getLabel = new QLabel();
    topSafeLabel = new QLabel();
    topSdLabel = new QLabel();
    ungetLabel = new QLabel();
    infoLabel = new QLabel();
    onekeyGetButton = new QPushButton();

    clickGetLabel = new QLabel();
    tipIconLabel = new QLabel();
    browserButton = new QPushButton();

    QPixmap topSafe(":/MedalWall/top_safe");
    topSafeLabel->setPixmap(topSafe);
    topSafeLabel->setScaledContents(true);
    topSafeLabel->setFixedSize(topSafe.size());

    QPixmap topSd(":/MedalWall/top_sd");
    topSdLabel->setPixmap(topSd);
    topSdLabel->setScaledContents(true);
    topSdLabel->setFixedSize(topSd.size());

    infoLabel->setObjectName("infoLabel");
    QFont infoFont = infoLabel->font();
    infoFont.setBold(true);
    infoFont.setPointSize(12);
    infoLabel->setFont(infoFont);

    QPixmap getPixmap(":/MedalWall/tag_get");
    getLabel->setPixmap(getPixmap);
    getLabel->setScaledContents(true);
    getLabel->setFixedSize(getPixmap.size());

    QPixmap ungetPixmap(":/MedalWall/tag_unget");
    ungetLabel->setPixmap(ungetPixmap);
    ungetLabel->setScaledContents(true);
    ungetLabel->setFixedSize(ungetPixmap.size());

    QPixmap clickGetPixmap(":/MedalWall/tag_tips");
    clickGetLabel->setPixmap(clickGetPixmap);
    clickGetLabel->setScaledContents(true);
    clickGetLabel->setFixedSize(clickGetPixmap.size());

    QPixmap tipIconPixmap(":/MedalWall/tag_rock");
    tipIconLabel->setPixmap(tipIconPixmap);
    tipIconLabel->setScaledContents(true);
    tipIconLabel->setFixedSize(tipIconPixmap.size());

    QPixmap browserIcon(":/MedalWall/btm_se");
    browserButton->setIcon(browserIcon);
    browserButton->setIconSize(browserIcon.size());
    browserButton->setFixedSize(browserIcon.size());
    browserButton->setObjectName("transparentButton");

    onekeyGetButton->setObjectName("loginGreenButton");
    onekeyGetButton->setFixedSize(120, 40);
    QFont onekeyGetFont = onekeyGetButton->font();
    onekeyGetFont.setPointSize(14);
    onekeyGetFont.setBold(true);
    onekeyGetButton->setFont(onekeyGetFont);

    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addStretch();
    titleLayout->addWidget(closeButton, 0, Qt::AlignTop);
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(0, 5, 12, 0);

    QHBoxLayout *getLayout = new QHBoxLayout();
    getLayout->addWidget(topSafeLabel);
    getLayout->addWidget(topSdLabel);
    getLayout->addStretch();
    getLayout->setSpacing(350);
    getLayout->setContentsMargins(70, 0, 0, 0);

    QHBoxLayout *infoLayout = new QHBoxLayout();
    infoLayout->addWidget(ungetLabel);
    infoLayout->addWidget(infoLabel);
    infoLayout->setSpacing(50);
    infoLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *ungetLayout = new QHBoxLayout();
    ungetLayout->addStretch();
    ungetLayout->addWidget(clickGetLabel);
    ungetLayout->addWidget(tipIconLabel);
    ungetLayout->addWidget(browserButton);
    ungetLayout->addStretch();
    ungetLayout->setSpacing(0);
    ungetLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();
    bottomLayout->addWidget(onekeyGetButton);
    bottomLayout->setSpacing(0);
    bottomLayout->setContentsMargins(0, 0, 30, 30);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(getLabel);
    mainLayout->addLayout(getLayout);
    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(ungetLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(bottomLayout);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(7, 0, 0, 0);

    this->setLayout(mainLayout);
    this->translateLanguage();

    connect(closeButton, SIGNAL(clicked()), this, SLOT(hide()));
}


MedalWallWidget::~MedalWallWidget()
{

}

void MedalWallWidget::translateLanguage()
{
    closeButton->setToolTip(tr("close"));
    infoLabel->setText(tr("you have got") + QString::number(2, 10) + tr("medal,will become superuser"));
    onekeyGetButton->setText(tr("onekey get"));
}

void MedalWallWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        ismousePress = true;
    }

    movePoint = event->globalPos() - pos();
}

void MedalWallWidget::mouseReleaseEvent(QMouseEvent *)
{
    ismousePress = false;
}

void MedalWallWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(ismousePress)
    {
        QPoint movePos = event->globalPos();
        move(movePos - movePoint);
    }
}

void MedalWallWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);
    painter.drawPixmap(this->rect(), QPixmap(":/MedalWall/bj"));
}
