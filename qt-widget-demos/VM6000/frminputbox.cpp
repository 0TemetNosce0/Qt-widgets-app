#include "frminputbox.h"
#include "ui_frminputbox.h"
#include "myhelper.h"
#include "iconhelper.h"
#include "myapp.h"

frmInputBox::frmInputBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmInputBox)
{
    ui->setupUi(this);
    this->InitStyle();
}

frmInputBox::~frmInputBox()
{
    delete ui;
}

void frmInputBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void frmInputBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void frmInputBox::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void frmInputBox::InitStyle()
{
    this->setProperty("Form", true);
    //���������ʾ
    myHelper::FormInCenter(this, myApp::DeskWidth, myApp::DeskHeight);
    this->mousePressed = false;
    //���ô������������
    this->setWindowFlags(Qt::FramelessWindowHint);
    //����ͼ������
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    //�����رհ�ť
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

void frmInputBox::SetMessage(QString title)
{
    ui->labInfo->setText(title);
}

void frmInputBox::on_btnOk_clicked()
{
    value = ui->txtValue->text();
    done(1);
    this->close();
}

