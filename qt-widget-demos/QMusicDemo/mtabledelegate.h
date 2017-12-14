/*
 *  ���ܣ� ������������ࡣʵ�ָ�ѡ��Ϳؼ��Ļ���
 *
 *  ���ߣ� vi7
 *  QQ�� 547719515
 *
 */

#ifndef MTABLEDELEGATE_H
#define MTABLEDELEGATE_H

#include <QTableView>
#include <QStyledItemDelegate>

class MTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit MTableDelegate(QObject *parent = 0);

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                const QStyleOptionViewItem &option, const QModelIndex &index);

    void  paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;


signals:
    void repaint();
    void sendMusicData(const QString &musicId, const int &flag);

private:
    bool isHoverBtnAdd;                 // �ж�����Ƿ���ĳ����Ӱ�ť��
    bool isHoverBtnPlay;
    bool isHoverBtnDown;

    static QModelIndex mouseHoverIndex; // ��¼��꾭����
};

#endif // MTABLEDELEGATE_H
