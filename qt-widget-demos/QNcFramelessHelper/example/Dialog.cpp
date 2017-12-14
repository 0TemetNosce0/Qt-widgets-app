/*
    NcFramelessHelper, an easy way to support move/resize on
    frameless toplevel windows.
    Copyright (C) 2011  Nishant Parashar
    Email:- nishcode (at) gmail (dot) com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QMdiArea>
#include <QCheckBox>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>

#include "Dialog.h"
#include "NcFramelessHelper.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Frameless Window Helper - 3.0.0");

    mFh = new NcFramelessHelper;

    mCbFrameless = new QCheckBox("Use Frameless Window");
    mCbWidgetMovable = new QCheckBox("Enable Move");
    mCbWidgetResizable = new QCheckBox("Enable Resize");
    mCbUseRubberBandOnMove = new QCheckBox("Use RubberBand on Move");
    mCbUseRubberBandOnResize = new QCheckBox("Use RubberBand on Resize");

    mBtnClose = new QPushButton("Close");
    mBtnMainWin = new QPushButton("MainWindow");

    QHBoxLayout* hl = new QHBoxLayout;
    hl->addWidget(mBtnMainWin);
    hl->addStretch();
    hl->addWidget(mBtnClose);

    QVBoxLayout* vl = new QVBoxLayout;
    vl->addWidget(mCbFrameless);
    vl->addWidget(mCbWidgetMovable);
    vl->addWidget(mCbWidgetResizable);
    vl->addWidget(mCbUseRubberBandOnMove);
    vl->addWidget(mCbUseRubberBandOnResize);
    vl->addStretch();
    vl->addLayout(hl);

    this->setLayout(vl);

    createMainWindow();

    connect(mBtnMainWin, SIGNAL(clicked()), mWidget, SLOT(show()));
    connect(mBtnClose, SIGNAL(clicked()), qApp, SLOT(closeAllWindows()));
    connect(mCbFrameless, SIGNAL(toggled(bool)), this, SLOT(onCbFramelessToggled(bool)));
    connect(mCbWidgetMovable, SIGNAL(toggled(bool)), this, SLOT(onCbWidgetMovableToggled(bool)));
    connect(mCbWidgetResizable, SIGNAL(toggled(bool)), this, SLOT(onCbWidgetResizableToggled(bool)));
    connect(mCbUseRubberBandOnMove, SIGNAL(toggled(bool)), this, SLOT(onCbUseRubberBandOnMoveToggled(bool)));
    connect(mCbUseRubberBandOnResize, SIGNAL(toggled(bool)), this, SLOT(onCbUseRubberBandOnResizeToggled(bool)));

    mCbFrameless->setChecked(true);//triggers the slot
}

Dialog::~Dialog()
{
    delete mFh;
}

void Dialog::onCbFramelessToggled(bool on)
{
    if (on)
    {
        mCbWidgetMovable->setEnabled(true);
        mCbWidgetResizable->setEnabled(true);
        mCbUseRubberBandOnMove->setEnabled(true);
        mCbUseRubberBandOnResize->setEnabled(true);
        mFh->activateOn(this);
        mFh->activateOn(mWidget);
    }
    else
    {
        mCbWidgetMovable->setEnabled(false);
        mCbWidgetResizable->setEnabled(false);
        mCbUseRubberBandOnMove->setEnabled(false);
        mCbUseRubberBandOnResize->setEnabled(false);
        mFh->removeFrom(this);
        mFh->removeFrom(mWidget);
    }

    mCbWidgetMovable->setChecked(mFh->isWidgetMovable());
    mCbWidgetResizable->setChecked(mFh->isWidgetResizable());
    mCbUseRubberBandOnMove->setChecked(mFh->isUsingRubberBandOnMove());
    mCbUseRubberBandOnResize->setChecked(mFh->isUsingRubberBandOnResisze());

}

void Dialog::onCbWidgetMovableToggled(bool on)
{
    mFh->setWidgetMovable(on);
}

void Dialog::onCbWidgetResizableToggled(bool on)
{
    mFh->setWidgetResizable(on);
}

void Dialog::onCbUseRubberBandOnMoveToggled(bool on)
{
    mFh->useRubberBandOnMove(on);
}

void Dialog::onCbUseRubberBandOnResizeToggled(bool on)
{
    mFh->useRubberBandOnResize(on);
}

void Dialog::createMainWindow()
{
    QPushButton* btn = new QPushButton("This is a MainWindow\nwith mdi area and subwindow\n(Close)");

    //On mainwindows with mdiarea or
    //any widget which takes the layout
    //margins as 0, the frameless helper
    //will not be able to detect corners.
    //To workaround this, either change the
    //mainwindow layout's margin or put the mainwindow
    //inside a QWidget with margins.
    QMainWindow* mw = new QMainWindow;
    QMdiArea* area = new QMdiArea;
    area->addSubWindow(btn);
    mw->setCentralWidget(area);

    //This dosent seem to work!
    //mw.layout()->setMargin(fh2.borderWidth());

    //so we will use a QWidget
    mWidget = new QWidget;
    QVBoxLayout* vl = new QVBoxLayout;
    vl->addWidget(mw);
    mWidget->setLayout(vl);

    connect(btn, SIGNAL(clicked()), mWidget, SLOT(close()));

    //mWidget->setAttribute(Qt::WA_DeleteOnClose);
    //mWidget->show();

}
