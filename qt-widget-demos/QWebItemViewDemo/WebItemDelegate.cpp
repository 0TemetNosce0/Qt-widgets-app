#include "WebItemDelegate.h"

#include <QDebug>

#include <QApplication>
#include <QHeaderView>
#include <QResizeEvent>
#include <QScrollBar>
#include <QStringListModel>
#include <QTableView>
#include <QTreeView>

#include <QWebElement>
#include <QWebFrame>
#include <QWebPage>
#include <QWebView>

QStringList WebItemFactory::itemClasses(const QModelIndex &index)
{
    Q_UNUSED(index);
    return QStringList();
}

bool WebItemFactory::recreateItemOnDataChange(const QModelIndex&) const
{
    return false;
}

WebItemDelegate::WebItemDelegate(WebItemFactory* factory, QObject *parent)
    : QStyledItemDelegate(parent)
    , m_itemFactory(factory)
    , m_webPage(new QWebPage(this))
    , m_view(0)
{
    connect(m_webPage, SIGNAL(repaintRequested(QRect)), this, SLOT(webSceneRepaint(QRect)));
    m_webPage->mainFrame()->setHtml(factory->pageHeader());

    m_webPage->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(m_webPage, SIGNAL(linkClicked(QUrl)), this, SIGNAL(linkClicked(QUrl)));

    // Hide the web page's scrollbars.  They interfere with input handling in several ways:
    //
    // - If the web page's scrollbars are visible, they will obscure part of the content and can
    //   block mouse events in the region of the scrollbar from being sent to the underlying web
    //   content.
    //
    // - They will accept key up/down events and prevent the event from being delivered to the
    //   item view (see QEvent::KeyPress, KeyRelease handling in eventFilter())
    //
    m_webPage->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    m_webPage->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    // setup a view on the QWebPage so that we can get notifications of cursor
    // and tooltip changes
    m_pageView.reset(new QWidget);
    m_webPage->setView(m_pageView.data());
    m_pageView->installEventFilter(this);
}

WebItemDelegate::~WebItemDelegate()
{
    m_webPage->setView(0);
}

void WebItemDelegate::showDebugWebView()
{
    m_pageView->show();
}

bool WebItemDelegate::eventFilter(QObject *object, QEvent *event)
{
    if (m_view && object == m_view->viewport()) {
        switch (event->type()) {
		case QEvent::Resize:
			m_webPage->setViewportSize(m_view->size());
			layoutAllDomNodes();
			break;
		case QEvent::MouseButtonPress:
		case QEvent::MouseButtonRelease:
		case QEvent::MouseButtonDblClick:
		case QEvent::MouseMove:
			sendMouseEvent(static_cast<QMouseEvent*>(event));
			break;
		case QEvent::Leave:
			m_webPage->event(event);
		default:
			break;
        }
    } else if (object == m_view) {
        // the view is a focus proxy for the viewport, so m_view rather than m_view->viewport()
        // receives keyboard and focus in/out events
        switch (event->type()) {
		case QEvent::KeyPress:
		case QEvent::KeyRelease:
		{
			// Avoid events bubbling up to the list view if accepted by a form
			// element or other control
			m_webPage->event(event);
			if (event->isAccepted())
			{
				return true;
			}
		}
			break;
		case QEvent::FocusIn:
		case QEvent::FocusOut:
			m_webPage->event(event);
			break;
		default:
			break;
        }
    } else if (object == m_pageView.data()) {
        switch (event->type()) {
		case QEvent::CursorChange:
			m_view->viewport()->setCursor(m_pageView->cursor());
			break;
		case QEvent::ToolTipChange:
			m_view->viewport()->setToolTip(m_pageView->toolTip());
			break;
		default:
			break;
        }
    }
    return false;
}

QPoint WebItemDelegate::mapToWebPageViewportPos(const QPoint& pos)
{
    QModelIndex index = m_view->indexAt(pos);
    QRect itemRect = m_view->visualRect(index);
    QPoint offset = pos - itemRect.topLeft();
    QRect itemGeometry = elementForIndex(index).geometry();
    QPoint webPagePos = itemGeometry.topLeft() + offset - m_webPage->mainFrame()->scrollPosition();

    return webPagePos;
}

QPoint WebItemDelegate::mapToWebPagePos(const QPoint& pos)
{
    return mapToWebPageViewportPos(pos) + m_webPage->mainFrame()->scrollPosition();
}

void WebItemDelegate::sendMouseEvent(QMouseEvent* event)
{
    QMouseEvent pageEvent(event->type(), mapToWebPageViewportPos(event->pos()), event->button(), event->buttons(), event->modifiers());
    m_webPage->event(&pageEvent);
}

