#ifndef SPLITTER_H
#define SPLITTER_H

#include <QMainWindow>

namespace Ui {
class splitter;
}

class splitter : public QMainWindow
{
    Q_OBJECT

public:
    explicit splitter(QWidget *parent = 0);
    ~splitter();

private:
    Ui::splitter *ui;
};

#endif // SPLITTER_H
