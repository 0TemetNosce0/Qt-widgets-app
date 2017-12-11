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

#include <QtGui>
#include <iostream> //NOTE: for debugging
#include <stdexcept>

#include "Table.h"
#include "Calculator.h"

using std::runtime_error;

Calculator* Calculator::_calculator = 0;

Calculator* Calculator::calculator()
{
    if (!_calculator)
    {
        _calculator = new Calculator;
    }

    return _calculator;
}

bool Calculator::isFormula(const QString &formula)
{
    if (formula.isEmpty())
    {
        return false;
    }
    else if (formula[0] != '=')
    {
        return false;
    }
    else
    {
        return true;
    }
}

QString Calculator::calculate(Table *t, int r, int c)
{
    table = t;
    currentRow = r;
    currentColumn = c;

    QString formula = table -> getItemText(currentRow, currentColumn, Qt::EditRole);

    if (!isFormula(formula))
    {
        return formula;
    }

    formula = formula.toUpper();
    formula.append(QChar(QChar::Null));

    int iterator = 1; //first character is '='
    QString errorMessage;
    int errorPosition;
    errorPosition = checkSyntax(formula, errorMessage, iterator);

    if (errorPosition >= 0)
    {
        return errorMessage + " at position " + QString::number(errorPosition+1);
    }
    else if (errorPosition == -2) //unknown error position
    {
        return errorMessage;
    }

    deleteSpaces(formula);
    QString answer;

    try
    {
        answer = QString::number(calculateSentences(formula, iterator));
    }
    catch (runtime_error &error)
    {
        answer = error.what();
    }

    return answer;
}

double Calculator::calculateSentences(const QString &formula, int &iterator)
{
    double sumOfSentences = 0;
    QChar sentencesOperator = '+';
    double currentSentence = 0;

    while(1)
    {
        currentSentence = calculateASentence(formula, iterator);

        if (sentencesOperator == '+')
        {
            sumOfSentences += currentSentence;
        }
        else  // sentencesOperator == '-'
        {
            sumOfSentences -= currentSentence;
        }

        if (formula[iterator] == QChar::Null)
        {
            return sumOfSentences;
        }

        if (formula[iterator] == ')')
        {
            iterator++;
            return sumOfSentences;
        }

        sentencesOperator = formula[iterator++];
    }
}

double Calculator::calculateASentence(const QString &formula, int &iterator)
{
    double answer;
    double operand;
    QChar currentSentenceOperator;

    answer = evaluateFactor(formula, iterator);
    while (formula[iterator] != QChar::Null)
    {
        currentSentenceOperator = formula[iterator];

        if (currentSentenceOperator != '*' && currentSentenceOperator != '/')
        {
            return answer;
        }

        iterator++;
        operand = evaluateFactor(formula, iterator);

        if (currentSentenceOperator == '*')
        {
            answer *= operand;
        }
        else //currentSentenceOperator == '/'
        {
            if (operand == 0)
            {
                throw runtime_error("Error: Divide by zero");
            }
            else
            {
                answer /= operand;
            }
        }
    }

    return answer;
}

double Calculator::evaluateFactor(const QString &formula, int &iterator)
{
    int lastIterator = iterator;

    if (isNumber(formula, iterator))
    {
        return formula.mid(lastIterator, iterator-lastIterator).toDouble();
    }
    else if (isVariable(formula, iterator))
    {
        return valueOfCell(formula.mid(lastIterator, iterator-lastIterator));
    }
    else if (isRange(formula, iterator))
    {
        return valueOfCell(formula.mid(lastIterator,
                                       formula.indexOf(':', lastIterator)-lastIterator));
    }
    else if (isOpenParenthesis(formula, iterator))
    {
        return calculateSentences(formula, iterator);
    }
    else if (isFunction(formula, iterator))
    {
        return evaluateFunction(formula.mid(lastIterator,
                                            iterator-lastIterator)+QChar(QChar::Null));
    }
    else //should not happen
    {
        throw runtime_error("Unknown factor");
    }
}

