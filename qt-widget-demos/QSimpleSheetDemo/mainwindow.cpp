// +-------------------------------------------------------------------------+
// | QSimpleSheet simple spreadsheet                                         |
// | Copyright (C) 2008 Shahab <shahab.sh.70@gmail.com>                      |
// +-------------------------------------------------------------------------+
// | License:                                                                |
// |                                                                         |
// | QSimpleSheet is free software; you can redistribute it and/or modify    |
// | it under the terms of the GNU General Public License as published by    |
// | the Free Software Foundation; either version 2 of the License, or       |
// | (at your option) any later version.                                     |
// |                                                                         |
// | QSimpleSheet is distributed in the hope that it will be useful,         |
// | but WITHOUT ANY WARRANTY; without even the implied warranty of          |
// | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            |
// | GNU General Public License for more details.                            |
// |                                                                         |
// | You should have received a copy of the GNU General Public License       |
// | along with QSimpleSheet; if not, write to the Free Software             |
// | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA|
// |                                                                         |
// +-------------------------------------------------------------------------+
// | Author:  Shahab Shirazi <shahab.sh.70@gmail.com>                        |
// +-------------------------------------------------------------------------+

#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QClipboard>
#include <QFontDialog>
#include <QColorDialog>
#include "MainWindow.h"
#include "QSimplesheet.h"
#include "Table.h"
#include "Commands.h"
#include "Dialogs/NewFileDialog.h"
#include "Dialogs/InsertRCDialog.h"
#include "Dialogs/FindDialog.h"
#include "Dialogs/FunctionListDialog.h"
#include "Calculator.h"
#include "Graphic.h"
#include "PictureGraphic.h"
#include "Dialogs/GraphicPropertiesDialog.h"
#include "Dialogs/SortDialog.h"
#include <iostream> //NOTE: for debugging

MainWindow::MainWindow()
{
    findDialog = 0;
    functionListDialog = 0;
    table = new Table(this); //NOTE does it need parent?
    table->newSheet(100, 26);
    connect(table, SIGNAL(modified()), this, SLOT(documentModified()));
    connect(table, SIGNAL(userChangedItemDataSignal(int, int, QString&, QString&)),
            this, SLOT(userChangedItemDataSlot(int, int, QString&, QString&)));
    connect(table, SIGNAL(itemSelectionChanged()),
            this, SLOT(updateActions()));
    connect(table, SIGNAL(graphicContextMenuSignal(QPoint)),
            this, SLOT(graphicContextMenuSlot(QPoint)));
    table->setContextMenuPolicy(Qt::ActionsContextMenu);
    setCentralWidget(table);
    creatActions();
    creatMenus();
    creatToolBars();
    creatFormulaToolBar();
    creatStatusBar();
    creatContextMenu();

    setWindowState(Qt::WindowMaximized);
    setWindowIcon(QIcon(":/images/applicationIcon.png"));

    setCurrentFile("");
    setWindowModified(false);
}

