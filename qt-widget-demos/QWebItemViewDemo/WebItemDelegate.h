#pragma once

#include <QWidget>
#include <QStyledItemDelegate>

class QItemSelection;
class QWebView;
class QWebPage;
class QWebElement;

/** A factory which produces HTML templates for items
  * displayed in an item view using a WebItemViewDelegate.
  */
class WebItemFactory
{
    public:
        /** Returns markup to be used in the <head>...</head> section
          * of the page.  This is used to define CSS styles for the page.
          */
        virtual QString pageHeader() = 0;

        /** Returns the HTML template to use for a given item.  This markup
          * is inserted into a <div> element which is then rendered where the
          * item appears in the view.
          */
        virtual QString itemTemplate(const QModelIndex& index) = 0;

        /** Returns the height for a given item.  If the result is -1,
          * the intrinsic height of the HTML content for the item is used.
          */
        virtual int itemHeight(const QModelIndex& index) = 0;

        /** Returns a list of CSS classes which should be used by a given item.
          * This allows items with the same HTML template to have different appearances.
          */
        virtual QStringList itemClasses(const QModelIndex& index);

        /** Returns true if item templates should be re-created when an item's data changes.
          * Defaults to true.
          */
        virtual bool recreateItemOnDataChange(const QModelIndex& index) const;
};

/** A helper which monitors a QAbstractItemView and provides notifications
  * when the visible set of items or their geometry changes.
  */
class ItemViewLayoutMonitor : public QObject
{
    Q_OBJECT

    public:
        ItemViewLayoutMonitor(QAbstractItemView* view, QObject* parent = 0);

        /** Returns a list of visible items. */
        QVector<QModelIndex> visibleIndexes(const QModelIndex& parent) const;

    Q_SIGNALS:
        void visibleItemsChanged();

    private:
        QAbstractItemView* m_view;
};

/** A delegate which renders item-view items using elements from
  * a web page.
  */
class WebItemDelegate : public QStyledItemDelegate
{
        Q_OBJECT

    public:
        WebItemDelegate(WebItemFactory* itemFactory, QObject* parent = 0);
        virtual ~WebItemDelegate();

        /** Set the view whoose items should be drawn by this delegate.
          * The delegate will install itself as the view's item delegate.
          */
        void setView(QAbstractItemView* view);

        /** Expose a QObject to item web content as a Javascript property
          * called @p name on the window object.
          */
        void addJavaScriptObject(const QString& name, QObject* object);

        void showDebugWebView();

        /** Draw the background for an item */
        void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

        // implements QAbstractItemDelegate
        virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
        virtual bool eventFilter(QObject *object, QEvent *event);

    Q_SIGNALS:
        /** Emitted when the user clicks a link in the web content for an item. */
        void linkClicked(const QUrl&);

    private Q_SLOTS:
        void webSceneRepaint(const QRect&);
        void viewScrolled();
        void selectionChanged(const QItemSelection&, const QItemSelection&);
        void layoutAllDomNodes();
        void modelDataChanged(const QModelIndex&, const QModelIndex&);

        void viewDestroyed();

    private:
        QWebElement elementForIndex(const QModelIndex& index, bool createElement = true) const;
        QString elementId(const QModelIndex& index) const;
        QWebElement createItem(const QModelIndex& index);
        QPair<QModelIndex, QModelIndex> visibleIndexes() const;
        void updateItemData(QWebElement element, const QModelIndex &index);
        void modelChanged();
        QWebElement pageStyleElement();
        void updatePageStyle();
        void updateItemSizes();
        int itemHeight(const QModelIndex&) const;
        void sendMouseEvent(QMouseEvent *event);
        QPoint mapToWebPageViewportPos(const QPoint& pos);
        QPoint mapToWebPagePos(const QPoint& pos);
        void positionDomNode(QWebElement element, const QModelIndex &index);
        void setDomNodeVisible(QWebElement element, bool visible);
        void removeElementForIndex(const QModelIndex& index);

        QHash<QString, int> m_roleNameToValue;
        WebItemFactory* m_itemFactory;
        QWebPage* m_webPage;
        QAbstractItemView* m_view;

        QVector<QModelIndex> m_visibleIndexes;

        // cache of QWebElements for visible items
        QHash<QModelIndex, QWebElement> m_visibleIndexElements;

        QScopedPointer<QWebView> m_debugWebView;
        QScopedPointer<QWidget> m_pageView;
        QScopedPointer<ItemViewLayoutMonitor> m_layoutMonitor;
};
