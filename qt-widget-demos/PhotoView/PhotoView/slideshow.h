#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include <QWidget>
#include <QMap>
class QFileInfo;


namespace Ui {
class SlideShow;
}

class SlideShow : public QWidget
{
    Q_OBJECT

public:
    explicit SlideShow(QWidget *parent = 0);
    ~SlideShow();

    void ZoomFit();


signals:
    void hideMe();

protected:
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent* event);

private slots:
    void SwitchPhoto();

private:
    Ui::SlideShow *ui;

    QMap<int,QFileInfo> PhotoMap;
    QTimer *timer;
    QImage image;
    int PhotoIndex;
};

#endif // SLIDESHOW_H
