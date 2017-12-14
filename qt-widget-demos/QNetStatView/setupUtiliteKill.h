#ifndef SETUPUTILITEKILL_H
#define SETUPUTILITEKILL_H

#include <QDialog>

namespace Ui {
class setupUtiliteKill;
}

class setupUtiliteKill : public QDialog{
    Q_OBJECT

    public:
        explicit setupUtiliteKill(QWidget *parent = 0);
        ~setupUtiliteKill();

    private:
        Ui::setupUtiliteKill *ui;

    private slots:
        void actionApply();
};

#endif // SETUPUTILITEKILL_H
