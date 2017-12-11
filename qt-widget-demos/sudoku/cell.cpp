#include "cell.h"

#include <QMessageBox>

Cell::Cell()
{
    setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    setTextColor(DEFAULT);
    setDirty(false);
}

Cell* Cell::clone() const
{
    return new Cell(*this);
}

QVariant Cell::data(int role) const
{
    QVariant value = QTableWidgetItem::data(role);

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        bool ok = false;
        int num = value.toInt(&ok);

        if (ok && num == 0)
        {
            return QVariant("");
        }
        else
        {
            return value;
        }
    }

    return value;
}

void Cell::setData(int role, const QVariant &value)
{
    if (role == Qt::EditRole)
    {
        setDirty(true);
        bool ok = false;
        int num = value.toInt(&ok);

        if (!ok)
        {
            return QTableWidgetItem::setData(role, 0);
        }
        else if (num > 9 || num < 0)    //ok
        {
            return QTableWidgetItem::setData(role, 0);
        }
        else
        {
            return QTableWidgetItem::setData(role, value);
        }
    }

    return QTableWidgetItem::setData(role, value);
}

bool Cell::editEnabled() const
{
    Qt::ItemFlags f = flags();
    return f & Qt::ItemIsEditable;
}

void Cell::setEditEnabled(bool flag)
{
    if (editEnabled() == flag)
    {
        return;
    }

    if (flag)
    {
        setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
    }
    else
    {
        setFlags(Qt::ItemFlag(~Qt::ItemIsEditable));
    }
}

bool Cell::dirty() const
{
    return dataIsDirty;
}

void Cell::setDirty(bool flag)
{
    dataIsDirty = flag;
}

void Cell::setTextColor(TextColor color)
{
    bool temp = editEnabled();
    setEditEnabled(true);
    QFont font;
    font.setPixelSize(22);

    if (color == DEFAULT)
    {
        font.setBold(true);
        setForeground(Qt::black);
    }
    else if (color == RIGHT)
    {
        font.setBold(false);
        setForeground(QColor(48, 175, 207));
    }
    else if (color == WRONG)
    {
        font.setBold(true);
        setForeground(QColor(234, 43, 21));
    }
    else
    {
        QMessageBox::critical(0, QObject::tr("error"), QObject::tr("in Cell::setTextColor"));
    }

    setFont(font);
    setEditEnabled(temp);
}

void Cell::setBackgroundColor(BackgroundColor color)
{
    bool temp = editEnabled();
    setEditEnabled(true);

    if (color == WHITE)
    {
        setBackground(QColor(255, 255, 255));
    }
    else if (color == GREY)
    {
        setBackground(QColor(235, 235, 235));
    }
    else
    {
        setBackground(QColor(217, 179, 255));
    }

    setEditEnabled(temp);
}
