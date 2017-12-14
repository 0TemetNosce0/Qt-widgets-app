#pragma once

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "PeopleDataModel.h"
#include "PeopleTableView.h"

class PeopleDialog : public QDialog
{
    Q_OBJECT

public:
    PeopleDialog(QWidget *parent = 0);

public slots:
    void finished(int result);
    void sectionClicked(int section);
    void customMenuRequested(QPoint pos);
    void deleteCurrentRows();
    void addRow();
    void scrollingEnded();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    QLabel *mTopLabel;
    PeopleTableView *mTableView;
    QVBoxLayout *mVLayout;
    QHBoxLayout *mBottomBtnLayout;
    PeopleDataModel *mDataModel;

private:
    void initHeader();
    void initTable();
    void createLayouts();
    void fillLayouts();
    void initDataSource();
    void connectSignalsToSlots();
    void sortByColumn( int col );
};
