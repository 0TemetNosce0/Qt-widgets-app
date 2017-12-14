#ifndef CCOMBOBOX_H
#define CCOMBOBOX_H

#include <QComboBox>
#include <QListWidget>

class CComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit CComboBox(QWidget *parent = 0);
    void setItemEnable(QListWidget *list, int index, bool enable);

signals:

public slots:

private:
    QString m_strText;

private slots:
    void textChanged(QString text);
};

#endif // CCOMBOBOX_H
