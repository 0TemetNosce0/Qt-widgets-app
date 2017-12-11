#include "../include/ViewerWindow.h"
#include "../include/TreeManager.h"
#include "../include/TreeView.h"
#include "../include/TreeScene.h"
#include "../include/Node.h"
#include "../include/Edge.h"
#include "../include/AddValuesDialog.h"
#include "../include/AddValuesWidget.h"
#include "../include/ValueByIndexDialog.h"
#include <cmath>
#include <QDebug>
#include <QErrorMessage>
#include <QToolBar>
#include <QStatusBar>
#include <QInputDialog>

ViewerWindow::ViewerWindow()
{
    m_tree = new TreeManager();
    m_view = new TreeView();
    m_view->setScene(m_tree->scene());
    m_view->setContextMenuPolicy(Qt::ActionsContextMenu);

    createActions();
    createToolbars();
    createMenus();
    createStatusbar();
    errorMessageDialog = new QErrorMessage(this);

    setCentralWidget(m_view);
    setWindowTitle(tr("Tree Viewer"));
    setWindowIcon(QIcon(":/img/icon.png"));
    connect(m_tree->scene(), SIGNAL(selectionChanged()), this, SLOT(updateActions()));
    connect(m_tree, SIGNAL(treeChanged()), this, SLOT(updateActions()));
    /*
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/img/icon.png"));
    trayIcon->show();
    */
}

void ViewerWindow::createActions()
{
    addValueAction = new QAction(tr("&Add Value"), this);
    addValueAction->setIcon(QIcon(":/img/addvalue.png"));
    addValueAction->setShortcut(tr("Ctrl+N"));
    addValueAction->setToolTip(tr("Add value to the tree"));
    connect(addValueAction, SIGNAL(triggered()), this, SLOT(addValue()));

    removeValueAction = new QAction(tr("&Remove Value"), this);
    removeValueAction->setIcon(QIcon(":/img/removevalue.png"));
    removeValueAction->setShortcut(tr("Ctrl+R"));
    removeValueAction->setToolTip(tr("Remove value from the tree"));
    connect(removeValueAction, SIGNAL(triggered()), this, SLOT(removeValue()));

    deleteSelectedAction = new QAction(tr("&Delete"), this);
    deleteSelectedAction->setIcon(QIcon(":/img/deleteselected.png"));
    deleteSelectedAction->setShortcut(tr("Del"));
    deleteSelectedAction->setToolTip(tr("Delete selected values"));
    deleteSelectedAction->setEnabled(false);
    connect(deleteSelectedAction, SIGNAL(triggered()), this, SLOT(deleteSelected()));

    deleteSelectedAction = new QAction(tr("&Delete"), this);
    deleteSelectedAction->setIcon(QIcon(":/img/deleteselected.png"));
    deleteSelectedAction->setShortcut(tr("Del"));
    deleteSelectedAction->setToolTip(tr("Delete selected values"));
    deleteSelectedAction->setEnabled(false);
    connect(deleteSelectedAction, SIGNAL(triggered()), this, SLOT(deleteSelected()));

    valueByIndexAction = new QAction(tr("Value by index"), this);
    valueByIndexAction->setIcon(QIcon(":/img/index.png"));
    valueByIndexAction->setEnabled(false);
    //valueByIndexAction->setShortcut(tr("Ctrl+N"));
    valueByIndexAction->setToolTip(tr("Get value by index"));
    connect(valueByIndexAction, SIGNAL(triggered()), this, SLOT(valueByIndex()));

    leftNodeRotationAction = new QAction(tr("Rotate left"), this);
    leftNodeRotationAction->setIcon(QIcon(":/img/leftrotation.png"));
    //leftNodeRotationAction->setShortcut(tr("Ctrl+N"));
    leftNodeRotationAction->setToolTip(tr("Rotate node left"));
    leftNodeRotationAction->setEnabled(false);
    connect(leftNodeRotationAction, SIGNAL(triggered()), this, SLOT(rotateLeft()));

    rightNodeRotationAction = new QAction(tr("Rotate right"), this);
    rightNodeRotationAction->setIcon(QIcon(":/img/rightrotation.png"));
    //rightNodeRotationAction->setShortcut(tr("Ctrl+N"));
    rightNodeRotationAction->setToolTip(tr("Rotate node right"));
    rightNodeRotationAction->setEnabled(false);
    connect(rightNodeRotationAction, SIGNAL(triggered()), this, SLOT(rotateRight()));

    zoomInAction = new QAction(tr("Zoom &In"), this);
    zoomInAction->setIcon(QIcon(":/img/zoomin.png"));
    zoomInAction->setShortcut(tr("Ctrl++"));
    zoomInAction->setToolTip(tr("Zoom in"));
    connect(zoomInAction, SIGNAL(triggered()), m_view, SLOT(zoomIn()));

    zoomNormalAction = new QAction(tr("Zoom 100%"), this);
    zoomNormalAction->setShortcut(tr("Ctrl+0"));
    zoomNormalAction->setToolTip(tr("Zoom 100%"));
    connect(zoomNormalAction, SIGNAL(triggered()), m_view, SLOT(zoomNormal()));

    zoomOutAction = new QAction(tr("Zoom &Out"), this);
    zoomOutAction->setIcon(QIcon(":/img/zoomout.png"));
    zoomOutAction->setShortcut(tr("Ctrl+-"));
    zoomOutAction->setToolTip(tr("Zoom out"));
    connect(zoomOutAction, SIGNAL(triggered()), m_view, SLOT(zoomOut()));

    handCursorAction = new QAction(tr("&Hand Cursor"), this);
    handCursorAction->setIcon(QIcon(":/img/hand.png"));
    handCursorAction->setShortcut(tr("Ctrl+H"));
    handCursorAction->setToolTip(tr("Hand cursor"));
    handCursorAction->setCheckable(true);
    connect(handCursorAction, SIGNAL(triggered()), m_view, SLOT(setHandCursor()));

    arrowCursorAction = new QAction(tr("Arro&w Cursor"), this);
    arrowCursorAction->setIcon(QIcon(":/img/arrow.png"));
    arrowCursorAction->setShortcut(tr("Ctrl+W"));
    arrowCursorAction->setToolTip(tr("Arrow cursor"));
    arrowCursorAction->setCheckable(true);
    connect(arrowCursorAction, SIGNAL(triggered()), m_view, SLOT(setArrowCursor()));

    cursorActionGroup = new QActionGroup(this);
    cursorActionGroup->addAction(handCursorAction);
    cursorActionGroup->addAction(arrowCursorAction);
    arrowCursorAction->setChecked(true);
}

