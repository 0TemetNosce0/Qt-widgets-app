#include <ctime>
#include <cstring>
#include <cstdlib>

#include <QMessageBox>

#include "sudokudata.h"

SudokuData::SudokuData()
{
    srand(time(NULL));
    clear();
}

void SudokuData::clear()
{
    memset(inputData, 0, sizeof(inputData));
    memset(invalidDataRecord, 0, sizeof(invalidDataRecord));

    memset(userAnswerData, 0, sizeof(userAnswerData));
    memset(previousAnswerData, 0, sizeof(previousAnswerData));
    memset(currentAnswerData, 0, sizeof(currentAnswerData));
    memset(nextAnswerData, 0, sizeof(nextAnswerData));

    currentAnswerOrder = 0;
    hasPreviousAnswer = false;
    hasNextAnswer = true;

    filledBoxs = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fillOrder[i][j] = -1;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                if (k == 0)
                {
                    numCanTry[0][i][j][k] = 9;
                }
                else
                {
                    numCanTry[0][i][j][k] = true;
                }
            }
        }
    }
}

void SudokuData::erase()
{
    int temp[9][9];
    getInputData(temp);
    clear();
    memcpy(inputData, temp, sizeof(temp));
    memcpy(userAnswerData, temp, sizeof(temp));
    checkDataValid(inputData);

    if (!hasValidData())
    {
        hasNextAnswer = false;
    }
    else
    {
        hasNextAnswer = getAnswerNum(1);
    }
}

void SudokuData::getInputData(int(*data)[9]) const
{
    memcpy(data, inputData, sizeof(inputData));
}

void SudokuData::setInputDataNum(int row, int column, int num)
{
    inputData[row][column] = num;
    checkDataValid(inputData);

    if (!hasValidData())
    {
        hasNextAnswer = false;
    }
    else
    {
        hasNextAnswer = getAnswerNum(1);
    }
}

void SudokuData::setUserAnswerNum(int row, int column, int num)
{
    userAnswerData[row][column] = num;
    checkDataValid(userAnswerData);
}

bool SudokuData::checkUserAnswer()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (!userAnswerData[i][j])
            {
                return false;
            }
        }
    }

    checkDataValid(userAnswerData);
    return hasValidData();
}

bool SudokuData::hasValidData() const
{
    return dataIsValid;
}

void SudokuData::getInvalidDataRecord(int(*data)[9]) const
{
    memcpy(data, invalidDataRecord, sizeof(invalidDataRecord));
}

void SudokuData::getPreviousAnswer(int(*data)[9])
{
    if (currentAnswerOrder <= 1)
    {
        QMessageBox::critical(0, QString("error"), QString("error in SudokuData::getPreviousAnswer"));
        return;
    }

    memcpy(previousAnswerData, currentAnswerData, sizeof(currentAnswerData));
    dfsInitialed = false;
    dfsPrevious(1);
    --currentAnswerOrder;

    if (currentAnswerOrder == 1)
    {
        hasPreviousAnswer = false;
    }

    hasNextAnswer = true;

    memcpy(currentAnswerData, previousAnswerData, sizeof(previousAnswerData));
    memcpy(data, currentAnswerData, sizeof(currentAnswerData));
}

void SudokuData::getNextAnswer(int(*data)[9])
{
    if (currentAnswerOrder == 0)
    {
        memcpy(currentAnswerData, inputData, sizeof(inputData));
        memcpy(nextAnswerData, inputData, sizeof(inputData));
        initial();
    }
    else
    {
        memcpy(nextAnswerData, currentAnswerData, sizeof(nextAnswerData));
        dfsInitialed = false;
    }

    dfsNext(1);
    currentAnswerOrder++;
    memcpy(currentAnswerData, nextAnswerData, sizeof(nextAnswerData));

    int tempFillOrder[9][9];
    int tempNumCanTry[82][9][9][10];
    int tempFilledBoxs;
    memcpy(tempFillOrder, fillOrder, sizeof(fillOrder));
    memcpy(tempNumCanTry, numCanTry, sizeof(numCanTry));
    tempFilledBoxs = filledBoxs;
    dfsInitialed = false;
    hasNextAnswer = dfsNext(1);
    memcpy(fillOrder, tempFillOrder, sizeof(fillOrder));
    memcpy(numCanTry, tempNumCanTry, sizeof(tempNumCanTry));
    filledBoxs = tempFilledBoxs;

    if (currentAnswerOrder > 1)
    {
        hasPreviousAnswer = true;
    }

    memcpy(data, currentAnswerData, sizeof(currentAnswerData));
}

