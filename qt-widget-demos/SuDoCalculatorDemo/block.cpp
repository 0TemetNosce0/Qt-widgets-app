#include "block.h"

Block::Block(QWidget *parent)
    : QWidget(parent)
{
    nubEidt = new QLineEdit(this);
    nubEidt->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPixelSize(30);

    nubEidt->setFont(font);
    nubEidt->setMinimumSize(50,50);
    nubEidt->setMaximumSize(50,50);
    QRegExp regExp("[1-9]{1}");
    nubEidt->setValidator(new QRegExpValidator(regExp,this));

    connect(nubEidt, SIGNAL(textChanged(QString)), this, SLOT(dataChange(QString)));
    nubEidt->setText("");
    da = -1;
}

int Block::data()
{
    return da;
}

void Block::setValue(int a)
{
    if(a < 1)
    {
        nubEidt->setText("");
        da = -1;
    }
    else
    {
        nubEidt->setText(QString::number(a));
        da = a;
    }

}

void Block::setEna(bool ok)
{
    nubEidt->setEnabled(ok);
}

void Block::dataChange(const QString &data)
{
    if(data.isEmpty())
    {
        da = -1;
    }
    else
    {
        da = data.toInt();
    }
}

void Block::changeColor(const QColor &color)
{
    QPalette pale;
    pale.setColor(QPalette::Text,color);
    nubEidt->setPalette(pale);
}

QPoint Block::getPos()
{
    return p;
}

void Block::setPos(int x, int y)
{
    QPoint point;
    point.setX(x);
    point.setY(y);
    this->p = point;
}

void Block::setPos(const QPoint &p)
{
    this->p = p;
}

