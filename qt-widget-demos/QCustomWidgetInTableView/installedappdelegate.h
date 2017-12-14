#ifndef INSTALLEDAPPDELEGATE_H
#define INSTALLEDAPPDELEGATE_H

#include <QItemDelegate>

class InstalledAppDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    InstalledAppDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
private slots:
    void handleStartButtonClicked();
    void handleRemoveButtonClicked();
    void handlePauseButtonClicked();
};

#endif // INSTALLEDAPPDELEGATE_H
