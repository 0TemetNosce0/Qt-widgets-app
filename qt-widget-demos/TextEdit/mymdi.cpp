
#include "mymdi.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QFileDialog>
#include <QPushButton>
#include <QCloseEvent>
#include <QMenu>

MyMdi::MyMdi(QWidget *parent) :
    QTextEdit(parent)//因为MyMdi是继承QTextEdit类的，所以它本身就是一个文本编辑类，可以编辑文字
{
    setAttribute(Qt::WA_DeleteOnClose);//加入了这句代码后，则该窗口调用close()函数不仅仅是隐藏窗口而已，同时也被销毁
    is_saved_ = false;
}

void MyMdi::NewFile()
{
    static int sequence_number = 1;
    is_saved_ = false;
    current_file_path_ = QStringLiteral("未命名文档%1.txt").arg(sequence_number++);
    setWindowTitle(current_file_path_ + "[*]");//设置文档默认标题,“[*]”在默认情况下是什么都不显示的，只有当调用setWindowModified()
    //函数的时候，会自动在由“[*]”的地方加上“*”，后面的文字会自动后移
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));//文档内容发生改变时，
    //触发槽函数DocumentWasModified().
}

QString MyMdi::CurrentFilePath()
{
    return current_file_path_;//current_file_path_是私有变量，对外隐藏起来了，但是CurrentFilePath()是公有成员函数，显示出现
}

//设置当前文件的一些信息，比如说窗口标题，该文件的路径名等
void MyMdi::SetCurrentFile(const QString &file_name)
{
    current_file_path_ = QFileInfo(file_name).canonicalFilePath();//得到解释过后的绝对路径名
    is_saved_ = true;//设置为被保存过，因为该函数是被LoadFile()函数调用的，所以肯定可以被当做是保存过的了
    document()->setModified(false);//文档没有被改过
    setWindowModified(false);//窗口不显示被更改的标志
    setWindowTitle(get_current_file_name() + "[*]");//设置窗口标题
}

bool MyMdi::LoadFile(const QString &file_name)
{
    QFile file(file_name);//建立需打开的文件对象
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        //打开失败时，输出错误信息
        QMessageBox::warning(this, "多文档编辑器", QStringLiteral("无法读取文件 %1：\n%2").arg(file_name).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);//文本流
    QApplication::setOverrideCursor(Qt::WaitCursor);//设置整个应用程序的光标形状为等待形状，因为如果文件的内容非常多时可以提醒用户
    setPlainText(in.readAll());//读取文本流中的所有内容，并显示在其窗体中
    QApplication::restoreOverrideCursor();//恢复开始时的光标状态
    SetCurrentFile(file_name);//设置标题什么的
    //注意这里发射信号用的是contentsChanged(),而不是contentsChange().
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

    return true;
}

QString MyMdi::get_current_file_name()
{
    return QFileInfo(current_file_path_).fileName();//从当前文件路径名中提取其文件名
}

void MyMdi::documentWasModified()
{
    setWindowModified(document()->isModified());//“*”显示出来
}

bool MyMdi::has_saved()
{
    if(document()->isModified())
    {
        QMessageBox box;
        box.setWindowTitle(QStringLiteral("多文档编辑器"));
        box.setText(QStringLiteral("是否保存对%1的更改？").arg(get_current_file_name()));
        box.setIcon(QMessageBox::Warning);//警告图标
        //下面是消息box上添加3个按钮，分别为yes，no，cancel
        QPushButton *yes_button = box.addButton(QStringLiteral("是"), QMessageBox::YesRole);
        QPushButton *no_button = box.addButton(QStringLiteral("否"), QMessageBox::NoRole);
        QPushButton *cancel_button = box.addButton(QStringLiteral("取消"), QMessageBox::RejectRole);
        box.exec();//在这里等待用户选择3个按钮中的一个
        if(box.clickedButton() == yes_button)
            return Save();
        else if(box.clickedButton() == no_button)
            return true;//不用保存，直接关掉
        else if(box.clickedButton() == cancel_button)
            return false;//什么都不做

    }
    return true;//要么已经保存好了，要么根本就没更改过其内容
}

bool MyMdi::Save()
{
    if(is_saved_)//已经保存过至少一次后，则说明文件的文件名等已经弄好了，直接保存内容即可。
        return SaveFile(current_file_path_);
    else return SaveAs();//第一次保存时，需要调用SaveAs
}

bool MyMdi::SaveAs()
{
    //返回的名字file_name是自己手动输入的名字，或者直接采用的是默认的名字
    QString file_name = QFileDialog::getSaveFileName(this, QStringLiteral("另存为"), current_file_path_);
    if(file_name.isEmpty())
        return false;

    return SaveFile(file_name);
}

bool MyMdi::SaveFile(const QString &file_name)
{
    QFile file(file_name);
    //即使是写入文本，也得将文本先打开
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "多文档编辑器", QStringLiteral("无法写入文件 %1：\n%2").arg(file_name).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();//以纯文本方式写入，核心函数
    QApplication::restoreOverrideCursor();
    //返回之前，也将该文件的标题，路径名等设置好。
    SetCurrentFile(file_name);
    return true;
}

void MyMdi::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu;

    //QKeySequence类是专门封装快捷键的，这里使用的是默认的快捷键操作，其快捷键位"&"号后面那个字母
    QAction *undo = menu->addAction(QStringLiteral("撤销(&U)"), this, SLOT(undo()), QKeySequence::Undo);//直接调用槽函数undo()
    undo->setEnabled(document()->isUndoAvailable());//因为该类是一个widget，所以可以直接使用document()函数

    QAction *redo = menu->addAction(QStringLiteral("恢复(&A)"), this, SLOT(redo()), QKeySequence::Redo);
    redo->setEnabled(document()->isRedoAvailable());

    menu->addSeparator();//增加分隔符

    QAction *cut = menu->addAction(QStringLiteral("剪切(&T)"), this, SLOT(cut()), QKeySequence::Cut);
    cut->setEnabled(textCursor().hasSelection());

    QAction *copy = menu->addAction(QStringLiteral("复制(&C)"), this, SLOT(copy()), QKeySequence::Copy);
    copy->setEnabled(textCursor().hasSelection());

    menu->addAction(QStringLiteral("粘贴&P"), this, SLOT(paste()), QKeySequence::Paste);

    QAction *clear = menu->addAction(QStringLiteral("清空"), this, SLOT(clear()));
    clear->setEnabled(!document()->isEmpty());//文本内容非空时就可以清除

    menu->addSeparator();//增加分隔符

    QAction *select_all = menu->addAction(QStringLiteral("全选"), this, SLOT(selectAll()), QKeySequence::SelectAll);
    select_all->setEnabled(!document()->isEmpty());

    menu->exec(event->globalPos());//获取鼠标位置，并显示菜单

    delete menu;//销毁这个菜单
}

//该函数是顶层窗口被关闭时发出的事件，是关闭窗口自带的关闭符号X
void MyMdi::closeEvent(QCloseEvent *event)//要记得加入 #include <QCloseEvent>
{
    if(has_saved())
        event->accept();//保存完毕后直接退出程序
    else
        event->ignore();

}
