#ifndef BUILTINDLG_H
#define BUILTINDLG_H

#include <QDialog>
#include <QtTest>
class QTextEdit;
class QPushButton;
class QWizardPage;
class QComboBox;

class CBuiltinDlg : public QDialog
{
    Q_OBJECT

public:
    CBuiltinDlg(QWidget *parent = 0);
    ~CBuiltinDlg();

private:
    QTextEdit*	    displayTextEdit;
    QPushButton*	colorPushBtn;
    QPushButton*	errorPushBtn;
    QPushButton*	filePushBtn;
    QPushButton*	fontPushBtn;
    QPushButton*	inputPushBtn;
    QPushButton*	pagePushBtn;
    QPushButton*	progressPushBtn;
    QPushButton*	printPushBtn;
    QPushButton*	savefilePushBtn;
    QPushButton*	multifilePushBtn;
    QPushButton*	getDirectory;

    QPushButton *nameButton;
    QPushButton *sexButton;
    QPushButton *ageButton;
    QPushButton *statureButton;

    QPushButton *questionBtn;
    QPushButton *informationBtn;
    QPushButton *warningBtn;
    QPushButton *criticalBtn;
    QPushButton *aboutBtn;
    QPushButton *aboutQtBtn;
    QPushButton *customBtn;

    QPushButton *wizardBtn;
    QComboBox *colorComboBox;
private slots:
    void doPushBtn();
    void slotName();
    void slotSex();
    void slotAge();
    void slotStature();
    void SaveFileName();
    void MultiOpenFile();
    void GettExistingDirectory();

    void slotQuestion();
    void slotInformation();
    void slotWarning();
    void slotCritical();
    void slotAbout();
    void slotAboutQt();
    void slotCustom();

    void slotWizard();
    void slotColor(int index);

private:
    QWizardPage* createFirstPage();
    QWizardPage* createSecondPage();
};

#endif // BUILTINDLG_H
