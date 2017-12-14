// File text2printer.cpp
// defines the memberfunctions of class text2Printer V 0.1, written in Qt 4.4.0
// July 2009


#include "text2printer.h"

text2Printer::text2Printer(QPrinter *prt, QPainter *p, bool pageNumbers)
{
    //before call this constructor, you must call QPainter::begin() and
    //set all varables in the QPrinter object, e.g. margins, papersize,
    //orientation, ... and set QPrinter::setFullPage(true)!! If not,
    //the calculation of the margins is incorrect.

    //the parameter pagenumbers, default=true, specifies the print out
    //of pagenumbers.
    
    rect2Print = NULL;
    m = NULL;

    if(!prt->isValid())
    {
        QMessageBox::critical(0, QObject::tr("Module text2printer"),
                              QObject::tr("Invalid Printer selected. Abort printing!"));
        this->~text2Printer();
    }
    
    if(!p->isActive())
    {
        QMessageBox::critical(0, QObject::tr("Module text2printer"),
                              QObject::tr("Painter Object not available. Abort printing!"));
        this->~text2Printer();
    }
    
    pr = prt;
    painter = p;
    
    linePos = 0;
    qreal l, t, r, b;

    enablePageNumber = pageNumbers;
    pagenumber = 0;   //set to zero shows that no print command is in progress

    //initialize page
    pr->getPageMargins(&l, &t, &r, &b, QPrinter::DevicePixel);
    rect2Print = new QRect();
    m = new struct Margins;
    
    m->pxLeft = static_cast<int>(l + 0.5);
    m->pxTop = static_cast<int>(t + 0.5);
    m->pxRight = static_cast<int>(r + 0.5);
    m->pxBottom = static_cast<int>(b + 0.5);
    
    if(pr->printRange() == QPrinter::PageRange)
    {
        startPage = pr->fromPage();
        endPage = pr->toPage();
    }
    else
    {
        startPage = 1;
        endPage = MAX_INT_VALUE;
    }
    
    initPage();
}

text2Printer::~text2Printer()
{
    if(rect2Print)
    {
        delete rect2Print;
    }

    if(m)
    {
        delete m;
    }
}

void text2Printer::PrintOut(QString p)      //public
{
    //send QString p to the printer. inserts automatically
    //linefeeds and formfeeds.
    
    linePos = string2Printer(p, linePos);
}

void text2Printer::insertBlankLine(void)    //public
{
    //insert a blank line on the actual position on the page
    //set new values of top and height of the printable area
    
    rect2Print->setY(rect2Print->y()+painter->fontMetrics().lineSpacing());
    linePos = rect2Print->y();
}

void text2Printer::setCurrentFont(QFont font)   //public
{
    //set the font which is used to print
    //the text
    
    painter->setFont(font);
}

QFont text2Printer::getCurrentFont(void)        //public
{
    //return the current font of the painter,
    //which is used to print the text
    
    return painter->font();
}

void text2Printer::appendNewPage(void)      //public
{
    //append a new page
    //and set the page variables to the start values
    
    pagenumber++;

    if((pagenumber>startPage) & (pagenumber<=endPage))
    {
        pr->newPage();
    }

    printPageNumber();
    initPage();
}

void text2Printer::initPage(void)
{   
#ifndef Q_OS_WIN32
    rect2Print->setX(m->pxLeft);
    rect2Print->setY(m->pxTop);
#else
    rect2Print->setX(0);
    rect2Print->setY(0);
#endif

    rect2Print->setWidth(pr->paperRect().width() - (m->pxLeft+m->pxRight));
    rect2Print->setHeight(pr->paperRect().height() - (m->pxTop+m->pxBottom));
}

