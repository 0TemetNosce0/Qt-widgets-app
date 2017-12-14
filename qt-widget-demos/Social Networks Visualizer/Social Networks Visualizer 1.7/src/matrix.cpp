/***************************************************************************
 SocNetV: Social Network Visualizer 
 version: 1.7
 Written in Qt

                        matrix  -  description
                             -------------------
    copyright            : (C) 2005-2015 by Dimitris B. Kalamaras
    email                : dimitris.kalamaras@gmail.com
 ***************************************************************************/

/*******************************************************************************
*     This program is free software: you can redistribute it and/or modify     *
*     it under the terms of the GNU General Public License as published by     *
*     the Free Software Foundation, either version 3 of the License, or        *
*     (at your option) any later version.                                      *
*                                                                              *
*     This program is distributed in the hope that it will be useful,          *
*     but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
*     GNU General Public License for more details.                             *
*                                                                              *
*     You should have received a copy of the GNU General Public License        *
*     along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
********************************************************************************/

#include "matrix.h"

#include <cstdlib>        //allows the use of RAND_MAX macro
#include <QtMath>         //needed for fabs, qFloor etc



/**
 * @brief Matrix::Matrix
 * Default constructor - creates a Matrix of given size (default 0)
 * Use resize(int) to resize it
 * @param Actors
 */
Matrix::Matrix(int Actors)
{
    row = new (nothrow) Row[m_Actors = Actors];
    Q_CHECK_PTR(row);

    for (register int i = 0; i < m_Actors; i++)
    {
        row[i].resize(m_Actors);
    }
}



/**
* @brief Matrix::Matrix
* Copy constructor. Creates a Matrix identical to Matrix b
* Allows Matrix a=b declaration
* Every Row object holds max_int=32762
* @param b
*/
Matrix::Matrix(const Matrix &b)
{
    qDebug()<< "Matrix:: constructor";
    row = new Row[m_Actors = b.m_Actors];
    Q_CHECK_PTR(row);

    for (register int i = 0; i < m_Actors; i++)
    {
        row[i].resize(m_Actors);
    }

    for (register int i = 0; i < m_Actors; i++)
    {
        row[i] = b.row[i];
    }
}


/**
 * @brief Matrix::~Matrix
 * Destructor
 */
Matrix::~Matrix()
{
    delete [] row;
}

 /**
 * @brief Matrix::clear
 * clears data
 */
void Matrix::clear()
{
    if (m_Actors > 0)
    {
        qDebug() << "Matrix::clear() deleting old rows";
        m_Actors = 0;
        delete [] row;
    }
}

/**
 * @brief Matrix::resize
 * Resize this matrix.
 * Called before every operation on new matrices.
 * Every Row object holds max_int=32762
 * @param Actors
 */
void Matrix::resize(int Actors)
{
    qDebug() << "Matrix: resize() ";
    clear();
    row = new (nothrow) Row[m_Actors = Actors];
    Q_CHECK_PTR(row);
    qDebug() << "Matrix: resize() -- resizing each row";

    for (register int i = 0; i < m_Actors; i++)
    {
        row[i].resize(m_Actors);
    }
}




/**
* @brief Matrix::operator =
* Assigment allows copying a matrix onto another using b=a where b,a matrices
* Equals two matrices.
* @param a
* @return
*/
Matrix& Matrix::operator=(Matrix & a)
{
    qDebug() << "Matrix::operator asignment =";
    if (this != &a)
    {
        if(a.m_Actors != m_Actors)
        {
            clear();
            row = new (nothrow)Row[m_Actors = a.m_Actors];
            Q_CHECK_PTR(row);
            for (int i = 0; i < m_Actors; i++)
            {
                row[i].resize(m_Actors); //every Row object holds max_int=32762 actors
            }
        }

        for (int i = 0; i < m_Actors; i++)
        {
            row[i] = a.row[i];
        }
    }

    return *this;
}


