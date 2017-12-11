#include "droplabel.h"


DropLabel::DropLabel(QWidget *parent) :
    QLabel(parent) {
    QPalette palette = this->palette();
    this->setAutoFillBackground(true);
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);
    this->setAcceptDrops(true);
}


void DropLabel::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText()) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DropLabel::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->text() == "DNA") {
        emit this->labelMatched();
    } else {
        event->ignore();
    }
    foreach (QObject *child, children()) {
        if (child->inherits("QWidget")) {
            QWidget *widget = static_cast<QWidget *>(child);
            if (!widget->isVisible())
                widget->deleteLater();
        }
    }
}
