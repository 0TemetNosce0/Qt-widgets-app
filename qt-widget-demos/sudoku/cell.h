#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
public:
    enum BackgroundColor { WHITE, GREY, EYECOLOR };
    enum TextColor { DEFAULT, RIGHT, WRONG };

    Cell();

    Cell* clone() const;
    QVariant data(int role) const;
    void setData(int role, const QVariant &value);

    bool editEnabled() const;
    void setEditEnabled(bool flag);
    bool dirty() const;
    void setDirty(bool flag);

    void setTextColor(TextColor color);
    void setBackgroundColor(BackgroundColor color);

private:
    bool dataIsDirty;
};

#endif // !CELL_H
