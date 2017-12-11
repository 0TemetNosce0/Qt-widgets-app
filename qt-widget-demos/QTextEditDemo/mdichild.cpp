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
    //this->setFontPointSize(12);//���������С
    this->setWordWrapMode(QTextOption::WrapAnywhere);//��Ϊ�Զ�����
    this->setAttribute(Qt::WA_DeleteOnClose);//�ڴ��ڹرյ�ͬʱ������
    isUntitled = true;//δ����
    connect(document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

    QPalette palette = this->palette();//���ĵ�ɫ�壬ʹ����ʱ�ܸ�����ʾ�ҵ�������
    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
    this->setPalette(palette);

     /**�Զ�����Ҽ��˵���Ŀ**/
    actUndo = new QAction(QIcon(":/images/undo.png"),QStringLiteral("����"),this);
    actUndo->setShortcuts(QKeySequence::Undo);
    actUndo->setEnabled(this->document()->isUndoAvailable());
    connect(this->document(),SIGNAL(undoAvailable(bool)),actUndo,SLOT(setEnabled(bool)));
    connect(actUndo,SIGNAL(triggered()),this,SLOT(undo()));

    actRedo = new QAction(QIcon(":/images/redo.png"),QStringLiteral("�ظ�"),this);
    actRedo->setShortcuts(QKeySequence::Redo);
    actRedo->setEnabled(this->document()->isRedoAvailable());
    connect(this->document(),SIGNAL(redoAvailable(bool)),actRedo,SLOT(setEnabled(bool)));
    connect(actRedo,SIGNAL(triggered()),this,SLOT(redo()));

    actCut = new QAction(QIcon(":/images/cut.png"),QStringLiteral("����"),this);
    actCut->setShortcuts(QKeySequence::Cut);
    actCut->setEnabled(this->textCursor().hasSelection());
    connect(this,SIGNAL(copyAvailable(bool)),actCut,SLOT(setEnabled(bool)));
    connect(actCut,SIGNAL(triggered()),this,SLOT(cut()));

    actCopy = new QAction(QIcon(":/images/copy.png"),QStringLiteral("����"),this);
    actCopy->setShortcuts(QKeySequence::Copy);
    actCopy->setEnabled(this->textCursor().hasSelection());
    connect(this,SIGNAL(copyAvailable(bool)),actCopy,SLOT(setEnabled(bool)));
    connect(actCopy,SIGNAL(triggered()),this,SLOT(copy()));

    actPaste = new QAction(QIcon(":/images/paste.png"),QStringLiteral("ճ��"),this);
    actPaste->setShortcuts(QKeySequence::Paste);
    //actPaste->setEnabled(!qApp->clipboard()->text().isEmpty());
    connect(actPaste,SIGNAL(triggered()),this,SLOT(paste()));

    actDel = new QAction(QIcon(":/images/stock_delete.png"),QStringLiteral("ɾ��"),this);
    actDel->setShortcuts(QKeySequence::Delete);
    actDel->setEnabled(this->textCursor().hasSelection());
    connect(this,SIGNAL(copyAvailable(bool)),actDel,SLOT(setEnabled(bool)));
    connect(actDel,SIGNAL(triggered()),this,SIGNAL(Del()));

    actSelectAll = new QAction(QIcon(":/images/edit-select-all.png"),QStringLiteral("ȫѡ"),this);
    actSelectAll->setShortcuts(QKeySequence::SelectAll);
    connect(actSelectAll,SIGNAL(triggered()),this,SLOT(selectAll()));

    actFontChang = new QAction(QIcon(":/images/font.png"),QStringLiteral("��������"),this);
    connect(actFontChang,SIGNAL(triggered()),this,SIGNAL(fontChang()));

    actFontColor = new QAction(QIcon(":/images/textcolor.png"),QStringLiteral("������ɫ"),this);
    connect(actFontColor, SIGNAL(triggered()), this, SIGNAL(fontColor()));

}

void MdiChild::newFile()//�½�
{
    static int sequenceNumber = 1;//�ĵ����к�

    isUntitled = true;
    curFile = QStringLiteral("�ޱ���%1").arg(sequenceNumber++);
    setWindowTitle(curFile + "[*]");

}

bool MdiChild::loadFile(const QString &fileName)//��ȡ�ļ�
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
            this,QStringLiteral("���Ϊ"),curFile,"(*.txt)"";;All File(*.*)");

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

void MdiChild::documentWasModified()//�ĵ��Ƿ��޸�,"*"����ʾ
{
    setWindowModified(document()->isModified());
}

bool MdiChild::maybeSave()//�Ƿ񱣴�
{
    if (this->document()->isModified())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, QStringLiteral("����"),
                     QStringLiteral("'%1'�������޸ĵ���δ���棬�Ƿ񱣴棿")
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

void MdiChild::closeEvent(QCloseEvent *event)//��д�ر��¼�
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

void MdiChild::contextMenuEvent(QContextMenuEvent *event)//��д�Ҽ��˵��¼�
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

void MdiChild::wheelEvent(QWheelEvent *e)//��д�������¼���ʵ�ְ���Ctrl��ͬʱ�������ַŴ����С����
{
    if (e->modifiers() == Qt::ControlModifier)//�Ƿ���Ctrl��
    {
        if(e->delta() > 0 )//�Ϲ�
        {
            this->zoomIn(1);//�Ŵ�
        }
        else
        {
            this->zoomOut(1);
        }
    }
    else//ʵ���ı������¹���
    {
         if(e->delta() > 0 )//�Ϲ�
         {
             this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()-25);
         }
         else
         {
             this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()+25);
         }
    }
}