void WebItemDelegate::setView(QAbstractItemView *view)
{
    if (m_view) {
        m_view->setItemDelegate(0);
        m_view->removeEventFilter(this);
        m_view->viewport()->removeEventFilter(this);
        disconnect(m_view, 0, this, 0);
        disconnect(m_view->selectionModel(), 0, this, 0);
        m_layoutMonitor.reset();
    }

    m_view = view;

    if (view) {
        view->setItemDelegate(this);
        view->installEventFilter(this);
        view->viewport()->installEventFilter(this);
        view->viewport()->setMouseTracking(true);
        m_layoutMonitor.reset(new ItemViewLayoutMonitor(view));

        connect(m_layoutMonitor.data(), SIGNAL(visibleItemsChanged()),
                this, SLOT(layoutAllDomNodes()));

        updatePageStyle();

        connect(view->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(viewScrolled()));
        connect(view->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(viewScrolled()));

        connect(view->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(selectionChanged(QItemSelection,QItemSelection)));

        connect(view, SIGNAL(destroyed()), this, SLOT(viewDestroyed()));

        modelChanged();
    }
}

void WebItemDelegate::viewDestroyed()
{
    m_view = 0;
}

void WebItemDelegate::addJavaScriptObject(const QString &name, QObject *object)
{
    m_webPage->mainFrame()->addToJavaScriptWindowObject(name, object);
}

void WebItemDelegate::updatePageStyle()
{
    QWebElement styleElement = pageStyleElement();

    QStringList selectors;

    // disable text selection.
    //
    // QtWebKit still changes the cursor when hovering the mouse over text after setting
    // -webkit-user-select to 'none', so add an additional 'cursor' value to prevent this.
    //
    selectors << QString("body { -webkit-user-select: none; -webkit-user-drag: none; cursor:default; }");
    selectors << QString("a { cursor:pointer; }");

    // setup font
    QFont font = m_view->viewport()->font();
    selectors << QString("body { font-family: %1; font-size: %2pt; }")
      .arg(font.family()).arg(font.pointSize());

    // TODO - Differentiate between different palette color groups (active / inactive / disabled)
    QPalette palette = m_view->viewport()->palette();
    QColor defaultColor = palette.color(QPalette::Text);
    QColor highlightColor = palette.color(QPalette::HighlightedText);

    selectors << QString("body { color: %1; }").arg(defaultColor.name());
    selectors << QString(".item-selected { color : %1 }").arg(highlightColor.name());
    selectors << QString(".view-item { position:absolute; overflow:hidden; text-overflow:ellipsis; }");

    styleElement.setPlainText(selectors.join("\n"));
}

void WebItemDelegate::updateItemSizes()
{
    // doItemsLayout() is public but not documented.
    m_view->doItemsLayout();
}

QWebElement WebItemDelegate::pageStyleElement()
{
    QWebElement element = m_webPage->mainFrame()->findFirstElement("#page-style");
    if (element.isNull()) {
        m_webPage->mainFrame()->findFirstElement("HEAD").appendInside("<style id='page-style'></style>");
        return m_webPage->mainFrame()->findFirstElement("#page-style");
    }
    return element;
}

void WebItemDelegate::modelChanged()
{
    Q_ASSERT_X(m_view->model(), "WebItemDelegate::modelChanged", "The view has no model set");

    m_roleNameToValue.clear();

    QHashIterator<int, QByteArray> iter(m_view->model()->roleNames());
    while (iter.hasNext()) {
        iter.next();
        m_roleNameToValue.insert(QString(iter.value()), iter.key());
    }

    connect(m_view->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(modelDataChanged(QModelIndex,QModelIndex)));
}

void WebItemDelegate::modelDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    for (int row = topLeft.row(); row <= bottomRight.row(); row++) {
        for (int column = topLeft.column(); column <= bottomRight.column(); column++) {
            QModelIndex index = m_view->model()->index(row, column, topLeft.parent());
            QWebElement element = elementForIndex(index, false /* do not auto-create element */);
            if (m_itemFactory->recreateItemOnDataChange(index)) {
                removeElementForIndex(index);
                elementForIndex(index, true /* re-create element */);
            }
            else if (!element.isNull()) {
                updateItemData(element, index);
            }
        }
    }
}

void WebItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    drawBackground(painter, option, index);

    QWebElement element = elementForIndex(index);

    painter->save();
    painter->setClipRect(option.rect);
    painter->translate(option.rect.left(), option.rect.top());
    element.render(painter);
    painter->restore();
}

QSize WebItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    int width = m_view->width();
    return QSize(width, itemHeight(index));
}

int WebItemDelegate::itemHeight(const QModelIndex& index) const
{
    int height = m_itemFactory->itemHeight(index);
    if (height == -1) {
        QWebElement element = const_cast<WebItemDelegate*>(this)->elementForIndex(index);

        // force any pending layout updates to be executed
        element.styleProperty("height", QWebElement::ComputedStyle);

        height = element.geometry().height();
    }
    return height;
}

