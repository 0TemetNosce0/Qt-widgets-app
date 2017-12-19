/*
   Copyright (c) 2008-1015 Alex Zhondin <qtinuum.team@gmail.com>

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

#ifndef QI_PAINTER_STATE_H
#define QI_PAINTER_STATE_H

#include "QiAPI.h"

class QPainter;
class QWidget;

namespace Qi
{

QI_EXPORT void copyPainterState(const QPainter* painterSource, QPainter* painterDest);
QI_EXPORT void copyPainterState(const QWidget* widgetSource, QPainter* painterDest);

} // end namespace Qi

#endif // QI_PAINTER_STATE_H