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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(
        #ifdef Q_OS_MAC
            Qt::SubWindow |
        #else
            Qt::Tool |
        #endif
            Qt::WindowSystemMenuHint |
            Qt::WindowStaysOnTopHint
        );
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    CollapsibleFrame* cf = new CollapsibleFrame(this, "Test");
    CollapsibleFrame* cf2 = new CollapsibleFrame(cf, "Test2");
    CollapsibleFrame* cf3 = new CollapsibleFrame(this, "Test3");
    cf->addWidget(cf2);
    layout->addWidget(cf);
    layout->addWidget(cf3);
    this->setLayout(layout);
}

MainWindow::~MainWindow()
{

}
