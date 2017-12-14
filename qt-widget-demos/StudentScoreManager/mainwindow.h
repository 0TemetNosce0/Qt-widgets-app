#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "head.h"
#include "logindialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setUpFirstWidget();
    void setUpEditStudentsWidget();
    void setUpNewStudentsWidget();
    void setUpDetailWidget();

public slots:
    void firstWidgetMove();
    void tableWidgetMove();
    void detailWidgetMove();
    void newWidgetMove();
    void switchWidget();
    void editWidgetFlag();
    void newWidgetFlag();
    void changeFlag();
    void getNewList();
    void setTableInformation();
    void addStudent();
    void saveAndExit();
    void showDetail();
    void deleteStudent();
    void filterStudentns(int classNum);
    void editCell(int r, int c);


private:
    int choice;
    int signInStudent;
    char stuNum[20];
    void readStuInfo();

    int widgetFlag;

    QList<Stu> studentsList;
    Ui::MainWindow *ui;

    QWidget *firstWidget;
    bool inOrOut;
    QToolButton *editStudents;
    QToolButton *newStudents;
    QToolButton *saveAndQuit;

    QWidget *editStudentsWidget;
    bool editWidgetInOut;
    QTableWidget *editStudentsTable;
    QPushButton *changeButton;
    QPushButton *detailButton;
    QPushButton *backButton;
    QPushButton *deleteButton;
    QLabel *selectClass;
    QSpinBox *spinBox;

    QWidget *detailWidget;
    bool detailWidgetInOut;
    QLabel *showNameLabel;
    QLabel *showName;
    QLabel *showNumLabel;
    QLabel *showNum;
    QLabel *showSexLabel;
    QLabel *showSex;
    QLabel *showEnglishLabel;
    QLabel *showEnglish;
    QLabel *showMathLabel;
    QLabel *showMath;
    QLabel *showChineseLabel;
    QLabel *showChinese;
    QLabel *showIDLabel;
    QLabel *showID;
    QLabel *showAddressLabel;
    QLabel *showAddress;
    QLabel *showClassLabel;
    QLabel *showClass;
    QPushButton *backButton3;
    QPushButton *changeInfoButton;

    QWidget *newStudentsWidget;
    bool newWidgetInOut;
    QPushButton  *addStudentButton;
    QPushButton *backButton2;
    QLabel *nameLabel;
    QLabel *numLabel;
    QLabel *sexLabel;
    QLabel *englishLabel;
    QLabel *mathLabel;
    QLabel *chineseLabel;
    QLabel *IDLabel;
    QLabel *addressLabel;
    QLabel *classLabel;
    QLineEdit *nameLineEdit;
    QLineEdit *numLineEdit;
    QLineEdit *sexLineEdit;
    QLineEdit *englishLineEdit;
    QLineEdit *mathLineEdit;
    QLineEdit *chineseLineEdit;
    QLineEdit *IDLineEdit;
    QLineEdit *addressLineEdit;
    QLineEdit *classLineEdit;

};

#endif // MAINWINDOW_H
