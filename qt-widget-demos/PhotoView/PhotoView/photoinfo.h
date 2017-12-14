#ifndef PHOTOINFO_H
#define PHOTOINFO_H

#include <QDialog>

namespace Ui {
class PhotoInfo;
}

class PhotoInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PhotoInfo(QWidget *parent = 0);
    ~PhotoInfo();

protected:
    void showEvent(QShowEvent *);

private slots:

    void on_OK_clicked();

private:
    Ui::PhotoInfo *ui;
};

#endif // PHOTOINFO_H
