#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include <QDialog>
#include <QTableView> //checked
#include <QFileDialog> //checked
#include <ui_csvexporter.h>

/*! \class CSVExporter
 *  \brief CSVExporter Editor
 *  \author Kund Gordos
 *  \version 4.0
 *  \date     2008
 */

class CSVExporter : public QDialog
{
    Q_OBJECT
public:
    CSVExporter(QTableView *p_tableView,  QWidget *parent=0);
    virtual ~CSVExporter();
    virtual int exec();

private slots:
    virtual void on_savePushButton_clicked();

private:
    Ui_CSVExporter ui;
    QTableView *tableView;
    QAbstractItemModel *model;
};

#endif // CSVEXPORTER_H