double Calculator::evaluateFunction(const QString &function)
{
    QString functionName;
    QStringList stringArgs;
    QList<double> doubleArgs;
    double answer = 0.0;
    int iterator = 0;

    while(function[iterator] != '(')
    {
        functionName += function[iterator++];
    }

    iterator++; //ignore '('

    while (function[iterator] != QChar::Null)
    {
        QString curArgument = getNextArgumentOfFunction(function, iterator);

        if (!curArgument.isEmpty())
        {
            stringArgs.append(curArgument);
        }
    }

    for (int i=0; i<stringArgs.size(); i++)
    {
        int j=0;
        doubleArgs.append(calculateSentences(stringArgs[i]+QChar(QChar::Null), j));
    }

    if (functionName == "SIN")
    {
        answer = func_sin(doubleArgs[0]);
    }
    else if (functionName == "COS")
    {
        answer = func_cos(doubleArgs[0]);
    }
    else if (functionName == "TAN")
    {
        answer = func_tan(doubleArgs[0]);
    }
    else if (functionName == "COT")
    {
        answer = func_cot(doubleArgs[0]);
    }
    else if (functionName == "FABS")
    {
        answer = func_fabs(doubleArgs[0]);
    }
    else if (functionName == "LOG")
    {
        answer = func_log(doubleArgs[0]);
    }
    else if (functionName == "LOG10")
    {
        answer = func_log10(doubleArgs[0]);
    }
    else if (functionName == "SQRT")
    {
        answer = func_sqrt(doubleArgs[0]);
    }
    else if (functionName == "POW")
    {
        answer = func_pow(doubleArgs[0], doubleArgs[1]);
    }
    else if (functionName == "ROW")
    {
        answer = func_row();
    }
    else if (functionName == "COLUMN")
    {
        answer = func_column();
    }
    else if (functionName == "PI")
    {
        answer = func_pi();
    }
    else if (functionName == "SUM")
    {
        answer = func_sum(stringArgs, doubleArgs);
    }
    else if (functionName == "PRODUCT")
    {
        answer = func_product(stringArgs, doubleArgs);
    }
    else if (functionName == "MIN")
    {
        answer = func_min(stringArgs, doubleArgs);
    }
    else if (functionName == "MAX")
    {
        answer = func_max(stringArgs, doubleArgs);
    }
    else if (functionName == "AVERAGE")
    {
        answer = func_average(stringArgs, doubleArgs);
    }
    else if (functionName == "MEDIAN")
    {
        answer = func_median(stringArgs, doubleArgs);
    }
    else if (functionName == "MODE")
    {
        answer = func_mode(stringArgs, doubleArgs);
    }
    else //should not happen
    {
        throw runtime_error("unknown function "+functionName.toStdString());
    }

    return answer;
}

double Calculator::valueOfCell(const QString &locationOfOtherCell)
{
    int otherCellRow, otherCellColumn;
    Table::decodePosition(locationOfOtherCell, otherCellRow, otherCellColumn);
    QString otherCellFormula = table -> getItemText(otherCellRow, otherCellColumn, Qt::EditRole);
    otherCellFormula.append(QChar(QChar::Null));

    //if the formula of cell "A1" is using the value of cell "A2" and
    //the formula of cell "A2" is using the value of cell "A1",
    //an infinite loop will occur... So:
    if (isFormula(otherCellFormula))
    {
        QString currentCellLocation;
        Table::encodePosition(currentCellLocation, currentRow, currentColumn);
        int i = otherCellFormula.indexOf(currentCellLocation, 0, Qt::CaseInsensitive);

        if (i != -1 && !otherCellFormula[i-1].isLetter()
                && !otherCellFormula[i+currentCellLocation.length()].isDigit())
        {
            throw runtime_error("Error: This formula makes an infinite loop");
        }
    }

    //QString::toDouble() returns 0 if conversion fails
    return table -> getItemText(otherCellRow, otherCellColumn).toDouble();
}

int Calculator::checkSyntax(const QString &formula, QString &errorMessage, int iterator)
{
    int parenthesis = countParenthesis(formula);

    if (parenthesis == -1)
    {
        errorMessage = "Syntax error: Missing parenthesis";
        return -2; //unknown position
    }
    else if (parenthesis > 0)
    {
        errorMessage = "Syntax error";
        return parenthesis;
    }

    while (1)
    {
        ignoreSpaces(formula, iterator);

        while(isOpenParenthesis(formula, iterator))
        {
            ignoreSpaces(formula, iterator);
        }

        if (formula[iterator] == QChar::Null
                || (!isVariable(formula, iterator)
                    && !isNumber(formula, iterator)
                    && !isRange(formula, iterator)))
        {
            int lastIterator = iterator;

            if (isFunction(formula, iterator))
            {
                QString function = formula.mid(lastIterator, iterator-lastIterator)
                        + QChar(QChar::Null);
                int errorPosition = checkFunctionSyntax(function, errorMessage);

                if (errorPosition != -1)
                {
                    return errorPosition == -2 ? -2 : errorPosition+lastIterator;
                }
            }
            else
            {
                errorMessage = "Syntax error";
                return iterator;
            }
        }

        ignoreSpaces(formula, iterator);

        while(isCloseParenthesis(formula, iterator))
        {
            ignoreSpaces(formula, iterator);
        }

        if (formula[iterator] == QChar::Null)
        {
            break;
        }

        if (!isOperator(formula, iterator))
        {
            errorMessage = "Syntax error";
            return iterator;
        }
    }

    return -1; //successful
}