/**
* @brief Matrix::operator +
* Matrix addition: +
* Adds two matrices of the same size and returns the sum.
* Allows to sum two matrices using c=a+b
* @param a
* @return
*/
Matrix& Matrix::operator+(Matrix & a)
{
      qDebug()<< "Matrix::operator addition";

      for (register int i = 0;i < rows(); i++)
      {
          for (register int j = 0; j < cols(); j++)
          {
              setItem(i, j, item(i, j) + a.item(i, j));
          }
      }

      return *this;
}


 //WARNING: this operator is slow! Avoid using it.
float  Matrix::operator()(const int r, const int c)
{
    return  row[r].column(c);
}


/**  	Outputs matrix m to a text stream
*/
QTextStream& operator <<  (QTextStream& os, Matrix& m)
{
    qDebug() << "Matrix: << Matrix";
    int fieldWidth = 8, newFieldWidth = 8, actorNumber=1;
    float maxVal, minVal;
    m.findMinMaxValues(maxVal,minVal);
    float element;

    if (maxVal == -1 || maxVal==RAND_MAX )
    {
        os << " max Value = " << QString("\xE2\x88\x9E") << endl;
    }
    else
    {
        os << " max Value = " << maxVal << endl;
    }

    if (minVal == -1 ||  minVal==RAND_MAX )
    {
        os << " min Value = " << QString("\xE2\x88\x9E") << endl;
    }
    else
    {
        os << " min Value = " << minVal << endl << endl;
    }

    if (maxVal > 999999)
    {
        fieldWidth = 14;
    }
    else if (maxVal > 99999)
    {
        fieldWidth = 13;
    }
    else if (maxVal > 9999)
    {
        fieldWidth = 12;
    }
    else if(maxVal > 999)
    {
        fieldWidth = 8;
    }
    else if(maxVal > 99)
    {
        fieldWidth = 7;
    }

    os << qSetFieldWidth(fieldWidth) << right <<  QString("v |");

    for (register int r = 0; r < m.cols(); ++r)
    {
        newFieldWidth = fieldWidth;
        actorNumber = r + 1;

        if (actorNumber > 99999)
        {
            newFieldWidth = fieldWidth - 5;
        }
        else if (actorNumber > 9999)
        {
            newFieldWidth = fieldWidth - 4;
        }
        else if (actorNumber > 999)
        {
            newFieldWidth = fieldWidth - 3;
        }
        else if (actorNumber > 99)
        {
            newFieldWidth = fieldWidth - 2;
        }
        else if (actorNumber > 9)
        {
            newFieldWidth = fieldWidth - 1;
        }

        os << qSetFieldWidth(newFieldWidth) << right  << QString("%1").arg(actorNumber) ;
    }

    os << endl;
    os.setFieldAlignment(QTextStream::AlignCenter);
    os.setPadChar('-');

    for (register int r = 0; r < m.cols()+1; ++r)
    {
        if ( r > 99999)
        {
            newFieldWidth = fieldWidth - 6;
        }
        else if ( r > 9999)
        {
            newFieldWidth = fieldWidth - 5;
        }
        else if ( r > 999)
        {
            newFieldWidth = fieldWidth - 4;
        }
        else if ( r > 99)
        {
            newFieldWidth = fieldWidth - 3;
        }
        else if ( r > 9)
        {
            newFieldWidth = fieldWidth - 2;
        }

        os << qSetFieldWidth(newFieldWidth) <<  QString("-") ;
    }

    os << qSetFieldWidth(1) << QString("-");
    os.setPadChar(' ');
    os << endl;

    for (register int r = 0; r < m.rows(); ++r)
    {
        actorNumber = r + 1;

        if (actorNumber > 99999)
        {
            newFieldWidth = fieldWidth - 5;
        }
        else if (actorNumber > 9999)
        {
            newFieldWidth = fieldWidth - 4;
        }
        else if (actorNumber > 999)
        {
            newFieldWidth = fieldWidth - 3;
        }
        else if (actorNumber > 99)
        {
            newFieldWidth = fieldWidth - 2;
        }
        else if (actorNumber > 9)
        {
            newFieldWidth = fieldWidth - 1;
        }
        else
        {
            newFieldWidth = fieldWidth;
        }

        os << qSetFieldWidth(newFieldWidth) << right << QString("%1 |").arg(actorNumber);

        for (register int c = 0; c < m.cols(); ++c)
        {
            element = m(r,c);
            newFieldWidth = fieldWidth;

            if (element == RAND_MAX )
            {
                newFieldWidth = fieldWidth;
            }
            else if (element > 9999)
            {
                newFieldWidth = fieldWidth - 5;
            }
            else if ( element > 9999)
            {
                newFieldWidth = fieldWidth - 4;
            }
            else if ( element > 999)
            {
                newFieldWidth = fieldWidth - 3;
            }
            else if ( element > 99)
            {
                newFieldWidth = fieldWidth - 2;
            }
            else if ( element > 9)
            {
                newFieldWidth = fieldWidth - 1;
            }
            else if ((element - floor(element)) != 0)
            {
                if ( element *10 == qFloor(10* element))
                {
                    newFieldWidth = fieldWidth - 1;
                }
                else if (element *100 == qFloor(100* element))
                {
                    newFieldWidth = fieldWidth - 1;
                }
                else if (element *1000 == qFloor(1000* element))
                {
                    newFieldWidth = fieldWidth - 2;
                }
                else
                {
                    newFieldWidth = fieldWidth - 2;
                }
            }
            else if (element < 1.0)
            {
                if (element *10 == qFloor(10* element))
                {
                    newFieldWidth = fieldWidth - 1;
                }
                else if (element *100 == qFloor(100* element))
                {
                    newFieldWidth = fieldWidth - 1;
                }
                else if (element *1000 == qFloor(1000* element))
                {
                    newFieldWidth = fieldWidth - 2;
                }
                else
                {
                    newFieldWidth = fieldWidth - 2;
                }
            }
            else
            {
                newFieldWidth = fieldWidth;
            }

            if ( element == -1 || element == RAND_MAX)  // we print infinity symbol instead of -1 (distances matrix).
            {
                os << qSetFieldWidth(newFieldWidth) << right << QString("\xE2\x88\x9E");
            }
            else
            {
                os << qSetFieldWidth(newFieldWidth)
                    << right << element;
            }
        }

        os << '\n';
    }

    return os;
}


