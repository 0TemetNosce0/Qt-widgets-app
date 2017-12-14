#include <QApplication>
#include <QPainter>

#include "HHeaderItemDelegate.h"
#include "HHeaderView.h"

HHeaderItemDelegate::HHeaderItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void HHeaderItemDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    int row = index.row();
    int col = index.column();

    const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
    
    QRect smallRect;

    //�ж��Ƿ���checkbox
    if (HHeaderView::m_Instance->isCheckedEnable(row, col))
    {
        smallRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                        QSize(option.fontMetrics.width(index.data(Qt::DisplayRole).toString()) + 25, option.fontMetrics.height() + 3),
                                        option.rect);
    }
    else
    {
        smallRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                        QSize(option.fontMetrics.width(index.data(Qt::DisplayRole).toString()) + 8, option.fontMetrics.height() + 3),
                                        option.rect);
    }
    
    QStyleOptionHeader header_opt;
    header_opt.rect = option.rect;
    header_opt.position = QStyleOptionHeader::Middle;
    header_opt.textAlignment = Qt::AlignCenter;

    header_opt.state = option.state;
    //header_opt.state |= QStyle::State_HasFocus;//QStyle::State_Enabled | QStyle::State_Horizontal | QStyle::State_None | QStyle::State_Raised;

    //�ж��Ƿ��ܹ�����  
    if (HHeaderView::m_Instance->isSortedEnable(row, col))
    {//��������
        //��ȡ����ǰ������˳��
        int ret = HHeaderView::m_Instance->sortedDirection(row, col);
        if (0 == ret)
        {
            header_opt.sortIndicator = QStyleOptionHeader::SortUp;
        }
        else if (1 == ret)
        {
            header_opt.sortIndicator = QStyleOptionHeader::SortDown;
        }
        else
        {
            header_opt.sortIndicator = QStyleOptionHeader::None;
        }    
    }
    
    if (HHeaderView::m_Instance->isItemPress(row, col))
    {
        header_opt.state |= QStyle::State_Sunken; //��ť����Ч��
    }

   // if ((QApplication::mouseButtons() && (Qt::LeftButton || Qt::RightButton)))
   //             header_opt.state |= QStyle::State_Sunken;

    painter->save();
    QApplication::style()->drawControl(QStyle::CE_Header, &header_opt, painter);
    painter->restore();

    painter->setPen(QColor(255,0,0));

    QStyleOptionViewItemV4 xopt(option);

    xopt.state &= ~QStyle::State_MouseOver;

    if (HHeaderView::m_Instance->isCheckedEnable(row, col))
    {//�ж��Ǹõ�Ԫ���Ƿ���checkbox
        xopt.features |= QStyleOptionViewItemV4::HasCheckIndicator;

        //�ж�checkbox��״̬
        Qt::CheckState state = HHeaderView::m_Instance->checkedState(row, col);
        if (Qt::Unchecked == state)
        {
            xopt.state |= QStyle::State_Off;
        }
        else if (Qt::PartiallyChecked == state)
        {
            xopt.state |= QStyle::State_NoChange;
        }
        else if (Qt::Checked == state)
        {
            xopt.state |= QStyle::State_On;
        }
    }  

    xopt.rect = smallRect;
   // xopt.rect = option.rect;
    //xopt.rect.setLeft(xopt.rect.left() + 10);
    //xopt.rect.setRight(xopt.rect.right() - 10);

    if (!HHeaderView::m_Instance->isColHide(col))
    {
        QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &xopt, painter);

         //����Ҫ�ж��Ƿ���hover״̬
        if (header_opt.state & QStyle::State_MouseOver)
        {
            //�ж��Ƿ��ܹ������������������ʾͼ��
            if (HHeaderView::m_Instance->isCustomMenuEnable(row, col))
            {
                drawMenuBtn(row, col, option.rect, painter);      
            }    
        }

         //�ж�ǰ��1���Ƿ����أ���������ˣ���Ҫ����߻������Ƿ���
        if (HHeaderView::m_Instance->isSectionHidden(col - 1))
        {
            drawPreBtn(option.rect, painter);
        }

        //�жϺ���1���Ƿ����أ���������ˣ���Ҫ���ұ߻������Ƿ���
        if (HHeaderView::m_Instance->isSectionHidden(col + 1))
        {
            drawNextBtn(option.rect, painter);
        }
    }  
}


bool HHeaderItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return false;
}

void HHeaderItemDelegate::drawMenuBtn(int row, int col, const QRect& rect, QPainter* painter) const
{
    QRect brect = QRect(rect.right() - 5 - 13, rect.center().y() - 6, 13, 13);

    //�ж�����Ƿ���menu�����棬����ǣ���Ҫ�ú�ɫ��ʾ�������ɫ
    int state = HHeaderView::m_Instance->customMenuState(row, col);
    bool enabled = (state == 1 ? true : false);

    painter->save();
    painter->setPen(enabled ? QColor(186, 186, 186) : QColor(223, 223, 223));
    painter->setBrush(QColor(246, 246, 246));
    painter->drawRect(brect.adjusted(0, 0 ,-1, -1));

    painter->setPen(enabled ? QColor(71, 71, 71) : QColor(193, 193, 193));
    painter->drawLine(brect.left() + 3, brect.top() + 5, brect.right() - 3, brect.top() + 5);
    painter->drawLine(brect.left() + 4, brect.top() + 6, brect.right() - 4, brect.top() + 6);
    painter->drawLine(brect.left() + 5, brect.top() + 7, brect.right() - 5, brect.top() + 7);
    painter->drawPoint(brect.left() + 6, brect.top() + 8);
    painter->restore();
}

void HHeaderItemDelegate::drawPreBtn(const QRect& rect, QPainter* painter) const 
{
    QRect brect = QRect(rect.left() + 1, rect.center().y() - 6, 13, 13);

    painter->save();
    painter->setPen(QColor(71, 71, 71));
    painter->drawLine(brect.left() + 1, brect.center().y() - 3, brect.left() + 1, brect.center().y() + 3);
    painter->drawLine(brect.left() + 2, brect.center().y() - 2, brect.left() + 2, brect.center().y() + 2);
    painter->drawLine(brect.left() + 3, brect.center().y() - 1, brect.left() + 3, brect.center().y() + 1);
    painter->drawPoint(brect.left() + 4, brect.center().y());
    painter->restore();
}

void HHeaderItemDelegate::drawNextBtn(const QRect& rect, QPainter* painter) const
{
    QRect brect = QRect(rect.right() - 13, rect.center().y() - 6, 13, 13);;

    painter->save();
    painter->setPen(QColor(71, 71, 71));
    painter->drawLine(brect.right() - 2, brect.center().y() - 3, brect.right() - 2, brect.center().y() + 3);
    painter->drawLine(brect.right() - 3, brect.center().y() - 2, brect.right() - 3, brect.center().y() + 2);
    painter->drawLine(brect.right() - 4, brect.center().y() - 1, brect.right() - 4, brect.center().y() + 1);
    painter->drawPoint(brect.right() - 5, brect.center().y());
    painter->restore();
}