QString WebItemDelegate::elementId(const QModelIndex& index) const
{
    QModelIndex parentIndex = index.parent();
    QString id = QString("item_%1_%2").arg(index.row()).arg(index.column());
    if (parentIndex.isValid()) {
        return elementId(parentIndex) + '-' + id;
    } else {
        return id;
    }
}

void WebItemDelegate::removeElementForIndex(const QModelIndex& index)
{
    QWebElement element = elementForIndex(index, false /* do not auto-create element */);
    if (!element.isNull()) {
        m_visibleIndexElements.remove(index);
        element.takeFromDocument();
    }
}

QWebElement WebItemDelegate::elementForIndex(const QModelIndex &index, bool createElement) const
{
    if (!index.isValid()) {
        return QWebElement();
    }

    QWebElement element = m_visibleIndexElements.value(index);
    if (element.isNull()) {
        element = m_webPage->mainFrame()->findFirstElement('#' + elementId(index));
    }

    if (element.isNull() && createElement) {
        element = const_cast<WebItemDelegate*>(this)->createItem(index);
    }
    return element;
}

void WebItemDelegate::updateItemData(QWebElement element, const QModelIndex& index)
{
    QString role = element.attribute("data-role");
    QString roleAttr = element.attribute("data-role-attribute");

    int roleId = m_roleNameToValue.value(role, -1);
    if (roleId != -1) {
        QString value = index.data(roleId).toString();
        if (!roleAttr.isEmpty()) {
            element.setAttribute(roleAttr, value);
        } else {
            element.setInnerXml(value);
        }
    }

    QWebElement child = element.firstChild();
    while (!child.isNull()) {
        updateItemData(child, index);
        child = child.nextSibling();
    }
}

QWebElement WebItemDelegate::createItem(const QModelIndex& index)
{
    QString content = m_itemFactory->itemTemplate(index);
    QString classList = m_itemFactory->itemClasses(index).join(" ");
    QString wrapperHtml = QString("<div class=\"view-item %1\" id=\"%2\">%3</div>").arg(classList).arg(elementId(index)).arg(content);
    QWebElement body = m_webPage->mainFrame()->findFirstElement("body");
    if (body.isNull()) {
        qDebug() << "Unable to create element";
    }
    body.appendInside(wrapperHtml);

    QWebElement element = m_webPage->mainFrame()->findFirstElement('#' + elementId(index));
    updateItemData(element, index);

    return element;
}

// copied from StyledItemDelegate::drawBackground()
void WebItemDelegate::drawBackground(
    QPainter* painter,
    const QStyleOptionViewItem& option,
    const QModelIndex& index
) const
{
	const QStyleOptionViewItemV4& viewOption(static_cast<const QStyleOptionViewItemV4&>(option));

	Q_UNUSED(index);

	const QWidget* widget = viewOption.widget;
	QStyle* style = widget ? widget->style() : QApplication::style();

	if (style->inherits("QWindowsVistaStyle") && widget) {
		// Workaround Qt 4.4.1 - QWindowsVistaStyle only draws a styled item-view background if the
		// widget passed to drawPrimitive(...PE_PanelItemViewItem...) is a QTreeView or a QListView
		// with viewMode() == QListView::IconMode
		static QTreeView* treeView = new QTreeView();
		widget = treeView;
	}

	// Note: Avoid drawing styled background if we don't have a widget as it can cause
	// crashes in QStyleSheetStyle
	if (widget) {
		style->drawPrimitive(QStyle::PE_PanelItemViewItem, &viewOption, painter, widget);
	}
}

QPair<QModelIndex, QModelIndex> WebItemDelegate::visibleIndexes() const
{
	const QRect viewportRect = m_view->viewport()->rect();
	QModelIndex topVisibleIndex = m_view->indexAt(QPoint(0,0));
	if (!topVisibleIndex.isValid()) {
		return qMakePair(QModelIndex(), QModelIndex());
	}
	QModelIndex bottomVisibleIndex = m_view->indexAt(viewportRect.bottomLeft());
	if (!bottomVisibleIndex.isValid()) {
		bottomVisibleIndex = topVisibleIndex.sibling(m_view->model()->rowCount(topVisibleIndex.parent()) - 1, topVisibleIndex.column());
	}

	return qMakePair(topVisibleIndex, bottomVisibleIndex);
}

