#include "qfindedit.h"
#include <QKeyEvent>
#include <QApplication>

QFindEdit::QFindEdit(QWidget *parent)
    : QLineEdit(parent)
    , m_bEditFocus(true)
{
	setPlaceholderText("please input find word");

	m_stringListmodel = new QStringListModel(this);
    m_pListView = new QListView(this);
    m_pListView->setWindowFlags(Qt::Popup);
    m_pListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pListView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pListView->setParent(0, Qt::Popup);
    m_pListView->setFocusPolicy(Qt::NoFocus);
    m_pListView->setFocusProxy(this);

    m_stringList << "Biao" << "Bin" << "Huang" << "Hua" << "Hello" << "Bi" << "Hallo";

	connect(this, SIGNAL(textEdited(const QString&)), this, SLOT(textEditedSlot(const QString&)));
    connect(m_pListView, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedSlot(QModelIndex)));
    connect(this, SIGNAL(activated(QModelIndex)), m_pListView, SLOT(hide()));

	this->installEventFilter(this);
    m_pListView->installEventFilter(this);
}

QFindEdit::~QFindEdit()
{
    delete m_pListView;
}

QStringList& QFindEdit::stringList()
{
	return m_stringList;
}

void QFindEdit::showList(const QString& text)
{
    //效率较低,需要优化
	QStringList sl;  

    foreach(QString word, m_stringList)
    {
        if (word.contains(text))
        {
			sl << word; 
		}  
	}

	if (sl.size() == 0) 
	{
        hideList();
		return;
	}
	m_stringListmodel->setStringList(sl);  
    m_pListView->setModel(m_stringListmodel);

	//高度需要优化
    m_pListView->resize(rect().width(), 200);
	QPoint pTopleft = mapToGlobal(rect().bottomLeft());
    m_pListView->move(pTopleft.x(), pTopleft.y());
    m_pListView->show();
}

void QFindEdit::textEditedSlot(const QString& text)
{
	QString strText = text.trimmed();

	if (!strText.isEmpty())
	{
        showList(strText);
	}
	else
	{
        hideList();
	}
}

void QFindEdit::clickedSlot(QModelIndex modelIndex)
{
    setText(m_pListView->model()->data(modelIndex).toString());
    hideList();
}

void QFindEdit::hideList()
{
    m_pListView->hide();
}

bool QFindEdit::eventFilter(QObject *target, QEvent *event)
{
    if (m_bEditFocus && (target == this) && event->type() == QEvent::FocusOut)
	{
        if (m_pListView && m_pListView->isVisible())
        {
            return true;
        }
    }

    if (target != m_pListView)
    {
        return QLineEdit::eventFilter(target, event);
    }

    switch (event->type())
	{
	case QEvent::KeyPress: 
		{
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            QModelIndex curIndex = m_pListView->currentIndex();
            QModelIndexList selList = m_pListView->selectionModel()->selectedIndexes();
            const int key = keyEvent->key();

			if ((key == Qt::Key_Up || key == Qt::Key_Down) && selList.isEmpty() && curIndex.isValid() )
			{
                m_pListView->setCurrentIndex(curIndex);
				return true;
			}

			switch (key) 
			{
			case Qt::Key_End:
			case Qt::Key_Home:
                if (keyEvent->modifiers() & Qt::ControlModifier)
                {
                    return false;
                }
                break;

			case Qt::Key_Up:
				if (!curIndex.isValid()) 
				{
                    int rowCount = m_pListView->model()->rowCount();
                    QModelIndex lastIndex = m_pListView->model()->index(rowCount - 1, m_pListView->modelColumn());
                    m_pListView->setCurrentIndex(lastIndex);
					return true;
				} 
				else if (curIndex.row() == 0) 
				{
					return true;
				}
				return false;

			case Qt::Key_Down:
				if (!curIndex.isValid()) 
				{
                    QModelIndex firstIndex = m_pListView->model()->index(0, m_pListView->modelColumn());
                    m_pListView->setCurrentIndex(firstIndex);
					return true;
				} 
                else if (curIndex.row() == m_pListView->model()->rowCount() - 1)
				{
					return true;
				}
				return false;
			}

            m_bEditFocus = false;
            this->event(keyEvent);
			m_bEditFocus = true;
            if (event->isAccepted() || !m_pListView->isVisible())
            {
				if (!this->hasFocus())
                {
                    hideList();
                }
                if (event->isAccepted())
                {
                    return true;
                }
            }

			switch (key) 
			{
			case Qt::Key_Return:
			case Qt::Key_Enter:
			case Qt::Key_Tab:
                hideList();
				if (curIndex.isValid()) 
				{  
                    QString text = m_pListView->currentIndex().data().toString();
					setText(text);  
				}  
				break;

			case Qt::Key_F4:
                if (keyEvent->modifiers() & Qt::AltModifier)
                {
                    hideList();
                }
                break;

			case Qt::Key_Backtab:
			case Qt::Key_Escape:
                hideList();
				break;

			default:
				break;
			}

			return true;
		}
	case QEvent::MouseButtonPress: 
        if (!m_pListView->underMouse())
		{
            hideList();
			return true;
		}
		return false;
	case QEvent::InputMethod:
	case QEvent::ShortcutOverride:
        QApplication::sendEvent(this, event);
		break;

	default:
		return false;
	}
	return false;
}
