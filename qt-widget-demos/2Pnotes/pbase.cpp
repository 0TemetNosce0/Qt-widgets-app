// File pbase.cpp
// Application 2Pnotes 2.0.5

#include <QApplication>
#include <string>
#include "pbase.h"

extern QString path2me; //absolute path to this application
extern QString myName;      //name of this application
extern bool fileChanged;

#include "filereadwrite.cpp"

pbase::pbase(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    
    mem = new mmgmt;
    baPbaseKey = new QByteArray();
    baOldPbaseKey = new QByteArray();
    sCurrentFile.clear();
    clipboardText.clear();
    
    showTooltips = true;
    bool found;
    
    // if this application runs for the 1st time, check for
    // existing rc-files of older versions

    test4olderVersion();
    // create a printer object for this application
    // set to the default system printer (if exists)
    selectedPrinter = new QPrinter(QPrinter::HighResolution);
    // get the last used printer settings
    getPrinterData(selectedPrinter);

    filelabel = new char[10];
    strcpy(filelabel, "pbasefile");
    
    clipboard = QApplication::clipboard();
    
    index = 0;
    fileChanged = false;
    fbmEdit = false;
    fkeyChd = false;
    pbdlg = 0;
    rmIsSelected = false;

    connect(actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(actionSave_as, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(actionPage_Setup, SIGNAL(triggered()), this, SLOT(setupPage()));
    connect(actionPrint_Pre_View, SIGNAL(triggered()), this, SLOT(previewPage()));
    connect(actionPrint, SIGNAL(triggered()), this, SLOT(printWithDialog()));
    connect(actionPrintRecord, SIGNAL(triggered()), this, SLOT(printCurrentRecord()));
    connect(actionClose, SIGNAL(triggered()), this, SLOT(closeFile()));
    connect(actionNew_Record, SIGNAL(triggered()), this, SLOT(addRecord()));
    connect(action_delRecord, SIGNAL(triggered()), this, SLOT(delRecord()));
    connect(action_cut, SIGNAL(triggered()), this, SLOT(cutText()));
    connect(actionC_opy, SIGNAL(triggered()), this, SLOT(copyText()));
    connect(action_paste, SIGNAL(triggered()), this, SLOT(pasteText()));
    connect(actionChange_Key, SIGNAL(triggered()), this, SLOT(changeKey()));
    connect(action_Fonts, SIGNAL(triggered()), this, SLOT(selectFont()));
    connect(actionEnable_ToolTips, SIGNAL(triggered()), this, SLOT(enableToolTips()));
    connect(action_About, SIGNAL(triggered()), this, SLOT(aboutPbase()));
    connect(actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(actionE_xit, SIGNAL(triggered()), this, SLOT(close()));
    connect(bookmark, SIGNAL(textEdited(QString)), this, SLOT(bmTextChanged(QString)));
    connect(bookmark, SIGNAL(editingFinished()), this, SLOT(bmChanged()));
    connect(bookmark, SIGNAL(selectionChanged()), this, SLOT(enableCutCopy()));
    connect(password, SIGNAL(textEdited(QString)), this, SLOT(pwTextChanged(QString)));
    connect(password, SIGNAL(editingFinished()), this, SLOT(pwChanged()));
    connect(password, SIGNAL(selectionChanged()), this, SLOT(enableCutCopy()));
    connect(listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(showActiveRecord(int)));
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(rmTextChanged()));
    connect(textEdit, SIGNAL(copyAvailable(bool)), this, SLOT(rmhasSelection(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)), this, SLOT(enableCutCopy(bool)));
    connect(clipboard, SIGNAL(dataChanged()), this, SLOT(enablePaste()));

    //filter for TooTips on/off
    toolBar->widgetForAction(actionNew)->installEventFilter(this);
    toolBar->widgetForAction(actionOpen)->installEventFilter(this);
    toolBar->widgetForAction(actionSave)->installEventFilter(this);
    toolBar->widgetForAction(actionPrintRecord)->installEventFilter(this);
    toolBar->widgetForAction(actionNew_Record)->installEventFilter(this);
    toolBar->widgetForAction(action_delRecord)->installEventFilter(this);
    toolBar->widgetForAction(action_cut)->installEventFilter(this);
    toolBar->widgetForAction(actionC_opy)->installEventFilter(this);
    toolBar->widgetForAction(action_paste)->installEventFilter(this);
    toolBar->widgetForAction(actionE_xit)->installEventFilter(this);

    listWidget->installEventFilter(this);
    textEdit->installEventFilter(this);
    bookmark->installEventFilter(this);
    password->installEventFilter(this);
    
    rcSettings rc(myName);
    
    rc.rcReadNumValue(&found, "global", "user_tooltips");

    if(found)
    {
        showTooltips = (bool)rc.rcReadNumValue(&found, "global", "user_tooltips");
        //tooltips are off
        if(!showTooltips)
        {
            actionEnable_ToolTips->setChecked(false);
        }
    }
    
    rc.rcReadNumValue(&found, "global", "main_widget_width");

    if(found)      // get last position and size from rc file
    {
        resize(QSize((int)rc.rcReadNumValue(&found, "global", "main_widget_width"),
                     (int)rc.rcReadNumValue(&found, "global", "main_widget_height")));
        move(QPoint((int)rc.rcReadNumValue(&found, "global", "main_widget_pos_x"),
                    (int)rc.rcReadNumValue(&found, "global", "main_widget_pos_y")));
    }
    
    // get font from ressource file
    rc.rcReadStrValue(&found, "global", "user_font_family");

    if(found)
    {
        appFont = QFont(rc.rcReadStrValue(&found, "global", "user_font_family"),
                        (int)rc.rcReadNumValue(&found, "global", "user_font_point"),
                        (int)rc.rcReadNumValue(&found, "global", "user_font_weight"),
                        (bool)rc.rcReadNumValue(&found, "global", "user_font_italic"));
    }
    else
    {
        appFont=QFont("Helvetica", 11, QFont::Normal);
    }

    activateFont(appFont);
    
    disableWidgets(true);

#ifdef Q_OS_WIN32
    setWindowTitle("2Pnotes V 2.0.5 W32 - Protect your Private notes");
#endif
}

pbase::~pbase()
{
    delete mem;
    delete baPbaseKey;
    delete baOldPbaseKey;
    delete filelabel;
    delete selectedPrinter;
}

//----------------------------------------------------------------------------
//Event Handler
bool pbase::eventFilter(QObject *obj, QEvent *ev)
{
    if(ev->type() == QEvent::ToolTip)
    {
        if(!showTooltips)   //break event processing, tooltips are hidden
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    //deselect any selection in the textEdit widget
    if(obj == textEdit)
    {
        if(ev->type() == QEvent::FocusOut)
        {
            if(rmIsSelected)
            {
                QString s=textEdit->toPlainText();
                textEdit->clear();
                textEdit->setPlainText(s);
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
    //return QMainWindow::eventFilter(obj, ev);
}

void pbase::closeEvent(QCloseEvent* event)        //Event handler
{
    // Call here all Functions, you want to proceed
    // before application terminates.
    bool acceptEv = true;
    
    rcSettings rc(myName);
    rc.rcSetNumValue("global", "main_widget_width", (long)width());
    rc.rcSetNumValue("global", "main_widget_height", (long)height());
    rc.rcSetNumValue("global", "main_widget_pos_x", (long)x());
    rc.rcSetNumValue("global", "main_widget_pos_y", (long)y());

    
    if(fileChanged)
    {
        int choice;
        
        choice = QMessageBox::question(this, tr("2Pnotes - save file?"),
                                       tr("You have changed the current file. Save it?"),
                                       QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                       QMessageBox::Yes);
        
        switch(choice)
        {
        case QMessageBox::Yes:
        {
            if(saveFile())
            {
                QMessageBox::information(this, tr("2Pnotes - save file"),
                                         tr("File successfully saved."),
                                         QMessageBox::Yes, QMessageBox::Yes);
            }
            else
            {
                acceptEv=false;
            }
            break;
        }
        case QMessageBox::Cancel:
        {
            acceptEv = false;
        }
        }
    }
    else
    {
        if(!sCurrentFile.isEmpty() & !baPbaseKey->isEmpty())
        {
            writePathtoResource(baPbaseKey, sCurrentFile);
        }
    }

    if(acceptEv)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

//End Event Handler
//----------------------------------------------------------------------------


void pbase::newFile(void)
{
    bool saved = true;

    //ensure that the last changes are hold in memory
    if(!mem->listIsEmpty())
    {
        bmChanged();
        pwTextChanged(QString());
        rmTextChanged();
    }
    
    if(fileChanged)
    {
        int choice;
        
        choice = QMessageBox::question(this, tr("2Pnotes - save file?"),
                                       tr("You have changed the current file. Save it?"),
                                       QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                       QMessageBox::Yes);
        
        switch(choice)
        {
        case QMessageBox::Yes:
        {
            if(saveFile())
            {
                clearAll();
            }
            else
            {
                saved = false;
            }

            break;
        }
        case QMessageBox::No:
        {
            clearAll();
            break;
        }
        case QMessageBox::Cancel:
        {
            saved = false;
            break;
        }
        }
    }
    else
    {
        clearAll();
    }

    if(saved)
    {
        addRecord();
        fileChanged = true;
        if(!actionSave->isEnabled())
        {
            actionSave->setEnabled(true);
        }
    }
}

void pbase::openFile(void)
{
    int cancel = false;
    //ensure that the last changes are hold in memory
    if(!mem->listIsEmpty())
    {
        bmChanged();
        pwTextChanged(QString());
        rmTextChanged();
    }

    //is the current file saved?
    if(fileChanged)
    {
        int choice;
        
        choice = QMessageBox::question(this, tr("2Pnotes - open file?"),
                                       tr("You have changed the current file. Save it?"),
                                       QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                       QMessageBox::Yes);
        
        switch(choice)
        {
        case QMessageBox::Yes:
        {
            if(!saveFile())
            {
                cancel = true;
            }
            else
            {
                clearAll();
            }

            break;
        }
        case QMessageBox::Cancel:
        {
            cancel=true;
            break;
        }
        default:
            clearAll();
        }
    }
    
    if(!cancel)
    {
        keydlg = new EnterKeyDlg(this, baPbaseKey);
        delete keydlg;

        if(!baPbaseKey->isEmpty())
        {
            QString p = getPathfromResource(baPbaseKey);

            if(p.isEmpty())
            {
                p = QFileDialog::getOpenFileName(this, tr("2Pnotes - open file"), QDir::homePath());
                //workaround to delete the automatic saving of the selected path
                //by the QFileDialog class. It deletes all selected paths of all Qt
                //applications used by this user. Parts of the code is extracted
                //from the file qfiledialog.cpp of the qt sources
                QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
                settings.beginGroup(QLatin1String("Qt"));
                settings.remove("filedialog");
                settings.endGroup();
            }
            else
            {
                if(!QFile::exists(p))
                {
                    //the pairing of the key and the path in the rc-file is invalid.
                    //delete invalid value
                    md5class md5;
                    QString pw = pw.fromUtf8(baPbaseKey->data());
                    QByteArray ba_md5PbaseKey = md5.md5FromStr(&pw);
                    pw.clear();
                    pw = ba_md5PbaseKey;
                    rcSettings rc(myName);
                    rc.rcdelVariable("data", pw);

                    p = QFileDialog::getOpenFileName(this, tr("2Pnotes - open file"), QDir::homePath());
                }
            }

            if(!p.isNull())
            {
                char *d;
                int l;
                //open the file
                d = readfile(p, &l); //array d must be deleted using the delete operator
                if(d!=0)
                {
                    if(decodeData(d, l))
                    {
                        if(writeDecodedData2Memory_v01(d))
                        {
                            index=0;
                            sCurrentFile.clear();
                            sCurrentFile=p;
                            listWidget->setCurrentRow(index);
                            showActiveRecord(index);
                            fileChanged=false;
                            if(actionSave->isEnabled())
                            {
                                actionSave->setEnabled(false);
                            }
                        }
                    }
                    delete d;

                    if(!bookmark->isEnabled())
                    {
                        disableWidgets(false);
                    }

                    bookmark->setFocus();
                }
            }
        }
    }
}

bool pbase::saveFile(void)
{
    if(!sCurrentFile.isEmpty())
    {
        //ensure that the last changes are hold in memory
        bmChanged();
        pwTextChanged(QString());
        rmTextChanged();

        if(write2file_v01(sCurrentFile))
        {
            fileChanged = false;
            if(actionSave->isEnabled())
            {
                actionSave->setEnabled(false);
            }

            if(fkeyChd) //delete old data in the resourcefile
            {
                md5class md5;
                QString p=p.fromUtf8(baOldPbaseKey->data());
                QByteArray ba_md5PbaseKey=md5.md5FromStr(&p);
                p.clear();
                p = ba_md5PbaseKey;
                rcSettings rc(myName);
                rc.rcdelVariable("data", p);
                fkeyChd = false;
            }
            
            writePathtoResource(baPbaseKey, sCurrentFile);
            return true;
        }
    }
    else
    {
        if(saveAs())
        {
            return true;
        }
    }

    return false;
}

bool pbase::saveAs(void)    //Slot
{
    //ensure that the last changes are hold in memory
    bmChanged();
    pwTextChanged(QString());
    rmTextChanged();

    if(baPbaseKey->isEmpty())
    {
        keydlg=new EnterKeyDlg(this, baPbaseKey);
        delete keydlg;
        fkeyChd=true;
    }

    if(!baPbaseKey->isEmpty()) //EnterKeyDlg exits with valid key
    {
        int choice;
        QString p;

        p = QFileDialog::getSaveFileName(this, tr("2Pnotes - save file as ..."),
                                         QDir::homePath(), "", 0, QFileDialog::DontConfirmOverwrite);

        if(!p.isNull())
        {
            if(!QFile::exists(p))
            {
                if(!fkeyChd) //new path and filename selected using the same key
                {
                    choice = QMessageBox::question(this, tr("2Pnotes - save file as ..."),
                                                   tr("This software uses a link between the path, filename and the key.\n"
                                                      "The principle is simple: One key for each file.\n"
                                                      "Saving now makes it nearly impossible for you to open the old file.\n"
                                                      "It is recommended to change first the key for this file before saving!\n\n"
                                                      "Do you want to change the key?\n"
                                                      "Using the 'No' button saves this file without changing the key!\n"),
                                                   QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                                   QMessageBox::Yes);
                    
                    if(choice == QMessageBox::Yes)
                    {
                        changeKey();
                    }

                    if(choice==QMessageBox::Cancel)
                    {
                        return false;
                    }
                }

                if(write2file_v01(p))
                {
                    fileChanged = false;
                    if(actionSave->isEnabled())
                    {
                        actionSave->setEnabled(false);
                    }

                    if(fkeyChd)  //delete old data in the resourcefile
                    {
                        md5class md5;
                        QString k = k.fromUtf8(baOldPbaseKey->data());
                        QByteArray ba_md5PbaseKey = md5.md5FromStr(&k);
                        k.clear();
                        k = ba_md5PbaseKey;
                        rcSettings rc(myName);
                        rc.rcdelVariable("data", k);
                        fkeyChd = false;
                    }
                    //save path and filename for later use
                    sCurrentFile = p;

                    writePathtoResource(baPbaseKey, p);
                    return true;
                }
            }
            else
            {
                choice = QMessageBox::question(this, tr("2Pnotes - save file as ..."),
                                               tr("File already exists.\nOverwrite?"),
                                               QMessageBox::No|QMessageBox::Yes,
                                               QMessageBox::No);

                if(choice == QMessageBox::Yes)
                {
                    if(write2file_v01(p))
                    {
                        fileChanged=false;
                        if(actionSave->isEnabled())
                        {
                            actionSave->setEnabled(false);
                        }

                        if(fkeyChd)  //delete old data in the resourcefile
                        {
                            md5class md5;
                            QString k=k.fromUtf8(baOldPbaseKey->data());
                            QByteArray ba_md5PbaseKey=md5.md5FromStr(&k);
                            k.clear();
                            k=ba_md5PbaseKey;
                            rcSettings rc(myName);
                            rc.rcdelVariable("data", k);
                        }

                        //save path and filename for later use
                        sCurrentFile=p;

                        writePathtoResource(baPbaseKey, p);
                        fkeyChd=false;
                        return true;
                    }
                }
            }
        }
    }
    fkeyChd=false;
    return false;
}

void pbase::setupPage(void)     //Slot
{
    qreal l, t, r, b;
    rcSettings rc(myName);

    QPageSetupDialog pagedlg(selectedPrinter, this);

    if(pagedlg.exec() == QDialog::Accepted)
    {
        selectedPrinter->getPageMargins(&l, &t, &r, &b, QPrinter::DevicePixel);
        // save settings to the resource file
        rc.rcSetNumValue("print", "leftMargin", static_cast<long>(l+0.5));
        rc.rcSetNumValue("print", "topMargin", static_cast<long>(t+0.5));
        rc.rcSetNumValue("print", "rightMargin", static_cast<long>(r+0.5));
        rc.rcSetNumValue("print", "bottomMargin", static_cast<long>(b+0.5));
        rc.rcSetNumValue("print", "paperSize", (long)selectedPrinter->paperSize());
        rc.rcSetNumValue("print", "orientation", (long)selectedPrinter->orientation());
    }
}

void pbase::previewPage(void)       //Slot
{
    QPrintPreviewDialog preview(selectedPrinter, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printoutData(QPrinter*)));
    preview.exec();
    disconnect(&preview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printoutData(QPrinter*)));
}

void pbase::printWithDialog(void)       //Slot
{
    int n;

    QPrintDialog printdlg(selectedPrinter, this);
    //find out the number of pages to be used to print out all data
    n=getMaxPageNum(selectedPrinter);
    printdlg.setFromTo(1, n);
    printdlg.setMinMax(1, n);
    printdlg.setEnabledOptions(printdlg.enabledOptions() & ~QPrintDialog::PrintCollateCopies);
    printdlg.setEnabledOptions(printdlg.enabledOptions() & ~QAbstractPrintDialog::PrintShowPageSize);
    
    if(printdlg.exec() == QDialog::Accepted)
    {
        rcSettings rc(myName);
        rc.rcSetStrValue("print", "last_selected_printer", selectedPrinter->printerName());
        
        //Only for testing the print routine
        //selectedPrinter->setOutputFormat(QPrinter::PdfFormat);
        
        printoutData(selectedPrinter);
    }
}

void pbase::printCurrentRecord(void)        //Slot
{
    //uses the last selected printer
    int item;
    QFont currentFont(appFont);
    QPainter paint;
    text2Printer *printtext=NULL;
    //Only for testing the print routine
    //selectedPrinter->setOutputFormat(QPrinter::PdfFormat);
    
    item=listWidget->currentRow();
    selectedPrinter->setPrintRange(QPrinter::AllPages);
    selectedPrinter->setFullPage(true); //if not, the calculation of the margins is incorrect
    selectedPrinter->setDocName(myName+", "+getCurrentFileName());

    //print routine
    if(paint.begin(selectedPrinter))
    {
        printtext=new text2Printer(selectedPrinter, &paint);
        //print filename on the first page
        currentFont.setBold(false);
        printtext->setCurrentFont(currentFont);
        printtext->PrintOut(tr("File name: ")+getCurrentFileName());
        //insert blank line
        printtext->insertBlankLine();
        printtext->PrintOut(tr("Entry# ")+ QString::number(item + 1));
        //print the Bookmark
        currentFont.setBold(true);
        printtext->setCurrentFont(currentFont);
        printtext->PrintOut(tr("Bookmark:"));
        currentFont.setBold(false);
        printtext->setCurrentFont(currentFont);
        printtext->PrintOut(mem->getBookmark(item));
        //insert blank line
        printtext->insertBlankLine();
        //print the Password
        currentFont.setBold(true);
        printtext->setCurrentFont(currentFont);
        printtext->PrintOut(tr("Password:"));
        currentFont.setBold(false);
        printtext->setCurrentFont(currentFont);
        printtext->PrintOut(mem->getPassword(item));
        //insert blank line
        printtext->insertBlankLine();
        //print the Annotations
        currentFont.setBold(true);
        printtext->setCurrentFont(currentFont);
        printtext->PrintOut(tr("Annotations:"));
        currentFont.setBold(false);
        printtext->setCurrentFont(currentFont);
        printtext->PrintOut(mem->getRemarks(item));
        
        paint.end();
    }

    if(printtext)
        delete printtext;
}

void pbase::printoutData(QPrinter *pr)      //Slot
{
    QFont currentFont(appFont);
    QPainter paint;
    text2Printer *printtext=NULL;
    
    //if not, the calculation of the margins is incorrect
#ifndef Q_OS_WIN32
    pr->setFullPage(true);
#else
    pr->setFullPage(false);
#endif
    
    pr->setDocName(myName+", "+getCurrentFileName());

    //print routine
    if(paint.begin(pr))
    {
        printtext=new text2Printer(pr, &paint);
        //print filename on the first page
        currentFont.setBold(false);
        printtext->setCurrentFont(currentFont);
        printtext->PrintOut(tr("File name: ")+getCurrentFileName());

        for(int item=0; item < mem->countOfItems(); item++)
        {
            //insert blank line
            printtext->insertBlankLine();
            printtext->PrintOut(tr("Entry# ")+ QString::number(item + 1));
            //print the Bookmark
            currentFont.setBold(true);
            printtext->setCurrentFont(currentFont);
            printtext->PrintOut(tr("Bookmark:"));
            currentFont.setBold(false);
            printtext->setCurrentFont(currentFont);
            printtext->PrintOut(mem->getBookmark(item));
            //insert blank line
            printtext->insertBlankLine();
            //print the Password
            currentFont.setBold(true);
            printtext->setCurrentFont(currentFont);
            printtext->PrintOut(tr("Password:"));
            currentFont.setBold(false);
            printtext->setCurrentFont(currentFont);
            printtext->PrintOut(mem->getPassword(item));
            //insert blank line
            printtext->insertBlankLine();
            //print the Annotations
            currentFont.setBold(true);
            printtext->setCurrentFont(currentFont);
            printtext->PrintOut(tr("Annotations:"));
            currentFont.setBold(false);
            printtext->setCurrentFont(currentFont);
            printtext->PrintOut(mem->getRemarks(item));
        }
        paint.end();

        if(printtext)
        {
            delete printtext;
        }
    }
}

void pbase::closeFile(void)
{
    if(fileChanged)
    {
        int choice;
        
        choice = QMessageBox::question(this, tr("2Pnotes - save file?"),
                                       tr("You have changed the current file. Save it?"),
                                       QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                       QMessageBox::Yes);
        
        switch(choice)
        {
        case QMessageBox::Yes:
        {
            if(saveFile())
            {
                //clears the memory, the widgets and the key. Resets all flags
                clearAll();
                disableWidgets(true);
            }
            break;
        }
        case QMessageBox::No:
        {
            //clears the memory, the widgets and the key. Resets all flags
            clearAll();
            disableWidgets(true);

            break;
        }
        case QMessageBox::Cancel:
        {
            break;
        }
        }
    }
    else
    {
        if(!sCurrentFile.isEmpty() & !baPbaseKey->isEmpty())
            writePathtoResource(baPbaseKey, sCurrentFile);

        clearAll();
        disableWidgets(true);
    }
}

//End Menu File
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Menu Edit
void pbase::addRecord(void)     //Slot
{
    QString bmText = "";
    QString pwText = "";
    QString remText = "";
    
    fbmEdit = false;
    fileChanged = true;

    if(!actionSave->isEnabled())
    {
        actionSave->setEnabled(true);
    }

    if(!bookmark->isEnabled())
    {
        disableWidgets(false);
    }

    //insert an empty record
    index = mem->insertRecord(&bmText, &pwText, &remText);
    updateListWidget(index);
    bookmark->setFocus();
}

void pbase::delRecord(void) //Slot
{
    if(mem->deleteRecord(index))
    {
        fileChanged=true;
        if(!actionSave->isEnabled())
        {
            actionSave->setEnabled(true);
        }

        updateListWidget(index);
    }
    else
    {
        QMessageBox::information(this, tr("2Pnotes - delete Record"),
                                 tr("The list is empty. Nothing more to delete!"),
                                 QMessageBox::Ok, QMessageBox::Ok);
    }
}

void pbase::enableCutCopy(bool b)   //Slot
{
    //find the active widget
    QWidget* w=focusWidget();
    
    if(w == textEdit)
    {
        action_cut->setEnabled(b);
        actionC_opy->setEnabled(b);
    }
    
    if(w == bookmark)
    {
        action_cut->setEnabled(bookmark->hasSelectedText());
        actionC_opy->setEnabled(bookmark->hasSelectedText());
    }
    
    if(w == password)
    {
        action_cut->setEnabled(password->hasSelectedText());
        actionC_opy->setEnabled(password->hasSelectedText());
    }
}   

void pbase::enablePaste(void)       //Slot
{
    //this slot is called every time if the content of the clipboard has changed
    clipboardText.clear();
    clipboardText=clipboard->text();
    if(!clipboardText.isEmpty())
        action_paste->setEnabled(true);
    else
        action_paste->setEnabled(false);
}

void pbase::cutText(void)
{
    //find the active widget
    QWidget* w=focusWidget();
    
    if(w == bookmark)
        bookmark->cut();

    if(w == password)
        password->cut();

    if(w == textEdit)
        textEdit->cut();

    fileChanged=true;
    if(!actionSave->isEnabled())
        actionSave->setEnabled(true);
}

void pbase::copyText(void)
{
    //find the active widget
    QWidget* w=focusWidget();
    
    if(w == bookmark)
        bookmark->copy();

    if(w == password)
        password->copy();

    if(w == textEdit)
        textEdit->copy();
}

void pbase::pasteText(void) //Slot
{
    //the paste-button is enabled, if there is plain text in the clipboard
    //find the active widget
    QWidget* w=focusWidget();
    
    if(w == bookmark)
        bookmark->paste();

    if(w == password)
        password->paste();

    if(w == textEdit)
        textEdit->paste();

    fileChanged=true;
    if(!actionSave->isEnabled())
        actionSave->setEnabled(true);
}

void pbase::changeKey(void)     //Slot
{
    QByteArray baTemp;
    keydlg=new EnterKeyDlg(this, &baTemp);
    
    if(!baTemp.isNull())
    {
        if(!baOldPbaseKey->isEmpty())
            baOldPbaseKey->clear();
        
        *baOldPbaseKey+=*baPbaseKey;
        baPbaseKey->clear();
        *baPbaseKey+=baTemp;
        fkeyChd=true;
        fileChanged=true;
        if(!actionSave->isEnabled())
            actionSave->setEnabled(true);
    }
    
    delete keydlg;
}

//End Menu Edit
//----------------------------------------------------------------------------- 

// Menu Extra
//----------------------------------------------------------------------------- 

void pbase::selectFont(void)        //Slot
{
    QFontDatabase fdb;
    bool ok;
    
    appFont=QFontDialog::getFont(&ok, qApp->font(), this, tr("Select Font"));
    
    if(ok)
    {
        //test, if the selected font is scalable.
        //non scalable fonts are not printable with this software
        if(!fdb.isScalable(appFont.family(), fdb.styleString(appFont)))
        {
            QMessageBox::information(this, tr("2Pnotes - select font"),
                                     tr("You has selected a non scalable font.\n")+
                                     tr("Cannot calculate pages with a non scalable font!\n")+
                                     tr("Select another font and try again please."),
                                     QMessageBox::Ok, QMessageBox::Ok);
        }
        else
        {
            QFontInfo fi(appFont);
            rcSettings rc(myName);

            activateFont(appFont);      //set new font

            // save changes
            rc.rcSetStrValue("global", "user_font_family", fi.family());
            rc.rcSetNumValue("global", "user_font_point", (long)fi.pointSize());
            rc.rcSetNumValue("global", "user_font_weight", (long)fi.weight());
            rc.rcSetNumValue("global", "user_font_italic", (long)fi.italic());
        }
    }
}

void pbase::enableToolTips(void)        //Slot
{
    //disable or enable the processing the signal QEvent::ToolTip
    //see function eventFilter(QObject *obj, QEvent *ev)
    if(actionEnable_ToolTips->isChecked())
        showTooltips=true;
    else
        showTooltips=false;

    //save state
    rcSettings rc(myName);
    rc.rcSetNumValue("global", "user_tooltips", (long)showTooltips);
}

//End Menu Extra
//----------------------------------------------------------------------------- 


//Menu About
//----------------------------------------------------------------------------- 

void pbase::aboutPbase(void)        //Slot
{
    //create a modal dialog
    pbdlg = new aboutPbaseDlg(this);
    delete pbdlg;
    pbdlg=0;
}

//End Menu About
//----------------------------------------------------------------------------- 

//-----------------------------------------------------------------------------
//Controls for the input widgets

void pbase::disableWidgets(bool disable)
{
    //if disable is true, disables the three widgets bookmark, password and remarks
    //if disable is false, the three widgets will be enabled
    
    bookmark->setDisabled(disable);
    password->setDisabled(disable);
    textEdit->setDisabled(disable);
}

void pbase::bmTextChanged(QString)      //Slot
{
    //bookmark text changed, signal doesn't send if only lost focus or return pressed.
    fbmEdit=true;
    fileChanged=true;
    if(!actionSave->isEnabled())
        actionSave->setEnabled(true);
}

void pbase::bmChanged(void) //Slot
{
    // this signal is send if bookmark has changed. return pressed or lost focus

    QString bmText=bookmark->text();
    QString pwText=password->text();
    QString remText=textEdit->toPlainText();
    
    if(fbmEdit)     //edit bookmark
    {
        index=mem->insertEditedRecord(index, &bmText, &pwText, &remText);
        updateListWidget(index);
        fbmEdit=false;
        fileChanged=true;
        if(!actionSave->isEnabled())
            actionSave->setEnabled(true);
    }
    
    //deselect any selection in the bookmark widget if lost focus
    if(bookmark->hasSelectedText())
        bookmark->deselect();
}

void pbase::pwTextChanged(QString)      //Slot
{
    //password text changed, signal doesn't send if only lost focus or return pressed.
    if(index<0 || index>mem->countOfItems())
        QMessageBox::critical(this, tr("2Pnotes - critical error"),
                              tr("Module pbase.cpp, func pwChanged: index out of range."),
                              QMessageBox::Ok, QMessageBox::Ok);
    else
    {
        QString p=password->text();
        mem->insertString(index, 1, p);

        fileChanged=true;
        if(!actionSave->isEnabled())
            actionSave->setEnabled(true);
    }
    
    /*QString p=password->text();
    mem->insertString(index, 1, p);

    fileChanged=true;
    if(!actionSave->isEnabled())
        actionSave->setEnabled(true);*/
}

void pbase::pwChanged(void) //Slot
{
    // this signal is send if password has changed. return pressed or lost focus
    
    //deselect any selection in the password widget if lost focus
    if(password->hasSelectedText())
        password->deselect();
}

void pbase::rmTextChanged(void) //Slot
{
    //avoid to process some signals, which are not needed
    if(textEdit->hasFocus())
    {
        if((index<0 || index>mem->countOfItems()) && mem->countOfItems()!=0 )
            QMessageBox::critical(this, tr("2Pnotes - critical error"),
                                  tr("Module pbase.cpp, func rmTextChanged(void): index out of range."),
                                  QMessageBox::Ok, QMessageBox::Ok);
        else
        {
            if(!textEdit->toPlainText().isEmpty())
            {
                //the following function overwrites the record.
                mem->insertString(index, 2, textEdit->toPlainText());

                // avoid setting flag 'fileChanged' if the singnal
                // based only on formating text and no changing of the content
                if(sRemarkOld != textEdit->toPlainText())
                {
                    fileChanged=true;
                    if(!actionSave->isEnabled())
                        actionSave->setEnabled(true);
                }
            }
        }
    }
}

void pbase::rmhasSelection(bool y)        //Slot
{
    rmIsSelected=y;
}

void pbase::showActiveRecord(int r)     //Slot
{
    if(listWidget->count()>0 && r>=0)       //listwidget not empty
    {
        bookmark->setText(mem->getBookmark(r));
        password->setText(mem->getPassword(r));
        textEdit->setPlainText(mem->getRemarks(r));
        sRemarkOld=textEdit->toPlainText();
        index=r;
    }
}

void pbase::updateListWidget(int index)
{
    int i, e;
    
    e=mem->countOfItems();
    listWidget->clear();
    
    if(e>0)
    {
        for(i=0; i<e; i++)
            listWidget->addItem(mem->getBookmark(i));

        listWidget->setCurrentRow(index);
    }
}

//End controls for the input widgets
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//miscellaneous functions
void pbase::test4olderVersion(void)
{   
    QString homedir=QDir::toNativeSeparators(QDir::homePath()+'/');
    // check existing rc-files of older versions of 2Pnotes
    if(!QFile::exists(homedir+myName+"rc"))
    {
        //this application runs for the 1st time
        QStringList sList;
        QStringList sListExists;
        int i;
        
        sList<<"2Pnotesrc"<<"2Pnotes-2.0.1rc"<<"2Pnotes-2.0.1.1rc"<<"2Pnotes-2.0.2rc"<<"2Pnotes-2.0.3rc"<<"2Pnotes-2.0.4rc";
        
        for(i=sList.size(); i > 0; i--) //check for latest version first
        {
            if(QFile::exists(homedir+sList.at(i-1)))
                sListExists.append(homedir+sList.at(i-1));
        }
        
        //there is only something to do, if an older rc-file exists
        if(!sListExists.isEmpty())
        {
            // if there are earlier versions
            // find the latest used version.
            QFileInfo fi_1, fi_2;
            int choice;
            int min=0;
            int j=0;
            i=0;

            for(i=0; i<sListExists.size(); i++)
            {
                min=i;
                for(j=i+1; j<sListExists.size(); j++)
                {
                    fi_1.setFile(sListExists.at(j));
                    fi_2.setFile(sListExists.at(min));
                    if(fi_1.lastModified()>fi_2.lastModified())
                        min=j;
                    
                    sListExists.swap(min, j);
                }
            }
            // sListExists.at(sListExists.size()-1) contains now
            // the latest used version of the rc file
            choice=QMessageBox::question(this, tr("2Pnotes - old settings take over"),
                                         tr("Found an earlier version of 2Pnotes.\n"
                                            "Do you want to take over the settings of the earlier version?"),
                                         QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
            
            if(choice==QMessageBox::Yes)
            {
                //only used to create the new rc-file which
                // contains the basic information
                rcSettings rc(myName);
                
                QFile f_old(sListExists.at(sListExists.size()-1));
                
                sList.clear();
                if(f_old.open(QIODevice::ReadOnly))
                {
                    QTextStream r(&f_old);

                    while(!r.atEnd())
                        sList.append(r.readLine()+"\n");

                    f_old.close();
                }
                else
                    QMessageBox::warning(this, tr("2Pnotes - old settings take over"),
                                         tr("Can not open file")+"\n"+sListExists.at(sListExists.size()-1)+"\n"+
                                         tr("Take over fails. Sorry, you must generate the settings again."),
                                         QMessageBox::Ok, QMessageBox::Ok);
                
                if(!sList.isEmpty())
                {
                    QFile f_new(homedir+myName+"rc");
                    int linecount;
                    bool firstfound=false;
                    
                    // find the line with the second group symbol
                    for(linecount=0; linecount< sList.size(); linecount++)
                    {
                        if(sList.at(linecount).contains(":-)"))
                        {
                            if(firstfound)      //found the second entry
                                break;

                            firstfound=true;    //found the private entry
                        }
                    }
                    
                    for(int i=0; i<linecount; i++)
                        sList.removeFirst();
                    
                    if(f_new.open(QIODevice::WriteOnly|QIODevice::Append))
                    {
                        QTextStream r(&f_new);
                        QStringList::iterator it;

                        for(it=sList.begin(); it != sList.end(); ++it)
                            r<<*it;

                        f_new.close();
                    }
                    else
                        QMessageBox::information(this, tr("2Pnotes - old settings take over"),
                                                 tr("Can not copy data into new resource file"),
                                                 QMessageBox::Ok, QMessageBox::Ok);
                }
            }
        }
    }
}

void pbase::activateFont(QFont f)
{
    qApp->setFont(f);
    menubar->setFont(f);
    menu_File->setFont(f);
    menu_Edit->setFont(f);
    menu_extra->setFont(f);
    menu_About->setFont(f);
    label->setFont(f);
    label_2->setFont(f);
    label_3->setFont(f);
    bookmark->setFont(f);
    listWidget->setFont(f);
    password->setFont(f);
    textEdit->setFont(f);
}

void pbase::clearAll(void)
{
    //clears the memory,widgets and the key. Resets all flags
    
    bookmark->clear();
    password->clear();
    textEdit->clear();
    listWidget->clear();
    mem->delAllContent();
    baPbaseKey->clear();
    baOldPbaseKey->clear();
    sCurrentFile.clear();
    index=0;
    fileChanged=false;
    if(actionSave->isEnabled())
        actionSave->setEnabled(false);

    fbmEdit=false;
    fkeyChd=false;
}

bool pbase::writeDecodedData2Memory_v01(char* d)
{
    // char* d include the decoded data of the file
    QByteArray baData;
    int coe, i;
    int counterOfByte_bm, counterOfByte_pw, counterOfByte_rm;
    unsigned int pos;
    char v[2];

    QString *sbm=new QString();
    QString *spw=new QString();
    QString *srm=new QString();

    //check if file is a pbasefile
    if(strncmp(filelabel, d+sizeof(int), strlen(filelabel))!=0)
    {
        QMessageBox::information(this, tr("2Pnotes - open file"),
                                 tr("It is possible, that this is not a pbase file, or \n"
                                    "this file is assigned to another keyword.\n"),
                                 QMessageBox::Ok|QMessageBox::Default);

        delete sbm;
        delete spw;
        delete srm;
        return false;
    }

    //check the file version
    v[0]=*(d+sizeof(int)+strlen(filelabel));
    v[1]=*(d+sizeof(int)+strlen(filelabel)+1);
    //here follows code for work with different
    //file versions. For future use.
    if(!(v[0]==FILEVERSION_MAJOR && v[1]==FILEVERSION_MINOR))
    {
        QMessageBox::information(this, tr("2Pnotes - open file"),
                                 tr("This file needs a recent version of pbase.\nPlease update your pbase."),
                                 QMessageBox::Ok);

        delete sbm;
        delete spw;
        delete srm;
        return false;
    }

    //if there are any data in memory, delete it
    if(!mem->listIsEmpty())
        mem->delAllContent();
    
    //clear Widgets
    bookmark->clear();
    password->clear();
    listWidget->clear();
    textEdit->clear();
    index=0;
    fbmEdit=false;
    

    //code for file version 1.0 (characters are saved as ascii symbols)
    //copy encoded d into the mem-object
    pos=copyByte((char*)&coe, d, sizeof(int), 0);
    pos+=strlen(filelabel)+2;
    for(i=0; i<coe; i++)
    {
        //get the length of the 3 datafields
        pos+=copyByte((char*)&counterOfByte_bm, d+pos, sizeof(int), 0);
        pos+=copyByte((char*)&counterOfByte_pw, d+pos, sizeof(int), 0);
        pos+=copyByte((char*)&counterOfByte_rm, d+pos, sizeof(int), 0);

        //get the data
        baData=QByteArray::fromRawData (d+pos, counterOfByte_bm);
        pos+=counterOfByte_bm;
        *sbm=baData; //uses fromAscii()
        baData.clear();
        baData=QByteArray::fromRawData (d+pos, counterOfByte_pw);
        pos+=counterOfByte_pw;
        *spw=baData; //uses fromAscii()
        baData.clear();
        baData=QByteArray::fromRawData (d+pos, counterOfByte_rm);
        pos+=counterOfByte_rm;
        *srm=baData; //uses fromAscii()
        baData.clear();
        index=mem->insertRecord(sbm, spw, srm);

        //fill the listWidget
        listWidget->insertItem(index, *sbm);

        //make free for the next item
        sbm->clear();
        spw->clear();
        srm->clear();
    }

    delete sbm;
    delete spw;
    delete srm;
    return true;
}

QString pbase::getCurrentFileName(void)
{
    //return the current filename or unknown
    //if a filename is not set.
    
    QString f;
    
    f=sCurrentFile.section('/', -1);
    
    if(f.isEmpty())
        f=tr("unknown");
    
    return f;
}

QString pbase::getPathfromResource(QByteArray* key)
{
    //Use the key, to find the encoded path to the data file
    //if sucessful returns the path, otherwise an empty QString
    
    QString p;
    
    if(!key->isEmpty())
    {
        QString sPath;
        bool found=false;
        md5class md5;
        
        p=p.fromUtf8(key->data());
        QByteArray ba_md5PbaseKey=md5.md5FromStr(&p);
        
        //processing resource file
        rcSettings rc(myName);
        p.clear();
        p=ba_md5PbaseKey;
        sPath=rc.rcReadStrValue(&found, "data", p);

        if(found)
        {
            //decode sPath
            CBlowFish bf;
            int l;
            char *d, *b, *c;

            d = sPath.toLatin1().data();   //d contains the hexadecimal value of the encoded path
            l = strlen(d);
            b = new char[l/2];
            hexString2bin(d, b);  //b contains the binary value of the encoded path
            c = new char[l];
            //Blowfish decryption
            bf.initialize((BYTE*)key->data(), (int)key->size());
            bf.decode((BYTE*)b, (BYTE*)c, (DWORD)l);
            //c contains now the path to the data file
            p.clear();
            p=c;    // convert to QString
            //size of path must be greater than 17 to avoid
            //fails in encoding data. Remove stuffed bytes
            p=p.trimmed();
            //now open the file
            delete b;
            delete c;

            return p;
        }
        else
        {
            p.clear();
            return p;
        }
    }
    return p;
}

bool pbase::writePathtoResource(QByteArray* key, QString path)
{
    //encodes the path using blowfish and the key
    //write the md5 sum of the key and the encoded path to the resource file
    //return true, if successful
    
    if(!key->isEmpty())
    {
        QByteArray baPath;
        QString p, v;
        char* e;
        char* h;
        int l, le;
        md5class md5;
        CBlowFish bf;
        
        p=p.fromUtf8(key->data());
        QByteArray ba_md5PbaseKey=md5.md5FromStr(&p);
        p.clear();
        p=ba_md5PbaseKey;
        
        //size of path must be greater than 17 to avoid
        //failer in encoding data. Append stuff bytes
        while(path.size()<18)   //fills size up to 18
            path.append(' ');
        
        baPath = path.toLatin1();
        l = baPath.size();

        //Blowfish encryption
        bf.initialize((BYTE*)key->data(), key->size());
        le=bf.getOutputLength((DWORD)l);
        e=new char[le];
        //write encoded path into char[] e
        le=bf.encode((BYTE*)baPath.data(), (BYTE*)e,(DWORD)l);
        h=new char[2*le+1];
        bin2hexString(h, e, le);
        v=h;
        //processing resource file
        rcSettings rc(myName);
        rc.rcSetStrValue("data", p, v);
        delete e;
        delete h;

        return true;
    }
    
    return false;
}

void pbase::bin2hexString(char* hex, char* byte, int l)
{
    //return the values of the char array byte as zero terminated hexadecimal string.
    //The values are in lowercase characters.
    //int l holds the amount of the characters of the char array byte.
    //the lenght of hex must be 2*l+1 for the zero termination.
    
    char lowNibble, highNibble;
    int i, j;

    j=0;
    for(i=0; i<l; i++)
    {
        lowNibble=byte[i]&0x0f;
        highNibble=(byte[i]&0xf0)>>4;

        if(lowNibble<0x0a)
            hex[j+1]=lowNibble+0x30;
        else
            hex[j+1]=lowNibble+0x57;

        if(highNibble<0x0a)
            hex[j]=highNibble+0x30;
        else
            hex[j]=highNibble+0x57;

        j+=2;
    }
    
    hex[2*l]='\0';
}

void pbase::hexString2bin(char* hex, char* byte)
{
    //convert the zero terminated hex string into a binary format
    //returns the binary values in the array byte
    //the amount of bytes of the array byte is strlen(hex)/2
    
    char lowNibble, highNibble;
    int i, j, l;
    
    l=strlen(hex) >> 1;
    j=0;
    
    for(i=0; i<l; i++)
    {
        if(hex[j] < 0x40)           //numbers 0-9
            highNibble=hex[j]-0x30;
        else
        {
            if(hex[j] > 0x50)       //lowercase characters
                highNibble=hex[j]-0x57;
            else
                highNibble=hex[j]-0x37; //uppercase characters
        }
        
        if(hex[j+1] < 0x40)         //numbers 0-9
            lowNibble=hex[j+1]-0x30;
        else
        {
            if(hex[j] > 0x50)       //lowercase characters
                lowNibble=hex[j+1]-0x57;
            else
                lowNibble=hex[j+1]-0x37;    //uppercase characters
        }
        
        highNibble=(highNibble << 4)&0xf0;
        lowNibble=lowNibble & 0x0f;
        byte[i]=highNibble | lowNibble;
        j+=2;
    }
}

void pbase::getPrinterData(QPrinter* pr)    
{
    bool found;
    qreal l, t, r, b;
    
    rcSettings rc(myName);
    rc.rcReadStrValue(&found, "print", "last_selected_printer");
    if(found)
    {
        pr->setPrinterName(rc.rcReadStrValue(&found, "print", "last_selected_printer"));
        pr->setPaperSize((QPrinter::PaperSize)rc.rcReadNumValue(&found, "print", "paperSize"));
        pr->setOrientation((QPrinter::Orientation)rc.rcReadNumValue(&found, "print", "orientation"));

        // read user defined margin values in px
        rc.rcReadNumValue(&found, "print", "leftMargin");
        if(found)
        {
            l=(qreal)rc.rcReadNumValue(&found, "print", "leftMargin");
            t=(qreal)rc.rcReadNumValue(&found, "print", "topMargin");
            r=(qreal)rc.rcReadNumValue(&found, "print", "rightMargin");
            b=(qreal)rc.rcReadNumValue(&found, "print", "bottomMargin");
            pr->setPageMargins(l, t, r, b, QPrinter::DevicePixel);
        }
    }
    else
    {
        //no printer specified in the rc-file. No printer installed?
        
        if(pr->printerName().isEmpty())     //no printer installed
        {
            actionPage_Setup->setEnabled(false);
            actionPrint->setEnabled(false);
            actionPrintRecord->setEnabled(false);
        }
        else    //using systems default printer
        {
            // set the default user defined page margins
            pr->setPageMargins(25.0, 25.0, 20.0, 25.0, QPrinter::Millimeter);
            pr->getPageMargins(&l, &t, &r, &b, QPrinter::DevicePixel);
            
            //save data to resource file
            rc.rcSetStrValue("print", "last_selected_printer", pr->printerName());
            rc.rcSetNumValue("print", "leftMargin", static_cast<long>(l+0.5));
            rc.rcSetNumValue("print", "topMargin", static_cast<long>(t+0.5));
            rc.rcSetNumValue("print", "rightMargin", static_cast<long>(r+0.5));
            rc.rcSetNumValue("print", "bottomMargin", static_cast<long>(b+0.5));
            rc.rcSetNumValue("print", "paperSize", (long)pr->paperSize());
            rc.rcSetNumValue("print", "orientation", (long)pr->orientation());
        }
    }
}

int pbase::getMaxPageNum(QPrinter *pr)
{
    //find out the max number of pages which are needed to print out
    //the whole file.
    //This functions replaces empty strings with a blank line. So
    //empty strings are skipped for the calculation
    
    qreal l, t, r, b;
    qint32 sumOfHeight=0;
    QRect printableRect;
    QFont currentFont(appFont);
    QFontMetrics fm(currentFont, pr);
    currentFont.setBold(true);
    QFontMetrics fmb(currentFont, pr);
    
    pr->setFullPage(true);  //if not, the calculation of the margins is incorrect
    pr->getPageMargins(&l, &t, &r, &b, QPrinter::DevicePixel);
    
    printableRect=pr->paperRect();
    printableRect.setWidth(printableRect.width()-static_cast<int>(l+0.5)-
                           static_cast<int>(r+0.5));
    printableRect.setHeight(printableRect.height()-static_cast<int>(t+0.5)-
                            static_cast<int>(b+0.5));
    //print filename on the first page
    //currentFont.setBold(false);
    sumOfHeight+=fm.boundingRect(printableRect, Qt::AlignLeft|Qt::TextWordWrap,
                                 tr("File name: ")+getCurrentFileName()).height();

    for(int item=0; item < mem->countOfItems(); item++)
    {
        //insert blank line
        sumOfHeight+=fm.lineSpacing();

        sumOfHeight+=fm.boundingRect(printableRect, Qt::AlignLeft|Qt::TextWordWrap,
                                     tr("Entry# ")+ QString::number(item+1)).height();
        //print the Bookmark

        sumOfHeight+=fmb.boundingRect(printableRect, Qt::AlignLeft|Qt::TextWordWrap,
                                      tr("Bookmark:")).height();
        
        if(!mem->getBookmark(item).isEmpty())
            sumOfHeight+=fm.boundingRect(printableRect, Qt::AlignLeft|Qt::TextWordWrap,
                                         mem->getBookmark(item)).height();
        //insert blank line
        sumOfHeight+=fm.lineSpacing();
        //print the Password
        sumOfHeight+=fmb.boundingRect(printableRect, Qt::AlignLeft|Qt::TextWordWrap,
                                      tr("Password:")).height();
        if(!mem->getPassword(item).isEmpty())
            sumOfHeight+=fm.boundingRect(printableRect, Qt::AlignLeft|Qt::TextWordWrap,
                                         mem->getPassword(item)).height();
        //insert blank line
        sumOfHeight+=fm.lineSpacing();
        //print the Annotations
        sumOfHeight+=fmb.boundingRect(printableRect, Qt::AlignLeft|Qt::TextWordWrap,
                                      tr("Annotations:")).height();
        if(!mem->getRemarks(item).isEmpty())
            sumOfHeight+=fm.boundingRect(printableRect, Qt::AlignLeft|Qt::TextWordWrap,
                                         mem->getRemarks(item).trimmed()).height();
    }
    
    return 1+(sumOfHeight/printableRect.height());
}

//End of miscellaneous functions
//-----------------------------------------------------------------------------

