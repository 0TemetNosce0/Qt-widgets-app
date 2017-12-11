#include "excelengine.h"
#include "qt_windows.h"

ExcelEngine::ExcelEngine()
{
    pExcel     = NULL;
    pWorkbooks = NULL;
    pWorkbook  = NULL;
    pWorksheet = NULL;

    sXlsFile     = "";
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;

    bIsOpen  = false;
    bIsValid = false;

    HRESULT r = OleInitialize(0);
    if (r != S_OK && r != S_FALSE)
    {
        qDebug("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
    }
}

ExcelEngine::ExcelEngine(QString xlsFile)
{
    pExcel     = NULL;
    pWorkbooks = NULL;
    pWorkbook  = NULL;
    pWorksheet = NULL;

    sXlsFile     = xlsFile;
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;

    bIsOpen  = false;
    bIsValid = false;

    HRESULT r = OleInitialize(0);
    if (r != S_OK && r != S_FALSE)
    {
        qDebug("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
    }
}

ExcelEngine::~ExcelEngine()
{
    if ( bIsOpen )
    {
        //析构前，先保存数据，然后关闭workbook
        close();
    }
    OleUninitialize();
}

/**
  *@brief 打开sXlsFile指定的excel报表
  *@return true : 打开成功
  *        false: 打开失败
  */
bool ExcelEngine::open(UINT nSheet, bool visible)
{
    if ( bIsOpen )
    {
        //return bIsOpen;
        close();
    }

    if ( NULL == pExcel )
    {
        pExcel = new QAxObject("Excel.Application");
        if ( pExcel )
        {
            bIsValid = true;
        }
        else
        {
            bIsValid = false;
            bIsOpen  = false;
            return bIsOpen;
        }

        pExcel->dynamicCall("SetVisible(bool)", bIsVisible);
    }

    if ( !bIsValid )
    {
        bIsOpen  = false;
        return bIsOpen;
    }

    if ( sXlsFile.isEmpty() )
    {
        bIsOpen  = false;
        return bIsOpen;
    }


    bool ok = createXlsFile(sXlsFile);
    if ( !ok )
    {
        bIsOpen  = false;
        return bIsOpen;
    }

    nCurrSheet = nSheet;
    bIsVisible = visible;

    pWorkbooks = pExcel->querySubObject("WorkBooks"); //获取工作簿
    pWorkbook = pWorkbooks->querySubObject("Open(QString, QVariant)",sXlsFile,QVariant(0)); //打开xls对应的工作簿
    pWorksheet = pWorkbook->querySubObject("WorkSheets(int)", nCurrSheet);//打开第一个sheet

    //至此已打开，开始获取相应属性
    QAxObject *usedrange = pWorksheet->querySubObject("UsedRange");//获取该sheet的使用范围对象
    QAxObject *rows = usedrange->querySubObject("Rows");
    QAxObject *columns = usedrange->querySubObject("Columns");

    //因为excel可以从任意行列填数据而不一定是从0,0开始，因此要获取首行列下标
    nStartRow    = usedrange->property("Row").toInt();    //第一行的起始位置
    nStartColumn = usedrange->property("Column").toInt(); //第一列的起始位置

    nRowCount    = rows->property("Count").toInt();       //获取行数
    nColumnCount = columns->property("Count").toInt();    //获取列数

    bIsOpen  = true;
    return bIsOpen;
}

/**
  *@brief Open()的重载函数
  */
bool ExcelEngine::open(QString xlsFile, UINT nSheet, bool visible)
{
    sXlsFile = xlsFile;
    nCurrSheet = nSheet;
    bIsVisible = visible;

    return open(nCurrSheet,bIsVisible);
}

/**
  *@brief 保存表格数据，把数据写入文件
  */
void ExcelEngine::save()
{
    if ( pWorkbook )
    {
        pWorkbook->dynamicCall("Save()");
    }
}

/**
  *@brief 关闭前先保存数据，然后关闭当前Excel COM对象，并释放内存
  */
void ExcelEngine::close()
{
    //关闭前先保存数据
    save();
    if ( pExcel && pWorkbook )
    {
        pWorkbook->dynamicCall("Close(bool)", true);
        pExcel->dynamicCall("Quit()");

        delete pExcel;
        pExcel = NULL;

        bIsOpen = false;
        bIsValid = false;
    }
}

/**
  *@brief 把tableWidget中的数据保存到excel中
  *@param tableWidget : 指向GUI中的tablewidget指针
  *@return 保存成功与否 true : 成功
  *                  false: 失败
  */
bool ExcelEngine::saveDataFrTable(QTableWidget *tableWidget)
{
    if ( NULL == tableWidget )
    {
        return false;
    }
    if ( !bIsOpen )
    {
        return false;
    }

    int tableR = tableWidget->rowCount();
    int tableC = tableWidget->columnCount();

    //获取表头写做第一行
    for (int i=0; i<tableC; i++)
    {
        if ( tableWidget->horizontalHeaderItem(i) != NULL )
        {
            this->setCellData(1,i+1,tableWidget->horizontalHeaderItem(i)->text());
        }
    }

    //写数据
    for (int i=0; i<tableR; i++)
    {
        for (int j=0; j<tableC; j++)
        {
            if ( tableWidget->item(i,j) != NULL )
            {
                this->setCellData(i+2,j+1,tableWidget->item(i,j)->text());
            }
        }
    }

    //保存
    save();

    return true;
}

/**
  *@brief 从指定的xls文件中把数据导入到tableWidget中
  *@param tableWidget : 执行要导入到的tablewidget指针
  *@return 导入成功与否 true : 成功
  *                   false: 失败
  */
bool ExcelEngine::readDataToTable(QTableWidget *tableWidget)
{
    if ( NULL == tableWidget )
    {
        return false;
    }

    //先把table的内容清空
    int tableColumn = tableWidget->columnCount();
    tableWidget->clear();
    for (int n=0; n<tableColumn; n++)
    {
        tableWidget->removeColumn(0);
    }

    int rowcnt    = nStartRow + nRowCount;
    int columncnt = nStartColumn + nColumnCount;

    //获取excel中的第一行数据作为表头
    QStringList headerList;
    for (int n = nStartColumn; n<columncnt; n++ )
    {
        QAxObject * cell = pWorksheet->querySubObject("Cells(int,int)",nStartRow, n);
        if ( cell )
        {
            headerList<<cell->dynamicCall("Value2()").toString();
        }
    }

    //重新创建表头
    tableWidget->setColumnCount(nColumnCount);
    tableWidget->setHorizontalHeaderLabels(headerList);


    //插入新数据
    for (int i = nStartRow+1, r = 0; i < rowcnt; i++, r++ )  //行
    {
        tableWidget->insertRow(r); //插入新行
        for (int j = nStartColumn, c = 0; j < columncnt; j++, c++ )  //列
        {
            QAxObject * cell = pWorksheet->querySubObject("Cells(int,int)", i, j );//获取单元格

            //在r新行中添加子项数据
            if ( cell )
            {
                tableWidget->setItem(r,c,new QTableWidgetItem(cell->dynamicCall("Value2()").toString()));
            }
        }
    }

    return true;
}

/**
  *@brief 获取指定单元格的数据
  *@param row : 单元格的行号
  *@param column : 单元格的列号
  *@return [row,column]单元格对应的数据
  */
QVariant ExcelEngine::getCellData(UINT row, UINT column)
{
    QVariant data;

    QAxObject *cell = pWorksheet->querySubObject("Cells(int,int)",row,column);//获取单元格对象
    if ( cell )
    {
        data = cell->dynamicCall("Value2()");
    }

    return data;
}

/**
  *@brief 修改指定单元格的数据
  *@param row : 单元格的行号
  *@param column : 单元格指定的列号
  *@param data : 单元格要修改为的新数据
  *@return 修改是否成功 true : 成功
  *                   false: 失败
  */
bool ExcelEngine::setCellData(UINT row, UINT column, QVariant data)
{
    bool op = false;

    QAxObject *cell = pWorksheet->querySubObject("Cells(int,int)",row,column);//获取单元格对象
    if ( cell )
    {
        QString strData = data.toString(); //excel 居然只能插入字符串和整型，浮点型无法插入
        cell->dynamicCall("SetValue(const QVariant&)",strData); //修改单元格的数据
        op = true;
    }
    else
    {
        op = false;
    }

    return op;
}

/**
  *@brief 创建一个xls报表文件
  *@param xlsFile : 报表文件名
  *@return true : 创建成功
  *        false: 创建失败
  */
bool ExcelEngine::createXlsFile(const QString &xlsFile)
{

    bool cr = false;
    QFile f(xlsFile);
    if ( !f.exists())
    {
        /**
          *@note 由于无法找到workbook增加一个工作簿的接口，只能用这种拷贝文件的方法
          *或者，直接创建一个.xls为后缀的空白文档
          */
        QFile copyFile(tr("./template/template.xls"));
        if ( copyFile.exists() )
        {
            //直接拷贝一个模块
            QFile::copy(tr("./template/template.xls"),xlsFile);
        }
        else
        {
            //创建已xls为后缀的空白文档
            f.open(QIODevice::WriteOnly);
            f.close();
        }

        //判断是否创建成功
        cr = f.open(QIODevice::ReadWrite);
        f.close();

    }
    else
    {
        cr = true;
    }

    return cr;
}

/**
  *@brief 清空除报表之外的数据
  */
void ExcelEngine::clear()
{
    sXlsFile     = "";
    nRowCount    = 0;
    nColumnCount = 0;
    nStartRow    = 0;
    nStartColumn = 0;
}

/**
  *@brief 判断excel是否已被打开
  *@return true : 已打开
  *        false: 未打开
  */
bool ExcelEngine::isOpen()
{
    return bIsOpen;
}

/**
  *@brief 判断excel COM对象是否调用成功，excel是否可用
  *@return true : 可用
  *        false: 不可用
  */
bool ExcelEngine::isValid()
{
    return bIsValid;
}

/**
  *@brief 获取excel的行数
  */
UINT ExcelEngine::getRowCount()const
{
    return nRowCount;
}

/**
  *@brief 获取excel的列数
  */
UINT ExcelEngine::getColumnCount()const
{
    return nColumnCount;
}
