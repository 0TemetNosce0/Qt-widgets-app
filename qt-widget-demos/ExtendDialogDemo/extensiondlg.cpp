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

    QVBoxLayout *layout =new QVBoxLayout(this);                 //����
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

    QLabel *nameLabel = new QLabel(QStringLiteral("������"));
    QLineEdit *nameLineEdit = new QLineEdit;

    QLabel *sexLabel = new QLabel(QStringLiteral("�Ա�"));
    QComboBox *sexComboBox = new  QComboBox;
    sexComboBox->insertItem(0,QStringLiteral("Ů"));
    sexComboBox->insertItem(1,QStringLiteral("��"));

    QGridLayout *LeftLayout = new QGridLayout;
    LeftLayout->addWidget(nameLabel,0,0);
    LeftLayout->addWidget(nameLineEdit,0,1);
    LeftLayout->addWidget(sexLabel);
    LeftLayout->addWidget(sexComboBox);

    QPushButton *oKBtn = new QPushButton(QStringLiteral("ȷ��"));
    QPushButton *detailBtn = new QPushButton(QStringLiteral("��ϸ"));
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

    QLabel *ageLabel = new QLabel(QStringLiteral("���䣺"));
    QLineEdit *ageLineEdit = new QLineEdit;
    ageLineEdit->setText(QStringLiteral("30"));

    QLabel *departmentLabel = new QLabel(QStringLiteral("���ţ�"));
    QComboBox *departmentComBox = new QComboBox;
    departmentComBox->addItem(QStringLiteral("����1"));
    departmentComBox->addItem(QStringLiteral("����2"));
    departmentComBox->addItem(QStringLiteral("����3"));
    departmentComBox->addItem(QStringLiteral("����4"));

    QLabel *emailLabel = new QLabel(QStringLiteral("email��"));
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
