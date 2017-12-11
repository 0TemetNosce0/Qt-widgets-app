#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QDockWidget;
class QTextEdit;
class QCalendarWidget;
class QListWidget;
class Form;
class QMenu;
class QAction;

//Ӧ�ó���������
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //���캯��
    MainWindow(QWidget *parent = 0);
    //��������
    ~MainWindow();
private:
    void createmenu();
    void createdock1();
    void createdock2();
    void createdock3();

private:
    //ͣ������1��ͣ������2
    QDockWidget *m_pDockWidget1;
    QDockWidget *m_pDockWidget2;
    QDockWidget *m_pDockWidget3;
    //�����ݲ���
    QTextEdit *m_pTextEdit;
    QCalendarWidget *m_pCale;
    QListWidget *m_pList;
    Form *m_pForm;
    QMenu *m_pFMenu;
    QMenu *m_pVMenu;
    QAction *m_pExit;

};

#endif // MAINWINDOW_H
