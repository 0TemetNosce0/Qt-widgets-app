// File pbase.h
// Application 2Pnotes 2.0.5

#ifndef PBASE_H
#define PBASE_H

#include <stdio.h>      // printf()

#include <QtDebug>
#include <QCloseEvent> //need by event handle
#include <QByteArray>
#include <QPainter>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QPageSetupDialog>
#include <QPrintPreviewDialog>
#include <QClipboard>
#include <QEvent>
#include <QSettings>
#include <QFont>
#include <QFontMetrics>
#include <QFontDatabase>
#include <QFontDialog>
#include <QList>
#include <QStringList>
#include <QFileInfo>
#include <QDateTime>
#include "ui_pbase.h"
#include "mmgmt.h"
#include "blowfish.h"
#include "pbasedialog.h"
#include "rcsettings.h"
#include "md5class.h"
#include "text2printer.h"

#define FILEVERSION_MAJOR   0X01
#define FILEVERSION_MINOR   0X00

class pbase : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    pbase(QWidget *parent=0);
    ~pbase();

    mmgmt* mem;
    int index;
    char *filelabel;

    QFont appFont;
    void activateFont(QFont f);

private:
    bool fbmEdit;       //Flag, if true indicates record exists else a new record.
    bool fkeyChd;
    bool showTooltips;
    bool rmIsSelected;
    QString sRemarkOld;
    QString sCurrentFile;
    QString clipboardText;
    QByteArray* baPbaseKey;
    QByteArray* baOldPbaseKey;
    QPrinter* selectedPrinter;
    QClipboard* clipboard;
    aboutPbaseDlg* pbdlg;
    EnterKeyDlg *keydlg;

    void clearAll(void);
    void updateListWidget(int index);
    void disableWidgets(bool disable);
    bool loadfile(void);
    char* readfile(const QString& path, int* l);
    bool decodeData(char* d, int l);
    bool writeDecodedData2Memory_v01(char* d);
    bool write2file_v01(const QString& path);
    unsigned int copyByte(char *dest, char *src, uint cb, uint pos);
    QString getPathfromResource(QByteArray* key);
    QString getCurrentFileName(void);
    bool writePathtoResource(QByteArray* key, QString path);
    void bin2hexString(char* hex, char* byte, int l);
    void hexString2bin(char* hex, char* byte);
    void closeEvent( QCloseEvent* event );
    void getPrinterData(QPrinter* pr);
    int getMaxPageNum(QPrinter *pr);
    bool eventFilter(QObject *obj, QEvent *ev);
    void test4olderVersion(void);

private slots:
    void newFile(void);
    void addRecord(void);
    void delRecord(void);
    void bmTextChanged(QString);
    void bmChanged(void);
    void pwTextChanged(QString);
    void pwChanged(void);
    void showActiveRecord(int r);
    void rmTextChanged(void);
    void rmhasSelection(bool);
    void openFile(void);
    bool saveFile(void);
    bool saveAs(void);
    void setupPage(void);
    void previewPage(void);
    void printWithDialog(void);
    void printCurrentRecord(void);
    void printoutData(QPrinter *pr);
    void closeFile(void);
    void changeKey(void);
    void selectFont(void);
    void enableToolTips(void);
    void aboutPbase(void);
    void enablePaste(void);
    void cutText(void);
    void copyText(void);
    void pasteText(void);
    void enableCutCopy(bool b = false);
};

#endif
