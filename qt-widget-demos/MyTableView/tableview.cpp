#include "TableView.h"
#include "DataTreeView.h"
#include "HHeaderView.h"

#include <QScrollBar>
#include <QHeaderView>
#include <QEvent>
#include <QWheelEvent>
#include <QTableView>

TableView* TableView::m_Instance = NULL;

TableView::TableView(QWidget *parent)
    : QTableView(parent)
{
    this->setWindowIcon(QIcon(":/Resources/logo.ico"));

    m_dataTree = new DataTreeView(this);
    m_Instance = this;

    //m_dataTree->installEventFilter(this);
    connect(m_dataTree->verticalScrollBar(), SIGNAL(valueChanged(int)), this->verticalScrollBar(), SLOT(setValue(int)));
    //connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), _dataTree->verticalScrollBar(), SLOT(setValue(int)));

    //connect(m_dataTree->horizontalScrollBar(), SIGNAL(valueChanged(int)), this->horizontalScrollBar(), SLOT(setValue(int)));
    connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), m_dataTree->horizontalScrollBar(), SLOT(setValue(int)));

    this->installEventFilter(this);
}

TableView::~TableView()
{

}


void TableView::setModel( QAbstractItemModel * model )
{
    //QTableView::setModel(model);
    m_dataTree->setModel(model);

    init();
}

void TableView::init()
{
    //m_dataTree->setFocusPolicy(Qt::NoFocus);

    //viewport()->stackUnder(_dataTree);

    //m_dataTree->setSelectionModel(selectionModel());
    //for(int col = 0; col < model()->columnCount(); col++)
    {
       // this->setColumnHidden(col, true);
       // m_dataTree->setColumnWidth(col, this->columnWidth(col) );
    }

    m_dataTree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //m_dataTree->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    m_dataTree->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_dataTree->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    //this->verticalHeader()->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    updateFrozenTableGeometry();
}

void TableView::resizeEvent(QResizeEvent * event)
{
    QTableView::resizeEvent(event);    
    updateFrozenTableGeometry();
}

void TableView::paintEvent(QPaintEvent *event)
{
    //table��paint�������ܽ���Ĭ�ϴ���Ҫ���ڽ���resize��ʱ������ҵ� ���������������������ʱ����ʱ������ͷʱҲ��ҵ�
    Q_UNUSED(event);
    return;
}

void TableView::updateFrozenTableGeometry()
{
    int verticalHeaderWidth = verticalHeader()->width();
    int frameWidth = this->frameWidth();
    int viewportWidth = viewport()->width();
    int viewportHeight = viewport()->height();
    int horizontalHeaderHeight = horizontalHeader()->height();

    m_dataTree->setGeometry(verticalHeaderWidth + frameWidth,
        frameWidth, viewportWidth, viewportHeight + horizontalHeaderHeight);

}

/*
void TableView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() < 0)
    {
        int value = this->verticalScrollBar()->value();
        this->verticalScrollBar()->setValue(value + 1 * 30);
    }
    else
    {
        int value = this->verticalScrollBar()->value();
        this->verticalScrollBar()->setValue(value - 1 * 30);
    }
}
*/

bool TableView::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this)
    {
        QEvent::Type type = event->type();

        if(type == QEvent::Show)
        {
            HHeaderView::m_Instance->resizeLastSection(false);
        }
        else if (type == QEvent::Hide)
        {
            HHeaderView::m_Instance->resizeLastSection(true);
        }
    }

    return false;
}
