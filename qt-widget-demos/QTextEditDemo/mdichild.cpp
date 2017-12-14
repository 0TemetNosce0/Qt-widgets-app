#include "mdichild.h"
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QScrollBar>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QCloseEvent>
#include <QApplication>

MdiChild::MdiChild()
{
    this->setAcceptDrops(false);
    //this->setFontPointSize(12);//设置字体大小
    this->setWordWrapMode(QTextOption::WrapAnywhere);//设为自动换行
    this->setAttribute(Qt::WA_DeleteOnClose);//在窗口关闭的同时销毁它
    isUntitled = true;//未命名
    connect(document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

    QPalette palette = this->palette();//更改调色板，使查找时能高亮显示找到的内容
    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
    this->setPalette(palette);

     /**自定义的右键菜单项目**/
    actUndo = new QAction(QIcon(":/images/undo.png"),QStringLiteral("撤销"),this);
    actUndo->setShortcuts(QKeySequence::Undo);
    actUndo->setEnabled(this->document()->isUndoAvailable());
    connect(this->document(),SIGNAL(undoAvailable(bool)),actUndo,SLOT(setEnabled(bool)));
    connect(actUndo,SIGNAL(triggered()),this,SLOT(undo()));

    actRedo = new QAction(QIcon(":/images/redo.png"),QStringLiteral("重复"),this);
    actRedo->setShortcuts(QKeySequence::Redo);
    actRedo->setEnabled(this->document()->isRedoAvailable());
    connect(this->document(),SIGNAL(redoAvailable(bool)),actRedo,SLOT(setEnabled(bool)));
    connect(actRedo,SIGNAL(triggered()),this,SLOT(redo()));

    actCut = new QAction(QIcon(":/images/cut.png"),QStringLiteral("剪切"),this);
    actCut->setShortcuts(QKeySequence::Cut);
    actCut->setEnabled(this->textCursor().hasSelection());
    connect(this,SIGNAL(copyAvailable(bool)),actCut,SLOT(setEnabled(bool)));
    connect(actCut,SIGNAL(triggered()),this,SLOT(cut()));

    actCopy = new QAction(QIcon(":/images/copy.png"),QStringLiteral("复制"),this);
    actCopy->setShortcuts(QKeySequence::Copy);
    actCopy->setEnabled(this->textCursor().hasSelection());
    connect(this,SIGNAL(copyAvailable(bool)),actCopy,SLOT(setEnabled(bool)));
    connect(actCopy,SIGNAL(triggered()),this,SLOT(copy()));

    actPaste = new QAction(QIcon(":/images/paste.png"),QStringLiteral("粘贴"),this);
    actPaste->setShortcuts(QKeySequence::Paste);
    //actPaste->setEnabled(!qApp->clipboard()->text().isEmpty());
    connect(actPaste,SIGNAL(triggered()),this,SLOT(paste()));

    actDel = new QAction(QIcon(":/images/stock_delete.png"),QStringLiteral("删除"),this);
    actDel->setShortcuts(QKeySequence::Delete);
    actDel->setEnabled(this->textCursor().hasSelection());
    connect(this,SIGNAL(copyAvailable(bool)),actDel,SLOT(setEnabled(bool)));
    connect(actDel,SIGNAL(triggered()),this,SIGNAL(Del()));

    actSelectAll = new QAction(QIcon(":/images/edit-select-all.png"),QStringLiteral("全选"),this);
    actSelectAll->setShortcuts(QKeySequence::SelectAll);
    connect(actSelectAll,SIGNAL(triggered()),this,SLOT(selectAll()));

    actFontChang = new QAction(QIcon(":/images/font.png"),QStringLiteral("字体设置"),this);
    connect(actFontChang,SIGNAL(triggered()),this,SIGNAL(fontChang()));

    actFontColor = new QAction(QIcon(":/images/textcolor.png"),QStringLiteral("字体颜色"),this);
    connect(actFontColor, SIGNAL(triggered()), this, SIGNAL(fontColor()));

}

void MdiChild::newFile()//新建
{
    static int sequenceNumber = 1;//文档序列号

    isUntitled = true;
    curFile = QStringLiteral("无标题%1").arg(sequenceNumber++);
    setWindowTitle(curFile + "[*]");

}

bool MdiChild::loadFile(const QString &fileName)//读取文件
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, QStringLiteral("MDI"),
                             QStringLiteral("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    this->setText(in.readAll());
   //  this->setHtml(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);

    return true;
}

bool MdiChild::save()
{
    if (isUntitled)
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}

bool MdiChild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(
            this,QStringLiteral("另存为"),curFile,"(*.txt)"";;All File(*.*)");

    if (fileName.isEmpty())
    {
        return false;
    }

    return saveFile(fileName);
}

bool MdiChild::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, QStringLiteral("MDI"),
                             QStringLiteral("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    return true;
}

void MdiChild::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(QFileInfo(fileName).fileName() + "[*]");
}

void MdiChild::documentWasModified()//文档是否被修改,"*"的显示
{
    setWindowModified(document()->isModified());
}

bool MdiChild::maybeSave()//是否保存
{
    if (this->document()->isModified())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, QStringLiteral("警告"),
                     QStringLiteral("'%1'内容已修改但尚未保存，是否保存？")
                     .arg(curFile),
                     QMessageBox::Save | QMessageBox::Discard
                     | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
        {
            return save();
        }
        else if (ret == QMessageBox::Cancel)
        {
            return false;
        }
    }

    return true;
}

void MdiChild::closeEvent(QCloseEvent *event)//重写关闭事件
{
    if (maybeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MdiChild::contextMenuEvent(QContextMenuEvent *event)//重写右键菜单事件
{
    QMenu* menu = new QMenu(this);
    menu->addAction(actUndo);
    menu->addAction(actRedo);
    menu->addSeparator();
    menu->addAction(actCut);
    menu->addAction(actCopy);
    menu->addAction(actPaste);
    menu->addAction(actDel);
    menu->addAction(actSelectAll);
    menu->addSeparator();
    menu->addAction(actFontChang);
    menu->addAction(actFontColor);

    menu->exec(event->globalPos());
}

void MdiChild::wheelEvent(QWheelEvent *e)//重写鼠标滚轮事件，实现按下Ctrl键同时滚动滚轮放大和缩小字体
{
    if (e->modifiers() == Qt::ControlModifier)//是否按下Ctrl键
    {
        if(e->delta() > 0 )//上滚
        {
            this->zoomIn(1);//放大
        }
        else
        {
            this->zoomOut(1);
        }
    }
    else//实现文本的上下滚动
    {
         if(e->delta() > 0 )//上滚
         {
             this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()-25);
         }
         else
         {
             this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()+25);
         }
    }
}