void MainWindow::creatActions()
{
    undoAction = table->getUndoStack()->createUndoAction(this);
    undoAction->setShortcut(tr("Ctrl+Z"));
    undoAction->setIcon(QIcon(":/images/undo.png"));
    redoAction = table->getUndoStack()->createRedoAction(this);
    redoAction->setShortcut(tr("Ctrl+Y"));
    redoAction->setIcon(QIcon(":/images/redo.png"));

    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setIcon(QIcon(":/images/new.png"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setIcon(QIcon(":/images/open.png"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setIcon(QIcon(":/images/save.png"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As"), this);
    saveAsAction->setShortcut(tr("Ctrl+Shift+S"));
    saveAsAction->setIcon(QIcon(":/images/saveAs.png"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setIcon(QIcon(":/images/copy.png"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

    cutAction = new QAction(tr("C&ut"), this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setIcon(QIcon(":/images/cut.png"));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

    findAction = new QAction(tr("&Find..."), this);
    findAction->setShortcut(tr("Ctrl+F"));
    findAction->setIcon(QIcon(":/images/find.png"));
    connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

    findNextAction = new QAction(tr("Find &Next"), this);
    findNextAction->setShortcut(tr("F3"));
    connect(findNextAction, SIGNAL(triggered()), this, SLOT(findNext()));

    findPreviousAction = new QAction(tr("Find &Previous"), this);
    findPreviousAction->setShortcut(tr("Shift+F3"));
    connect(findPreviousAction, SIGNAL(triggered()), this, SLOT(findPrevious()));

    deleteContentsAction = new QAction(tr("&Delete"), this);
    deleteContentsAction->setShortcut(tr("Del"));
    connect(deleteContentsAction, SIGNAL(triggered()), this, SLOT(deleteContents()));

    deleteEntireRowsAction = new QAction(tr("Delete Entire &Row(s)"), this);
    deleteEntireRowsAction->setShortcut(tr("Ctrl+Del"));
    connect(deleteEntireRowsAction, SIGNAL(triggered()), this, SLOT(deleteEntireRows()));

    deleteEntireColumnsAction = new QAction(tr("Delete Entire C&olumn(s)"), this);
    deleteEntireColumnsAction->setShortcut(tr("Ctrl+Shift+Del"));
    connect(deleteEntireColumnsAction, SIGNAL(triggered()), this, SLOT(deleteEntireColumns()));

    selectCurRowAction = new QAction(tr("Select Current Ro&w"), this);
    connect(selectCurRowAction, SIGNAL(triggered()), table, SLOT(selectCurrentRow()));

    selectCurColAction = new QAction(tr("Select Current Co&lumn"), this);
    connect(selectCurColAction, SIGNAL(triggered()), table, SLOT(selectCurrentColumn()));

    selectAllAction = new QAction(tr("Select &All"), this);
    selectAllAction->setShortcut(tr("Ctrl+A"));
    connect(selectAllAction, SIGNAL(triggered()), table, SLOT(selectAll()));

    insertRowsAction = new QAction(tr("Insert &Rows"), this);
    insertRowsAction->setShortcut(tr("Ctrl+Shift+R"));
    connect(insertRowsAction, SIGNAL(triggered()), this, SLOT(insertRows()));

    insertColumnsAction = new QAction(tr("Insert &Columns"), this);
    insertColumnsAction->setShortcut(tr("Ctrl+Shift+C"));
    connect(insertColumnsAction, SIGNAL(triggered()), this, SLOT(insertColumns()));

    insertImageAction = new QAction(tr("Insert &Image..."), this);
    insertImageAction->setShortcut(tr("Ctrl+I"));
    connect(insertImageAction, SIGNAL(triggered()), this, SLOT(insertImage()));

    textLineFormatAction = new QAction(tr("&Text Line (default)"), this);
    connect(textLineFormatAction, SIGNAL(triggered()), this, SLOT(textLineFormat()));

    dateFormatAction = new QAction(tr("&Date"), this);
    connect(dateFormatAction, SIGNAL(triggered()), this, SLOT(dateFormat()));

    timeFormatAction = new QAction(tr("T&ime"), this);
    connect(timeFormatAction, SIGNAL(triggered()), this, SLOT(timeFormat()));

    integerFormatAction = new QAction(tr("I&nteger"), this);
    connect(integerFormatAction, SIGNAL(triggered()), this, SLOT(integerFormat()));

    decimalFormatAction = new QAction(tr("D&ecimal"), this);
    connect(decimalFormatAction, SIGNAL(triggered()), this, SLOT(decimalFormat()));

    fontAction = new QAction(tr("&Font.."), this);
    fontAction->setIcon(QIcon(":/images/font.png"));
    connect(fontAction, SIGNAL(triggered()), this, SLOT(font()));

    alignLeftAction = new QAction(tr("Align &Left"), this);
    alignLeftAction->setCheckable(true);
    alignLeftAction->setIcon(QIcon(":/images/alignLeft.png"));
    connect(alignLeftAction, SIGNAL(toggled(bool)), this, SLOT(align(bool)));

    alignCenterAction = new QAction(tr("Align &Center"), this);
    alignCenterAction->setCheckable(true);
    alignCenterAction->setIcon(QIcon(":/images/alignCenter.png"));
    connect(alignCenterAction, SIGNAL(toggled(bool)), this, SLOT(align(bool)));

    alignRightAction = new QAction(tr("Align &Right"), this);
    alignRightAction->setCheckable(true);
    alignRightAction->setIcon(QIcon(":/images/alignRight.png"));
    connect(alignRightAction, SIGNAL(toggled(bool)), this, SLOT(align(bool)));

    QActionGroup *alignGroup = new QActionGroup(this);
    alignGroup->setExclusive(true);
    alignGroup->addAction(alignLeftAction);
    alignGroup->addAction(alignCenterAction);
    alignGroup->addAction(alignRightAction);

    backgroundAction = new QAction(tr("&Background Color"), this);
    backgroundAction->setIcon(QIcon(":/images/background.png"));
    connect(backgroundAction, SIGNAL(triggered()), this, SLOT(background()));

    foregroundAction = new QAction(tr("&Text Color"), this);
    foregroundAction->setIcon(QIcon(":/images/foreground.png"));
    connect(foregroundAction, SIGNAL(triggered()), this, SLOT(foreground()));

    sortAction = new QAction(tr("&Sort"), this);
    connect(sortAction, SIGNAL(triggered()), this, SLOT(sort()));

    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setShortcut(tr("Ctrl+G"));
    showGridAction->setCheckable(true);
    showGridAction->setChecked(table->showGrid());
    connect(showGridAction, SIGNAL(toggled(bool)), table, SLOT(setShowGrid(bool)));

    aboutQSimpleSheetAction = new QAction(tr("&About QSimpleSheet"), this);
    aboutQSimpleSheetAction->setIcon(QIcon(":/images/applicationIcon.png"));
    connect(aboutQSimpleSheetAction, SIGNAL(triggered()), this, SLOT(aboutQSimpleSheet()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    functionListAction = new QAction(tr("&Function List"), this);
    functionListAction->setShortcut(tr("F1"));
    connect(functionListAction, SIGNAL(triggered()), this, SLOT(functionList()));

}

void MainWindow::creatMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(copyAction);
    editMenu->addAction(cutAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(findNextAction);
    editMenu->addAction(findPreviousAction);
    editMenu->addSeparator();
    editMenu->addAction(deleteContentsAction);
    editMenu->addAction(deleteEntireRowsAction);
    editMenu->addAction(deleteEntireColumnsAction);
    editMenu->addSeparator();
    editMenu->addAction(selectAllAction);
    editMenu->addAction(selectCurRowAction);
    editMenu->addAction(selectCurColAction);

    insertMenu = menuBar()->addMenu(tr("&Insert"));
    insertMenu->addAction(insertRowsAction);
    insertMenu->addAction(insertColumnsAction);
    insertMenu->addSeparator();
    insertMenu->addAction(insertImageAction);

    formatMenu = menuBar()->addMenu(tr("Fo&rmat"));
    QMenu *dataFormat = formatMenu->addMenu(tr("&Data Format"));
    dataFormat->addAction(textLineFormatAction);
    dataFormat->addAction(timeFormatAction);
    dataFormat->addAction(dateFormatAction);
    dataFormat->addAction(integerFormatAction);
    dataFormat->addAction(decimalFormatAction);
    formatMenu->addAction(fontAction);
    formatMenu->addSeparator();
    formatMenu->addAction(alignLeftAction);
    formatMenu->addAction(alignCenterAction);
    formatMenu->addAction(alignRightAction);
    formatMenu->addSeparator();
    formatMenu->addAction(backgroundAction);
    formatMenu->addAction(foregroundAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(sortAction);

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(functionListAction);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutQSimpleSheetAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::creatToolBars()
{
    mainToolBar = addToolBar(tr("Main Toolbar"));
    mainToolBar->addAction(newAction);
    mainToolBar->addAction(openAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(saveAction);
    mainToolBar->addAction(saveAsAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(undoAction);
    mainToolBar->addAction(redoAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(copyAction);
    mainToolBar->addAction(cutAction);
    mainToolBar->addAction(pasteAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(alignLeftAction);
    mainToolBar->addAction(alignCenterAction);
    mainToolBar->addAction(alignRightAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(fontAction);
    mainToolBar->addAction(backgroundAction);
    mainToolBar->addAction(foregroundAction);
}

void MainWindow::creatFormulaToolBar()
{
    currentCellLineEdit = new QLineEdit;
    //NOTE: function currentCellLineEdit->sizeHint() does not return an appropriate size!
    currentCellLineEdit->setFixedWidth(QLabel("NNN00:NNN00").sizeHint().width());
    formulaLineEdit = new QLineEdit;
    QLabel *label = new QLabel("Current &location: ");
    label->setBuddy(currentCellLineEdit);
    connect(table, SIGNAL(itemSelectionChanged()),
            this, SLOT(updateFormulaToolBar()));
    connect(currentCellLineEdit, SIGNAL(returnPressed()),
            this, SLOT(currentCellLineEditReturnPressed()));
    connect(formulaLineEdit, SIGNAL(returnPressed()),
            this, SLOT(formulaLineEditReturnPressed()));
    addToolBarBreak();
    formulaToolBar = addToolBar(tr("Formula Toolbar"));
    formulaToolBar->addWidget(label);
    formulaToolBar->addWidget(currentCellLineEdit);
    formulaToolBar->addWidget(formulaLineEdit);
    updateFormulaToolBar();
}

void MainWindow::creatStatusBar()
{
    currentCellDataLabel = new QLabel("No cell is selected.");
    currentCellDataLabel->setIndent(5);
    statusBar()->addWidget(currentCellDataLabel, 1);
    connect(table, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(updateStatusBar()));
}

void MainWindow::creatContextMenu()
{
    //FIXME: any better ways???
    QAction *separator1 = new QAction(this);
    separator1->setSeparator(true);

    QAction *separator2 = new QAction(this);
    separator2->setSeparator(true);

    QAction *separator3 = new QAction(this);
    separator3->setSeparator(true);

    QAction *separator4 = new QAction(this);
    separator4->setSeparator(true);

    QAction *cellFormat = new QAction(tr("Cell Format"), this);
    cellFormat->setMenu(formatMenu);

    table->addAction(cellFormat);
    table->addAction(separator1);
    table->addAction(undoAction);
    table->addAction(redoAction);
    table->addAction(separator2);
    table->addAction(copyAction);
    table->addAction(cutAction);
    table->addAction(pasteAction);
    table->addAction(separator3);
    table->addAction(deleteContentsAction);
    table->addAction(deleteEntireRowsAction);
    table->addAction(deleteEntireColumnsAction);
    table->addAction(separator4);
    table->addAction(showGridAction);
}

void MainWindow::updateStatusBar()
{
    //TODO: it should show the SUM
    QString shownText = "Sum = ";
    if (!Calculator::isFormula(table->getCurrentItemText(Qt::EditRole)))
        shownText += "0";
    else
        shownText += table->getCurrentItemText();
    currentCellDataLabel->setText(shownText);
}

void MainWindow::updateFormulaToolBar()
{
    QTableWidgetSelectionRange range = table->getSelectedRange();
    if (range.topRow() < 0 || range.bottomRow() < 0)
        range = QTableWidgetSelectionRange(0,0,0,0);
    QString text;
    if (range.rowCount() > 1 || range.columnCount() > 1)
        Table::encodeRange(text, range);
    else
        Table::encodePosition(text, range.topRow(), range.leftColumn());
    currentCellLineEdit->setText(text);
    formulaLineEdit->setText(table->getCurrentItemText(Qt::EditRole));
}

void MainWindow::currentCellLineEditReturnPressed()
{
    QString input = currentCellLineEdit->text();
    int row, column;
    QTableWidgetSelectionRange range;
    if (Table::decodePosition(input, row, column))
    {
        if (row < table->rowCount() && column < table->columnCount())
            table->setCurrentCell(row, column);
    }
    else if (Table::decodeRange(input, range))
    {
        if (range.bottomRow() < table->rowCount() && range.rightColumn())
        {
            table->clearSelection();
            table->setCurrentCell(range.topRow(), range.leftColumn());
            table->setRangeSelected(range, true);
        }
    }
    table->setFocus();
}

void MainWindow::formulaLineEditReturnPressed()
{
    table->getUndoStack()->push(new DataChanged(table,
                                                table->currentRow(),
                                                table->currentColumn(),
                                                table->getItemText(table->currentRow(),
                                                                   table->currentColumn(), Qt::EditRole),
                                                formulaLineEdit->text()));
    table->setFocus();
}

bool MainWindow::askToSaveChanges()
{
    if (isWindowModified())
    {
        int answer = QMessageBox::warning(this, "Save",
                                          "This document has been modified.\n"
                                          "Do you want to save it?",
                                          QMessageBox::Yes | QMessageBox::Default,
                                          QMessageBox::No,
                                          QMessageBox::Cancel | QMessageBox::Escape);
        if (answer == QMessageBox::Cancel)
            return false;
        else if (answer == QMessageBox::Yes)
            return save();
    }
    return true;
}

bool MainWindow::newFile()
{
    if (askToSaveChanges())
    {
        NewFileDialog dialog(this);
        if (dialog.exec())
        {
            int rowCount = dialog.rowsSpinBox->value();
            int columnCount = dialog.columnsSpinBox->value();
            table->newSheet(rowCount, columnCount);
            setCurrentFile("");
            setWindowModified(true);
            return true;
        }
    }

    return false;
}


bool MainWindow::open(QString fileName)
{
    if (fileName.isEmpty())
        fileName = QFileDialog::getOpenFileName(this, tr("Open"), ".",
                                                tr("QSimpleSheet Documents (*.qsd)\n"
                                                   "All Files (*.*)"));
    if (!fileName.isEmpty())
    {
        if (table->readSheet(fileName))
        {
            setCurrentFile(fileName);
            setWindowModified(false);
            return true;
        }
    }

    return false;
}

bool MainWindow::save()
{
    if (currentFile.isEmpty())
        return saveAs();
    else
        return saveFile(currentFile);
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), ".",
                                                    tr("QSimpleSheet Documents (*.qsd)"));
    if (!fileName.isEmpty())
    {
        QString fileSuffix = QFileInfo(fileName).suffix();
        if (fileSuffix.isEmpty())
            fileName += ".qsd";
        return saveFile(fileName);
    }
    return false;
}

bool MainWindow::saveFile(const QString &fileName)
{
    if(table->writeSheet(fileName))
    {
        setCurrentFile(fileName);
        setWindowModified(false);
        return true;
    }
    return false;
}

void MainWindow::setCurrentFile(const QString &fullFileName)
{
    QString shownName = "Untitled";
    if (!fullFileName.isEmpty())
        shownName = QFileInfo(fullFileName).fileName();
    setWindowTitle(shownName + "[*] - QSimpleSheet");
    currentFile = fullFileName;
}

void MainWindow::documentModified()
{
    setWindowModified(true);
    updateStatusBar();
    updateFormulaToolBar();
    updateActions();
}

void MainWindow::userChangedItemDataSlot(int row, int column,
                                         QString &oldData, QString &newData)
{
    table->getUndoStack()->push(new DataChanged(table, row, column, oldData, newData));
}

void MainWindow::graphicContextMenuSlot(QPoint point)
{
    QMenu graphicMenu(this);
    graphicMenu.addAction(copyAction);
    graphicMenu.addAction(cutAction);
    graphicMenu.addAction(pasteAction);
    graphicMenu.addSeparator();
    graphicMenu.addAction(deleteContentsAction);
    graphicMenu.addSeparator();
    QAction properties(tr("Properties..."), this);
    graphicMenu.addAction(&properties);
    if (graphicMenu.exec(point) == &properties)
        table->getSelectedGraphic()->execPropertiesDialog();

}

void MainWindow::updateActions()
{
    if (isWindowModified())
    {
        saveAction->setEnabled(true);
    }
    else
    {
        saveAction->setEnabled(false);
    }

    QTableWidgetSelectionRange selectedRange = table->getSelectedRange();

    if (selectedRange.rowCount()>1 || selectedRange.columnCount()>1)
    {
        alignLeftAction->setChecked(false);
        alignCenterAction->setChecked(false);
        alignRightAction->setChecked(false);
    }
    else
    {
        int alignment = table->getItemAlignment(selectedRange.topRow(),
                                                selectedRange.leftColumn());
        if (alignment == (Qt::AlignLeft | Qt::AlignVCenter))
        {
            alignLeftAction->setChecked(true);
        }
        else if (alignment == Qt::AlignCenter)
        {
            alignCenterAction->setChecked(true);
        }
        else if (alignment == (Qt::AlignRight | Qt::AlignVCenter))
        {
            alignRightAction->setChecked(true);
        }
    }
}

void MainWindow::cut()
{
    table->getUndoStack()->push(new CutCommand(table));
}

void MainWindow::copy()
{
    QApplication::clipboard()->setText(table->getItemsText(table->getSelectedRange(),
                                                           Qt::EditRole), QClipboard::Selection);
    QMimeData *mimeData = new QMimeData;
    table->copy(*mimeData);
    QApplication::clipboard()->setMimeData(mimeData);
}

void MainWindow::paste()
{
    table->getUndoStack()->push(new PasteCommand(table));
}

void MainWindow::deleteContents()
{
    table->getUndoStack()->push(new DeleteContents(table));
}

void MainWindow::deleteEntireRows()
{
    QTableWidgetSelectionRange range = table->getSelectedRange();
    int position = range.topRow();
    int amount = range.rowCount();
    table->getUndoStack()->push(new DeleteEntireRows(table, position, amount));
}

void MainWindow::deleteEntireColumns()
{
    QTableWidgetSelectionRange range = table->getSelectedRange();
    int position = range.leftColumn();
    int amount = range.columnCount();
    table->getUndoStack()->push(new DeleteEntireColumns(table, position, amount));
}

void MainWindow::insertRows()
{
    InsertRCDialog dialog(InsertRCDialog::InsertRows, this);

    if (dialog.exec())
    {
        int amount = dialog.amountSpinBox->value();
        int position = dialog.afterRadioButton ->
                isChecked() ? Table::InsertAfter : Table::InsertBefore;
        table->getUndoStack()->push(new InsertRowsCommand(table, position, amount));
    }
}

void MainWindow::insertColumns()
{
    InsertRCDialog dialog(InsertRCDialog::InsertColumns, this);

    if (dialog.exec())
    {
        int amount = dialog.amountSpinBox->value();
        int position = dialog.afterRadioButton ->
                isChecked() ? Table::InsertAfter : Table::InsertBefore;
        table->getUndoStack()->push(new InsertColumnsCommand(table, position, amount));
    }
}

void MainWindow::insertImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), ".",
                                                    tr("All Files (*.*)"));
    if (fileName.isEmpty())
    {
        return;
    }

    QImage image;

    if (!image.load(fileName))
    {
        QMessageBox::warning(this, tr("Opening failed"), tr("Unknown file format!"));
        return;
    }

    int xCoordinate = table->columnViewportPosition(table->currentColumn());
    int yCoordinate = table->rowViewportPosition(table->currentRow());
    table->getUndoStack()->push(new InsertImageCommand(table, image, xCoordinate, yCoordinate));
}

void MainWindow::textLineFormat()
{
    table->getUndoStack()->push(new ChangeCellsEditor(table, table->getSelectedRange(), Table::TextLineEditor));
}

void MainWindow::dateFormat()
{
    table->getUndoStack()->push(new ChangeCellsEditor(table,
                                                      table->getSelectedRange(), Table::DateEditor));
}

void MainWindow::timeFormat()
{
    table->getUndoStack()->push(new ChangeCellsEditor(table,
                                                      table->getSelectedRange(), Table::TimeEditor));
}

void MainWindow::integerFormat()
{
    table->getUndoStack()->push(new ChangeCellsEditor(table,
                                                      table->getSelectedRange(), Table::IntegerEditor));
}

void MainWindow::decimalFormat()
{
    table->getUndoStack()->push(new ChangeCellsEditor(table,
                                                      table->getSelectedRange(), Table::DecimalEditor));
}

void MainWindow::font()
{
    bool ok;
    QFont newFont = QFontDialog::getFont(&ok, table-> getItemFont(table->currentRow(),
                                                                  table->currentColumn()), this);
    if (ok)
    {
        table->getUndoStack()->push(new ChangeCellsFont(table,
                                                        table->getSelectedRange(), newFont));
    }
}

void MainWindow::align(bool checked)
{
    if (!checked)
    {
        return;
    }

    int alignment = Qt::AlignLeft;

    if (alignCenterAction->isChecked())
    {
        alignment = Qt::AlignHCenter;
    }
    else if (alignRightAction->isChecked())
    {
        alignment = Qt::AlignRight;
    }

    alignment |= Qt::AlignVCenter;

    QTableWidgetSelectionRange range = table->getSelectedRange();

    for (int i=0; i<range.rowCount(); i++)
    {
        for (int j=0; j<range.columnCount(); j++)
        {
            if (table->getItemAlignment(i+range.topRow(), j+range.leftColumn()) != alignment)
            {
                table->getUndoStack()->push(new ChangeCellsAlignment(table, range, alignment));
                return;
            }
        }
    }
}

void MainWindow::background()
{
    QColor color = table->getItemBackground(table->currentRow(),
                                            table->currentColumn()).color();
    color = QColorDialog::getColor(color, this);
    if (color.isValid())
        table->getUndoStack()->push(new ChangeCellsBackground(table,
                                                              table->getSelectedRange(), color));
}

void MainWindow::foreground()
{
    QColor color = table->getItemForeground(table->currentRow(),
                                            table->currentColumn()).color();
    color = QColorDialog::getColor(color, this);
    if (color.isValid())
        table->getUndoStack()->push(new ChangeCellsForeground(table,
                                                              table->getSelectedRange(), color));
}

void MainWindow::find()
{
    if (!findDialog)
    {
        findDialog = new FindDialog(this);
        connect(findDialog, SIGNAL(findNextSignal()), this, SLOT(findNext()));
        connect(findDialog, SIGNAL(findPreviousSignal()), this, SLOT(findPrevious()));
    }
    findDialog->exec();
}

void MainWindow::findNext()
{
    if (!findDialog)
        find();
    else
    {
        QString text = findDialog->text();
        table->findNext(text, findDialog->caseSensitivity(), findDialog->inFormula());
    }
}

void MainWindow::findPrevious()
{
    if (!findDialog)
        find();
    else
    {
        QString text = findDialog->text();
        table->findPrevious(text, findDialog->caseSensitivity(), findDialog->inFormula());
    }
}

void MainWindow::sort()
{
    QTableWidgetSelectionRange range = table->getSelectedRange();
    if (range.rowCount() <= 1 && range.columnCount() <= 1)
    {
        QMessageBox::warning(this, tr("Nothing to sort"),
                             tr("You should select at least 2 rows/columns to sort."));
        return;
    }
    SortDialog dialog(range, this);
    if (dialog.exec())
    {
        table->getUndoStack()->push(new SortCommand(table, dialog.getTableSort()));
    }
}

void MainWindow::aboutQSimpleSheet()
{
    QMessageBox::about(this, tr("About QSimpleSheet"),
                       tr("<p align=\"center\"><b>QSimpleSheet</b><br>version "VERSION"</p>"
                          "<p>QSimpleSheet is a simple spreadsheet.<br>"
                          "This is a free software; you can redistribute it and/or modify "
                          "it under the terms of the GNU General Public License (GPL) "
                          "as published by the Free Software Foundation; "
                          "either version 2 of the License, or (at your option) "
                          "any later version."
                          "<p>Copyright (c) 2008, Shahab "
                          "Shirazi<br>shahab.sh.70@gmail.com</p>"));
}

void MainWindow::functionList()
{
    if (!functionListDialog)
        functionListDialog = new FunctionListDialog(this);
    functionListDialog->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (askToSaveChanges())
        event->accept();
    else
        event->ignore();
}


