#ifndef PAGE1_H
#define PAGE1_H

#include <QWidget>
#include "ui_page.h"

class Page : public QWidget
{
    Q_OBJECT

public:
    Page(QWidget *parent = 0);
    ~Page();

    void initialize(int value);
    int returnTimeEducationSpinBoxValue() const;
    bool returnFlagHowToWork () const;

private:
    Ui::Page ui;
};

#endif // PAGE1_H
