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
  *@brief ����һ������Qt��дexcel��װ���࣬ͬʱ�����ڰ�excel�е�����
  *��ʾ�������ϣ����߰ѽ����ϵ�����д��excel�У�ͬGUI���н�������ϵ���£�
  *Qt tableWidget <--> ExcelEngine <--> xls file.
  *
  *@note ExcelEngine��ֻ�����/д���ݣ���������������м��
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
    bool open(UINT nSheet = 1, bool visible = false);//��xls�ļ�
    bool open(QString xlsFile, UINT nSheet = 1, bool visible = false);
    void save();                //����xls����
    void close();               //�ر�xls����

    bool saveDataFrTable(QTableWidget *tableWidget); //�������ݵ�xls
    bool readDataToTable(QTableWidget *tableWidget); //��xls��ȡ���ݵ�ui

    QVariant getCellData(UINT row, UINT column);                //��ȡָ����Ԫ����
    bool     setCellData(UINT row, UINT column, QVariant data); //�޸�ָ����Ԫ����

    UINT getRowCount()const;
    UINT getColumnCount()const;

    bool isOpen();
    bool isValid();

protected:
    bool createXlsFile(const QString &xlsFile);
    void clear();

private:
    QAxObject *pExcel;      //ָ������excelӦ�ó���
    QAxObject *pWorkbooks;  //ָ��������,excel�кܶ๤����
    QAxObject *pWorkbook;   //ָ��sXlsFile��Ӧ�Ĺ�����
    QAxObject *pWorksheet;  //ָ�������е�ĳ��sheet��

    QString   sXlsFile;     //xls�ļ�·��
    UINT      nCurrSheet;   //��ǰ�򿪵ĵڼ���sheet
    bool      bIsVisible;   //excel�Ƿ�ɼ�
    int       nRowCount;    //����
    int       nColumnCount; //����
    int       nStartRow;    //��ʼ�����ݵ����±�ֵ
    int       nStartColumn; //��ʼ�����ݵ����±�ֵ

    bool      bIsOpen;      //�Ƿ��Ѵ�
    bool      bIsValid;     //�Ƿ���Ч

};

#endif // EXCELENGINE_H
