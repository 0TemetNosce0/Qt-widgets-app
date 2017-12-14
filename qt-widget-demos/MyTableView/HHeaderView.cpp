#include <QPainter>
#include <QMouseEvent>
#include <QIcon>
#include <QCursor>
#include <QMenu>
#include <QAction>

#include "HHeaderView.h"
#include "HHeaderItemDelegate.h"
#include "HHeaderModel.h"
#include "DataTreeView.h"

HHeaderView* HHeaderView::m_Instance = NULL;

HHeaderView::HHeaderView(Qt::Orientation orientation, QWidget * parent)
    : QHeaderView(orientation, parent)
{
    m_Instance = this;

    //���ô����ɴ�����л���Ԫ��
    HHeaderItemDelegate* delegate = new HHeaderItemDelegate();
    setItemDelegate(delegate);

    connect(this, SIGNAL(sectionResized(int,int,int)), this, SLOT(onSectionResized(int,int,int)));

    this->setSectionResizeMode(QHeaderView::Interactive);
    //setCascadingSectionResizes(true);

    //this->setOffset(-5);
	this->setSectionsMovable(true);

    this->setSectionsClickable(true);
    //setMinimumSectionSize(166);
    //setStretchLastSection(true);
    //setHighlightSections(true);

    //setAttribute(Qt::WA_Hover, false);

	this->setWindowIcon(QIcon(":/Resources/logo.ico"));

   // setDefaultSectionSize(100);

    m_menu = new QMenu(this);
    m_actHideCol = new QAction(this);
    m_actHideCol->setText(QStringLiteral("������"));
    m_actHideCol->setIcon(QIcon(":/Resources/scene.svg"));

    m_actsortUp = new QAction(this);
    m_actsortUp->setText(QStringLiteral("��A->Z����"));
    m_actsortUp->setIcon(QIcon(":/Resources/scene.svg"));

    m_actSortDown = new QAction(this);
    m_actSortDown->setText(QStringLiteral("��Z->A����"));
    m_actSortDown->setIcon(QIcon(":/Resources/scene.svg"));

    m_menu->addAction(m_actHideCol);
    m_menu->addAction(m_actsortUp);
    m_menu->addAction(m_actSortDown);

    m_menu->hide();
}

HHeaderView::~HHeaderView()
{
}
 
int HHeaderView::sectionSizes(int lIndex, int sectionCount)
{
    int width = 0;
    for(int i = lIndex; i < lIndex + sectionCount; ++i)
    {
        width += sectionSize(i);
    }

    return width;
}

QSize HHeaderView::sectionSizeFromContents(int logicalIndex) const
{
    //return QHeaderView::sectionSizeFromContents(logicalIndex);
    QSize size;
    int maxWidth = 0;

    HHeaderModel* model = static_cast<HHeaderModel*> (this->model());
    for(int i = 0; i < model->rowCount(QModelIndex()); ++i)
    {
        QFont fnt;
        QStyleOptionHeader opt;
        initStyleOption(&opt);
        fnt.setBold(true);
        opt.text = model->item(i, logicalIndex);
        opt.fontMetrics = QFontMetrics(fnt);
        size = style()->sizeFromContents(QStyle::CT_HeaderSection, &opt, QSize(), this);
        maxWidth = qMax(maxWidth, size.width());
    }

    return QSize(maxWidth + 4, size.height() * model->rowCount(QModelIndex())); //��Ҫ�����ø߶ȣ����������ָ��û���ã���Ҫ��headerview�ĸ�����������
}

