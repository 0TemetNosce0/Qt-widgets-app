#ifndef ASSUMPTION_PAGE_H
#define ASSUMPTION_PAGE_H

#include <QWidget>
#include "ui_assumptionpage.h"

class AssumptionPage : public QWidget
{
    Q_OBJECT

public:
    AssumptionPage(QWidget *parent = 0);
    ~AssumptionPage();

    void initialize(int educationMonthCount, bool willWorkHard);

    int  educationMonthCount() const;
    bool willWorkHard() const;

private:
    Ui::AssumptionPage ui;
};

#endif // PAGE1_H
