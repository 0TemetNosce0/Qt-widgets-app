#ifndef DIALOG_H
#define DIALOG_H

#include <QFile>
#include <QPrinter>
#include <QByteArray>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataStream>

#include "blowfish.h"
#include "ui_enterKey.h"
#include "ui_AboutPbase.h"

//class EnterKeyDlg -------------------------------------------------------------------
class EnterKeyDlg : public QDialog, private Ui::enterKeyDialog
{
    Q_OBJECT

public:
    EnterKeyDlg(QWidget *parent = 0, QByteArray* k = 0);

private:
    char* keyBytes;

protected:
    QByteArray* key;

protected slots:
    void okkey(void);
    bool loadkey(void);
    bool savekeyas(void);
};
//end class EnterKeyDlg ---------------------------------------------------------------

//class AboutPbaseDlg -----------------------------------------------------------------
class aboutPbaseDlg : public QDialog, private Ui::AboutDialog
{
    Q_OBJECT

public:
    aboutPbaseDlg(QWidget *parent=0);
};
//end class AboutPbaseDlg -------------------------------------------------------------

#endif