void HHeaderView::paintEvent(QPaintEvent *event)
{
    QPainter painter(viewport());
    QMultiMap<int, int> rowSpanList;

    int cnt = this->count ();
    int curRow, curCol;

    HHeaderModel* model = static_cast<HHeaderModel*> (this->model());
    for(int row = 0; row < model->rowCount(QModelIndex()); ++row)
    {
        for(int col = 0; col < model->columnCount(QModelIndex()); ++col)
        {
            curRow = row;
            curCol = col;

            QStyleOptionViewItemV4 opt = viewOptions();

            QStyleOptionHeader header_opt;
            initStyleOption(&header_opt);

            header_opt.textAlignment = Qt::AlignCenter;
           // header_opt.icon = QIcon("./Resources/logo.ico");
            QFont fnt;
            fnt.setBold(true);
            header_opt.fontMetrics = QFontMetrics(fnt);

            opt.fontMetrics = QFontMetrics(fnt);
            QSize size = style()->sizeFromContents(QStyle::CT_HeaderSection, &header_opt, QSize(), this);
            
           // size.setHeight(25);
            header_opt.position = QStyleOptionHeader::Middle;

            //�жϵ�ǰ���Ƿ��������ͣ״̬
            if(m_hoverIndex == model->index(row, col, QModelIndex()))
            {
                header_opt.state |= QStyle::State_MouseOver;
               // header_opt.state |= QStyle::State_Active;
            }

            opt.text = model->item(row, col);
            header_opt.text = model->item(row, col);
          
            CellSpan span = model->getSpan(row, col);

            int rowSpan = span._rowSpan;
            int columnSpan = span._colSpan;

            if(columnSpan > 1 && rowSpan > 1)
            {//��Ԫ���Խ���кͶ���, ��֧�֣���Ϊ����1��
                continue;
                /*header_opt.rect = QRect(sectionViewportPosition(logicalIndex(col)), row * size.height(), sectionSizes(col, columnSpan), rowSpan * size.height());
                opt.rect = header_opt.rect;
                col += columnSpan - 1; */
            }
            else if(columnSpan > 1)
            {//��Ԫ���Խ����
                header_opt.rect = QRect(sectionViewportPosition(logicalIndex(col)), row * size.height(), sectionSizes(col, columnSpan), size.height());
                opt.rect = header_opt.rect;
                col += columnSpan - 1; 
            }
            else if(rowSpan > 1)
            {//��Ԫ���Խ����
                header_opt.rect = QRect(sectionViewportPosition(logicalIndex(col)), row * size.height(), sectionSize(logicalIndex(col)), size.height() * rowSpan);
                opt.rect = header_opt.rect;
                for(int i = row + 1; i <= rowSpan - 1; ++i)
                {
                    rowSpanList.insert(i, col);
                }
            }
            else
            {//�����ĵ�Ԫ��
                header_opt.rect = QRect(sectionViewportPosition(logicalIndex(col)), row * size.height(), sectionSize(logicalIndex(col)), size.height());
                opt.rect = header_opt.rect;
            }

            opt.state = header_opt.state;

            //opt.displayAlignment = Qt::AlignCenter;
                
            opt.icon = QIcon("./Resources/logo.ico");
            //opt.backgroundBrush = QBrush( QColor(255,0,0));
            QMultiMap<int, int>::iterator it = rowSpanList.find(curRow, curCol);
            if(it == rowSpanList.end())
            {
                //���浱ǰitem�ľ���
                m_itemRectMap[curRow][curCol] = header_opt.rect;
                itemDelegate()->paint(&painter, opt, model->index(curRow, curCol, QModelIndex()));
            }
            else
            {
                //����ǿ�Խ����1�е����������Ĭ�ϵ�paint
            }
        }
    }
}

void HHeaderView::onSectionResized(int logicalIndex, int oldSize, int newSize)
{
    if (0 == newSize)
    {//���˵������е��µ�resize
        viewport()->update();
        return;
    }

    static bool selfEmitFlag = false;
    if (selfEmitFlag)
    {
        return;
    }

    int minWidth = 99999;
    QFontMetrics metrics(this->font());
    //��ȡ��������С�������ȣ��ƶ��ĳ��Ȳ��ܴ�����С��������
    HHeaderModel* model = static_cast<HHeaderModel*> (this->model());
    for(int i = 0; i < model->rowCount(QModelIndex()); ++i)
    {
        QString text =  model->item(i, logicalIndex);
        if (text.isEmpty())
            continue;

        int textWidth = metrics.width(text);
        if (minWidth > textWidth)
        {
            minWidth = textWidth;
        }
    }

    if (newSize < minWidth)
    {
        selfEmitFlag = true;
        this->resizeSection(logicalIndex, oldSize);
        selfEmitFlag = false;
    }

    viewport()->update();
}
/*
int HHeaderView::sectionSizeHint(int logicalIndex)
{
    if (logicalIndex == 0)
    {
        return 10;
    }
}
*/
 //�����ǰ���λ�����ڵ�index
