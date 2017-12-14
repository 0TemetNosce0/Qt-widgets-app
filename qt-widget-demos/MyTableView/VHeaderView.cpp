#include <QMouseEvent>
#include <QPainter>

#include "VHeaderView.h"
#include "DataTreeView.h"

VHeaderView* VHeaderView::m_Instance = NULL;

VHeaderView::VHeaderView(Qt::Orientation orientation, QWidget * parent) : QHeaderView(orientation, parent)
{
    m_Instance = this;
    this->setSectionResizeMode(QHeaderView::Fixed);
    m_selectRow = -1;
}

VHeaderView::~VHeaderView()
{

}

void VHeaderView::mousePressEvent ( QMouseEvent * event )
{
    //��ȡ��ǰ������к�
    int row = this->logicalIndexAt (event->pos());

    //�����к�
    m_selectRow = row;

    //��ȡ��ǰ���е����νڵ��index
    QModelIndex selIndex = DataTreeView::m_Instance->rowIndex(row);
    if (!selIndex.isValid())
        return;

    //��ȡ���ε�ѡ��ģ��
    QItemSelectionModel* selModel = DataTreeView::m_Instance->selectionModel();
    if (NULL == selModel)
        return;

    //���֮ǰѡ�е�
    selModel->clear();

    //ѡ�е�ǰ��
    selModel->setCurrentIndex(selIndex, QItemSelectionModel::Rows | QItemSelectionModel::Select);

    //��Ҫ����Ϊ���㣬���ܸ�����ʾ
    DataTreeView::m_Instance->setFocus();
}

//�����������أ����paintevent�� �ػ�ÿһ��
void VHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    //�ȵ���Ĭ�ϵĴ���
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    //�ж��Ƿ�ѡ�У����ѡ���˵�ǰ�У���Ҫ��һ�����Ƿ���
    if (m_selectRow == logicalIndex)
    {
        drawPreBtn(rect, painter);
        viewport()->update();
    }
}

void VHeaderView::drawPreBtn(const QRect& rect, QPainter* painter) const
{
    QRect brect = QRect(rect.right() - 13, rect.center().y() - 6, 13, 13);

    painter->save();
    painter->setPen(QColor(71, 71, 71));
    painter->drawLine(brect.right() - 4, brect.center().y() - 3, brect.right() - 4, brect.center().y() + 3);
    painter->drawLine(brect.right() - 3, brect.center().y() - 2, brect.right() - 3, brect.center().y() + 2);
    painter->drawLine(brect.right() - 2, brect.center().y() - 1, brect.right() - 2, brect.center().y() + 1);
    painter->drawPoint(brect.right() - 1, brect.center().y());
    painter->restore();
}

void VHeaderView::selectRow(int row)
{
    m_selectRow = row;
    viewport()->update();
}
