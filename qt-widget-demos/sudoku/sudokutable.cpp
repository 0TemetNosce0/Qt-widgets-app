#include "sudokutable.h"

#include <QHeaderView>
#include <QMessageBox>

SudokuTable::SudokuTable(QWidget *parent)
    : QTableWidget(parent)
{
    setItemPrototype(new Cell);
    setSelectionMode(NoSelection);
    setStyleSheet("gridline-color: black");
    setShowGrid(true);
    setFocusPolicy(Qt::NoFocus);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);

    sudokuData = new SudokuData;
    setDataSolutions(1);
    clear();
    connect(this, SIGNAL(cellChanged(int, int)),
            this, SLOT(somethingChanged(int, int)));
    connect(this, SIGNAL(currentCellChanged(int, int, int, int)),
            this, SLOT(drawEyeModeBackground(int, int)));

}

void SudokuTable::newPuzzle()
{
    disconnect(this, SIGNAL(cellChanged(int, int)),
               this, SLOT(somethingChanged(int, int)));
    connect(this, SIGNAL(currentCellChanged(int, int, int, int)),
            this, SLOT(drawEyeModeBackground(int, int)));
    setCurrentCell(4, 4);
    clear();
    setGodMode(false);
    int data[9][9];
    sudokuData->getNewPuzzle(data);
    Cell *c;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            c = cell(i, j);
            if (data[i][j])
            {
                c->setTextColor(Cell::DEFAULT);
                c->setData(Qt::EditRole, data[i][j]);
                c->setDirty(false);
                c->setEditEnabled(false);
            }
            else
                c->setTextColor(Cell::RIGHT);
        }
    connect(this, SIGNAL(cellChanged(int, int)),
            this, SLOT(somethingChanged(int, int)));
}

void SudokuTable::previous()
{
    disconnect(this, SIGNAL(cellChanged(int, int)),
               this, SLOT(somethingChanged(int, int)));
    disconnect(this, SIGNAL(currentCellChanged(int, int, int, int)),
               this, SLOT(drawEyeModeBackground(int, int)));
    drawBasicBackgroud();
    int inputData[9][9];
    int answerData[9][9];
    sudokuData->getInputData(inputData);
    sudokuData->getPreviousAnswer(answerData);
    Cell *c;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            c = cell(i, j);
            c->setEditEnabled(true);
            if (inputData[i][j])
                c->setTextColor(Cell::DEFAULT);
            else
                c->setTextColor(Cell::RIGHT);
            c->setData(Qt::EditRole, answerData[i][j]);
            c->setDirty(false);
            c->setEditEnabled(false);
        }
    setCurrentCell(-1, -1);
    emit setNextEnabled(sudokuData->hasNext());
    emit setPreviousEnabled(sudokuData->hasPrevious());
    connect(this, SIGNAL(cellChanged(int, int)),
            this, SLOT(somethingChanged(int, int)));
}

void SudokuTable::next()
{
    disconnect(this, SIGNAL(cellChanged(int, int)),
               this, SLOT(somethingChanged(int, int)));
    disconnect(this, SIGNAL(currentCellChanged(int, int, int, int)),
               this, SLOT(drawEyeModeBackground(int, int)));
    drawBasicBackgroud();
    int inputData[9][9];
    int answerData[9][9];
    sudokuData->getInputData(inputData);
    sudokuData->getNextAnswer(answerData);
    Cell *c;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            c = cell(i, j);
            c->setEditEnabled(true);

            if (inputData[i][j])
            {
                c->setTextColor(Cell::DEFAULT);
            }
            else
            {
                c->setTextColor(Cell::RIGHT);
            }

            c->setData(Qt::EditRole, answerData[i][j]);
            c->setDirty(false);
            c->setEditEnabled(false);
        }
    }

    setCurrentCell(-1, -1);

    emit setNextEnabled(sudokuData->hasNext());
    emit setPreviousEnabled(sudokuData->hasPrevious());

    connect(this, SIGNAL(cellChanged(int, int)),
            this, SLOT(somethingChanged(int, int)));
}

void SudokuTable::erase()
{
    disconnect(this, SIGNAL(cellChanged(int, int)),
               this, SLOT(somethingChanged(int, int)));
    connect(this, SIGNAL(currentCellChanged(int, int, int, int)),
            this, SLOT(drawEyeModeBackground(int, int)));

    setCurrentCell(4, 4);
    sudokuData->erase();

    int inputData[9][9];
    sudokuData->getInputData(inputData);
    Cell *c = nullptr;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            c = cell(i, j);

            if (!inputData[i][j])
            {
                c->setEditEnabled(true);
                c->setData(Qt::EditRole, 0);
                c->setDirty(false);
            }
        }
    }

    emit setNextEnabled(sudokuData->hasNext());
    emit setPreviousEnabled(sudokuData->hasPrevious());

    connect(this, SIGNAL(cellChanged(int, int)),
            this, SLOT(somethingChanged(int, int)));
}

