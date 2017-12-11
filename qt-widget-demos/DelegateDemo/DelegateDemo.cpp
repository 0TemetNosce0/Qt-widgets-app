#include "DelegateDemo.h"
#include "ui_DelegateDemo.h"
#include "GLDDefaultItemDelegate.h"
#include "GLDMultiHeaderView.h"
#include "GLDTableViewExport.h"
#include "GSPCore.h"

#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

DelegateDemo::DelegateDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DelegateDemo)
{
    ui->setupUi(this);

    loadData();
    initTableView();
    doSomeTest();

    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->addWidget(m_tableView);

    m_debugButton = new QPushButton(QStringLiteral("²âÊÔ"));
    connect(m_debugButton, SIGNAL(clicked()), this, SLOT(debug()));

    pLayout->addWidget(m_debugButton);
    ui->centralWidget->setLayout(pLayout);
}

DelegateDemo::~DelegateDemo()
{
    delete ui;
}

void DelegateDemo::loadData()
{
    m_tableView = new GSPTableView(this);

//    m_tableView->setStyleSheet("QTableCornerButton::section{background:red;}");
    m_tableView->horizontalHeader()->setStyleSheet("GlodonHeaderView::section{height:50px;}");
//    m_tableView->horizontalHeader()->setStyleSheet("GlodonHeaderView::section{background:red;}");
    m_tableView->verticalHeader()->setStyleSheet("GlodonHeaderView::section{width:50px;}");
    m_tableView->verticalHeader()->setStyleSheet("GlodonHeaderView::section{background:green;}");
    m_tableView->setStyleSheet("GTableCornerbutton::section{background:red;}");
//    m_tableView->setStyleSheet("GTableCornerbutton::section{border-image:url(E:/pg.png);}");

    m_model = gspEngine().createModel();
    GSPModelPersistent(m_model).loadFromFile(exePath() + "DelegateDemo.GSP");

    GSPViews views;
    views.push_back(m_model[0].findTable("DelegateDemo").createView(""));

    m_gridDataSourceModel = new GSPGridDataSourceModel(m_tableView);
    m_gridDataSourceModel->dataSource()->setViews(views);

    m_gridDataSourceModel->setGridSettingFileName(exePath() + "DelegateDemo.GSF");

    m_gridDataSourceModel->setActive(true);
    GSPGridDataSource *pDataSource = dynamic_cast<GSPGridDataSource *>(m_gridDataSourceModel->dataSource());
    if (pDataSource)
    {
        pDataSource->setMultiRowMerge(false);
    }
}

void DelegateDemo::initTableView()
{
    m_tableView->setModel(m_gridDataSourceModel);
//    m_tableView->viewport()->installEventFilter(this);
    m_tableView->setAllowSelectRow(true);
//    m_tableView->setAllowSelectCol(false);
    m_tableView->setAllowCopy(true);
    m_tableView->setAllowPaste(true);
    m_tableView->horizontalHeader()->setMovable(true);
    m_tableView->setAllow3DStyle(true);
//    m_tableView->setAllowSelectCol(false);
//    m_tableView->setAllowSelectRow(false);

//    GIntList *list = new GIntList;
//    for (int i = 0; i < m_tableView->horizontalHeader()->count(); i++)
//    {
//        list->push_back(i);
//    }
//    m_tableView->setFitColWidths(list);

//    m_tableView->setRowHeight(0, 0, true);
//    m_tableView->setColumnWidth(0, 0);
//    m_tableView->setDragEnabled(true);
//    m_tableView->horizontalHeader()->setStyleSheet("GlodonHeaderView::section{background:red;}");
//    m_tableView->setStyleSheet("GTableCornerbutton::section{background:red;}");
}

void DelegateDemo::doSomeTest()
{
    //m_tableView->setAlwaysShowEditorPro(true);
    //m_tableView->setHideEditOnExit(true);
    //m_tableView->setEditStyleDrawType(GlodonAbstractItemView::SdtAll);
}

bool DelegateDemo::eventFilter(QObject *object, QEvent *event)
{
    return QMainWindow::eventFilter(object, event);
}

void DelegateDemo::debug()
{
    qDebug() << "If the m_tableView is tree:" << m_tableView->isTree();
    GString strFile = QFileDialog::getSaveFileName(this, QObject::tr("excel"),
                                                   QObject::tr("myExcel"), QObject::tr("Excel File(*.xls)"));
    if (strFile != "")
    {
        GlodonTableViewToExcel::execute(m_tableView, strFile, tr("1-2"));
    }

//    bool bSuccessed;
//    m_tableView->copyTextFromSelections(&bSuccessed);
//    if(!bSuccessed)
//    {
//        qDebug() << "can not!";
//    }
}

void TestEventHandler::onGetDropDownList(GSPCustomRowNode *rowNode,
    int col, GSPField field, GSPRecord record, GStrings &items,
    GStrings &pickResult, unsigned int &dropDownRows, bool &handled)
{
    G_UNUSED(rowNode);
    G_UNUSED(col);
    G_UNUSED(record);
    G_UNUSED(dropDownRows);

    if ((NULL != field) && (sameText(field.fieldName(), "Combobox")))
    {
        int nIndex = items.indexOf(QStringLiteral("One"));
        if (nIndex != -1)
        {
            items.removeAt(nIndex);
        }
        nIndex = pickResult.indexOf("");
        if (nIndex != -1)
        {
            pickResult.removeAt(nIndex);
        }

        handled = true;
    }
}
