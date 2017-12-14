#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Node;
class QLabel;
class TreeView;
class TreeManager;
class QActionGroup;
class QErrorMessage;
class AddValuesWidget;

class ViewerWindow: public QMainWindow
{
    Q_OBJECT

public:
    ViewerWindow();

public slots:
    void addValue();
    void addValuesFromWidget();
    void removeValue();
    void deleteSelected();
    void rotateLeft();
    void rotateRight();
    void valueByIndex();
    void updateStatusbar();
    void updateActions();

private slots:
    void valueByIndexSlot(int index);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void createActions();
    void createToolbars();
    void createMenus();
    void createStatusbar();

    QToolBar *editToolbar;
    QToolBar *toolsToolbar;
    QToolBar *viewToolbar;
    QAction *addValueAction;
    QAction *removeValueAction;
    QAction *deleteSelectedAction;
    QAction *valueByIndexAction;
    QAction *leftNodeRotationAction;
    QAction *rightNodeRotationAction;
    QAction *zoomInAction;
    QAction *zoomNormalAction;
    QAction *zoomOutAction;
    QAction *handCursorAction;
    QAction *arrowCursorAction;
    QActionGroup *cursorActionGroup;
    QErrorMessage *errorMessageDialog;
    QLabel *sizeLabel;
    QLabel *zoomLabel;
    AddValuesWidget *addValuesWidget;

    TreeManager* m_tree;
    TreeView *m_view;
};

#endif /* VIEWERWINDOW_H */
