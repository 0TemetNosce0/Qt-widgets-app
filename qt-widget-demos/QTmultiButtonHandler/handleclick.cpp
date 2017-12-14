#include "handleclick.h"
#include <QMessageBox>

handleClick::handleClick(QObject *parent)
    : QObject(parent)
{

}

void handleClick::whichPress(const QString &ss)
{
    QMessageBox *m = new QMessageBox;
    m->setText(ss);
    m->show();
}

