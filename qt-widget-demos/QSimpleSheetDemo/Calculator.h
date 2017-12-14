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

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <cmath>
#define PI 3.14159265358979323846

class Table;

class Calculator
{
public:
    static Calculator* calculator();
    //returns true if the string is a formula (a formula should start with '=')
    static bool isFormula(const QString&);
    //receives a Table pointer, row and column number of the cell which is calculating
    //returns the answer of the formula
    QString calculate(Table*, int, int);

private:
    //receives two string (formula, errorMessage) and an iterator then:
    //returns -1 if there is no syntax error,
    //otherwise returns the position of error (-2 for unknown position)
    //and puts the error message in errorMessage string
    int checkSyntax(const QString&, QString&, int);
    //receives a string (formula) and an iterator then
    //evaluates all sentences
    double calculateSentences(const QString&, int&);
    //evaluates just a sentence
    double calculateASentence(const QString&, int&);
    //evaluates a factor. a factor can be a number, a function, a paranthesis, a variable,...
    double evaluateFactor(const QString&, int&);
    //receives a string (function) and returns the answer of the function
    double evaluateFunction(const QString&);
    //it receives two strings (function, errorMessage) then:
    //returns -1 if there is no syntax error
    //otherwise returns the position of error (-2 for unknown position)
    //and puts the error message in errorMessage string
    int checkFunctionSyntax(const QString&, QString&);
    //receives a string (formula) and deletes all spaces
    void deleteSpaces(QString&);
    //receives a string (formula) and an iterator, then ignores spaces
    void ignoreSpaces(const QString&, int&);
    //receives a string (formula) and an iterator, then:
    //returns true if it is a variable (like "A1")
    bool isVariable(const QString&, int&);
    //receives a string (formula) and an iterator, then:
    //returns true if it is a variable (like "A1:B1")
    bool isRange(const QString&, int&);
    //receives a string (formula) and an iterator, then:
    //returns true if it is a digit (like "123")
    bool isNumber(const QString&, int&);
    //receives a string (formula) and an iterator, then:
    //returns true if it is a function (it doesn't check the syntax of the function)
    bool isFunction(const QString&, int&);
    //receives a string (formula) and an iterator, then:
    //returns true if it is an operator (like "+", '-', "*", '/')
    bool isOperator(const QString&, int&);
    //receives a string (formula) and an iterator, then:
    //returns true if it is an open parenthesis (like "(" )
    bool isOpenParenthesis(const QString&, int&);
    //receives a string (formula) and an iterator, then:
    //returns true if it is a close parenthesis (like ")" )
    bool isCloseParenthesis(const QString&, int&);
    //receives two strings (formula, errorMessage), then:
    //returns 0 if number of '(' characters are equal to number of ')' characters
    //or returns the position of error
    //or returns -1 for parenthesis missing
    int countParenthesis(const QString&);
    QString getNextArgumentOfFunction(const QString&, int&);
    //receives a string (location of cell) then
    //returns the value of cell the cell in table.
    double valueOfCell(const QString&);
    QList<double> extractData(const QStringList&, const QList<double>&);

    double degToRad(double angle)
    {
        return 180 * angle / PI;
    }

    double radToDeg(double angle)
    {
        return PI*angle/180;
    }

    Calculator()
    {
        table = 0;
        currentRow = currentColumn = 0;
    }

    static Calculator *_calculator;
    Table *table;
    int currentRow;
    int currentColumn;


    ///Functions:
    double func_sin(double);
    double func_cos(double);
    double func_tan(double);
    double func_cot(double);
    double func_fabs(double);
    double func_log(double);
    double func_log10(double);
    double func_sqrt(double);
    double func_pow(double, double);
    double func_row();
    double func_column();
    double func_pi();
    double func_sum(const QStringList&, const QList<double>&);
    double func_product(const QStringList&, const QList<double>&);
    double func_min(const QStringList&, const QList<double>&);
    double func_max(const QStringList&, const QList<double>&);
    double func_average(const QStringList&, const QList<double>&);
    double func_median(const QStringList&, const QList<double>&);
    double func_mode(const QStringList&, const QList<double>&);
};

#endif

