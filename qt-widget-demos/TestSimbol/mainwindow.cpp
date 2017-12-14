#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GLDDefaultItemDelegate.h"
#include "GLDGlobal.h"
#include "GLDFileUtils.h"
#include "GSPException.h"
#include "GSPEngineUtils.h"
#include "windows.h"

#include <tchar.h>

#include <QFontDatabase>
#include <QTextStream>
#include <iostream>
#include <QLibrary>

#include <QDebug>
using namespace std;

typedef bool (WINAPI *ProcEnableEUDC)(bool);
ProcEnableEUDC EnableEUDC;
const QString c_defaultFont                     = "EUDC";

GlodonSimbolBtn::GlodonSimbolBtn(QWidget *parent, const QString &simbol) :
	QPushButton(parent),
	m_simbol(simbol)
{
	setFont(QFont(c_defaultFont));
	setText(m_simbol);
	connect(this, &GlodonSimbolBtn::clicked, this, &GlodonSimbolBtn::onclicked);
}

void GlodonSimbolBtn::onclicked()
{
	emit showText(m_simbol);
}

GlodonSimbolRow::GlodonSimbolRow(const QStringList &simbols, QWidget *parent) :
	QWidget(parent),
	m_rowLayout(new QHBoxLayout(this))
{
	foreach (QString text, simbols)
	{
		GlodonSimbolBtn *m_simbol = new GlodonSimbolBtn(this, text);
		m_simbolBtns.append(m_simbol);
		connect(m_simbol, &GlodonSimbolBtn::showText, this, &GlodonSimbolRow::showText);
	}
}

void GlodonSimbolRow::layoutSimbolRow()
{
	m_rowLayout->setSpacing(0);
	m_rowLayout->setContentsMargins(0, 0, 0, 0);
	foreach (GlodonSimbolBtn *simbolBtn, m_simbolBtns)
	{
		m_rowLayout->addWidget(simbolBtn);
	}
}

GlodonSimbolTable::GlodonSimbolTable(const QStringList &simbols, QWidget *parent) :
	QWidget(parent),
	m_simbolTableLayout(new QVBoxLayout(this))
{
	GlodonSimbolRow *firstRow = new GlodonSimbolRow(simbols, this);
	firstRow->layoutSimbolRow();
	m_simbolRows.append(firstRow);
	connect(firstRow, &GlodonSimbolRow::showText, this , &GlodonSimbolTable::showText);
}

void GlodonSimbolTable::appendSimbolRow(const QStringList &simbols)
{
	GlodonSimbolRow *otherSimbolRow = new GlodonSimbolRow(simbols, this);
	otherSimbolRow->layoutSimbolRow();
	m_simbolRows.append(otherSimbolRow);
	connect(otherSimbolRow, &GlodonSimbolRow::showText, this , &GlodonSimbolTable::showText);
}