int Calculator::checkFunctionSyntax(const QString &function, QString &errorMessage)
{
    QString functionName;
    QStringList arguments;
    int iterator = 0;

    while(function[iterator] != '(')
    {
        functionName += function[iterator++];
    }

    ignoreSpaces(function, iterator);
    iterator++; //ignore '('

    while (function[iterator] != QChar::Null)
    {
        int lastIterator = iterator;
        arguments.append(getNextArgumentOfFunction(function, iterator));

        if (arguments.last().isEmpty())
        {
            if (arguments.size() > 1)
            {
                errorMessage = "Syntax error";
                return iterator;
            }
            else
            {
                arguments.clear();
            }
        }
        else
        {
            int errorPosition = checkSyntax(arguments.last()+QChar(QChar::Null), errorMessage, 0);

            if (errorPosition != -1)
            {
                return errorPosition == -2 ? -2 : errorPosition+lastIterator;
            }
        }
    }

    int argumentCount = arguments.size();
    bool rightArguments = false;

    if (functionName == "SIN"
            || functionName == "COS"
            || functionName == "TAN"
            || functionName == "COT"
            || functionName == "FABS"
            || functionName == "LOG"
            || functionName == "LOG10"
            || functionName == "SQRT")
        rightArguments = argumentCount == 1;

    else if (functionName == "POW")
    {
        rightArguments = argumentCount == 2;
    }
    else if (functionName == "ROW" || functionName == "COLUMN" || functionName == "PI")
    {
        rightArguments = argumentCount == 0;
    }
    else if (functionName == "SUM"
             || functionName == "PRODUCT"
             || functionName == "MIN"
             || functionName == "MAX"
             || functionName == "AVERAGE"
             || functionName == "MEDIAN"
             || functionName == "MODE")
    {
        rightArguments = argumentCount > 0;
    }

    if (rightArguments)
    {
        return -1; //successful
    }
    else
    {
        errorMessage = "Syntax Error: Unknown function " + functionName;
        return 0;
    }
}

QString Calculator::getNextArgumentOfFunction(const QString &function, int &iterator)
{
    QString argument;
    int parenthesisCount = 1;

    while (function[iterator] != QChar::Null)
    {
        QChar curChar = function[iterator++];

        if (curChar == '(')
        {
            parenthesisCount++;
        }
        else if (curChar == ')')
        {
            parenthesisCount--;
            if (parenthesisCount == 0)
            {
                return argument;
            }
        }
        else if (curChar == ',' && parenthesisCount == 1)
        {
            return argument;
        }

        argument += curChar;
    }

    return argument; //should not reach here
}

void Calculator::deleteSpaces(QString &formula)
{
    formula.remove(QRegExp("\\s"));
}

void Calculator::ignoreSpaces(const QString &formula, int &iterator)
{
    while (1)
    {
        if (formula[iterator].isSpace())
        {
            iterator++;
        }
        else
        {
            break;
        }
    }
}

bool Calculator::isVariable(const QString &formula, int &iterator)
{
    // a variable starts with (at least) one letter
    // and continues with (at least) one digit (e.g "EF23")
    // but if it ends with ')' it's a function
    // and if it ends with ':' it's a range
    int i = iterator;
    int lastI = iterator;

    while(formula[i].isLetter())
    {
        i++;
    }

    if (i == lastI)
    {
        return false;
    }

    lastI = i;

    while(formula[i].isDigit())
    {
        i++;
    }

    if (i==lastI)
    {
        return false;
    }

    ignoreSpaces(formula, i);
    lastI = i;

    if (formula[i] == '(' || formula[i] == ':')
    {
        return false; //it is a function or a range, not a variable
    }

    iterator = lastI;
    return true;
}

