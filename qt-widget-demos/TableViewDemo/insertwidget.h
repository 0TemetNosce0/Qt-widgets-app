#ifndef INSERTWIDGET_H
#define INSERTWIDGET_H

#include <QDialog>

namespace Ui {
class InsertWidget;
}

class InsertWidget : public QDialog
{
    Q_OBJECT

    Q_PROPERTY(int num READ num)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(int id READ id)
    Q_PROPERTY(QString phone READ phone)
    Q_PROPERTY(QString level READ level)
    Q_PROPERTY(QString desc READ desc)

public:
    explicit InsertWidget(QWidget *parent = 0);
    ~InsertWidget();

    int num() const;
    QString name() const;
    int id() const;
    QString phone() const;
    QString level() const;
    QString desc() const;

private:
    Ui::InsertWidget *ui;
};

#endif // INSERTWIDGET_H