void Matrix::findMinMaxValues (float & maxVal, float &minVal)
{
    maxVal = 0;
    minVal = RAND_MAX;
    for (register int r = 0; r < rows(); ++r)
    {
        for (register int c = 0; c < cols(); ++c)
        {
            if ( item(r,c) > maxVal)
            {
                maxVal = item(r, c);
            }

            if ( item(r,c) < minVal)
            {
                minVal = item(r, c);
            }
        }
    }
}



// makes this matrix the identity matrix I
void Matrix::identityMatrix(int Actors)
{
    qDebug() << "Matrix: identityMatrix() -- deleting old rows";
    clear();
    row = new (nothrow)Row[m_Actors = Actors];
    Q_CHECK_PTR(row);
    qDebug() << "Matrix: resize() -- resizing each row";
    for (int i = 0; i < m_Actors; i++)
    {
        row[i].resize(m_Actors);
        setItem(i, i, 1);
    }
}


// makes this matrix the zero matrix of size Actors
void Matrix::zeroMatrix(int Actors)
{
    qDebug() << "Matrix:: zeroMatrix() of size " << Actors;
    clear();
    row = new (nothrow) Row [m_Actors=Actors];
    Q_CHECK_PTR(row);
    qDebug() << "Matrix::zeroMatrix - resizing each row";

    for (int i = 0; i < m_Actors; i++)
    {
        row[i].resize(m_Actors);
        setItem(i,i, 0);
    }

}

