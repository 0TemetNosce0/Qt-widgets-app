#include <QApplication>
#include <QDebug>

#include "qexcel.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//打开文件，取得工作簿
    QExcel j("C:/Users/litz-a/Desktop/QExcel/QExcelDemo/source.xls");

	//取得工作表数量
    // qDebug() << "SheetCount" << j.getSheetsCount();

	//激活一张工作表
	//j.selectSheet(1);
    //j.selectSheet("JSheet2");

	//取得工作表名称
	//j.selectSheet(1);
	//j.getSheetName();
    //qDebug()<<"SheetName 1"<<j.getSheetName(1);

	//取得工作表已使用范围
	//int topLeftRow, topLeftColumn, bottomRightRow, bottomRightColumn;
	//j.getUsedRange(&topLeftRow, &topLeftColumn, &bottomRightRow, &bottomRightColumn);

	//读值
	//j.getCellValue(2, 2).toString();

	//删除工作表
	//j.selectSheet("Sheet1");
	//j.selectSheet(1);
	//j.deleteSheet();
	//j.save();

	//插入数据
    //j.selectSheet("JSheet3");
    //j.setCellString(1, 7, "addString");
    //j.setCellString("A3", "abc");
    //j.save();

	//合并单元格
	//j.selectSheet(2);
	//j.mergeCells("G1:H2");
	//j.mergeCells(4, 7, 5 ,8);
	//j.save();

	//设置列宽
	//j.selectSheet(1);
	//j.setColumnWidth(1, 20);
	//j.save();

	//设置粗体
	//j.selectSheet(1);
	//j.setCellFontBold(2, 2, true);
	//j.setCellFontBold("A2", true);
	//j.save();

	//设置文字大小
	//j.selectSheet(1);
	//j.setCellFontSize("B3", 20);
	//j.setCellFontSize(1, 2, 20);
	//j.save();

	//设置单元格文字居中
	//j.selectSheet(2);
	//j.setCellTextCenter(1, 2);
	//j.setCellTextCenter("A2");
	//j.save();

	//设置单元格文字自动折行
	//j.selectSheet(1);
	//j.setCellTextWrap(2,2,true);
	//j.setCellTextWrap("A2", true);
	//j.save();

	//设置一行自适应行高
	//j.selectSheet(1);
	//j.setAutoFitRow(2);
	//j.save();

	//新建工作表
	//j.insertSheet("abc");
	//j.save();

	//清除单元格内容
	//j.selectSheet(4);
	//j.clearCell(1,1);
    //j.clearCell("A2");
    //j.save();

	//合并一列中相同连续的单元格
	//j.selectSheet(1);
	//j.mergeSerialSameCellsInColumn(1, 2);
	//j.save();

	//获取一张工作表已用行数
    j.selectSheet(1);
    qDebug() << j.getUsedRowsCount();

	//设置行高
//	j.selectSheet(1);
//    j.setRowHeight(2, 200);
//	j.save();

	j.close();
	qDebug()<<"App End";
	return a.exec();
}
