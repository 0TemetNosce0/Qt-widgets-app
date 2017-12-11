#ifndef SUDOKUDATA_H
#define SUDOKUDATA_H

#include <ctime>

class SudokuData
{
public:
    SudokuData();

    void clear();
    void erase();

    void getInputData(int(*data)[9]) const;
    void setInputDataNum(int row, int column, int num);

    void setUserAnswerNum(int row, int column, int num);
    bool checkUserAnswer();

    bool hasValidData() const;
    void getInvalidDataRecord(int(*data)[9]) const;

    void getPreviousAnswer(int(*data)[9]);
    void getNextAnswer(int(*data)[9]);

    void getNewPuzzle(int(*data)[9]);

    bool hasNext() const;
    bool hasPrevious() const;

    int getSolutions() const;
    void setSolutions(int num);

private:
    void initial();

    int getAnswerNum(int max, int time_limit = 100000000);
    bool dfsNum(int order, int &ans, int max, time_t beg, int time_limit);
    bool dfsPrevious(int order);
    bool dfsNext(int order);

    bool isEnd() const;
    bool isValidNum(int(*data)[9], int row, int column, int num) const;
    bool canContinue() const;

    void tryNum(int row, int column, int num);
    void checkDataValid(int(*data)[9]);
    bool findOrederPos(int &row, int &column, int order) const;
    bool findBestPos(int &row, int &column) const;
    void fillAnswerNum(int(*data)[9], int &row, int &column, int num, int order);
    void unfillAnswerNum(int(*data)[9], int row, int column);

private:
    int inputData[9][9];
    int invalidDataRecord[9][9];
    bool dataIsValid;

    int userAnswerData[9][9];
    int previousAnswerData[9][9];
    int currentAnswerData[9][9];
    int nextAnswerData[9][9];

    int solutions;
    int currentAnswerOrder;
    bool dfsInitialed;
    bool hasPreviousAnswer;
    bool hasNextAnswer;

    int filledBoxs;
    int fillOrder[9][9];
    int numCanTry[82][9][9][10];
};

#endif