// returns the (r,c) matrix element
float Matrix::item(int r, int c)
{
    return row[r].column(c);
}

// sets the (r,c) matrix element calling the setColumn method
void Matrix::setItem(int r, int c, float elem )
{
    row [r].setColumn(c, elem);
}

// clears the (r,c) matrix element
void Matrix::clearItem(int r, int c)
{
    row[r].clearColumn(c); 
}


//returns the number of edges starting from r
int Matrix::edgesFrom(int r)
{
    qDebug() << "Matrix: edgesFrom() " << r << " = "<< row[r].outEdges();
    return row[r].outEdges();
}


int Matrix::edgesTo(int t)
{
    int m_inEdges=0;
    for (register int i = 0; i < rows(); ++i)
    {
        if (item(i, t) != 0)
        {
            m_inEdges++;
        }
    }
    qDebug() << "Matrix: edgesTo() " << t << " = " << m_inEdges;
    return m_inEdges;
}

int Matrix::totalEdges()
{
    int m_totalEdges = 0;

    for (register int r = 0; r < rows(); ++r)
    {
        m_totalEdges+=edgesFrom(r);
    }

    qDebug() << "Matrix: totalEdges " << m_totalEdges;

    return m_totalEdges;
}


bool Matrix::printMatrixConsole()
{
    qDebug() << "Matrix: printMatrixConsole";

    for (register int r = 0; r < rows(); ++r)
    {
        for (register int c = 0; c < cols(); ++c)
        {
            QTextStream(stdout) << item(r, c) << ' ';
        }

        QTextStream(stdout) <<'\n';
    }

    return true;
}



void Matrix::deleteRowColumn(int erased)
{
    qDebug() << "Matrix: deleteRowColumn() : "<< erased;
    qDebug() << "Matrix: mActors before " <<  m_Actors;

    --m_Actors;
    qDebug() << "Matrix: mActors now " << m_Actors << ". Resizing...";
    for (register int i = 0; i < m_Actors+1; i++)
    {
        for (register int j = 0; j < m_Actors + 1; j++)
        {
            qDebug() << "Matrix: (" <<  i << ", " << j << ")="<< item(i, j) ;

            if (j == erased && item(i, erased))
            {
                clearItem(i,j);
                qDebug() << i << "  connected to " << erased << ". Clearing...";
            }

            if (i < erased && j < erased)
            {
                qDebug() << "i, j < erased. Skipping. Item remains";
            }

            if (i < erased && j >= erased)
            {
                setItem(i, j, item(i,j+1));
                qDebug() << "case 2";
            }

            if (i >= erased && j < erased)
            {
                setItem(i, j, item(i+1,j));
                qDebug() << "case 3";
            }

            if (i >= erased && j >= erased)
            {
                setItem(i, j, item(i+1,j+1));
                qDebug() << "case 4";
            }

            if (i >= m_Actors || j >= m_Actors)
            {
                setItem(i, j, 0);
                qDebug() << "case 5 (border)";
            }

            qDebug() << "Matrix: new value (" <<  i << ", " << j << ")=" << item(i, j) ;
        }
    }

    for (register int i = 0; i < m_Actors; i++)
    {
        row[i].updateOutEdges();
    }
}


/**
 * @brief Matrix::fillMatrix
 * fills a matrix with a given value
 * @param value
 */
void Matrix::fillMatrix(float value)
{
    for (int i = 0; i < m_Actors; i++)
    {
        for (int j = 0; j < m_Actors; j++)
        {
            setItem(i, j, value);
        }
    }
}

