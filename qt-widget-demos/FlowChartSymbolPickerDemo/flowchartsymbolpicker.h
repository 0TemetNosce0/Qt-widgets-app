#ifndef FLOWCHARTSYMBOLPICKER_H
#define FLOWCHARTSYMBOLPICKER_H

#include <QMap>
#include <QIcon>
#include <QDialog>
#include <QListWidget>
#include <QDialogButtonBox>

class FlowChartSymbolPicker : public QDialog
{
    Q_OBJECT

public:
    FlowChartSymbolPicker(const QMap<int, QString> &symbolMap,
                          QWidget *parent = 0);

    int selectedId() const { return id; }
    void done(int result);

private:
    QIcon iconForSymbol(const QString &symbolName);

    int id;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;
};

#endif
