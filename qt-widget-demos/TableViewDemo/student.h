#ifndef STUDENT_H
#define STUDENT_H

#include <QAbstractTableModel>

class Student
{
public:
    Student(int num, QString name, int id, QString phone,
            QString level, QString desc, bool checked = false);

public:
    int m_id;
    int m_num;

    QString m_desc;
    QString m_name;
    QString m_phone;
    QString m_level;

    bool m_checked;
};

class CustomModel : public QAbstractTableModel
{
public:
    CustomModel(QObject *parent = 0);

    void setStudenetList(const QList<Student>& list);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    void unselect();
    void selectAll();

private:
    QList<Student> m_list;
};

#endif // STUDENT_H
