#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class LabelBtn;
class WaterWaveBtn;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void showOrHideBtns();

private:
    void showBtns();
    void hideBtns();
    void setBtnsLayout();

private:
    QPixmap		m_OnPixmap;
    QPixmap		m_OffPixmap;
    LabelBtn*	m_SwitchBtn;

private:
    WaterWaveBtn*	m_Btn1;
    WaterWaveBtn*	m_Btn2;
    WaterWaveBtn*	m_Btn3;
    WaterWaveBtn*	m_Btn4;
    WaterWaveBtn*	m_Btn5;
    WaterWaveBtn*	m_Btn6;
    WaterWaveBtn*	m_Btn7;
    WaterWaveBtn*	m_Btn8;

private:
    enum {GAP = 20};
    bool  m_IsOn;

private:
//    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