// takes two matrices of the same size and returns their product as a reference to the calling object
// Beware: do not use it as B.product(A,B) because it will destroy B on the way.
Matrix& Matrix::product(Matrix &a, Matrix & b, bool symmetry)
{
    qDebug()<< "Matrix::product()";
    for (register int i = 0; i < rows(); i++)
    {
        for (register int j = 0; j < cols(); j++)
        {
            setItem(i, j, 0);
            for (register int k = 0; k < m_Actors; k++)
            {
                qDebug() << "Matrix::product() - a(" << i + 1 << "," << k + 1 << ")="
                    << a.item(i, k) << "* b(" << k + 1 << "," << j + 1 << ")="
                    << b.item(k, j) << " gives " << a.item(i, k)*b.item(k, j);
                if (k > j && symmetry)
                {
                    if (a.item(i, k) != 0 && b.item(j, k) != 0)
                        setItem(i, j, item(i, j) + a.item(i, k)*b.item(j, k));
                }
                else
                {
                    setItem(i, j, item(i, j) + a.item(i, k)*b.item(k, j));
                }
            }
            qDebug() << "Matrix::product() - (" << i + 1 << "," << j + 1 << ") = "
                << item(i, j);
        }
    }

    return *this;
}

//takes two (AXA) matrices (symmetric) and outputs an upper triangular matrix
Matrix& Matrix::productSym(Matrix &a, Matrix & b)
{
    for (register int i = 0; i < m_Actors; i++)
        for (register int j = 0; j < m_Actors; j++)
        {
            setItem(i, j, 0);
            if (i >= j)
            {
                continue;
            }

            for (register int k = 0; k < m_Actors; k++)
            {
                if (k > j)
                {
                    if (a.item(i, k) != 0 && b.item(j, k) != 0)
                    {
                        setItem(i, j, item(i, j) + a.item(i, k)*b.item(j, k));
                    }
                }
                else  //k <= j  && i<j
                {
                    if (i > k)
                    {
                        if (a.item(k, i) != 0 && b.item(k, j) != 0)
                        {
                            setItem(i, j, item(i, j) + a.item(k, i)*b.item(k, j));
                        }
                    }
                    else
                    {
                        if (a.item(i, k) != 0 && b.item(k, j) != 0)
                        {
                            setItem(i, j, item(i, j) + a.item(i, k)*b.item(k, j));
                        }
                    }
                }
            }
        }

    return *this;
}

Matrix& Matrix::pow(int power, bool symmetry)
{
    Matrix t = *this;

    for (register int k = 1; k < power; k++)
    {
        product(*this, t, symmetry);
    }

    return *this;
}


//takes two (nxn) matrices and returns their product as a reference to this
Matrix& Matrix::sum( Matrix &a, Matrix & b)
{
    for (register int i = 0; i < rows(); i++)
    {
        for (register int j = 0; j < cols(); j++)
        {
            setItem(i, j, a.item(i, j)*b.item(i, j));
        }
    }

    return *this;
}



Matrix& Matrix::subtractFromI()
{
    for (register int i=0;i< rows();i++)
    {
        for (register int j = 0; j < cols(); j++)
        {
            if (i == j)
            {
                setItem(i, j, 1.0 - item(i, j));
            }
            else
            {
                setItem(i, j, item(i, j));
            }
        }
    }

    return *this;
}


/* Swaps row A with row B of this matrix */
void Matrix::swapRows(int rowA,int rowB)
{
    qDebug() << "   swapRow() " << rowA + 1 << " with " << rowB + 1;
    float *tempRow = new (nothrow) float[rows()];
    Q_CHECK_PTR(tempRow);

    for (register int j = 0; j < rows(); j++)
    {
        tempRow[j] = item(rowB, j);
        setItem(rowB, j, item(rowA, j));
        setItem(rowA, j, tempRow[j]);
    }

    delete[] tempRow;
}




/* Multiply every element of row A by value */
void Matrix::multiplyRow(int row, float value)
{
    qDebug()<<"   multiplyRow() "<< row+1 << " by value " << value;
    for (register int j = 0; j < rows(); j++)
    {
        setItem(row, j, value * item(row, j));
        qDebug() << "   item(" << row+1 << "," << j+1 << ") = " <<  item(row,j);
    }
}





