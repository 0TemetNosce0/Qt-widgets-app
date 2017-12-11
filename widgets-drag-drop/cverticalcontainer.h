#ifndef CVERTICALCONTAINER_H
#define CVERTICALCONTAINER_H

#include <QtGlobal>
#if QT_VERSION < 0x050000
#include <QtGui>
#else
#include <QtWidgets>
#endif

#include "cdragablecontainer.h"

class CVerticalContainer : public QWidget
{
	Q_OBJECT

public:
	explicit CVerticalContainer(QWidget *parent = 0);

	void appedWidget(QWidget *widget);
	void removeWidget(QWidget *widget);

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);
	void dropEvent(QDropEvent *event);

private slots:
	void movingUp();
	void movingDown();

private:
	QVBoxLayout *_layout;
	QMap<QWidget*, CDragableContainer*> _widgetsMap;
	QFrame _dropLine;
};

#endif // CVERTICALCONTAINER_H
