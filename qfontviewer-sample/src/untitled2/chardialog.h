#ifndef CHARDIALOG_H
#define CHARDIALOG_H

#include "ui_chardialog.h"
#include <QWidget>
#include <QDialog>
#include <QMap>

typedef QMap<QChar::Category, QString> CategoryString;

class CharDialog : public QDialog, Ui::CharDialog
{
    QChar ch;

public:
    CharDialog(QChar ch = QChar(), const QString & fontFamily = QString(),
               const CategoryString & categories = CategoryString(),
               QWidget *parent = 0);
    ~CharDialog();
};

#endif
