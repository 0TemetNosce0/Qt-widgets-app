#ifndef MDICHILD_H
#define MDICHILD_H

#include <QTextEdit>


class MdiChild : public QTextEdit
{
    Q_OBJECT

public:
    MdiChild();

    QString curFile;
    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString currentFile() { return curFile; }

private:
    bool isUntitled;
    bool maybeSave();
    void setCurrentFile(const QString &fileName);

    //�Զ�����Ҽ��˵���Ŀ
    QAction *actRedo;
    QAction *actUndo;
    QAction *actCut;
    QAction *actCopy;
    QAction *actPaste;
    QAction *actDel;
    QAction *actSelectAll;
    QAction *actFontChang;
    QAction *actFontColor;

public slots:
    void documentWasModified();

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void closeEvent(QCloseEvent *);
    void wheelEvent(QWheelEvent *e);
    //void dragEnterEvent(QDragEnterEvent *e);
   // void dropEvent(QDropEvent *e);

signals:
    void fontChang();//���������ź�
    void fontColor();//������ɫ�ź�
    void Del();//ɾ���ź�
};

#endif // MDICHILD_H
