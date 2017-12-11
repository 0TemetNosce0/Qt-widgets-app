#ifndef CDRAGABLECONTAINER_H
#define CDRAGABLECONTAINER_H

#include <QtGlobal>
#if QT_VERSION < 0x050000
#include <QtGui>
#else
#include <QtWidgets>
#endif

namespace Ui {
class CDragableContainer;
}

const static QString gDragableContainerMimeType = "qapplication/dragableContainer";

class CDragableContainer : public QWidget
{
	Q_OBJECT

public:
	explicit CDragableContainer(QWidget *widget);
	~CDragableContainer();

	bool eventFilter(QObject *object, QEvent *event);

	inline QWidget* widget(){ return _widget; }

signals:
	void movingUp();
	void movingDown();

private:
	Ui::CDragableContainer *ui;
	QWidget *_widget;
};

#endif // CDRAGABLECONTAINER_H
