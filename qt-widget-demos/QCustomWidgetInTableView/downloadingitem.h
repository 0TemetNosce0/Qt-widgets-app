#ifndef DOWNLOADINGITEM_H
#define DOWNLOADINGITEM_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class downloadingitem;
}

class QModelIndex;

class downloadingitem : public QWidget
{
    Q_OBJECT

public:
    explicit downloadingitem(QWidget *parent = 0);
    ~downloadingitem();

    void setItemIndex(const QModelIndex& index);
    void setItemIcon(QString url);
    void setItemName(QString name);
    void setItemSize(qint64 size);
    void setItemVersion(QString version);
    void setItemProgress(int progress);
    void setItemDownloadedSize(qint64 size);
    void setItemSpeed(qint64 speed);
    void setItemStatus(int status);

signals:
    void startButtonClicked();
    void removeButtonClicked();
    void pauseButtonClicked();

private slots:
    void on_startButton_clicked();
    void on_removeButton_clicked();
    void on_pauseButton_clicked();

private:
    Ui::downloadingitem *ui;
    QModelIndex m_index;
};

#endif // DOWNLOADINGITEM_H
