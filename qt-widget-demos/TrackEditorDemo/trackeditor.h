#ifndef TRACKEDITOR_H
#define TRACKEDITOR_H

#include <QDialog>

#include "track.h"

QT_BEGIN_NAMESPACE
class QTableView;
class TrackModel;
class QAbstractTableModel;
QT_END_NAMESPACE

namespace Ui {
class TrackEditor;
}

/**
  @brief 用于组装显示的控件类。
*/
class TrackEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TrackEditor(QList<Track>* tracks, QWidget *parent = 0);
    ~TrackEditor();

private:
    Ui::TrackEditor *ui;
    QTableView* tableView;
    TrackModel* model;
    //QAbstractTableModel* model;
};

#endif // TRACKEDITOR_H
