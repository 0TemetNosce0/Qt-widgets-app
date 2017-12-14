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

#include "FunctionListDialog.h"

FunctionListDialog::FunctionListDialog(QWidget *parent)
   : QDialog(parent)
{
   setupUi(this);
   textEdit -> setHtml(
      "<p><b>AVERAGE(value,...)</b><br>This function calculates the average of the given values. Each value can be a floating point or a range (e.g. A1:B1).</p>"
      "<p><b>COLUMN()</b><br>This function returns the column of the cell.</p>"
      "<p><b>COS(value)</b><br>This function returns the cosine of the given value in degrees.</p>"
      "<p><b>COT(value)</b><br>This function returns the cotangent of the given value in degrees.</p>"
      "<p><b>FABS(value)</b><br>This function returns the absolute value of the given floating-point.</p>"
      "<p><b>LOG(value)</b><br>This function returns the natural logarithm of the give value.</p>"
      "<p><b>LOG10(value)</b><br>This function returns the base-10 logarithm of the given value.</p>"
      "<p><b>MAX(value,...)</b><br>This function returns the largest value. Each value can be a floating point or a range (e.g. A1:B1).</p>"
      "<p><b>MEDIAN(value,...)</b><br>This function calculates the median of the given values. Each value can be a floating point or a range (e.g. A1:B1).</p>"
      "<p><b>MIN(value,...)</b><br>This function returns the smallest value. Each value can be a floating point or a range (e.g. A1:B1).</p>"
      "<p><b>MODE(value,...)</b><br>This function calculates the mode of the given values. Each value can be a floating point or a range (e.g. A1:B1).</p>"
      "<p><b>PI()</b><br>This function returns the value of PI.</p>"
      "<p><b>POW(value1, value2)</b><br>This function returns the value of value1 raised to the power of value2.</p>"
      "<p><b>PRODUCT(value,...)</b><br>This function calculates the product of the given values. Each value can be a floating point or a range (e.g. A1:B1).</p>"
      "<p><b>ROW()</b><br>This function returns the row of the cell.</p>"
      "<p><b>SIN(value)</b><br>This function returns the sine of the given value in degrees.</p>"
      "<p><b>SQRT(value)</b><br>This function returns the square root of the given value. If the value is negative, \"nan\" is returned.</p>"
      "<p><b>SUM(value1,...)</b><br>This function calculates the sum of the given values. Each value can be a floating point or a range (e.g. A1:B1).</p>"
      "<p><b>TAN(value)</b><br>This function returns the tangent of the given value in degrees.</p>"
                      );
}


