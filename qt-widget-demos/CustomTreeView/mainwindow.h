#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QComboBox>
#include "Windows.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private slots:
    void expanded(QModelIndex index);
    void treeViewCustomContextMenuRequested(const QPoint &pos);
    void changeStyle(int index);

private:
    QTreeView *m_treeView;
    QRect m_rect;
    int m_height;
    int m_shadowSize;
    QMenu *m_menu;
    QLabel *m_label;
    QPushButton *m_closeButton;
    QComboBox *m_comboBox;
};

#endif // MAINWINDOW_H
