#include "qlightboxwidget.h"

#include <QPixmap>
#include <QEvent>
#include <QPaintEvent>
#include <QChildEvent>
#include <QPainter>

QLightBoxWidget::QLightBoxWidget(QWidget* _parent, bool _folowToHeadWidget)
    : QWidget(_parent)
    , m_isInUpdateSelf(false)
{
    Q_ASSERT_X(_parent, "", Q_FUNC_INFO);

    if (_folowToHeadWidget)
    {
        while (_parent->parentWidget() != 0)
        {
            _parent = _parent->parentWidget();
        }

        setParent(_parent);
    }

    _parent->installEventFilter(this);

    setVisible(false);
}

bool QLightBoxWidget::eventFilter(QObject* _object, QEvent* _event)
{
    if (_event->type() == QEvent::ChildAdded)
    {
        QChildEvent* childEvent = dynamic_cast<QChildEvent*>(_event);

        if (childEvent->child() != this)
        {
            QWidget* parent = parentWidget();
            setParent(0);
            setParent(parent);
        }
    }

    if (isVisible() && _event->type() == QEvent::Resize)
    {
        updateSelf();
    }

    return QWidget::eventFilter(_object, _event);
}

void QLightBoxWidget::paintEvent(QPaintEvent* _event)
{
    QPainter p;
    p.begin(this);

    p.drawPixmap(0, 0, width(), height(), m_parentWidgetPixmap);

    p.setBrush(QBrush(QColor(0, 0, 0, 220)));
    p.drawRect(0, 0, width(), height());
    p.end();

    QWidget::paintEvent(_event);
}

void QLightBoxWidget::showEvent(QShowEvent* _event)
{
    updateSelf();

    QWidget::showEvent(_event);
}

void QLightBoxWidget::updateSelf()
{
    if (!m_isInUpdateSelf)
    {
        m_isInUpdateSelf = true;

        {
            hide();
            resize(parentWidget()->size());
            m_parentWidgetPixmap = grabParentWidgetPixmap();
            show();
        }

        m_isInUpdateSelf = false;
    }
}

QPixmap QLightBoxWidget::grabParentWidgetPixmap() const
{
    QPixmap parentWidgetPixmap;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    parentWidgetPixmap = parentWidget()->grab();
#else
    parentWidgetPixmap = QPixmap::grabWidget(parentWidget());
#endif

    return parentWidgetPixmap;
}
