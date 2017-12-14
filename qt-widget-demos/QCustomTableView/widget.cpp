#include "widget.h"

Widget::Widget(QWidget *parent)
    : QTableView(parent)
{
    // ����ı���ɫ
    QPalette pal;
    pal.setColor(QPalette::Base, QColor(255, 0, 0));
    pal.setColor(QPalette::AlternateBase, QColor(255, 62, 255));
    setPalette(pal);
    setAlternatingRowColors(true);
}

Widget::~Widget()
{

}
