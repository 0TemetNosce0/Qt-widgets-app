/*
   Copyright 2012 Cameron Tinker

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "extendedqlabel.h"

ExtendedQLabel::ExtendedQLabel(const QString& text, QWidget * parent)
    : QLabel(parent)

{
    this->setText(text);
}

ExtendedQLabel::~ExtendedQLabel()
{

}

void ExtendedQLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit clicked();
}

void ExtendedQLabel::mouseMoveEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit hover();
}
