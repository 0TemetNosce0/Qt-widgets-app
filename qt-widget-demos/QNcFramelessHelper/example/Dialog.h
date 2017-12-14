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

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QCheckBox;
class NcFramelessHelper;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void onCbFramelessToggled(bool on);
    void onCbWidgetMovableToggled(bool on);
    void onCbWidgetResizableToggled(bool on);
    void onCbUseRubberBandOnMoveToggled(bool on);
    void onCbUseRubberBandOnResizeToggled(bool on);
    void createMainWindow();

private:
    QWidget* mWidget;

    QPushButton* mBtnClose;
    QPushButton* mBtnMainWin;

    QCheckBox* mCbFrameless;
    QCheckBox* mCbWidgetMovable;
    QCheckBox* mCbWidgetResizable;
    QCheckBox* mCbUseRubberBandOnMove;
    QCheckBox* mCbUseRubberBandOnResize;

    NcFramelessHelper* mFh;

};

#endif // DIALOG_H
