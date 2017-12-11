#ifndef DROPLABEL
#define DROPLABEL

#include <iostream>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QFrame>
#include <QMimeData>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QList>
#include <QByteArray>
#include "draglabel.h"

class QDragEnterEvent;
class QDragMoveEvent;
class QFrame;


class DropLabel : public QLabel {
    Q_OBJECT

public:
    DropLabel(QWidget *parent);

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

signals:
    void labelMatched();
};

#endif // DROPLABEL

