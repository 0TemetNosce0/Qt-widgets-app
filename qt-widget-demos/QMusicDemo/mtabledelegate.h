/*
 *  功能： 搜索框表格代理类。实现复选框和控件的绘制
 *
 *  作者： vi7
 *  QQ： 547719515
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
    bool isHoverBtnAdd;                 // 判断鼠标是否在某个添加按钮处
    bool isHoverBtnPlay;
    bool isHoverBtnDown;

    static QModelIndex mouseHoverIndex; // 记录鼠标经过的
};

#endif // MTABLEDELEGATE_H