QModelIndex HHeaderView::indexAt(const QPoint& pos) const
{
    int x = pos.x();
    int y = pos.y();

    QMap<int, QRect>::const_iterator iterCol;
    QMap<int, QMap<int, QRect> >::const_iterator iterRow = m_itemRectMap.begin();
    for (; iterRow != m_itemRectMap.end(); ++iterRow)
    {
        for (iterCol = iterRow.value().begin(); iterCol != iterRow.value().end(); ++iterCol)
        {
            if(x > iterCol.value().x() && x < iterCol.value().x() + iterCol.value().width() &&
                y > iterCol.value().y() && y < iterCol.value().y() + iterCol.value().height())
            {
                return model()->index(iterRow.key(), iterCol.key(), QModelIndex());
            }
        }
    }

    return QModelIndex();
}

void HHeaderView::mouseMoveEvent(QMouseEvent *event)
{
    QHeaderView::mouseMoveEvent(event);
    QModelIndex index = indexAt(event->pos());
    if (!index.isValid())
    {
        QHeaderView::mouseMoveEvent(event);
        return;
    }

    //���浱ǰhover��index
    m_hoverIndex = index;
    
    int row = index.row();
    int col = index.column();
    //�ж��Ƿ����Զ���menu
    if (isCustomMenuEnable(row, col))
    {
        QRect rect = menuRect(row, col);
        QPoint pos = this->mapFromGlobal(QCursor::pos());
        if (rect.contains(pos))
        {
            setCustomMenuState(row, col, 1);
        }
        else
        {
            setCustomMenuState(row, col, 0);
        }
    }

    viewport()->update();
    QHeaderView::mouseMoveEvent(event);
}

void HHeaderView::mousePressEvent ( QMouseEvent * event )
{
    m_pressIndex = indexAt(event->pos());
     viewport()->update();
     QHeaderView::mousePressEvent(event);
}

void HHeaderView::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressIndex = QModelIndex();

    int row = indexAt(event->pos()).row();
    int col = indexAt(event->pos()).column();
    //�ж��Ƿ����check
    if (isCheckedEnable(row, col))
    {
        Qt::CheckState state = checkedState(row, col) == Qt::Unchecked ? Qt::Checked : Qt::Unchecked;
        setCheckedState(row, col, state);

        //��Ҫͬ������dataview��ѡ��״̬
        DataTreeView::m_Instance->updateCheckStateByCol(col, state);
    }
    //�ж��Ƿ��������
    if (isSortedEnable(row, col))
    {
        int direction = sortedDirection(row, col) != 1 ? 1 : 0;
        setSortedDirection(row, col, direction);

        if (1 == direction)
        {
            sortDown(row, col);
        }
        else if (0 == direction)
        {
            sortUp(row, col);
        }
    }

    QPoint pos = this->mapFromGlobal(QCursor::pos());

    //�ж��Ƿ����Զ���menu
    if (isCustomMenuEnable(row, col))
    {
        QRect rect = menuRect(row, col);     
        if (rect.contains(pos))
        {
            m_actHideCol->setEnabled(hiddenSectionCount() < count() - 1);
            QAction* act = m_menu->exec(mapToGlobal(event->pos()));
            if (act == m_actHideCol)
            {
                m_hideColSet.insert(col); // ���浽�����б���

                hideSection(col);
                //updateSection(col - 1);             
            }
            else if (act == m_actsortUp)
            {
                sortUp(row, col);
            }
            else if (act == m_actSortDown)
            {
                sortDown(row, col);
            }
        }
    }

    //�ж�ǰ������Ƿ�����
    if (isColHide(col - 1))
    {
        QRect rect = prevRect(row, col);
        if (rect.contains(pos))
        {
            showSection(col - 1);
            //updateSection(col - 2);
            
            //�������б���ɾ����¼
            m_hideColSet.remove(col - 1);
        }
    }

    //�жϺ�������Ƿ�����
    if (isColHide(col + 1))
    {
        QRect rect = nextRect(row, col);
        if (rect.contains(pos))
        {
            showSection(col + 1);
            //updateSection(col + 2);

            //�������б���ɾ����¼
            m_hideColSet.remove(col + 1);
        }
    }

    //��Ҫ���½���
    viewport()->update();

    QHeaderView::mouseReleaseEvent(event);
}

