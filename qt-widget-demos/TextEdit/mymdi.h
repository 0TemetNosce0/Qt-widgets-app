#ifndef MYMDI_H
#define MYMDI_H

#include <QTextEdit>

class MyMdi : public QTextEdit
{
    Q_OBJECT

public:
    explicit MyMdi(QWidget *parent = 0);
    void NewFile();
    bool LoadFile(const QString &file_name);
    QString CurrentFilePath();
    QString get_current_file_name();
    void SetCurrentFile(const QString &file_name);
    bool Save();
    bool SaveAs();
    bool SaveFile(const QString &file_name);//��ΪSave()��SaveAs()�кܶ๲ͬ�Ĵ��룬������õ���д������������á�

signals:

public slots:

private:
    QString current_file_path_;//��ǰ�ļ����ļ���
    bool is_saved_;  //�ļ��Ƿ񱣴��־
    bool has_saved();
    void contextMenuEvent(QContextMenuEvent *event);

protected:
    void closeEvent(QCloseEvent *);//��д�ر��¼�

private slots:
    void documentWasModified();//���ĵ����ݱ��ĺ�����ִ�еĲ���

};

#endif // MYMDI_H
