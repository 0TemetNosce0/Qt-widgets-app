#include "pbase.h"
#include "pbasedialog.h"

//Enter a key an return it in QByteArray* k
EnterKeyDlg::EnterKeyDlg(QWidget *parent, QByteArray* k)
    : QDialog(parent)
{
    key=k;
    setupUi(this);
    
    QFontMetrics fm(qApp->font());
    QSize s;
    int w, x, y;
    
    //find the longest button text
    s = fm.size(Qt::TextIncludeTrailingSpaces, okKeyButton->text());
    w = s.width();
    s = fm.size(Qt::TextIncludeTrailingSpaces, cancelKeyButton->text());
    w = (s.width() > w) ? s.width():w;
    s = fm.size(Qt::TextIncludeTrailingSpaces, loadKeyButton->text());
    w = (s.width() > w) ? s.width():w;
    s = fm.size(Qt::TextIncludeTrailingSpaces, saveKeyButton->text());
    w = (s.width() > w) ? s.width():w;    //w holds the amount of px of the the longest text
    
    // set the geometry of the buttons
    okKeyButton->setGeometry(0, 0, w+5, s.height()+5);
    cancelKeyButton->setGeometry(0, 0, w+5, s.height()+5);
    loadKeyButton->setGeometry(0, 0, w+5, s.height()+5);
    saveKeyButton->setGeometry(0, 0, w+5, s.height()+5);
    
    // arrange the Buttons
    x = 20;
    y = 110;
    okKeyButton->move(x, y);
    x = x + okKeyButton->frameGeometry().width()+20;
    cancelKeyButton->move(x, y);
    x = x + cancelKeyButton->frameGeometry().width()+40;
    loadKeyButton->move(x, y);
    x = x + loadKeyButton->frameGeometry().width()+20;
    saveKeyButton->move(x, y);
    
    // set the geometry of the label and the lineedit
    w = 4 * loadKeyButton->frameGeometry().width()+80;
    label->setGeometry(20, 25, w, s.height()+5);
    enterKeyEdit->setGeometry(20, 60, w, s.height()+5);
    
    // set the width and height of the dialogbox
    w = x + saveKeyButton->frameGeometry().width() + 20;
    QRect r = parent->geometry(); // we need the x, y coordinates of the parent
    r.setY(r.y() + 50);   // move position of the dialog into the mainwindow
    r.setWidth(w);
    //restore the height of the dialogbox
    r.setHeight(geometry().height());
    setGeometry(r);
    
    connect(okKeyButton, SIGNAL(clicked()), this, SLOT(okkey()));
    connect(cancelKeyButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(loadKeyButton, SIGNAL(clicked()), this, SLOT(loadkey()));
    connect(saveKeyButton, SIGNAL(clicked()), this, SLOT(savekeyas()));
    
    setFont(qApp->font());

    // shows the dialog
    exec();

}

void EnterKeyDlg::okkey(void)           //Slot
{
    QString txt = enterKeyEdit->text();

    //check min. length of key
    if(txt.size() < 6)
    {
        QMessageBox::information(this, tr("2Pnotes - Enter Key"),
                                 tr("The key length must have an amount between 6 and 56 characters. ")+
                                 tr("It's recommended to have a key with a lenght of 12 or above characters."));

        if(!enterKeyEdit->hasFocus())
        {
            enterKeyEdit->setFocus();
        }
    }
    else
    {
        if(txt.size() < 12)
        {
            QMessageBox::warning(this, tr("2Pnotes - Enter Key"),
                                 tr("A key length lower than 12 is unsafe today. This is only allowed ")+
                                 tr("here for compatibility with earlier versions. It's recommended to ")+
                                 tr("choose a new key with the 'Edit - Change Key' menu."));
        }
        *key=txt.toUtf8();
        accept();
    }
}

bool EnterKeyDlg::loadkey(void)
{
    QFile f;
    int l;
    QString p;
    
    p = QFileDialog::getOpenFileName(this, tr("2Pnotes - Open Keyfile"));
    //workaround to delete the automatic saving of the selected path
    //by the QFileDialog class. It deletes all selected paths of all Qt
    //applications used by this user. Parts of the code is extracted
    //from the file qfiledialog.cpp of the qt sources

    QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
    settings.beginGroup(QLatin1String("Qt"));
    settings.remove("filedialog");
    settings.endGroup();

    if(p.isNull())
    {
        return false;
    }
    else
    {
        f.setFileName(p);

        if(f.open(QIODevice::ReadOnly))
        {
            l = f.size();

            if(l <= (MAXKEYBYTES + 5))
            {
                QDataStream i(&f);
                keyBytes = new char[l];       // delete erfolgt beim Löschen der Klasse. Sonst Absturz! Warum??
                i.readRawData(keyBytes, l);
                f.close();
                keyBytes[l] = '\0';
            }
            else
            {
                f.close();
                QMessageBox::information(this, tr("2Pnotes - Open Keyfile"),
                                         tr( "The selected file is not a 2Pnotes keyfile."));

                return false;
            }
        }

        //check for 'pbkey' label
        if(strncmp(keyBytes, "pbkey", 5)!=0)
        {
            QMessageBox::information(this, tr("2Pnotes - Open Keyfile"),
                                     tr("The selected file is not a 2Pnotes keyfile."));
            return false;
        }

        p.clear();
        p = (keyBytes + 5);     //don't use the first 5 characters. Operator uses the func "fromAscii"
        enterKeyEdit->setText(p);
    }

    return true;
}

bool EnterKeyDlg::savekeyas(void)       //Slot
{
    int choice;
    QFile f;
    QString p;

    QString txt = enterKeyEdit->text();

    //check min. length of key
    if(txt.size() < 6)
    {
        QMessageBox::information(this, tr("2Pnotes - Enter Key"),
                                 tr("The key length must have an amount between 6 and 56 characters."));

        if(!enterKeyEdit->hasFocus())
        {
            enterKeyEdit->setFocus();
        }
    }
    else
    {
        p = QFileDialog::getSaveFileName(this, tr("2Pnotes - Save Key as"), "", "", 0, QFileDialog::DontConfirmOverwrite);

        if(p.isNull())
        {
            return false;
        }
        else
        {
            f.setFileName(p);

            if(f.exists())
            {
                choice = QMessageBox::warning(this, tr("2Pnotes - Save Key as"),
                                            tr("Keyfile already exists.")+ "\n"+tr("Overwrite?"),
                                            QMessageBox::Yes, QMessageBox::No);

                if(choice == QMessageBox::No)
                {
                    return false;
                }
            }
            
            
            if(f.open(QIODevice::WriteOnly))
            {
                QDataStream o(&f);
                QByteArray b;
                p.clear();
                p = txt;      //no change of QString txt
                p.prepend("pbkey");
                b = p.toLatin1();
                o.writeRawData(b.data(), b.size());
                f.close();
                return true;
            }
        }
    }
    return false;
}


aboutPbaseDlg::aboutPbaseDlg(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    
    label1->setFont(qApp->font());
    label2->setFont(qApp->font());
    buttonBox->setFont(qApp->font());
    
    exec();
}
