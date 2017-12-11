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

#include "collapsibleframe.h"

CollapsibleFrame::CollapsibleFrame(QObject *parent, QString headerText)
{
    m_headerText = headerText;
    m_parent = parent;
    m_frameState = CLOSED;

    m_headerArea = new QWidget;
    m_widgetArea = new QWidget;
    m_headerArea->setMaximumHeight(20);
    m_widgetArea->setMaximumHeight(1000);
    this->setMaximumHeight(1000);
    this->setMinimumHeight(20);

    this->setStyleSheet("QWidget { border: 1px solid #000000; }");

    icon = new ExtendedQLabel;
    icon->setMaximumSize(15, 15);
    icon->setPixmap(m_collapseIcon);
    connect(icon, SIGNAL(clicked()), this, SLOT(changeState()));

    headerTextLabel = new QLabel;
    headerTextLabel->setText(m_headerText);

    ExtendedQLabel* test = new ExtendedQLabel;
    test->setText("Testing");
    test->setMaximumSize(50,20);

    widgetLayout = new QVBoxLayout;
    widgetLayout->setMargin(0);
//    widgetLayout->setSpacing(0);
    m_widgetArea->setLayout(widgetLayout);
//    m_widgetArea->setMaximumHeight(20);
    widgetLayout->addWidget(test); /*, 0, Qt::AlignTop | Qt:: AlignLeft);*/

    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->setMargin(0);
    headerLayout->addWidget(icon); /*, 0, Qt::AlignTop | Qt:: AlignLeft);*/
    headerLayout->addWidget(headerTextLabel); /*, 0, Qt::AlignTop | Qt:: AlignLeft);*/
    m_headerArea->setLayout(headerLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_headerArea);/*, 0, Qt::AlignTop | Qt:: AlignLeft);*/
    mainLayout->addWidget(m_widgetArea);/*, 0, Qt::AlignTop | Qt:: AlignLeft);*/

    setLayout(mainLayout);
    show();
    determineIcon();
}

CollapsibleFrame::~CollapsibleFrame()
{
    delete m_headerArea;
    delete m_widgetArea;
}

void CollapsibleFrame::determineIcon()
{
    if(m_frameState == OPEN)
    {
        icon->setStyleSheet("QLabel { image: url(:/open.png) no-repeat; } QLabel:hover { image: url(:/open_hover.png) no-repeat; }");
        icon->setToolTip("Close");
        m_widgetArea->show();
    }
    else
    {
        icon->setStyleSheet("QLabel { image: url(:/closed.png) no-repeat; } QLabel:hover { image: url(:/closed_hover.png) no-repeat; }");
        icon->setToolTip("Open");
        m_widgetArea->hide();
    }
}

void CollapsibleFrame::changeState()
{
    if(m_frameState == OPEN)
    {
        m_frameState = CLOSED;
        headerTextLabel->setText("Closed");
        m_widgetArea->hide();
    }
    else
    {
        m_frameState = OPEN;
        headerTextLabel->setText("Open");
        m_widgetArea->show();
    }

    determineIcon();
}

void CollapsibleFrame::addWidget(QWidget * widget)
{
    widgetLayout->addWidget(widget);
}

void CollapsibleFrame::addLayout(QLayout *layout)
{
    widgetLayout->addLayout(layout);
}