void SudokuData::getNewPuzzle(int(*data)[9])
{
    const int maxCry = 1000;
    const int maxCryTimeLimit = 1000;
    int row, column, num, order;
    order = 0;
    clear();

    int count = 0;
    while (true)
    {
        row = rand() % 9;
        column = rand() % 9;

        if (inputData[row][column])
        {
            continue;
        }

        num = rand() % 9 + 1;

        if (!isValidNum(inputData, row, column, num))
        {
            continue;
        }

        inputData[row][column] = num;

        //排除一些超级坏的情况
        clock_t beg = clock();
        int ans_num = getAnswerNum(solutions + 1, maxCryTimeLimit);
        clock_t now = clock();

        if (now - beg > maxCryTimeLimit)
        {
            getNewPuzzle(data);
            return;
        }

        if (ans_num == solutions)
        {
            break;
        }
        else if (ans_num > solutions)
        {
            continue;
        }
        else
        {
            inputData[row][column] = 0;

            if (++count > maxCry)
            {
                getNewPuzzle(data);
                return;
            }
        }
    }

    memcpy(userAnswerData, inputData, sizeof(inputData));
    memcpy(data, userAnswerData, sizeof(userAnswerData));
}

bool SudokuData::hasNext() const
{
    return hasNextAnswer;
}

bool SudokuData::hasPrevious() const
{
    return hasPreviousAnswer;
}

int SudokuData::getSolutions() const
{
    return solutions;
}

void SudokuData::setSolutions(int num)
{
    solutions = num;
}

//根据currentAnswerData更新fillOrder和numCanTry。
void SudokuData::initial()
{
    //初始化部分
    filledBoxs = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fillOrder[i][j] = -1;
        }
    }


    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                if (k == 0)
                {
                    numCanTry[0][i][j][k] = 9;
                }
                else
                {
                    numCanTry[0][i][j][k] = true;
                }
            }
        }
    }


    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (currentAnswerData[i][j])
            {
                ++filledBoxs;
                tryNum(i, j, currentAnswerData[i][j]);
                fillOrder[i][j] = -1;
            }
            else
            {
                fillOrder[i][j] = 0;
            }
        }
    }
}

int SudokuData::getAnswerNum(int max, int time_limit /* = 100000000 */)
{
    memcpy(currentAnswerData, inputData, sizeof(inputData));
    initial();
    int ans = 0;
    clock_t beg = clock();
    dfsNum(1, ans, max, beg, time_limit);
    return ans;
}

bool SudokuData::dfsNum(int order, int &ans, int max, time_t beg, int time_limit)
{
    clock_t now = clock();

    if (now - beg > time_limit)
    {
        return true;
    }

    if (!canContinue())
    {
        return false;
    }

    int row, column;

    if (!findBestPos(row, column))
    {
        if (isEnd())
        {
            ans++;

            if (ans == max)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            QMessageBox::critical(0, QString("error"), QString("error in SudokuData::dfsNum"));
        }
    }

    for (int i = 1; i <= 9; i++)
    {
        if (!numCanTry[filledBoxs][row][column][i])
        {
            continue;
        }

        fillAnswerNum(currentAnswerData, row, column, i, order);

        if (dfsNum(order + 1, ans, max, beg, time_limit))
        {
            return true;
        }

        unfillAnswerNum(currentAnswerData, row, column);
    }

    return false;
}

bool SudokuData::dfsPrevious(int order)
{
    if (!canContinue())
    {
        return false;
    }

    int row, column;
    bool hasBegin = false;

    if (!dfsInitialed)
    {
        hasBegin = true;

        if (findOrederPos(row, column, order))
        {
            if (dfsPrevious(order + 1))
            {
                return true;
            }
        }
        else
        {
            dfsInitialed = true;
            return false;
        }
    }
    else if (!findBestPos(row, column))
    {
        if (isEnd())
        {
            return true;
        }
        else
        {
            QMessageBox::critical(0, QString("error"), QString("error in SudokuData::dfsPrevious"));
        }
    }

    for (int i = 9; i >= 1; i--)
    {
        if (hasBegin)
        {
            hasBegin = false;
            i = previousAnswerData[row][column];
            unfillAnswerNum(previousAnswerData, row, column);
            continue;
        }

        if (!numCanTry[filledBoxs][row][column][i])
        {
            continue;
        }

        fillAnswerNum(previousAnswerData, row, column, i, order);

        if (dfsPrevious(order + 1))
        {
            return true;
        }

        unfillAnswerNum(previousAnswerData, row, column);
    }

    return false;
}

bool SudokuData::dfsNext(int order)
{
    if (!canContinue())
    {
        return false;
    }

    int row, column;
    bool hasBegin = false;

    if (currentAnswerOrder != 0 && !dfsInitialed)
    {
        hasBegin = true;

        if (findOrederPos(row, column, order))
        {
            if (dfsNext(order + 1))
            {
                return true;
            }
        }
        else
        {
            dfsInitialed = true;
            return false;
        }
    }
    else if (!findBestPos(row, column))
    {
        if (isEnd())
        {
            return true;
        }
        else
        {
            QMessageBox::critical(0, QString("error"), QString("error in SudokuData::dfsNext"));
        }
    }

    for (int i = 1; i <= 9; i++)
    {
        if (hasBegin)
        {
            hasBegin = false;
            i = nextAnswerData[row][column];
            unfillAnswerNum(nextAnswerData, row, column);
            continue;
        }

        if (!numCanTry[filledBoxs][row][column][i])
        {
            continue;
        }

        fillAnswerNum(nextAnswerData, row, column, i, order);

        if (dfsNext(order + 1))
        {
            return true;
        }

        unfillAnswerNum(nextAnswerData, row, column);
    }

    return false;
}