void GlodonSimbolTable::layoutSimbolTable()
{
	m_simbolTableLayout->setSpacing(0);
	m_simbolTableLayout->setContentsMargins(0, 0, 0, 0);
	foreach (GlodonSimbolRow *row, m_simbolRows)
	{
		m_simbolTableLayout->addWidget(row);
	}
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    loadDataToTableView();
    loadTableView();
//    loadFooterTableView();
//    loadGSPTableView();
//    loadGTPGSPTableView();
    loadFont();
    initWidget();

	QVBoxLayout *pOuterLayout = new QVBoxLayout(this);
	m_simbolBtn = new QPushButton(this);
	m_simbolBtn->setText("Special_Simbol");
	m_simbolBtn->setFixedSize(QSize(120, 30));

	pOuterLayout->addWidget(m_simbolBtn);
    pOuterLayout->addWidget(m_showWidget);
	this->centralWidget()->setLayout(pOuterLayout);

	connect(m_simbolBtn, &QPushButton::clicked, this, &MainWindow::showPopWidget);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::testGlodonSimbolRow()
{
	loadSimbolText();

	m_simbolRow = new GlodonSimbolRow(m_simbolList.at(0), this);
	m_simbolRow->layoutSimbolRow();
}

void MainWindow::testGlodonSimbolTable()
{
	loadSimbolText();
	m_simbolTable = new GlodonSimbolTable(m_simbolList.at(0), this);
	for (int i = 1; i < m_simbolList.size(); ++i)
	{
		m_simbolTable->appendSimbolRow(m_simbolList.at(i));
	}
	m_simbolTable->layoutSimbolTable();
}

void MainWindow::loadDataToTableView()
{
	m_model = new QStandardItemModel(this);

	//构造部门数据
	for (int i = 1; i <= 10; ++i)
	{
		QList<QStandardItem*> empt;

		QStandardItem *rowNoItem = new QStandardItem();
		rowNoItem->setData(QVariant(i), Qt::EditRole);
        empt.append(rowNoItem);

        QStandardItem *simbol_Col1 = new QStandardItem();
		empt.append(simbol_Col1);

		QStandardItem *simbol_Col2 = new QStandardItem("");
		empt.append(simbol_Col2);

		QStandardItem *simbol_Col3 = new QStandardItem("");
        empt.append(simbol_Col3);

//		QList<QStandardItem*> pSimbolCols;
		//simbol_Col1
		QStandardItem *simbol_Col1Data = new QStandardItem();
		simbol_Col1Data->setData(0, Qt::EditRole);
        empt.append(simbol_Col1Data);

		//simbol_Col2
		QStandardItem *simbol_Col2Data = new QStandardItem();
		simbol_Col2Data->setData(0, Qt::EditRole);
        empt.append(simbol_Col2Data);

		QStandardItem *simbol_Col3Data = new QStandardItem();
		simbol_Col3Data->setData(0, Qt::EditRole);
        empt.append(simbol_Col3Data);

		//下拉选择框
		QStandardItem *pDropDown = new QStandardItem();
		pDropDown->setData("java");
        empt.append(pDropDown);

		//增加到部门列表中
//		rowNoItem->appendRow(pSimbolCols);
//		empt.append(rowNoItem);
		m_model->appendRow(empt);
	}

	m_model->setHeaderData(0, Qt::Horizontal, "RowNo");
	m_model->setHeaderData(1, Qt::Horizontal, "Simbol_Col1");
	m_model->setHeaderData(2, Qt::Horizontal, "Simbol_Col2");
	m_model->setHeaderData(3, Qt::Horizontal, "Simbol_Col3");
	m_model->setHeaderData(4, Qt::Horizontal, TRANS_STRING("下拉选择框"));

	m_model->setData(m_model->index(0, 0), "ToolTip", Qt::ToolTipRole);
}

QWidget* MainWindow::loadTableView()
{
	m_showWidget = new QWidget(this);
	QHBoxLayout *pLayout = new QHBoxLayout(m_showWidget);
	m_showWidget->setLayout(pLayout);

    m_pTableView = new GlodonTableView(m_showWidget);
    m_pTableView->setModel(m_model);
    m_pTableView->setItemDelegate(new GlodonTableViewDelegate(m_pTableView));

    pLayout->addWidget(m_pTableView);

    return m_showWidget;
}

QWidget *MainWindow::loadFilterTableView()
{
    m_showWidget = new QWidget(this);
    QHBoxLayout *pLayout = new QHBoxLayout(m_showWidget);
    m_showWidget->setLayout(pLayout);

    m_filterTableView = new GlodonFilterTableView(m_showWidget);
    m_filterTableView->setModel(m_model);
    m_filterTableView->setItemDelegate(new GlodonTableViewDelegate(m_pTableView));

    pLayout->addWidget(m_filterTableView);
    return m_showWidget;
}

QWidget *MainWindow::loadFooterTableView()
{
    m_showWidget = new QWidget(this);
    QHBoxLayout *pLayout = new QHBoxLayout(m_showWidget);
    m_showWidget->setLayout(pLayout);

    m_footerTableView = new GlodonFooterTableView(m_showWidget);
    m_footerTableView->setModel(m_model);
    m_footerTableView->setItemDelegate(new GlodonTableViewDelegate(m_footerTableView));

    pLayout->addWidget(m_footerTableView);

    return m_showWidget;
}

QList<QStringList> MainWindow::loadSimbolText()
{
//	HMODULE hGDI32=LoadLibrary(_T("GDI32.dll"));
    QLibrary myLib("GDI32.dll");
    typedef void (*MyPrototype)();
    MyPrototype myFunction = (MyPrototype) QLibrary::resolve("GDI32.dll", "EnableEUDC");
    if (myFunction)
        myFunction();

//	EnableEUDC = (ProcEnableEUDC)GetProcAddress(hGDI32, "EnableEUDC");
//	EnableEUDC(false);

	QString fileName = QCoreApplication::applicationDirPath() + "/SpecialSymbols.txt";
	QTextStream textStream;
	m_simbolText = "";

	QFile oSymbolFile(fileName);
	if (oSymbolFile.open(QIODevice::ReadOnly))
	{
		textStream.setDevice(&oSymbolFile);

		m_simbolText = textStream.readAll();
	}
	oSymbolFile.close();
	QStringList slines = m_simbolText.split("\r\n");

	for (int i = 0; i < slines.count(); ++i)
	{
		QString oLine = slines[i];

		QStringList oSymbolsList = oLine.split(",");
		m_simbolList.push_back(oSymbolsList);
	}
	return m_simbolList;
}

void MainWindow::loadFont()
{
    QString filename = QCoreApplication::applicationDirPath() + "/GrandSoft_GBQ_V2.ttf";
	int index = QFontDatabase::addApplicationFont(filename);
	G_UNUSED(index);
}

void MainWindow::initWidget()
{
	m_simbolWidget = new QWidget(NULL);
	m_simbolWidget->setFixedSize(QSize(500, 380));
	QVBoxLayout *pSimbolVLayout = new QVBoxLayout(m_simbolWidget);

	testGlodonSimbolTable();
	pSimbolVLayout->addWidget(m_simbolTable);

	m_lineEdit1 = new QLineEdit(m_simbolWidget);
	pSimbolVLayout->addWidget(m_lineEdit1);

	m_lineEdit2 = new QLineEdit(m_simbolWidget);
	pSimbolVLayout->addWidget(m_lineEdit2);

//	QFont oFont(QFont("EUDC"));
    QFont::insertSubstitution("simsun", "EUDC");
//	m_lineEdit1->setFont(oFont);
//	m_lineEdit2->setFont(oFont);
//    m_gspTableView->setFont(oFont);
//    m_pTableView->setFont(oFont);
//    m_footerTableView->setFont(oFont);
//    m_filterTableView->setFont(oFont);

    connect(m_simbolTable, &GlodonSimbolTable::showText, this, &MainWindow::displayOnLineEdit);
}

void MainWindow::loadGSPTableView()
{
    m_showWidget = new QWidget(this);
    m_gsplayout = new QHBoxLayout(m_showWidget);
    m_showWidget->setLayout(m_gsplayout);

    m_gspModel = gspEngine().createModel(true);
    GSPModelPersistent(m_gspModel).loadFromFile(exePath() + "GBG.GSP", false, false);

    GSPViews iViews;
    iViews.push_back(m_gspModel[0].findTable("FBFX").createView("", NULL));
    iViews.push_back(m_gspModel[0].findTable("NormItem").createView("", NULL));
    iViews.push_back(m_gspModel[0].findTable("NormItemUsage").createView("", NULL));

    m_dataSource = new GSPGridDataSource;
    m_dataSource->setViews(iViews);
    m_dataSource->setGridSettingFileName(exePath() + "GBG.GSF");
    m_dataSource->setActive(true);

    m_dataSourceModel = new GSPGridDataSourceModel;
    m_dataSourceModel->setDataSource(m_dataSource);
//    m_dataSourceModel->setViews(iViews);
//    m_dataSourceModel->setGridSettingFileName(exePath() + "GBG.GSF");
    m_dataSourceModel->setActive(true);

    m_gspTableView = new GSPTableView(m_showWidget);
    m_gspTableView->setModel(m_dataSourceModel);


    GSPTableViewDelegate *tableViewDelegate = new GSPTableViewDelegate(this);
    tableViewDelegate->setDataSourceModel(m_dataSourceModel);

    m_gspTableView->setItemDelegate(tableViewDelegate);
    m_gsplayout->addWidget(m_gspTableView);
}

void MainWindow::showPopWidget()
{
	m_simbolWidget->show();
}

void MainWindow::displayOnLineEdit(const QString &text)
{
//    ushort gd[]={0xE000,0};
//    QString gteq = QString::fromUtf16(gd);
//    qDebug() << gteq;
//    m_lineEdit1->setText(text);

//    QKeyEvent keyPress(QEvent::KeyPress,Qt::Key_unknown, Qt::NoModifier, text);
//    qDebug() << keyPress.text();
//    QCoreApplication::sendEvent(m_pTableView->focusWidget(), &keyPress);
//    QCoreApplication::postEvent(m_lineEdit1, &keyPress);

//    bool result = QCoreApplication::sendEvent(m_lineEdit1, &keyPress);
//    qDebug() << "<QCoreApplication::sendEvent>----result:" << result;
//    m_gspTableView->dataModel()->setData(curIndex, text, Qt::EditRole);
//    m_dataSourceModel->setData(curIndex, text, Qt::EditRole);

    //GlodonTableView
//    QModelIndex curIndex = m_pTableView->currentIndex();
//    m_model->setData(curIndex, text, Qt::EditRole);

    // GSPTableView
    QModelIndex curIndex = m_dataSourceModel->currentIndex();
    m_dataSourceModel->setData(curIndex, text, Qt::EditRole);
    qDebug() <<  m_dataSourceModel->data(curIndex);
//    GSPModelPersistent(m_gspModel).saveToFile(exePath() + "GBG.GSP");

    // GlodonFooterTableView
//    QModelIndex curIndex = m_footerTableView->currentIndex();
//    m_footerTableView->model()->setData(curIndex, text, Qt::EditRole);
//    qDebug() <<  m_footerTableView->model()->data(curIndex);

    //GlodonFilterTableView
//    QModelIndex curIndex = m_filterTableView->currentIndex();
//    m_filterTableView->model()->setData(curIndex, text, Qt::EditRole);
}

GEditStyle GlodonTableViewDelegate::editStyle(const QModelIndex &index, bool &readOnly) const
{
    if (1 == index.column())
	{
		return esLineEdit;
	}
    else if (2 == index.column())
    {
        return esDropDownWindow;
    }
	else if (3 == index.column())
	{
		return esPlainEllipsis;
	}
	else if (4 == index.column())
	{
		return esDropDown;
	}
	else
	{
		return GlodonDefaultItemDelegate::editStyle(index, readOnly);
	}
}

void GlodonTableViewDelegate::initComboBox(QComboBox *comboBox, const QModelIndex &index) const
{
	comboBox->addItem("+++test1");
	comboBox->addItem("+++test2");
	comboBox->addItem("+++test3");
	comboBox->addItem("+++test4");
	comboBox->addItem("+++test5");
	comboBox->addItem("+++test6");
	comboBox->addItem("+++test7");
	comboBox->addItem("+++test8");
	comboBox->addItem("+++test9");
	comboBox->addItem("+++test10");
	comboBox->addItem("+++test11");
	comboBox->addItem("+++test12");
	comboBox->addItem("+++test13");
	comboBox->addItem("+++test14");
	comboBox->addItem("+++test15");
	G_UNUSED(index);
}

GSPTableViewDelegate::GSPTableViewDelegate(QObject *parent)
    : GSPDefaultItemDelegate(parent)
{
}

GEditStyle GSPTableViewDelegate::editStyle(const QModelIndex &index, bool &readOnly) const
{
    return esDropDownWindow;
    G_UNUSED(readOnly);
}
