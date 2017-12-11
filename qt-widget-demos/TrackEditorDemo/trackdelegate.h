#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

QT_BEGIN_NAMESPACE
class QPainter;
QT_END_NAMESPACE

/**
  @brief 继承的委托类。
*/
class TrackDelegate : public QStyledItemDelegate
{
public:
    explicit TrackDelegate(QObject* parent = 0);
    ~TrackDelegate();

    virtual QWidget* createEditor(QWidget *parent,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const;
    virtual void setEditorData(QWidget* parent,
                               const QModelIndex& index) const;

    virtual void setModelData(QWidget* editor,
                              QAbstractItemModel* model,
                              const QModelIndex& index) const;

    virtual void updateEditorGeometry(QWidget* editor,
                                      const QStyleOptionViewItem& option,
                                      const QModelIndex& index) const;

    virtual void paint(QPainter* painter,
                       const QStyleOptionViewItem &option,
                       const QModelIndex &index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

private:

    bool isRightColumn(const QModelIndex& index, const int column) const;
private slots:
    void commitAndCloseEditor();

private:
    static const int columnNumber;
};

#endif // TRACKDELEGATE_H
