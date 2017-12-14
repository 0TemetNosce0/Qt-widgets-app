// File text2printer.h
// provides class text2Printer V 0.1, written in Qt 4.4.0
// July 2009


#ifndef TEXT2PRINTER_H_
#define TEXT2PRINTER_H_

#include <QDebug>
#include <QString>
#include <QPainter>
#include <QPrinter>
#include <QMessageBox>

#define MAX_INT_VALUE   2147483647

class text2Printer
{   
public:
    text2Printer(QPrinter *prt, QPainter *p, bool pageNumbers=true);
    ~text2Printer();

    void PrintOut(QString p);
    void insertBlankLine(void);
    void setCurrentFont(QFont font);
    QFont getCurrentFont(void);
    void appendNewPage(void);

private:
    struct Margins
    {
        //values in px
        int pxTop;
        int pxBottom;
        int pxLeft;
        int pxRight;
    };
    void initPage(void);
    void printPageNumber(void);
    QString adjustStr2printRect(const QString inp, QString* outp);
    int string2Printer(QString ps, int startTop);

    QPrinter *pr; //holds the parameter printer for internal use
    QPainter *painter;
    QRect *rect2Print;
    QFont currentFont;
    bool enablePageNumber; //holds a copy of parameter pageNumbers for internal use
    int pagenumber;
    int startPage;
    int endPage;
    int linePos;
    struct Margins *m;
};



#endif /*TEXT2PRINTER_H_*/
