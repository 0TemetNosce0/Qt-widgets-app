#ifndef TAGVIEWER_H
#define TAGVIEWER_H

#include <QDialog>

namespace Ui {
class TagViewer;
}

class TagViewer : public QDialog
{
    Q_OBJECT

public:
    explicit TagViewer(QList <QString> currentMediaInfo, QPixmap *cover, QWidget *parent = 0);
    ~TagViewer();

private:
    void setupInfos(QPixmap *cover);
    //Attributes
    Ui::TagViewer *ui;
    QList <QString> a_metas;
};

#endif // TAGVIEWER_H
