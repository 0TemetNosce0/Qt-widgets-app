#ifndef ADDVALUESWIDGET_H_
#define ADDVALUESWIDGET_H_

#include <QLineEdit>
#include <QList>

class QToolButton;

class AddValuesWidget : public QLineEdit
{
    Q_OBJECT

public:
    AddValuesWidget(QWidget *parent = 0);
    AddValuesWidget(const QIcon &icon, QWidget *parent = 0);
    QList<int> values();

signals:
    void valuesListChanged();

private slots:
    void updateValuesList();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void init();
    void updateButtonGeometry();
    QToolButton *m_button;
    QList<int> m_valuesList;
};

#endif /* ADDVALUESWIDGET_H_ */
