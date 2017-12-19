#include <QDebug>
#include <QPainter>

#include <QImage>
#include <QFileDialog>

#include <ctime>

#include "filter.h"

const long _RADIUS = 100;

#define CHECK_TIME(text, ...) \
{ \
    clock_t t1 = std::clock(); \
    { __VA_ARGS__; } \
    clock_t t2 = std::clock(); \
    qDebug() << #__VA_ARGS__ << text << "->" << (long)((double)(t2 - t1) / (double)(CLOCKS_PER_SEC) * 1000.0); \
}

//////////////////////////////////////////////////////////////////////////

#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
	loadImage("ground.bmp");
}

Widget::~Widget() {}

QImage _image[2];

void Widget::loadImage(const QString& path)
{
	_image[0].load(path);
	
	_image[1] = GaussFilter(_image[0], _RADIUS);
//	if (_image[0].isNull())
//	{
//		return;
//	}
//
//	_image[1] = _image[0].convertToFormat(QImage::Format_RGB888);
//
//	static filter::pair_t pair[] =
//	{
//		{ filter::Gauss, filter::Blur1D },
//		{ filter::Gauss, filter::Blur2D }
//	};
//	filter::bitmap_t bmp;
//	bmp.set((filter::bitmap_t::pixel_t*)_image[1].bits(),
//		_image[1].width(), _image[1].height());
////	filter::Filter(pair[1 - 1], bmp, _RADIUS);
//	CHECK_TIME(1, filter::Filter(pair[1 - 1], bmp, _RADIUS))

	resize(_image[0].width() * 2, _image[0].height());
}

void Widget::paintEvent(QPaintEvent *)
{
	if (_image[0].isNull())
	{
		return;
	}

	QPainter painter(this);

	for (int i = 0, w = 0; i < 2; w += _image[i].width(), ++i)
		painter.drawImage(w, 0, _image[i]);
}

void Widget::mouseDoubleClickEvent(QMouseEvent *)
{
	QString filename = QFileDialog::getOpenFileName(
		this, "Open Image", QDir::currentPath(), "Image files (*.bmp *.jpg *.png);;All files(*.*)");

	if (!filename.isNull())
	{
		loadImage(filename);
	}
}