bool Calculator::isRange(const QString &formula, int &iterator)
{
    // A range starts with one variable, then ':', then another variable (e.g. "A1:B1"
    int i = iterator;
    int lastI = iterator;

    while(formula[i].isLetter())
    {
        i++;
    }

    if (i == lastI)
    {
        return false;
    }

    lastI = i;

    while(formula[i].isDigit())
    {
        i++;
    }

    if (i==lastI)
    {
        return false;
    }

    ignoreSpaces(formula, i);

    if (formula[i++] != ':')
    {
        return false;
    }

    ignoreSpaces(formula, i);

    lastI = i;

    while(formula[i].isLetter())
    {
        i++;
    }

    if (i == lastI)
    {
        return false;
    }

    lastI = i;

    while(formula[i].isDigit())
    {
        i++;
    }

    if (i == lastI)
    {
        return false;
    }

    iterator = i;
    return true;
}

bool Calculator::isNumber(const QString &formula, int &iterator)
{
    //valid number formats:
    //"123", "123.123", "123E+123", "123E-123"
    //it can start with '+' or '-' (or no sign)
    int count = 0;
    int i=iterator;
    int pointPosition = -1;

    if (formula[i] == '-' || formula[i] == '+')
    {
        i++;
    }

    for (;; i++)
    {
        if (formula[i].isDigit())
        {
            count++;
        }
        else if (formula[i] == '.')
        {
            if (pointPosition != -1)
            {
                return false;
            }
            else
            {
                pointPosition = count;
            }
        }
        else
        {
            break;
        }
    }

    if (count==0 || pointPosition==0 || pointPosition==count)
    {
        return false;
    }

    iterator = i;

    if (formula[i] == 'E' && (formula[i+1] == '-' || formula[i+1] == '+'))
    {
        count = 0;
        i += 2;

        while(formula[i].isDigit())
        {
            count++;
            i++;
        }

        if (count)
        {
            iterator = i;
        }
    }

    return true;
}

bool Calculator::isFunction(const QString &formula, int &iterator)
{
    int count = 0;
    int i = iterator;

    //first character should be a letter
    if (!formula[i].isLetter())
    {
        return false;
    }

    //letter or number
    for (; formula[i].isLetter() || formula[i].isDigit(); i++)
    {
        count++;
    }

    if (!count)
    {
        return false;
    }

    ignoreSpaces(formula, i);

    if (formula[i++] != '(')
    {
        return false;
    }

    int parenthesisCount = 1;

    for (; parenthesisCount != 0; i++)
    {
        if (formula[i] == '(')
        {
            parenthesisCount++;
        }
        else if (formula[i] == ')')
        {
            parenthesisCount--;
        }
    }

    iterator = i;
    return true;
}

bool Calculator::isOperator(const QString &formula, int &iterator)
{
    int i = iterator;

    if (formula[i] == '+'
            || formula[i] == '-'
            || formula[i] == '*'
            || formula[i] == '/')
    {
        iterator++;
        return 1;
    }
    else
    {
        return 0;
    }
}

bool Calculator::isOpenParenthesis(const QString &formula, int &iterator)
{
    if (formula[iterator] == '(')
    {
        iterator++;
        return true;
    }
    else
    {
        return false;
    }
}

bool Calculator::isCloseParenthesis(const QString &formula, int &iterator)
{
    if (formula[iterator] == ')')
    {
        iterator++;
        return true;
    }
    else
    {
        return false;
    }
}

int Calculator::countParenthesis(const QString &formula)
{
    int parenthesisCount = 0;

    for (int i=0; formula[i] != QChar::Null; i++)
    {
        if (formula[i] == '(')
        {
            parenthesisCount++;
        }
        else if (formula[i] == ')')
        {
            parenthesisCount--;
        }

        if (parenthesisCount < 0)
        {
            return i;
        }
    }

    if (parenthesisCount > 0)
    {
        return -1; //missing parenthesis
    }
    else
    {
        return 0;
    }
}

QList<double> Calculator::extractData(const QStringList &stringArgs, const QList<double> &doubleArgs)
{
    QList<double> returnList;

    for (int i = 0; i < stringArgs.size(); i++)
    {
        int iterator = 0;

        if (isRange(stringArgs[i] + QChar(QChar::Null), iterator))
        {
            if (iterator == stringArgs[i].size()) //if there is only a range in the argument
            {
                QTableWidgetSelectionRange range;
                Table::decodeRange(stringArgs[i], range);

                for (int row=range.topRow(); row<=range.bottomRow(); row++)
                {
                    for (int column=range.leftColumn(); column<=range.rightColumn(); column++)
                    {
                        returnList.append(table -> getItemText(row, column).toDouble());
                    }
                }

                continue;
            }
        }

        returnList.append(doubleArgs[i]);
    }

    return returnList;
}


