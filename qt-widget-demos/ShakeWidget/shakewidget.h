#ifndef SHAKEWIDGET_H
#define SHAKEWIDGET_H

#include <QWidget>

namespace Ui {
class ShakeWidget;
}

class ShakeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShakeWidget(QWidget *parent = 0);
    ~ShakeWidget();

private slots:
    void slot_btnTestclicked();
    void slot_timerOut();

private:
    QTimer* m_timer;
    int m_nPosition;
    QPoint m_curPos;

private:
    Ui::ShakeWidget *ui;
};

#endif // SHAKEWIDGET_H
