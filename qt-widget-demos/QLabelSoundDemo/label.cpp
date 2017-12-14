#include "label.h"

#include <QEvent>
#include <QSound>
#include <QMouseEvent>

Label::Label(const QString& text, QWidget *parent) 
	: QLabel(parent)
{
	this->setText(text);
}

Label::~Label()
{

}

void Label::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
        QSound::play(":/Resource/4.wav");
	}
	QLabel::mousePressEvent(event);
}

void Label::enterEvent(QEvent * event)
{
    QSound::play(":/Resource/3.wav");

	QLabel::enterEvent(event);
}
