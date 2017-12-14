#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>
#include <QList>

class QLabel;
class QEvent;

namespace Ui {
    class PageWidget;
}

class PageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageWidget(int blockSize = 3, QWidget *parent = 0);
    ~PageWidget();

    int getBlockSize() const;
    int getMaxPage() const;
    int getCurrentPage() const;

    // 其他组件只需要调用这两个函数即可
    /**
     * @brief 当总页数改变时调用
     * @param maxPage
     */
    void setMaxPage(int maxPage);

    /**
     * @brief 修改当前页时调用
     * @param currentPage
     * @param signalEmitted
     */
    void setCurrentPage(int currentPage, bool signalEmitted = false);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *e);

signals:
    void currentPageChanged(int page);

private:
    Ui::PageWidget *ui;
    int blockSize;
    int maxPage;
    int currentPage;
    QList<QLabel *> *pageLabels;

    void setBlockSize(int blockSize);
    void updatePageLabels();
    void initialize();
};

#endif // PAGEWIDGET_H
