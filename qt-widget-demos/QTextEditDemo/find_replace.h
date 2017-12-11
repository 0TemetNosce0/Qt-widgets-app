#ifndef FIND_REPLACE_H
#define FIND_REPLACE_H

#include <QDialog>

namespace Ui {
    class Find_Replace;
}

class Find_Replace : public QDialog
{
    Q_OBJECT

public:
    Find_Replace(QWidget *parent = 0);
    ~Find_Replace();

protected:
    void changeEvent(QEvent *e);

private slots:
    void button_Enabed();

public:
    Ui::Find_Replace *ui;
};

#endif // FIND_REPLACE_H