/**
 * @brief Matrix::inverseByGaussJordanElimination
 * Inverts given matrix A by Gauss Jordan elimination
   Input:  matrix A
   Output: matrix A becomes unit matrix
   *this becomes the invert of A and is returned back.
 * @param A
 * @return inverse matrix of A
 */
Matrix& Matrix::inverseByGaussJordanElimination(Matrix &A)
{
    qDebug() << "Matrix::inverseByGaussJordanElimination()";
    int n = A.cols();
    qDebug() << "Matrix::inverseByGaussJordanElimination() - starting with the identity Matrix; this will become A^-1 in the end";
    identityMatrix(n);
    int l = 0, m_pivotLine = 0;
    float m_pivot = 0, temp_pivot = 0, elim_coef = 0;

    for (register int j = 0; j < n; j++)
    {
        // for n, it is the last diagonal element of A
        l = j + 1;
        m_pivotLine = -1;
        m_pivot = A.item(j, j);
        qDebug() << "inverseByGaussJordanElimination() at column " << j + 1
            << " Initial pivot " << m_pivot;
        for (register int i = l; i<n; i++)
        {
            temp_pivot = A.item(i, j);
            if (qFabs(temp_pivot) > qFabs(m_pivot))
            {
                qDebug() << " A(" << i + 1 << "," << j + 1 << ") = " << temp_pivot
                    << " absolutely larger than current pivot " << m_pivot
                    << ". Marking new pivot line: " << i + 1;
                m_pivotLine = i;
                m_pivot = temp_pivot;
            }
        }

        if (m_pivotLine != -1)
        {
            A.swapRows(m_pivotLine, j);
            swapRows(m_pivotLine, j);
        }


        qDebug() << "   multiplyRow() " << j + 1 << " by value " << 1 / m_pivot;
        for (register int k = 0; k < rows(); k++)
        {
            A.setItem(j, k, (1 / m_pivot) * A.item(j, k));
            setItem(j, k, (1 / m_pivot) * item(j, k));
            qDebug() << "   A.item(" << j + 1 << "," << k + 1 << ") = " << A.item(j, k);
            qDebug() << "   item(" << j + 1 << "," << k + 1 << ") = " << item(j, k);
        }

        qDebug() << "eliminate variables FromRowsBelow()" << j + 1;
        for (register int i = 0; i < rows(); i++)
        {
            qDebug() << "   Eliminating item(" << i + 1 << "," << j + 1 << ") = "
                << A.item(i, j) << " while at column j=" << j + 1;
            if (A.item(i, j) == 0)
            {
                qDebug() << " ...already eliminated - continue";
                continue;
            }

            if (i == j)
            {
                qDebug() << " ...skip pivotline - continue";
                continue;
            }

            elim_coef = A.item(i, j);

            for (register int k = 0; k < cols(); k++)
            {
                qDebug() << "   A.item(" << i + 1 << "," << k + 1 << ") = " << A.item(i, k)
                    << " will be subtracted by " << " A.item (" << i + 1
                    << ", " << j + 1 << ") x A.item(" << j + 1 << "," << k + 1
                    << ") =" << elim_coef * A.item(j, k);
                A.setItem(i, k, A.item(i, k) - elim_coef * A.item(j, k));
                qDebug() << "   A.item(" << i + 1 << "," << k + 1 << ") = " << A.item(i, k);

                qDebug() << "   item(" << i + 1 << "," << k + 1 << ") = " << item(i, k)
                    << " will be subtracted by " << " A.item (" << i + 1
                    << ", " << j + 1 << ") x item(" << j + 1 << "," << k + 1
                    << ") =" << elim_coef * item(j, k) << " = "
                    << elim_coef << " x " << item(j, k);

                setItem(i, k, item(i, k) - elim_coef * item(j, k));
                qDebug() << "   item(" << i + 1 << "," << k + 1 << ") = " << item(i, k);

            }
        }
    }

    return *this;
}
