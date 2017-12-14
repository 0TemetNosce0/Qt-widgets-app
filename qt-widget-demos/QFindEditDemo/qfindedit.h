#ifndef QFINDEDIT_H
#define QFINDEDIT_H

#include <QEvent>
#include <QLineEdit>
#include <QListView>
#include <QListWidgetItem>
#include <QStringListModel>

class QFindEdit : public QLineEdit
{
	Q_OBJECT

public:
	QFindEdit(QWidget *parent);
	~QFindEdit();

    QStringList& stringList();

signals:
	void itemClicked(QListWidgetItem *item);

protected slots:
	void textEditedSlot(const QString& text);
	void clickedSlot(QModelIndex modelIndex);

protected:
    virtual bool eventFilter(QObject *target, QEvent *event);

private:
    void         showList(const QString& text);
    void         hideList();

    bool             m_bEditFocus;
    QListView        *m_pListView;
    QStringList      m_stringList;
    QStringListModel *m_stringListmodel;
};

#endif // QFINDEDIT_H
