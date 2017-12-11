#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~Dialog();

protected:
    void mousePressEvent(QMouseEvent *mouseEvent);
    void mouseMoveEvent(QMouseEvent *mouseEvent);

private:
    QPoint pPos;
    Ui::Dialog *ui;
    QPushButton* m_pPreButton;
    QPushButton* m_pNextButton;

};

#endif // DIALOG_H
