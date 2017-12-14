#ifndef EXCELENGINE_H
#define EXCELENGINE_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QAxBase>
#include <QAxObject>

#include <QTableWidget>
#include <QTableView>
#include <QTableWidgetItem>
#include <QDebug>

typedef unsigned int UINT;

/**
  *@brief 这是一个便于Qt读写excel封装的类，同时，便于把excel中的数据
  *显示到界面上，或者把界面上的数据写入excel中，同GUI进行交互，关系如下：
  *Qt tableWidget <--> ExcelEngine <--> xls file.
  *
  *@note ExcelEngine类只负责读/写数据，不负责解析，做中间层
  *@author yaoboyuan 254200341@qq.com
  *@date 2012-412
  */
class ExcelEngine : protected QObject
{
public:
    ExcelEngine();
    ExcelEngine(QString xlsFile);
    ~ExcelEngine();

public:
    bool open(UINT nSheet = 1, bool visible = false);//打开xls文件
    bool open(QString xlsFile, UINT nSheet = 1, bool visible = false);
    void save();                //保存xls报表
    void close();               //关闭xls报表

    bool saveDataFrTable(QTableWidget *tableWidget); //保存数据到xls
    bool readDataToTable(QTableWidget *tableWidget); //从xls读取数据到ui

    QVariant getCellData(UINT row, UINT column);                //获取指定单元数据
    bool     setCellData(UINT row, UINT column, QVariant data); //修改指定单元数据

    UINT getRowCount()const;
    UINT getColumnCount()const;

    bool isOpen();
    bool isValid();

protected:
    bool createXlsFile(const QString &xlsFile);
    void clear();

private:
    QAxObject *pExcel;      //指向整个excel应用程序
    QAxObject *pWorkbooks;  //指向工作簿集,excel有很多工作簿
    QAxObject *pWorkbook;   //指向sXlsFile对应的工作簿
    QAxObject *pWorksheet;  //指向工作簿中的某个sheet表单

    QString   sXlsFile;     //xls文件路径
    UINT      nCurrSheet;   //当前打开的第几个sheet
    bool      bIsVisible;   //excel是否可见
    int       nRowCount;    //行数
    int       nColumnCount; //列数
    int       nStartRow;    //开始有数据的行下标值
    int       nStartColumn; //开始有数据的列下标值

    bool      bIsOpen;      //是否已打开
    bool      bIsValid;     //是否有效

};

#endif // EXCELENGINE_H