/// Functions

double Calculator::func_sin(double arg1)
{
    return std::sin(radToDeg(arg1));
}

double Calculator::func_cos(double arg1)
{
    return std::cos(radToDeg(arg1));
}

double Calculator::func_tan(double arg1)
{   return std::tan(radToDeg(arg1));
}

double Calculator::func_cot(double arg1)
{
    return 1/std::tan(radToDeg(arg1));
}

double Calculator::func_fabs(double arg1)
{
    return std::fabs(arg1);
}

double Calculator::func_log(double arg1)
{
    return std::log(arg1);
}

double Calculator::func_log10(double arg1)
{
    return std::log10(arg1);
}

double Calculator::func_sqrt(double arg1)
{
    return std::sqrt(arg1);
}

double Calculator::func_pow(double arg1, double arg2)
{
    return std::pow(arg1, arg2);
}

double Calculator::func_row()
{
    return currentRow+1;
}

double Calculator::func_column()
{
    return currentColumn+1;
}

double Calculator::func_pi()
{
    return PI;
}

double Calculator::func_sum(const QStringList &stringArgs, const QList<double> &doubleArgs)
{
    double sum = 0;
    QList<double> allData = extractData(stringArgs, doubleArgs);

    for (int i=0; i<allData.size(); i++)
    {
        sum += allData[i];
    }

    return sum;
}

double Calculator::func_product(const QStringList &stringArgs, const QList<double> &doubleArgs)
{
    double product = 1;
    QList<double> allData = extractData(stringArgs, doubleArgs);

    for (int i=0; i<allData.size(); i++)
    {
        product *= allData[i];
    }

    return product;
}

double Calculator::func_min(const QStringList &stringArgs, const QList<double> &doubleArgs)
{
    QList<double> allData = extractData(stringArgs, doubleArgs);
    double min = allData[0];

    for (int i=1; i<allData.size(); i++)
    {
        if (allData[i] < min)
        {
            min = allData[i];
        }
    }

    return min;
}

double Calculator::func_max(const QStringList &stringArgs, const QList<double> &doubleArgs)
{
    QList<double> allData = extractData(stringArgs, doubleArgs);
    double max = allData[0];

    for (int i=1; i<allData.size(); i++)
    {
        if (allData[i] > max)
        {
            max = allData[i];
        }
    }

    return max;
}

double Calculator::func_average(const QStringList &stringArgs, const QList<double> &doubleArgs)
{
    QList<double> allData = extractData(stringArgs, doubleArgs);
    double sum = 0;

    for (int i=0; i<allData.size(); i++)
    {
        sum += allData[i];
    }

    return sum/allData.size();
}

double Calculator::func_median(const QStringList &stringArgs, const QList<double> &doubleArgs)
{
    QList<double> allData = extractData(stringArgs, doubleArgs);
    qStableSort(allData);

    if (allData.size()%2 != 0)
    {
        return allData[allData.size()/2];
    }
    else
    {
        return (allData[allData.size()/2]+allData[allData.size()/2-1])/2;
    }
}

double Calculator::func_mode(const QStringList &stringArgs, const QList<double> &doubleArgs)
{
    //TODO: A faster way to find mode.
    QList<double> allData = extractData(stringArgs, doubleArgs);
    QList<int> repeatitions;

    for (int i=0; i<allData.size(); i++)
    {
        repeatitions.append(0);
        for (int j=0; j<allData.size(); j++)
        {
            if (allData[j] == allData[i])
            {
                repeatitions[i]++;
            }
        }
    }

    int maxRepeated = 0;

    for (int i=1; i<repeatitions.size(); i++)
    {
        if(repeatitions[i] > repeatitions[maxRepeated])
        {
            maxRepeated = i;
        }
    }

    //if there is any value with the same repeatition as the maxRepeated value,
    //then return the least value
    QList<int> sameRepeatitions;

    for (int i=0; i<repeatitions.size(); i++)
    {
        if (repeatitions[i] == repeatitions[maxRepeated])
        {
            sameRepeatitions.append(i);
        }
    }

    int leastOne = 0;

    for (int i=1; i<sameRepeatitions.size(); i++)
    {
        if (allData[sameRepeatitions[i]] < allData[sameRepeatitions[leastOne]])
        {
            leastOne = i;
        }
    }

    return allData[sameRepeatitions[leastOne]];
}


