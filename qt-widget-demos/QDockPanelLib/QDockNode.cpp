#include "QDockNode.h"
#include <QDebug>

QDockNode::QDockNode(QWidget *parent)
	: QSplitter(parent)
{
	qDebug() << "cons";
}

QDockNode::~QDockNode()
{
	qDebug() << "des";
}
