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

    // �������ֻ��Ҫ������������������
    /**
     * @brief ����ҳ���ı�ʱ����
     * @param maxPage
     */
    void setMaxPage(int maxPage);

    /**
     * @brief �޸ĵ�ǰҳʱ����
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
