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
    bool SaveFile(const QString &file_name);//因为Save()和SaveAs()有很多共同的代码，所以最好单独写个函数供其调用。

signals:

public slots:

private:
    QString current_file_path_;//当前文件的文件名
    bool is_saved_;  //文件是否保存标志
    bool has_saved();
    void contextMenuEvent(QContextMenuEvent *event);

protected:
    void closeEvent(QCloseEvent *);//重写关闭事件

private slots:
    void documentWasModified();//当文档内容被改后所需执行的操作

};

#endif // MYMDI_H