void WebItemDelegate::webSceneRepaint(const QRect & _webPageRect)
{
	QRect webPageRect(_webPageRect);
	webPageRect.translate(m_webPage->mainFrame()->scrollPosition());

	// iterate over each of the visible rows and check whether the corresponding web element
	// for the model item intersects the dirty area.  If so, repaint that item.
	QPair<QModelIndex, QModelIndex> visibleIndexes = this->visibleIndexes();
	QRegion dirtyRegion;
	for (int i=visibleIndexes.first.row(); i <= visibleIndexes.second.row(); i++) {
		QModelIndex sibling = visibleIndexes.first.sibling(i, visibleIndexes.first.column());
		QWebElement element = elementForIndex(sibling);
		QRect itemGeometry = element.geometry();
		if ((itemGeometry & webPageRect).isValid()) {
			dirtyRegion |= m_view->visualRect(sibling);
		}
	}
	m_view->viewport()->update(dirtyRegion);
}

void WebItemDelegate::viewScrolled()
{
	// scroll the web page so that the element corresponding to the first visible element in
	// the item view is at the top of the web page.

	// In order for us to receive repaint requests for DOM nodes corresponding
	// to the visible items and to be able to deliver mouse events to those DOM nodes,
	// the notes need to be visible in QWebPage's viewport.
	m_webPage->mainFrame()->setScrollPosition(mapToWebPagePos(QPoint(0,0)));
}

void WebItemDelegate::positionDomNode(QWebElement element, const QModelIndex& index)
{
	QRect itemRect = m_view->visualRect(index);

	itemRect.setLeft(itemRect.left() + m_view->horizontalScrollBar()->value());
	itemRect.setTop(itemRect.top() + m_view->verticalScrollBar()->value());

	element.setStyleProperty("left",QString::number(itemRect.left()));
	element.setStyleProperty("top", QString::number(itemRect.top()));
	element.setStyleProperty("width", QString::number(itemRect.width()));
	element.setStyleProperty("height", QString::number(itemRect.height()));
}

void WebItemDelegate::setDomNodeVisible(QWebElement element, bool visible)
{
	QString displayMode;
	if (!visible) {
		displayMode = "none";
	}
	element.setStyleProperty("display", displayMode);
}

void WebItemDelegate::layoutAllDomNodes()
{
	Q_FOREACH(const QModelIndex& index, m_visibleIndexes) {
		setDomNodeVisible(elementForIndex(index), false);
	}

	QVector<QModelIndex> newVisibleIndexes = m_layoutMonitor->visibleIndexes(QModelIndex());

	// prepare an update cache of (index -> DOM node)
	QHash<QModelIndex, QWebElement> visibleElementCache;
	visibleElementCache.reserve(newVisibleIndexes.count());

	Q_FOREACH(const QModelIndex& index, newVisibleIndexes) {
		QWebElement element = elementForIndex(index);
		visibleElementCache.insert(index, element);

		setDomNodeVisible(element, true);
		positionDomNode(element, index);
	}

	m_visibleIndexes = newVisibleIndexes;
	m_visibleIndexElements = visibleElementCache;
}

void WebItemDelegate::selectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{
	Q_FOREACH(const QModelIndex& index, selected.indexes()) {
		elementForIndex(index).addClass("item-selected");
	}
	Q_FOREACH(const QModelIndex& index, deselected.indexes()) {
		elementForIndex(index).removeClass("item-selected");
	}
}


ItemViewLayoutMonitor::ItemViewLayoutMonitor(QAbstractItemView *view, QObject *parent)
	: QObject(parent)
	, m_view(view)
{
	QList<QHeaderView*> headerViews;

	QTableView* tableView = qobject_cast<QTableView*>(view);
	if (tableView) {
		headerViews << tableView->horizontalHeader();
		headerViews << tableView->verticalHeader();
	}

	QTreeView* treeView = qobject_cast<QTreeView*>(view);
	if (treeView) {
		headerViews << treeView->header();

		connect(treeView, SIGNAL(expanded(QModelIndex)),
				this, SIGNAL(visibleItemsChanged()));
		connect(treeView, SIGNAL(collapsed(QModelIndex)),
				this, SIGNAL(visibleItemsChanged()));
	}

	Q_FOREACH(QHeaderView* header, headerViews) {
		connect(header, SIGNAL(sectionMoved(int,int,int)),
				this, SIGNAL(visibleItemsChanged()));
		connect(header, SIGNAL(sectionResized(int,int,int)),
				this, SIGNAL(visibleItemsChanged()));
	}
}

QVector<QModelIndex> ItemViewLayoutMonitor::visibleIndexes(const QModelIndex& parent) const
{
	QVector<QModelIndex> indexes;

	QTreeView* treeView = qobject_cast<QTreeView*>(m_view);

	int rowCount = m_view->model()->rowCount(parent);
	int columnCount = m_view->model()->columnCount(parent);

	for (int row = 0; row < rowCount; row++) {
		for (int column = 0; column < columnCount; column++) {
			QModelIndex index = m_view->model()->index(row, column, parent);
			indexes << index;
			if (treeView && treeView->isExpanded(index)) {
				indexes += visibleIndexes(index);
			}
		}
	}

	return indexes;
}
