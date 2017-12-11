#ifndef SOMEPAGE_H
#define SOMEPAGE_H

#include <QWidget>
#include "ui_somepage.h"

class SomePage : public QWidget
{
    Q_OBJECT

public:
    SomePage(QWidget *parent = 0);
    ~SomePage();

    void initialize(int someData);

    int someData() const;

private:
    Ui::SomePage ui;
};

#endif // SOMEPAGE_H
