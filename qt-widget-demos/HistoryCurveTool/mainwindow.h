#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>

namespace Ui {
class MainWindow;
}

class TagTreeModel;

class TreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit TreeView(QWidget *parent = 0);
    ~TreeView();

public slots:
    void expand(const QModelIndex &);
    void collapse(const QModelIndex &);

private:
    Ui::MainWindow *ui;

    TagTreeModel *pModel;
};

#endif // MAINWINDOW_H
