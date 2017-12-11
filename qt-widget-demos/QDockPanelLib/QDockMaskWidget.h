#ifndef QDOCKMASKWIDGET_H
#define QDOCKMASKWIDGET_H

#include <QWidget>
#include "QDockCommon.h"

class QDockMaskWidget : public QWidget
{
    Q_OBJECT

public:
    QDockMaskWidget(QWidget* parent);
    ~QDockMaskWidget();

    void showOnDockArea(DockArea area);
private:

};

#endif // QDOCKMASKWIDGET_H
