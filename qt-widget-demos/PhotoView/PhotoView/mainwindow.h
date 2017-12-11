#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "toolbar.h"
#include "about.h"
#include "photoinfo.h"
#include "mirrorview.h"
#include "slideshow.h"
#include <QMainWindow>
#include <QPushButton>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SwitchPhoto(int index);
    QFileInfo GetFileInfo();
    QMap<int,QFileInfo> GetAllFileInfo();
    void Zoom();
    void SetToolBarLabel();
    void SwitchLanguage();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void resizeEvent (QResizeEvent *);
    void closeEvent (QCloseEvent *event);

private slots:
    void ZoomIn();
    void ZoomOut();
    void ZoomFit();
    void PhotoNext();
    void PhotoPrev();
    void FullScreen();
    void RotateRight();
    void RotateLeft();
    void FlipH();
    void FlipV();
    void Play();
    void Info();
    void Delete();

    void hideMirrorView();
    void hideSlideShow();
    void photoNeeded(int index);

    void on_actionHomePage_triggered();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionPrint_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionEffect1_triggered();

    void on_actionEffect2_triggered();

    void on_actionSkin1_triggered();

    void on_actionSkin2_triggered();

    void on_actionZH_triggered();

    void on_actionEN_triggered();

    void on_actionSkin3_triggered();

private:
    Ui::MainWindow *ui;
    ToolBar *toolBar;
    QImage image;
    QImage image1;
    QMap<int,QFileInfo> PhotoMap;
    MirrorView* mirrorView;
    SlideShow* slideShow;
    bool windowMaxState;


    bool ZoomFlag;
    bool RotateFlipFlag;

    bool ZoomFactorFlag;
    qreal ZoomFactor;
    bool PhotoExist;
    int PhotoIndex;
};

#endif // MAINWINDOW_H
