#ifndef SUDOKUTABLE_H
#define SUDOKUTABLE_H

#include <QTableWidget>

#include "cell.h"
#include "sudokudata.h"

class SudokuTable : public QTableWidget
{
    Q_OBJECT

public:
    SudokuTable(QWidget *parent  = 0);

public slots:
    void newPuzzle();
    void previous();
    void next();
    void erase();
    void clear();
    int dataSolutions() const;
    void setDataSolutions(int num);
    bool eyeMode() const;
    void setEyeMode(bool flag);
    bool godMode() const;
    void setGodMode(bool flag);
    void drawBasicBackgroud();
    void drawEyeModeBackground(int row, int column);
    void somethingChanged(int row, int column);

signals:
    void setPreviousEnabled(bool flag);
    void setNextEnabled(bool flag);

private:
    Cell * cell(int row, int column);

    SudokuData *sudokuData;
    bool isGodMode;
    bool isEyeMode;
};
#endif // !SUDOKUTABLE_H