void SudokuTable::clear()
{
    sudokuData->clear();
    setGodMode(true);

    setRowCount(0);
    setColumnCount(0);
    setRowCount(9);
    setColumnCount(9);

    for (int i = 0; i < 9; i++)
    {
        setRowHeight(i, 35);
        setColumnWidth(i, 35);
    }

    Cell * c = nullptr;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            c = new Cell;
            setItem(i, j, c);
        }
    }

    setCurrentCell(4, 4);
    drawEyeModeBackground(4, 4);

    connect(this, SIGNAL(currentCellChanged(int, int, int, int)),
            this, SLOT(drawEyeModeBackground(int, int)));

    emit setPreviousEnabled(false);
    emit setNextEnabled(true);
}

int SudokuTable::dataSolutions() const
{
    return sudokuData->getSolutions();
}

void SudokuTable::setDataSolutions(int num)
{
    sudokuData->setSolutions(num);
}

bool SudokuTable::eyeMode() const
{
    return isEyeMode;
}

void SudokuTable::setEyeMode(bool flag)
{
    isEyeMode = flag;
    Cell * c = nullptr;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            c = cell(i, j);

            if (c->editEnabled())
            {
                c = static_cast<Cell *>(currentItem());

                if (!c)
                {
                    return;
                }

                drawEyeModeBackground(c->row(), c->column());

                return;
            }
        }
    }
}

bool SudokuTable::godMode() const
{
    return isGodMode;
}

void SudokuTable::setGodMode(bool flag)
{
    isGodMode = flag;
}

void SudokuTable::drawBasicBackgroud()
{
    Cell *c;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            c = cell(i, j);
            int newr = i / 3;
            int newc = j / 3;
            if ((newr + newc) % 2)
                c->setBackgroundColor(Cell::WHITE);
            else
                c->setBackgroundColor(Cell::GREY);
        }
}

void SudokuTable::drawEyeModeBackground(int row, int column)
{
    if (row == -1 || column == -1) return;
    Cell *c;
    drawBasicBackgroud();
    if (!eyeMode()) return;

    for (int i = 0; i < 9; i++)
    {
        c = cell(row, i);
        c->setBackgroundColor(Cell::EYECOLOR);
        c = cell(i, column);
        c->setBackgroundColor(Cell::EYECOLOR);
    }

    int newr = row / 3;
    int newc = column / 3;

    for (int i = newr * 3; i < (newr + 1) * 3; i++)
        for (int j = newc * 3; j < (newc + 1) * 3; j++)
        {
            c = cell(i, j);
            c->setBackgroundColor(Cell::EYECOLOR);
        }
}

void SudokuTable::somethingChanged(int row, int column)
{
    Cell *c = cell(row, column);
    if (!c) return;
    if (!c->dirty())
        return;
    else
        c->setDirty(false);
    int num = c->data(Qt::EditRole).toInt();
    if (godMode())
    {
        sudokuData->setInputDataNum(row, column, num);
        int invalidData[9][9];
        sudokuData->getInvalidDataRecord(invalidData);
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                c = cell(i, j);
                if (invalidData[i][j])
                    c->setTextColor(Cell::WRONG);
                else
                    c->setTextColor(Cell::DEFAULT);
            }
        emit setPreviousEnabled(sudokuData->hasPrevious());
        emit setNextEnabled(sudokuData->hasNext());
    }
    else
    {
        sudokuData->setUserAnswerNum(row, column, num);
        bool win = sudokuData->checkUserAnswer();
        if (win)
        {
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                {
                    c = cell(i, j);
                    if (!c->editEnabled()) continue;
                    c->setEditEnabled(false);
                }
            QMessageBox::information(0, QStringLiteral("Ê¤Àû"), QStringLiteral("ÄãÓ®ÁË£¡£¡£¡"));
        }
        else
        {
            int invalidData[9][9];
            sudokuData->getInvalidDataRecord(invalidData);
            Cell *c;
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                {
                    c = cell(i, j);
                    if (!c->editEnabled()) continue;
                    if (invalidData[i][j])
                        c->setTextColor(Cell::WRONG);
                    else
                        c->setTextColor(Cell::RIGHT);
                }
        }
    }
}

Cell * SudokuTable::cell(int row, int column)
{
    return static_cast<Cell *>(item(row, column));
}