bool SudokuData::isEnd() const
{
    return filledBoxs == 81;
}

bool SudokuData::isValidNum(int(*data)[9], int row, int column, int num) const
{
    if (num == 0)
    {
        return true;
    }

    for (int i = 0; i < 9; i++)
    {
        if (i != column && data[row][i] == num)
        {
            return false;
        }

        if (i != row && data[i][column] == num)
        {
            return false;
        }
    }

    int newr = row / 3;
    int newc = column / 3;

    for (int i = newr * 3; i < (newr + 1) * 3; i++)
    {
        for (int j = newc * 3; j < (newc + 1) * 3; j++)
        {
            if (i == row && j == column)
            {
                continue;
            }

            if (data[i][j] == num)
            {
                return false;
            }
        }
    }

    return true;
}

bool SudokuData::canContinue() const
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (numCanTry[filledBoxs][i][j][0] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

void SudokuData::tryNum(int row, int column, int num)
{
    memcpy(numCanTry[filledBoxs], numCanTry[filledBoxs - 1], sizeof(numCanTry[0]));

    numCanTry[filledBoxs][row][column][0] = -1;

    for (int i = 0; i < 9; i++)
    {
        if (numCanTry[filledBoxs][row][i][0] != -1
                && numCanTry[filledBoxs][row][i][num])
        {
            numCanTry[filledBoxs][row][i][num] = false;
            numCanTry[filledBoxs][row][i][0]--;
        }
        if (numCanTry[filledBoxs][i][column][0] != -1
                && numCanTry[filledBoxs][i][column][num])
        {
            numCanTry[filledBoxs][i][column][num] = false;
            numCanTry[filledBoxs][i][column][0]--;
        }
    }

    int newr = row / 3;
    int newc = column / 3;

    for (int i = newr * 3; i < (newr + 1) * 3; i++)
    {
        for (int j = newc * 3; j < (newc + 1) * 3; j++)
        {
            if (numCanTry[filledBoxs][i][j][0] != -1
                    && numCanTry[filledBoxs][i][j][num])
            {
                numCanTry[filledBoxs][i][j][num] = false;
                numCanTry[filledBoxs][i][j][0]--;
            }
        }
    }
}

void SudokuData::checkDataValid(int(*data)[9])
{
    dataIsValid = true;
    memset(invalidDataRecord, 0, sizeof(invalidDataRecord));

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (!isValidNum(data, i, j, data[i][j]))
            {
                dataIsValid = false;
                invalidDataRecord[i][j] = true;
            }
        }
    }
}

bool SudokuData::findOrederPos(int &row, int &column, int order) const
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (fillOrder[i][j] == order)
            {
                row = i;
                column = j;
                return true;
            }
        }
    }

    return false;
}

bool SudokuData::findBestPos(int &row, int &column) const
{
    int min = 10;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int goodName = numCanTry[filledBoxs][i][j][0];

            if (goodName != -1 && goodName != 0 && min > goodName)
            {
                min = goodName;
                row = i;
                column = j;
            }
        }
    }

    if (min != 10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SudokuData::fillAnswerNum(int(*data)[9], int &row, int &column, int num, int order)
{
    data[row][column] = num;
    fillOrder[row][column] = order;
    ++filledBoxs;
    memcpy(numCanTry[filledBoxs], numCanTry[filledBoxs - 1], sizeof(numCanTry[filledBoxs]));

    numCanTry[filledBoxs][row][column][0] = -1;

    for (int i = 0; i < 9; i++)
    {
        if (numCanTry[filledBoxs][row][i][0] != -1 &&
                numCanTry[filledBoxs][row][i][num])
        {
            numCanTry[filledBoxs][row][i][num] = false;
            numCanTry[filledBoxs][row][i][0]--;
        }

        if (numCanTry[filledBoxs][i][column][0] != -1 &&
                numCanTry[filledBoxs][i][column][num])
        {
            numCanTry[filledBoxs][i][column][num] = false;
            numCanTry[filledBoxs][i][column][0]--;
        }
    }

    int newr = row / 3;
    int newc = column / 3;

    for (int i = newr * 3; i < (newr + 1) * 3; i++)
    {
        for (int j = newc * 3; j < (newc + 1) * 3; j++)
        {
            if (numCanTry[filledBoxs][i][j][0] != -1 &&
                    numCanTry[filledBoxs][i][j][num])
            {
                numCanTry[filledBoxs][i][j][num] = false;
                numCanTry[filledBoxs][i][j][0]--;
            }
        }
    }
}

void SudokuData::unfillAnswerNum(int(*data)[9], int row, int column)
{
    data[row][column] = 0;
    fillOrder[row][column] = 0;
    --filledBoxs;
}
