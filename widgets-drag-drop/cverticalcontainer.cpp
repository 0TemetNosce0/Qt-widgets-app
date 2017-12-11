#include "cverticalcontainer.h"

CVerticalContainer::CVerticalContainer(QWidget *parent) :
	QWidget(parent),
	_layout(new QVBoxLayout)
{
	setLayout(_layout);
	setAcceptDrops(true);
	_dropLine.setFrameShape(QFrame::HLine);
}

void CVerticalContainer::appedWidget(QWidget *widget)
{
	CDragableContainer *container = new CDragableContainer(widget);
	connect(container, SIGNAL(movingUp()), this, SLOT(movingUp()));
	connect(container, SIGNAL(movingDown()), this, SLOT(movingDown()));
	_widgetsMap.insert(widget, container);
	_layout->addWidget(container);
}

void CVerticalContainer::removeWidget(QWidget *widget)
{
	if(_widgetsMap.contains(widget) == false)
	{
		qWarning() << "CVerticalContainer: can not find widget " << widget;
		return;
	}

	CDragableContainer *container = _widgetsMap.take(widget);
	_layout->removeWidget(container);
	delete container;
}

void CVerticalContainer::dragEnterEvent(QDragEnterEvent *event)
{
	QWidget::dragEnterEvent(event);

	if(event->mimeData()->hasFormat(gDragableContainerMimeType))
		event->accept();
}

void CVerticalContainer::dragMoveEvent(QDragMoveEvent *event)
{
	QWidget::dragMoveEvent(event);

	const int currentLineIndex = _layout->indexOf(&_dropLine);

	QWidget *child = childAt(event->pos());
	while(child && _layout->indexOf(child) == -1)
		child = child->parentWidget();

	if(child)
	{
		int newLineIndex = _layout->indexOf(child);
		if(event->pos().y() > child->pos().y() + (child->height() / 2))
			newLineIndex++;

		if(currentLineIndex != -1
				&& currentLineIndex < newLineIndex)
			newLineIndex--;

		if(newLineIndex != currentLineIndex)
		{
			if(currentLineIndex != -1)
				_layout->removeWidget(&_dropLine);

			_layout->insertWidget(newLineIndex, &_dropLine);
			_dropLine.show();
		}
	}
	event->accept();
}

void CVerticalContainer::dragLeaveEvent(QDragLeaveEvent *event)
{
	QWidget::dragLeaveEvent(event);

	if(QRect(QPoint(), size()).contains(mapFromGlobal(QCursor::pos()), false) == false)	//fix from wrong leave event.
	{
		_layout->removeWidget(&_dropLine);
		_dropLine.hide();
		event->accept();
	}
}

void CVerticalContainer::dropEvent(QDropEvent *event)
{
	QWidget::dropEvent(event);

	const QByteArray data = event->mimeData()->data(gDragableContainerMimeType);
	CDragableContainer *dragingWidget = (CDragableContainer*)data.toULongLong();
	const int dragingIndex = _layout->indexOf(dragingWidget);
	int newIndex = _layout->indexOf(&_dropLine);
	if(dragingIndex != -1 && dragingIndex != newIndex)
	{
		if(dragingIndex < newIndex)
			newIndex--;
		_layout->removeWidget(dragingWidget);
		_layout->insertWidget(newIndex, dragingWidget);
	}

	_layout->removeWidget(&_dropLine);
	_dropLine.hide();
	event->acceptProposedAction();
	event->accept();
}

void CVerticalContainer::movingUp()
{
	CDragableContainer *container = static_cast<CDragableContainer*>( QObject::sender() );
	const int index = _layout->indexOf(container);
	if(index < 1)
		QApplication::beep();
	else
	{
		_layout->removeWidget(container);
		_layout->insertWidget(index - 1, container);
	}
}

void CVerticalContainer::movingDown()
{
	CDragableContainer *container = static_cast<CDragableContainer*>( QObject::sender() );
	const int index = _layout->indexOf(container);
	if(index < 0 || index >= _layout->count() - 1)
		QApplication::beep();
	else
	{
		_layout->removeWidget(container);
		_layout->insertWidget(index + 1, container);
	}
}
