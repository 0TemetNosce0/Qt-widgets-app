#ifndef MEDALWALLWIDGET_H
#define MEDALWALLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>


class MedalWallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MedalWallWidget(QWidget *parent = 0);
    ~MedalWallWidget();

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void translateLanguage();
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);


private:
    bool ismousePress;

    QPushButton* closeButton;
    QPushButton* onekeyGetButton;
    QPushButton* browserButton;

    QLabel* getLabel;
    QLabel* topSafeLabel;
    QLabel* topSdLabel;
    QLabel* ungetLabel;
    QLabel* infoLabel;
    QLabel* clickGetLabel;
    QLabel* tipIconLabel;

    QPoint movePoint;
};

#endif // MEDALWALLWIDGET_H
