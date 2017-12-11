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

    //自定义的右键菜单项目
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
    void fontChang();//字体设置信号
    void fontColor();//字体颜色信号
    void Del();//删除信号
};

#endif // MDICHILD_H
