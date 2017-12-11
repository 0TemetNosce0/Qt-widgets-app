#include "extensiondlg.h"
#include "ui_extensiondlg.h"

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDialogButtonBox>

extensiondlg::extensiondlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::extensiondlg)
{
    ui->setupUi(this);

    setWindowTitle(QStringLiteral("Extension Dialog"));

    createBaseInfo();
    createDetailInfo();

    QVBoxLayout *layout =new QVBoxLayout(this);                 //布局
    layout->addWidget(baseWidget);
    layout->addWidget(detailWidget);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(10);
}

extensiondlg::~extensiondlg()
{
    delete ui;
}

void extensiondlg::createBaseInfo()
{
    baseWidget = new QWidget;

    QLabel *nameLabel = new QLabel(QStringLiteral("姓名："));
    QLineEdit *nameLineEdit = new QLineEdit;

    QLabel *sexLabel = new QLabel(QStringLiteral("性别："));
    QComboBox *sexComboBox = new  QComboBox;
    sexComboBox->insertItem(0,QStringLiteral("女"));
    sexComboBox->insertItem(1,QStringLiteral("男"));

    QGridLayout *LeftLayout = new QGridLayout;
    LeftLayout->addWidget(nameLabel,0,0);
    LeftLayout->addWidget(nameLineEdit,0,1);
    LeftLayout->addWidget(sexLabel);
    LeftLayout->addWidget(sexComboBox);

    QPushButton *oKBtn = new QPushButton(QStringLiteral("确定"));
    QPushButton *detailBtn = new QPushButton(QStringLiteral("详细"));
    QDialogButtonBox *btnBox = new QDialogButtonBox(Qt::Vertical);
    btnBox->addButton(oKBtn,QDialogButtonBox::ActionRole);
    btnBox->addButton(detailBtn,QDialogButtonBox::ActionRole);

    QHBoxLayout *mainLayout = new QHBoxLayout(baseWidget);
    mainLayout->addLayout(LeftLayout);
    mainLayout->addWidget(btnBox);
    connect(detailBtn,SIGNAL(clicked()),this,SLOT(showDetailInfo()));
}

void extensiondlg::createDetailInfo()
{
    detailWidget = new QWidget;

    QLabel *ageLabel = new QLabel(QStringLiteral("年龄："));
    QLineEdit *ageLineEdit = new QLineEdit;
    ageLineEdit->setText(QStringLiteral("30"));

    QLabel *departmentLabel = new QLabel(QStringLiteral("部门："));
    QComboBox *departmentComBox = new QComboBox;
    departmentComBox->addItem(QStringLiteral("部门1"));
    departmentComBox->addItem(QStringLiteral("部门2"));
    departmentComBox->addItem(QStringLiteral("部门3"));
    departmentComBox->addItem(QStringLiteral("部门4"));

    QLabel *emailLabel = new QLabel(QStringLiteral("email："));
    QLineEdit *emailLineEdit = new QLineEdit;

    QGridLayout *mainLayout = new QGridLayout(detailWidget);
    mainLayout->addWidget(ageLabel,0,0);
    mainLayout->addWidget(ageLineEdit,0,1);
    mainLayout->addWidget(departmentLabel,1,0);
    mainLayout->addWidget(departmentComBox,1,1);
    mainLayout->addWidget(emailLabel,2,0);
    mainLayout->addWidget(emailLineEdit,2,1);

    detailWidget->hide();
}

void extensiondlg::showDetailInfo()
{
    if(detailWidget->isHidden())
        detailWidget->show();
    else
        detailWidget->hide();
}
