#include <QApplication>
#include <QTextEdit>

#include "../src/ScalableWrapper.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTextEdit editor;
	ScalableWrapper w(&editor);
	w.resize(600, 400);
	w.show();

	return a.exec();
}
