#include <QPen>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QToolTip>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QApplication>
#include <QStyleOptionButton>

#include "MTableModel.h"
#include "MTableDelegate.h"

QModelIndex MTableDelegate::mouseHoverIndex;

MTableDelegate::MTableDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    isHoverBtnAdd = false;
    isHoverBtnDown = false;
    isHoverBtnPlay = false;

    mouseHoverIndex = QModelIndex();

}

void MTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // ���ƺ���
    painter->setPen(QColor(228,228,228));
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());

    QStyleOptionViewItem  myOption(option);

    if (myOption.state & QStyle::State_HasFocus)
    {
        myOption.state = myOption.state ^ QStyle::State_HasFocus;
    }

    QStyledItemDelegate::paint(painter, myOption, index); // �ȵ��ú��Լ�����ͼƬ������ͼƬ�ᱻ����


    // ���б��л�����ز�����ͼ��
    if (index.column() == 3)
    {
        QPixmap pixmap(":/icons/search_listen.png"); // ����ͼ��

        if (isHoverBtnPlay == true && mouseHoverIndex == index)
        {
            pixmap.load(":/icons/search_listen1.png");
        }
        painter->drawPixmap(option.rect.x()+60, option.rect.y()+4, 26,22, pixmap);


        QPixmap pixmap2(":/icons/search_add.png");

        if (isHoverBtnAdd == true && mouseHoverIndex == index)
        {
            pixmap2.load(":/icons/search_add1.png");
        }

        painter->drawPixmap(option.rect.x()+60+35, option.rect.y()+4, 26,22, pixmap2);// ��Ӱ�ť


        QPixmap pixmap3(":/icons/search_down.png");

        if (isHoverBtnDown == true && mouseHoverIndex == index)
        {
            pixmap3.load(":/icons/search_down1.png");
        }

        painter->drawPixmap(option.rect.x() + 60 + 35 + 35, option.rect.y() + 4, 26, 22, pixmap3); // ���ذ�ť
    }
}

bool MTableDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                 const QStyleOptionViewItem &option, const QModelIndex &index)
{
    isHoverBtnAdd = false;
    isHoverBtnDown = false;
    isHoverBtnPlay = false;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

    if (mouseEvent->type() == QMouseEvent::MouseMove && index.column() == 3)
    {
        mouseHoverIndex = index;

        if (mouseEvent->pos().x() >= option.rect.x() + 60 && mouseEvent->pos().x() <= 86 + option.rect.x())
        {
            isHoverBtnPlay = true;
            QToolTip::showText(mouseEvent->globalPos(), QStringLiteral("����"));
        }
        else if (mouseEvent->pos().x() >= option.rect.x() + 60 + 35 && mouseEvent->pos().x() <= 35 + 86 + option.rect.x())
        {
            isHoverBtnAdd = true;
            QToolTip::showText(mouseEvent->globalPos(), QStringLiteral("��ӵ��б�"));
        }
        else if (mouseEvent->pos().x() >= option.rect.x() + 35 + 35 +60 && mouseEvent->pos().x() <= 35 + 35 + 86 + option.rect.x())
        {
            isHoverBtnDown = true;
            QToolTip::showText(mouseEvent->globalPos(), QStringLiteral("����"));
        }
        else
        {
            QToolTip::showText(mouseEvent->globalPos(), QStringLiteral(""));
        }

        // emit model->dataChanged(preMouseHoverIndex, index); �����鷳
        model->insertRows(0, 0); // α����,Ϊ��ˢ�½���
    }

    if (mouseEvent->type() == QMouseEvent::MouseButtonPress)
    {
        if (mouseEvent->button() == Qt::LeftButton && index.column() != 0)
        {
            MTableModel *myModel = static_cast<MTableModel*>(model);
            myModel->changeChecked(index);

            QModelIndex indexTemp = model->index(index.row(), 3); // ע���޸���

            if (mouseEvent->pos().x()>= option.rect.x() +60 && mouseEvent->pos().x()<= 86+option.rect.x())
            {
                emit sendMusicData(indexTemp.data(Qt::DecorationRole).toString(), 0);
            }
            else if (mouseEvent->pos().x()>= option.rect.x() +60+35 && mouseEvent->pos().x()<= 35+86+option.rect.x())
            {
                emit sendMusicData(indexTemp.data(Qt::DecorationRole).toString(), 1);
            }
            //    else if (mouseEvent->pos().x()>= option.rect.x()+35+35 +60 && mouseEvent->pos().x()<=35+35+ 86+option.rect.x())

        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