void ViewerWindow::createToolbars()
{
    editToolbar = addToolBar(tr("Edit"));
    editToolbar->addAction(addValueAction);
    editToolbar->addAction(removeValueAction);
    editToolbar->addAction(deleteSelectedAction);

    toolsToolbar = addToolBar(tr("Tools"));
    toolsToolbar->addAction(valueByIndexAction);
    toolsToolbar->addAction(leftNodeRotationAction);
    toolsToolbar->addAction(rightNodeRotationAction);

    viewToolbar = addToolBar(tr("Zoom"));
    viewToolbar->addAction(zoomInAction);
    viewToolbar->addAction(zoomOutAction);
    viewToolbar->addSeparator();
    viewToolbar->addAction(handCursorAction);
    viewToolbar->addAction(arrowCursorAction);
}

void ViewerWindow::createMenus()
{
    m_view->addAction(zoomInAction);
    m_view->addAction(zoomNormalAction);
    m_view->addAction(zoomOutAction);
}

void ViewerWindow::createStatusbar()
{
    sizeLabel = new QLabel("Tree size: 0 values");
    sizeLabel->setIndent(5);
    zoomLabel = new QLabel(" Zoom: 100% ");
    zoomLabel->setMinimumSize(zoomLabel->sizeHint());

    statusBar()->addWidget(sizeLabel, 1);
    statusBar()->addWidget(zoomLabel);
    
    addValuesWidget = new AddValuesWidget(QIcon(":/img/addvalue.png"), this);
    statusBar()->addWidget(addValuesWidget);
    //addValuesWidget->setVisible(true);
    
    connect(addValuesWidget, SIGNAL(valuesListChanged()),
            this, SLOT(addValuesFromWidget()));

    connect(m_tree, SIGNAL(treeChanged()), this, SLOT(updateStatusbar()));
    connect(m_view, SIGNAL(zoomChanged()), this, SLOT(updateStatusbar()));
}

void ViewerWindow::updateStatusbar()
{
    int size = m_tree->treeSize();
    QString sizeText = "Tree size: " + QString::number(size);
    if (size == 1)
    {
        sizeText += " value";
    }
    else
    {
        sizeText += " values";
    }
    sizeLabel->setText(sizeText);

    zoomLabel->setText(QString(" Zoom: %1% ").arg(qRound(m_view->zoom() * 100)));
}

void ViewerWindow::updateActions()
{
    int selectionSize = m_tree->scene()->selectedItems().size();
    deleteSelectedAction->setEnabled(selectionSize != 0);
    rightNodeRotationAction->setEnabled(selectionSize == 1);
    leftNodeRotationAction->setEnabled(selectionSize == 1);
    valueByIndexAction->setEnabled(!m_tree->isEmpty());
}

void ViewerWindow::addValuesFromWidget()
{
    QList<int> l = addValuesWidget->values();
    foreach (int value, l)
    {
        m_tree->addValue(value);
    }
}

void ViewerWindow::addValue()
{
    static bool batch = false;
    AddValuesDialog dialog(this, batch);
    if (dialog.exec())
    {
        QList<int> l = dialog.values();
        foreach (int value, l)
        {
            m_tree->addValue(value);
        }
    }

    batch = dialog.batchMode();
}

void ViewerWindow::removeValue()
{
    bool ok;
    int value = QInputDialog::getInt(this, tr("Remove value"),
                                     tr("Enter value:"),
                                     0, -2147483647, 2147483647, 1, &ok);
    if (!ok)
    {
        return;
    }
    ok = m_tree->removeValue(value);
    if (!ok)
    {
        errorMessageDialog->showMessage(tr("There is no such value in the tree."));
    }
}

void ViewerWindow::deleteSelected()
{
    bool ok = m_tree->deleteSelected();
    if (!ok)
    {
        errorMessageDialog->showMessage(tr("There are no selected values."));
    }
}

void ViewerWindow::rotateLeft()
{
    m_tree->rotateSelectedLeft();
}

void ViewerWindow::rotateRight()
{
    m_tree->rotateSelectedRigth();
}

void ViewerWindow::valueByIndex()
{
    if (!m_tree->isEmpty())
    {
        ValueByIndexDialog dialog(this);
        dialog.setRange(1, m_tree->treeSize());
        dialog.setValue(m_tree->valueByIndex(dialog.index()));
        connect(&dialog, SIGNAL(indexChanged(int)), this, SLOT(valueByIndexSlot(int)));
        dialog.exec();
        disconnect(&dialog, SIGNAL(indexChanged(int)), this, SLOT(valueByIndexSlot(int)));
    }
}

void ViewerWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
}

void ViewerWindow::valueByIndexSlot(int index)
{
    ValueByIndexDialog *dialog = qobject_cast<ValueByIndexDialog *>(sender());
    if (dialog)
    {
        dialog->setValue(m_tree->valueByIndex(index));
    }
}
