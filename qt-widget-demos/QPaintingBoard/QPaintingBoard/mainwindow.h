#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintarea.h"
#include <QScrollArea>
#include <QComboBox>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void doNew();    //新建文件操作
    void doOpen();   //打开文件操作
    bool doFileSave();   //保存文件操作
    bool doFileSaveAs();   //文件另存为操作

    void creatColorComboBox(QComboBox *comboBox);  //构建颜色组合框

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    PaintArea *area;
    QScrollArea *scrollArea;

    bool isSaved;   //标志文件是否保存过
    QString curFile;  //保存当前文件的路径
    bool maybeSave();   //是否保存文件

    bool saveFile(QString fileName);   //实现文件的存储


private slots:
    void on_brushColorComboBox_currentIndexChanged(int index);
    void on_penColorComboBox_currentIndexChanged(int index);
    void on_penWidthSpinBox_valueChanged(int );
    void on_penStyleComboBox_currentIndexChanged(QString );
    void on_shapeComboBox_currentIndexChanged(QString );
    void on_action_11_triggered();
    void on_action_10_triggered();
    void on_action_8_triggered();
    void on_action_7_triggered();
    void on_action_6_triggered();
    void on_action_5_triggered();
    void on_action_4_triggered();
    void on_action_P_triggered();
    void on_action_X_triggered();
    void on_action_A_triggered();
    void on_action_S_triggered();
    void on_action_O_triggered();
    void on_action_N_triggered();
};

#endif // MAINWINDOW_H
