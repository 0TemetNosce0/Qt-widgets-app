#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBasicTimer>      // timer is used to simulate changing signal volume over time
#include "qanimatedtimer.h"
#include "qvumeter.h"

namespace Ui
{
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    // animated timer section
    void onStartClicked();
    void onStopClicked();
    void onPauseClicked();
    void onFadeClicked();
    void onYellowChanged(int); // user changes the yellow threshold
    void onRedChanged(int);    // user changes the red threshold

    // vu meter section
    void onDimVUClicked();
    void onPlayVUClicked();
    void onSelectionChanged(float);

protected:
    void recalcLabels();
    void timerEvent(QTimerEvent *event); // Q_DECL_OVERRIDE;

private:
    Ui::MainWindow *ui;
    bool _timerVisible;
    bool _vuPlaying;
    QBasicTimer _vuClock;
};

#endif // MAINWINDOW_H
