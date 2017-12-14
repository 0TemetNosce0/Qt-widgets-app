#ifndef TOOLBAR
#define TOOLBAR

#include <QToolBar>
#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QLabel>
class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = 0);

    QPushButton *ZoomIn;
    QPushButton *ZoomOut;
    QPushButton *ZoomFit;
    QPushButton *FullScreen;
    QPushButton *Prev;
    QPushButton *Next;
    QPushButton *RotateLeft;
    QPushButton *RotateRight;
    QPushButton *Delete;
    QPushButton *Info;
    QPushButton *FlipH;
    QPushButton *FlipV;
    QPushButton *Play;
    QPushButton *Resize;
    QLabel *label;

    void SwitchLanguage();
};


#endif // TOOLBAR

