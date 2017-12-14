#ifndef COORDINATESETTER_H
#define COORDINATESETTER_H

#include <QDialog>

namespace Ui {
class CoordinateSetter;
}

class QTableWidget;
class QDialogButtonBox;

class CoordinateSetter : public QDialog
{
    Q_OBJECT

public:
    explicit CoordinateSetter(QList<QPointF> *coords, QWidget *parent = 0);
    ~CoordinateSetter();

    void done(int result);

private:
    Ui::CoordinateSetter *ui;

    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;
    QList<QPointF> *coordinates;

private slots:
    void addRow();
};

#endif // COORDINATESETTER_H