void text2Printer::printPageNumber(void)    //private
{
    //prints the pagenumber into the center of the page bottom.
    //The position is above the min. bottom margin
    //Does nothing, if enablePageNumber=false
    
    if(enablePageNumber)
    {
        QString n;
        QRect r;
        
        // offset for print the page number
        int o = (int)(3.0/25.4)*pr->logicalDpiY();

#ifndef Q_OS_WIN32
        r.setX(m->pxLeft);
        r.setY(pr->paperRect().height()-m->pxTop+o);
#else
        r.setX(0);
        r.setY(pr->pageRect().height()+o);
#endif

        r.setWidth(pr->paperRect().width()-(m->pxLeft+m->pxRight));

        QFont currentFont = painter->font();
        
        painter->setFont(QFont("Helvetica", 9));
        r.setHeight(painter->fontMetrics().height()+2);

        if((pagenumber>=startPage) & (pagenumber<=endPage))
        {
            painter->drawText(r , Qt::AlignCenter, n.setNum(pagenumber));
        }

        painter->setFont(currentFont);
    }
}

QString text2Printer::adjustStr2printRect(const QString inp, QString* outp)     //private
{
    //Adjust the QString inp till it fits into the given QRect printArea,
    //starting at the left side. The QString inp is split on wordborders and give back
    //as string outp. The returnvalue is the rest of the string inp or an empty string.
    
    QString retStr = inp; //don't change the original string
    QRect tmp;
    
    int lnew = 0;
    int addedChars;
    float part, area;
    
    area = (float)rect2Print->height();
    
    if(painter->isActive())
    {
        addedChars=rect2Print->width()/painter->fontMetrics().averageCharWidth();
    }
    else
    {
        qWarning("Module text2printer, func adjustStr2printRect\n"
                 "Painter is not active! Abort this function");
        return QString();
        
    }

    do
    {
        // subdivison of QString* inp
        tmp = painter->boundingRect(*rect2Print, Qt::AlignLeft|Qt::TextWordWrap, retStr);
        
        part = area/(float)tmp.height();

        if(part < 1)  //printArea.height<tmp.height()
        {
            //increase lnew to fill out the line
            if(retStr.size() >= addedChars+retStr.size() * part)
                //avoid adresses outside the string
                lnew = (int)((float)addedChars + (float)retStr.size() * part);
            else
                lnew = retStr.size();
            
            // avoid broken words, look to the last separator character
            for(int i = lnew; i > 0; i--)
            {
                if(retStr[i].isSpace())
                {
                    lnew = i;
                    break;
                }
            }

            retStr = retStr.left(lnew);
        }

    }while(part < 1);
    
    //printable string
    *outp = retStr;
    //remove whitespace characters at the start and end of outp.
    *outp = outp->trimmed();
    
    if(!lnew)       //retStr fits into printArea without changes
    {
        retStr.clear();
    }
    else
    {
        retStr = inp.right((inp.size()-lnew));
    }

    return retStr;
}

int text2Printer::string2Printer(QString str2print, int startTop)   //private
{
    //send string str2print to the printer
    //uses the blanks between words to separate at end of line and end of page
    //append new pages automatically
    
    QRect retRect;
    QString rest = str2print; //do not change the original string
    QString printout;
    int h;

    if(pagenumber == 0)     //first page
    {
        pagenumber++;
        startTop = rect2Print->y();
        h = rect2Print->height();
        printPageNumber();
    }
    else
    {
        h = rect2Print->height();
        
        if(h < painter->fontMetrics().height())
        {
            appendNewPage();
            startTop = rect2Print->y();
            h = rect2Print->height();
        }
    }
    
    do
    {
        rest = adjustStr2printRect(rest, &printout);
        
        if(printout.isEmpty())  //nothing to print
        {
            break;
        }

        if((pagenumber >= startPage) & (pagenumber <= endPage))
        {
            painter->drawText(*rect2Print, Qt::AlignLeft|Qt::TextWordWrap, printout, &retRect);
        }
        else
        {
            painter->drawText(*rect2Print, Qt::AlignLeft|Qt::TextWordWrap|Qt::TextDontPrint,
                              printout, &retRect);
        }

        startTop = startTop+retRect.height();
        h = h-retRect.height();
        rect2Print->setRect(rect2Print->x(), startTop, rect2Print->width(), h);
        
        if(!rest.isEmpty())
        {
            appendNewPage();
            initPage();
            startTop = rect2Print->y();
            h = rect2Print->height();
        }

    }while(!rest.isEmpty());
    
    return startTop;
}
