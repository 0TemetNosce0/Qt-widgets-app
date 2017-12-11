#include "cdragablecontainer.h"
#include "ui_cdragablecontainer.h"

CDragableContainer::CDragableContainer(QWidget *widget) :
	QWidget(0),
	ui(new Ui::CDragableContainer),
	_widget(widget)
{
	ui->setupUi(this);
	ui->verticalLayout->addWidget(widget);
	ui->wTitle->installEventFilter(this);

	connect(ui->tbnUp, SIGNAL(clicked()), this, SIGNAL(movingUp()));
	connect(ui->tbnDown, SIGNAL(clicked()), this, SIGNAL(movingDown()));
}

CDragableContainer::~CDragableContainer()
{
	delete ui;
}

bool CDragableContainer::eventFilter(QObject *object, QEvent *event)
{
	if(object == ui->wTitle)
	{
		if(event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
			if(mouseEvent->button() == Qt::LeftButton)
			{
				QDrag *drag = new QDrag(this);
				QMimeData *mimeData = new QMimeData;

				const QByteArray data(QString::number((quintptr)this).toLatin1());
				mimeData->setData(gDragableContainerMimeType, data);
				drag->setMimeData(mimeData);
				drag->start();
			}
		}
	}
	return false;
}
