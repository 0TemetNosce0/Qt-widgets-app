#include "labelsound.h"
#include "ui_labelsound.h"
#include "label.h"

#include <QSound>
#include <QPushButton>
#include <QVBoxLayout>

LabelSound::LabelSound(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LabelSound)
{
    ui->setupUi(this);

    QPushButton* btn = new QPushButton("test sound", this);
    connect(btn, &QPushButton::clicked, this, &LabelSound::playSound);

    Label* text1 = new Label("text1", this);
    Label* text2 = new Label("text2", this);
    Label* text3 = new Label("text3", this);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(text1);
    mainLayout->addWidget(text2);
    mainLayout->addWidget(text3);
    mainLayout->addWidget(btn);

    this->setLayout(mainLayout);
}

LabelSound::~LabelSound()
{
    delete ui;
}

void LabelSound::playSound()
{
    QSound::play(":/Resource/3.wav");
}