bool HHeaderView::event(QEvent* event )
{
    if (event->type() == QEvent::Leave)
    {//�����뿪headerviewʱ��ȡ��hover״̬
        m_hoverIndex = QModelIndex();
        viewport()->update(); //������Ҫupdate��Ҫ�����治����
    }

    return true;
}


void HHeaderView::setCheckedEnable(int row, int col, bool Flag)
{
    m_itemStateMap[row][col]._isChecked = Flag;
}

bool HHeaderView::isCheckedEnable(int row, int col)
{
    return m_itemStateMap[row][col]._isChecked;
}

void HHeaderView::setCheckedState(int row, int col, Qt::CheckState state)
{
    m_itemStateMap[row][col]._checkedState = state;
}

Qt::CheckState HHeaderView::checkedState(int row, int col)
{
    return m_itemStateMap[row][col]._checkedState;
}

void HHeaderView::setSortedEnable(int row, int col, bool Flag)
{
    m_itemStateMap[row][col]._isSorted = Flag;
}

bool HHeaderView::isSortedEnable(int row, int col)
{
    return m_itemStateMap[row][col]._isSorted;
}

void HHeaderView::setSortedDirection(int row, int col, int direction)
{
    m_itemStateMap[row][col]._sortedDirection = direction;
}

int HHeaderView::sortedDirection(int row, int col)
{
    return m_itemStateMap[row][col]._sortedDirection;
}

void HHeaderView::setCustomMenuEnbale(int row, int col, bool Flag)
{
    m_itemStateMap[row][col]._isCustomMenu = Flag;
}

bool HHeaderView::isCustomMenuEnable(int row, int col)
{
    return m_itemStateMap[row][col]._isCustomMenu;
}

void HHeaderView::setCustomMenuState(int row, int col, int state)
{
    m_itemStateMap[row][col]._menuEnabled = state;
}

int HHeaderView::customMenuState(int row, int col)
{
    return m_itemStateMap[row][col]._menuEnabled;
}

QRect HHeaderView::menuRect(int row, int col)
{
    QRect sectionRect = m_itemRectMap[row][col];
    return QRect(sectionRect.right() - 5 - 13, sectionRect.center().y() - 6, 13, 13);
}

bool HHeaderView::isColHide(int col)
{
    if (m_hideColSet.end() == m_hideColSet.find(col))
        return false;

    return true;
}

QRect HHeaderView::prevRect(int row, int col)
{
    QRect sectionRect = m_itemRectMap[row][col];
    return QRect(sectionRect.left() + 1, sectionRect.center().y() - 6, 13, 13);
}

QRect HHeaderView::nextRect(int row, int col)
{
    QRect sectionRect = m_itemRectMap[row][col];
    return QRect(sectionRect.right() - 13, sectionRect.center().y() - 6, 13, 13);
}

void HHeaderView::sortUp(int row, int col)
{
    return;
}

void HHeaderView::sortDown(int row, int col)
{
    return;
}

bool HHeaderView::isItemPress(int row, int col)
{
    if (!m_pressIndex.isValid())
        return false;

    if (row == m_pressIndex.row() && col == m_pressIndex.column())
        return true;

    return false;
}

void HHeaderView::resizeLastSection(bool increase)
{
    int count = this->count();
    int width = this->sectionSize(count - 1);

    if (increase)
    {
        this->resizeSection(count - 1, width + 1);
    }
    else
    {
        this->resizeSection(count - 1, width - 1);
    }
}
