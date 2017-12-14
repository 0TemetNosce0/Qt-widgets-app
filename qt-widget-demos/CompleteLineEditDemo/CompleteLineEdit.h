#ifndef COMPLETELINEEDIT_H
#define COMPLETELINEEDIT_H


#include <QLineEdit>
#include <QStringList>

class QListView;
class QModelIndex;
class QStringListModel;

class CompleteLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    CompleteLineEdit(QStringList words, QWidget *parent = 0);

public slots:
    void setComplete(const QString &text); // ��̬����ʾ����б�
    void completeText(const QModelIndex &index); // �������б��е��ʹ�ô����Զ��������ĵ���

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);

private:
    QStringList words; // ��������б�ĵ���
    QListView *listView; // ����б�
    QStringListModel *model; // ����б��model
};

#endif // COMPLETELINEEDIT_H
