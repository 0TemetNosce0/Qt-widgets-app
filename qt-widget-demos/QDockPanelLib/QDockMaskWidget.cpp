#include "QDockMaskWidget.h"

QDockMaskWidget::QDockMaskWidget(QWidget* parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_InputMethodTransparent);
	setAttribute(Qt::WA_TransparentForMouseEvents);

	setPalette(QColor(0, 0, 255, 100));
	setAutoFillBackground(true);
}

QDockMaskWidget::~QDockMaskWidget()
{

}

void QDockMaskWidget::showOnDockArea(DockArea area)
{
	QRect rc = parentWidget()->rect();
	switch (area)
	{
	case LeftArea:
		rc.setWidth(rc.width() * 3 / 10);
		break;
	case CenterLeftArea:
		rc.setWidth(rc.width() / 2);
		break;
	case TopArea:
		rc.setHeight(rc.height() * 3 / 10);
		break;
	case CenterTopArea:
		rc.setHeight(rc.height() / 2);
		break;
	case RightArea:
		rc.setLeft(rc.left() + rc.width() * 7 / 10);
		break;
	case CenterRightArea:
		rc.setLeft(rc.left() + rc.width() / 2);
		break;
	case BottomArea:
		rc.setTop(rc.top() + rc.height() * 7 / 10);
		break;
	case CenterBottomArea:
		rc.setTop(rc.top() + rc.height() / 2);
		break;
	case CenterArea:
		break;
	default:
		hide();
		return;
	}

	move(rc.topLeft());
	resize(rc.size());
	show();
	raise();
}
