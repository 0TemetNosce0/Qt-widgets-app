#ifndef MIRRORVIEW_H
#define MIRRORVIEW_H

#include <QWidget>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QTransform>
#include <QMouseEvent>
#include <QTimer>
#include <QList>
#include <QDesktopWidget>
#include "ui_mirrorview.h"
#include "mirroreditem.h"

class MirrorView : public QWidget
{
    Q_OBJECT

public:
    MirrorView(QWidget *parent = 0);
    ~MirrorView();
    void setImageList(QList<int> imageList);
    void loadImage(int index,QPixmap image);
    void removeIndex(int index);

protected:
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent* event);
    void keyPressEvent(QKeyEvent* event);

private slots:
    void moveLeft();                        //Move photos Left
    void moveRight();                       //Move photos Right
    void animate();                         //Animate photos move

signals:
    void hideMe();
    void neededPhoto(int id);

private:
    void makeScene();
    void removeLeft();
    void removeRight();
    Ui::MirrorView_ui ui;
    QList<int> itemIndexList;               //read items;
    QList<MirroredItem*> items;             //photos in scene
    int currentIndex;                       //current scene photo index
    int dIndex;                             //index offset
    int itemW;                              //item width
    int itemH;                              //item height
    int lastX;
    int lastY;
    QTimer* timer;                          //photo animator
};

#endif // MIRRORVIEW_H
