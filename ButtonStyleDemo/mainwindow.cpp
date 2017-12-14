/****************************************************************************
**
** Copyright (C) 2013 Yigit Agabeyli.
**
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    color = "#333";
    border = 2;
    ui->bordThickSlider->setValue(border);

    solid = "#555";
    ui->renkLabel->setPalette(QPalette(QColor(color)));
    ui->renkLabel->setAutoFillBackground(true);

    ui->renkLabel2->setPalette(QPalette(QColor(solid)));
    ui->renkLabel2->setAutoFillBackground(true);

    fontFamily = "MS Shell Dlg 2";
    ui->fontComboBox->setCurrentFont(QFont(fontFamily));
    fontSize = 8;
    ui->fontSizeSlider->setValue(fontSize);
    borderRadius = 11;
    ui->bordRadSlider->setValue(borderRadius);
    padding = 5;

    gradyanType = "qradialgradient";
    bgGrad_cx = 0.3;
    bgGrad_cy = - 0.4;
    bgGrad_fx = 0.3;
    bgGrad_fy = -0.4;

    bgGrad2_cx = 0.4;
    bgGrad2_cy = -0.1;
    bgGrad2_fx = 0.4;
    bgGrad2_fy = -0.1;

    bgGrad_radius = 1.35;
    ui->gRadiusSlider->setValue(bgGrad_radius*100);
    bgGrad_stop0  = "#fff";
    bgGrad_stop11 = "#888";
    bgGrad_stop12 = "#bbb";
    bgGrad_stop13 = "#ddd";
    ui->grenkLabel1->setPalette(QPalette(QColor(bgGrad_stop0)));
    ui->grenkLabel1->setAutoFillBackground(true);

    ui->grenkLabel2->setPalette(QPalette(QColor(bgGrad_stop11)));
    ui->grenkLabel2->setAutoFillBackground(true);

    ui->grenkLabel3->setPalette(QPalette(QColor(bgGrad_stop12)));
    ui->grenkLabel3->setAutoFillBackground(true);

    ui->grenkLabel4->setPalette(QPalette(QColor(bgGrad_stop13)));
    ui->grenkLabel4->setAutoFillBackground(true);
    updateStylesheet();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStylesheet()
{
    styleText = QString(" QPushButton {\ncolor: "
                       +color
                       +";\nborder: "+QString::number(border)
                       +"px solid "+solid
                       +";\nfont: "+QString::number(fontSize)+"pt \""+fontFamily+"\""+
                       +";\nborder-radius: "+QString::number(borderRadius)
                       +"px;\npadding: "+QString::number(padding)
                       +"px;\nbackground: qradialgradient(cx: "+QString::number(bgGrad_cx)
                       +", cy: "+QString::number(bgGrad_cy)
                       +",\nfx: "+QString::number(bgGrad_fx)
                       +", fy: "+QString::number(bgGrad_fy)
                       +",\nradius: "+QString::number(bgGrad_radius)
                       +", stop: 0 "+bgGrad_stop0
                       +", stop: 1 "+bgGrad_stop11
                       +");\nmin-width: 80px;\n}\n\n"+
                       "QPushButton:hover {\nbackground: qradialgradient(cx: "+QString::number(bgGrad_cx)
                       +", cy: "+QString::number(bgGrad_cy)
                       +",\nfx: "+QString::number(bgGrad_fx)
                       +", fy: "+QString::number(bgGrad_fy)
                       +",\nradius: "+QString::number(bgGrad_radius)
                       +", stop: 0 "+bgGrad_stop0
                       +", stop: 1 "+bgGrad_stop12
                       +");\n}\n\n "+
                       "QPushButton:pressed {\nbackground: qradialgradient(cx: "+QString::number(bgGrad2_cx)
                       +", cy: "+QString::number(bgGrad2_cy)
                       +",\nfx: "+QString::number(bgGrad2_fx)
                       +", fy: "+QString::number(bgGrad2_fy)
                       +",\nradius: "+QString::number(bgGrad_radius)
                       +", stop: 0 "+bgGrad_stop0
                       +", stop: 1 "+bgGrad_stop13+");\n}");

    ui->pushButton->setStyleSheet(styleText);
    ui->styleOutput->setText(styleText);
}
QString MainWindow::prependZeros(QString col)
{
    QString rightColor = col;
    while(rightColor.size() < 6)
    {
        rightColor.prepend("0");
    }

    return rightColor;

}
void MainWindow::on_renkButton_clicked()
{
    QColorDialog diag;
    QColor bColor = diag.getColor(QColor(bgGrad_stop0));

    if(bColor.isValid())
    {
        ui->renkLabel->setPalette(bColor);
        ui->renkLabel->setAutoFillBackground(true);
        color = bColor.name();
        updateStylesheet();
    }

}
void MainWindow::on_renkButton2_clicked()
{
    QColorDialog diag;
    QColor bColor = diag.getColor(QColor(bgGrad_stop11));

    if(bColor.isValid())
    {
        ui->renkLabel2->setPalette(bColor);
        ui->renkLabel2->setAutoFillBackground(true);
        solid = bColor.name();
        updateStylesheet();
    }
}

void MainWindow::on_grenkButton1_clicked()
{
    QColorDialog diag;
    QColor bColor = diag.getColor(QColor(bgGrad_stop0));

    if(bColor.isValid())
    {
        ui->grenkLabel1->setPalette(bColor);
        ui->grenkLabel1->setAutoFillBackground(true);
        bgGrad_stop0 = bColor.name();
        updateStylesheet();
    }
}

void MainWindow::on_grenkButton2_clicked()
{
    QColorDialog diag;
    QColor bColor = diag.getColor(QColor(bgGrad_stop11));

    if(bColor.isValid())
    {
        ui->grenkLabel2->setPalette(bColor);
        ui->grenkLabel2->setAutoFillBackground(true);
        bgGrad_stop11 = bColor.name();

        int h,s,v;
        bColor.getHsv(&h,&s,&v);
        s = s/2;
        bColor.setHsv(h,s,v);

        ui->grenkLabel3->setPalette(bColor);
        ui->grenkLabel3->setAutoFillBackground(true);
        bgGrad_stop12 = bColor.name();

        bColor.getHsv(&h,&s,&v);
        s = s/2;
        bColor.setHsv(h,s,v);

        ui->grenkLabel4->setPalette(bColor);
        ui->grenkLabel4->setAutoFillBackground(true);
        bgGrad_stop13 = bColor.name();

        updateStylesheet();
    }

}

void MainWindow::on_grenkButton3_clicked()
{
    QColorDialog diag;
    QColor bColor = diag.getColor(QColor(bgGrad_stop12));

    if(bColor.isValid())
    {
        ui->grenkLabel3->setPalette(bColor);
        ui->grenkLabel3->setAutoFillBackground(true);
        bgGrad_stop12 = bColor.name();
        updateStylesheet();
    }
}


void MainWindow::on_grenkButton4_clicked()
{
    QColorDialog diag;
    QColor bColor = diag.getColor(QColor(bgGrad_stop13));

    if(bColor.isValid())
    {
        ui->grenkLabel4->setPalette(bColor);
        ui->grenkLabel4->setAutoFillBackground(true);
        bgGrad_stop13 = bColor.name();
        updateStylesheet();
    }
}

void MainWindow::on_bordRadSlider_valueChanged(int value)
{
    borderRadius = value;
    updateStylesheet();
}

void MainWindow::on_bordThickSlider_valueChanged(int value)
{
    border = value;
    updateStylesheet();
}

void MainWindow::on_gRadiusSlider_valueChanged(int value)
{
    bgGrad_radius = value / 100.0;
    updateStylesheet();
}

void MainWindow::on_fontComboBox_currentIndexChanged(const QString &arg1)
{
    fontFamily = ui->fontComboBox->currentFont().family();
    updateStylesheet();
}

void MainWindow::on_fontSizeSlider_valueChanged(int value)
{
    fontSize = value;
    updateStylesheet();
}
