#include "labelbtn.h"
#include "mainwindow.h"
#include "waterwavebtn.h"

#include <QLabel>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    m_OnPixmap = QPixmap(":/Resource/on.png");
    m_OffPixmap = QPixmap(":/Resource/off.png");

    m_Btn1 = new WaterWaveBtn(":/Resource/1.png",this);//所有btn的Png(1.png...8.png)大小必须相同;
    m_Btn2 = new WaterWaveBtn(":/Resource/2.png",this);
    m_Btn3 = new WaterWaveBtn(":/Resource/3.png",this);
    m_Btn4 = new WaterWaveBtn(":/Resource/4.png",this);
    m_Btn5 = new WaterWaveBtn(":/Resource/5.png",this);
    m_Btn6 = new WaterWaveBtn(":/Resource/6.png",this);
    m_Btn7 = new WaterWaveBtn(":/Resource/7.png",this);
    m_Btn8 = new WaterWaveBtn(":/Resource/8.png",this);

    m_IsOn = false;
    m_SwitchBtn = new LabelBtn(":/Resource/off.png", ":/Resource/onoff.wav", this);
    m_SwitchBtn->move((width() - m_SwitchBtn->width())/2,(height() - m_SwitchBtn->height())/2);

    this->hideBtns();

    connect(m_SwitchBtn, SIGNAL(clicked()), this, SLOT(showOrHideBtns()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    m_SwitchBtn->move(width()/2 - m_SwitchBtn->width()/2, height()/2 - m_SwitchBtn->height()/2);
    this->setBtnsLayout();
    QWidget::resizeEvent(event);
}

void MainWindow::showOrHideBtns()
{
    m_IsOn = !m_IsOn;
    if(m_IsOn)
    {
        m_SwitchBtn->setPixmap(m_OnPixmap);
        this->showBtns();
    }
    else
    {
        m_SwitchBtn->setPixmap(m_OffPixmap);
        this->hideBtns();
    }
}

void MainWindow::showBtns()
{
    m_Btn1->show();
    m_Btn2->show();
    m_Btn3->show();
    m_Btn4->show();
    m_Btn5->show();
    m_Btn6->show();
    m_Btn7->show();
    m_Btn8->show();
}

void MainWindow::hideBtns()
{
    m_Btn1->hide();
    m_Btn2->hide();
    m_Btn3->hide();
    m_Btn4->hide();
    m_Btn5->hide();
    m_Btn6->hide();
    m_Btn7->hide();
    m_Btn8->hide();
}

void MainWindow::setBtnsLayout()
{
    int btnR = m_Btn1->width()/2;
    int r = (m_SwitchBtn->width()/2 + btnR + GAP);
    int d = (int)(r*0.7071);
    QPoint centerPos(m_SwitchBtn->geometry().x()+m_SwitchBtn->width()/2,m_SwitchBtn->geometry().y()+m_SwitchBtn->height()/2);

    m_Btn1->move(centerPos.x()-btnR,centerPos.y()-r-btnR);
    m_Btn3->move(centerPos.x()+r-btnR,centerPos.y()-btnR);
    m_Btn5->move(centerPos.x()-btnR,centerPos.y()+r-btnR);
    m_Btn7->move(centerPos.x()-r-btnR,centerPos.y()-btnR);

    m_Btn2->move(centerPos.x()+d-btnR,centerPos.y()-d-btnR);
    m_Btn4->move(centerPos.x()+d-btnR,centerPos.y()+d-btnR);
    m_Btn6->move(centerPos.x()-d-btnR,centerPos.y()+d-btnR);
    m_Btn8->move(centerPos.x()-d-btnR,centerPos.y()-d-btnR);
}
