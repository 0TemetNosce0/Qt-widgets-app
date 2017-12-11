#ifndef WIZARDSAMPLE_H
#define WIZARDSAMPLE_H

#include <QMainWindow>
#include "ui_wizardsample.h"

class WizardSample : public QMainWindow
{
    Q_OBJECT

public:
    enum Direction
    {
        Forward,
        Backward
    };

    WizardSample(QWidget *parent = 0);
    ~WizardSample();

private:
    Ui::WizardSampleClass ui;

    void changePage(QWidget *page, Direction direction);

signals:
    void currentPageChanged(QWidget *, Direction);

private slots:
    void forward();
    void back();

    void initializePage(QWidget *page, Direction direction);
};

#endif // WIZARDSAMPLE_H
