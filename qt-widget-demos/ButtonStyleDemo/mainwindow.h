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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_renkButton_clicked();

    void on_renkButton2_clicked();

    void on_grenkButton1_clicked();

    void on_grenkButton2_clicked();

    void on_grenkButton3_clicked();

    void on_grenkButton4_clicked();

    void on_bordRadSlider_valueChanged(int value);

    void on_bordThickSlider_valueChanged(int value);

    void on_gRadiusSlider_valueChanged(int value);

    void on_fontComboBox_currentIndexChanged(const QString &arg1);

    void on_fontSizeSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QString styleText;
    QString color;
    int border;
    QString solid;
    int borderRadius;
    int padding;

    double bgGrad_x1;
    double bgGrad_x2;
    double bgGrad_y1;
    double bgGrad_y2;

    double bgGrad_cx;
    double bgGrad_cy;
    double bgGrad_fx;
    double bgGrad_fy;

    double bgGrad2_cx;
    double bgGrad2_cy;
    double bgGrad2_fx;
    double bgGrad2_fy;
    float bgGrad_radius;
    QString bgGrad_stop0;
    QString bgGrad_stop11;
    QString bgGrad_stop12;
    QString bgGrad_stop13;
    QString fontFamily;
    QString gradyanType;
    QString gradyanString;
    int fontSize;
    void updateStylesheet();
    QString prependZeros(QString);
};

#endif // MAINWINDOW_H
