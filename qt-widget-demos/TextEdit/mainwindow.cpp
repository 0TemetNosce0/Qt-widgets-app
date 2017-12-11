#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mymdi.h"
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QDebug>
#include <QSignalMapper>
#include <QSettings>
#include <QCloseEvent>
#include <QLabel>
#include <QMessageBox>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    actionSeparator = new QAction(this);
    actionSeparator->setSeparator(true);
    UpdateMenus();
    //有子窗口被激活，则更新菜单栏
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(UpdateMenus()));

    window_mapper = new QSignalMapper(this);//创建信号发生器
    connect(window_mapper, SIGNAL(mapped(QWidget*)), this, SLOT(set_active_sub_window(QWidget*)));//通过信号发生器设置活动窗口

    UpdateWindowMenu();//更新窗口子菜单
    connect(ui->menuW, SIGNAL(aboutToShow()), this, SLOT(UpdateWindowMenu()));//当窗口子菜单将要出现时，就触发更新窗口子菜单

    read_settings();//因为在退出窗口时，执行了write_settings()函数，即保存了退出窗口时的窗口位置，尺寸等信息。因此下次打开该程序时，其位置尺寸
                    //等信息会保留
    init_window();//初始化窗口
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
//    MyMdi *new_mdi = new MyMdi();
//   ui->mdiArea->addSubWindow(new_mdi);

    /*为什么不能使用上面的方法呢？因为上面的方法没有涉及到文档内容改变时，比如选中了文字，有过撤销操作等。
     即使我们又UpdateMenus()函数，但是关联它的connect函数的信号为当有新的活动窗口出现时，所以一旦新
     的活动窗口出现后，后面该文档内容的改变就不会触发菜单栏和工具栏对应action的变化了。
    */
    MyMdi *new_mdi = CreateMyMdi();
    new_mdi->NewFile();//新建文件
    new_mdi->show();
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this);//手动选择需要打开的文件,其实返回的file_name是包含路径名的文件名
    if(!file_name.isEmpty())
        {
            QMdiSubWindow *existing_window = FindMdiChild(file_name);
            if(existing_window) //如果该文件对应窗口已经打开
            {
                set_active_sub_window(existing_window);//设置该窗口为活动窗口,虽然set_active_sub_window是该类的成员函数，但是不能使用
                                                        //ui->来调用，冒失ui->调用的都是跟界面相关自动生成的一些量
                return ;
            }
            MyMdi *open_window = CreateMyMdi();//否则新建子窗口,且加入到多文档容器中
            if(open_window->LoadFile(file_name))
                {
                    ui->statusBar->showMessage(QStringLiteral("打开文件成功"), 2000);//状态栏显示打开文件成功，持续2秒
                    open_window->show();
                }
            else
                {
                    open_window->close();//打不开该文件时，则销毁新建的窗口
                }
        }
}

MyMdi* MainWindow::CreateMyMdi()
{
    MyMdi *child = new MyMdi();
    ui->mdiArea->addSubWindow(child);

    //根据是否可复制来设置剪切复制动作是否可用
    connect(child, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
    connect(child, SIGNAL(copyAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));

    //根据文档时否可用撤销和恢复来设置相应的撤销恢复动作是否可用
    connect(child->document(), SIGNAL(undoAvailable(bool)), ui->actionUndo, SLOT(setEnabled(bool)));
    connect(child->document(), SIGNAL(redoAvailable(bool)), ui->actionRedo, SLOT(setEnabled(bool)));

    connect(child, SIGNAL(cursorPositionChanged()), this, SLOT(ShowTextRowCol()));
    return child;
}

QMdiSubWindow* MainWindow::FindMdiChild(const QString &file_name)
{
    QString canonical_file_path = QFileInfo(file_name).canonicalFilePath();//解释过后的绝对路径
    foreach(QMdiSubWindow *window, ui->mdiArea->subWindowList())
        {
            MyMdi *my_mdi = qobject_cast<MyMdi *>(window->widget());//qobject_cast为进行强制类型转换
            if(my_mdi->CurrentFilePath() == canonical_file_path)//如果已经存在该窗口，则返回。比较的是绝对路径名+文件名
                return window;
        }
    return 0;//没找到，则返回0
}

void MainWindow::set_active_sub_window(QWidget *window)
{
    if(!window)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(window));//将当前窗口设置为多文档中的活动窗口
}

MyMdi* MainWindow::GetActiveWindow()
{
//    //获得子窗口后还需要获得其widget()
//    MyMdi *active_window = qobject_cast<MyMdi*>(ui->mdiArea->activeSubWindow()->widget());
//    if(active_window)
//        return active_window;
//    else
//        return 0;//虽然返回类型是类的指针，但是这里也可以返回0，表示的是空指针。
    /*上面的方法在后面会报内存错误*/
    if(QMdiSubWindow *active_sub_window = ui->mdiArea->activeSubWindow())
        return qobject_cast<MyMdi*>(active_sub_window->widget());//为什么还要调用widget()呢？
    else
        return 0;
}

void MainWindow::on_actionExit_triggered()
{
    qApp->closeAllWindows();//qApp为全局指针，关闭所有窗口
}

void MainWindow::on_actionSave_triggered()
{
    if(GetActiveWindow() && GetActiveWindow()->Save())
        ui->statusBar->showMessage(QStringLiteral("保存文件成功"), 2000);//状态栏显示保存成功字样2秒

}

void MainWindow::on_actionSaveAs_triggered()
{
    if(GetActiveWindow() && GetActiveWindow()->SaveAs())
        ui->statusBar->showMessage(QStringLiteral("保存文件成功"), 2000);//状态栏显示保存成功字样2秒
}

void MainWindow::on_actionCut_triggered()
{
    if(GetActiveWindow())
        GetActiveWindow()->cut();//直接调用QTextEdit这个类的cut()函数
}

void MainWindow::on_actionCopy_triggered()
{
    if(GetActiveWindow())
        GetActiveWindow()->copy();//复制
}

void MainWindow::on_actionPaste_triggered()
{
    if(GetActiveWindow())
        GetActiveWindow()->paste();//粘贴
}

void MainWindow::on_actionUndo_triggered()
{
    if(GetActiveWindow())
        GetActiveWindow()->undo();//撤销
}

void MainWindow::on_actionRedo_triggered()
{
    if(GetActiveWindow())
        GetActiveWindow()->redo();//恢复
}

void MainWindow::on_actionClose_triggered()
{
    ui->mdiArea->closeActiveSubWindow();//关闭当前活动窗口
}

void MainWindow::on_actionCloseAll_triggered()
{
    ui->mdiArea->closeAllSubWindows();//关闭所有子窗口
}

void MainWindow::on_actionTile_triggered()
{
    ui->mdiArea->tileSubWindows();//平铺窗口
}

void MainWindow::on_actionCascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();//重叠窗口
}

void MainWindow::on_actionNext_triggered()
{
    ui->mdiArea->activateNextSubWindow();//下一个窗口
}

void MainWindow::on_actionPrevious_triggered()
{
    ui->mdiArea->activatePreviousSubWindow();//上一个窗口
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, QStringLiteral("关于本软件"), QStringLiteral("参考www.yafeilinux.com网站做的一个实验"));
}

void MainWindow::on_actionAboutQt_triggered()
{
    qApp->aboutQt();//这里的qApp是QApplication对象的全局指针
}

void MainWindow::UpdateMenus()
{
    bool has_active_window; //如果有活动窗口，则为1，没有则为0
    if(GetActiveWindow())
       has_active_window = true;
    else has_active_window = false;

    //设置间隔器是否显示，貌似没有效果？
   // actionSeparator->setVisible(has_active_window);

    //下面是根据是否存在活动窗口来设置各个动作是否可用
    ui->actionSave->setEnabled(has_active_window);
    ui->actionSaveAs->setEnabled(has_active_window);
    ui->actionPaste->setEnabled(has_active_window);
    ui->actionClose->setEnabled(has_active_window);
    ui->actionCloseAll->setEnabled(has_active_window);
    ui->actionTile->setEnabled(has_active_window);
    ui->actionCascade->setEnabled(has_active_window);
    ui->actionNext->setEnabled(has_active_window);
    ui->actionPrevious->setEnabled(has_active_window);

    //只有当有活动窗口，且有文字被选中时，剪切和复制功能才可以使用
    bool has_text_selection;
  //  QTextEdit->textCursor().hasSelection()用来判断是否有文本被选中
    has_text_selection = (GetActiveWindow() && GetActiveWindow()->textCursor().hasSelection());
    ui->actionCut->setEnabled(has_text_selection);
    ui->actionCopy->setEnabled(has_text_selection);

    //有活动窗口，且系统判断可以执行撤销操作时才显示撤销可用,判断恢复操作可执行时恢复操作才可用
    ui->actionUndo->setEnabled(GetActiveWindow() && GetActiveWindow()->document()->isUndoAvailable());
    ui->actionRedo->setEnabled(GetActiveWindow() && GetActiveWindow()->document()->isRedoAvailable());
}

//状态栏上显示光标的行号和列号
void MainWindow::ShowTextRowCol()
{
    if(GetActiveWindow())
        {
            ui->statusBar->showMessage(QStringLiteral("%1行 %2列").arg(GetActiveWindow()->textCursor().blockNumber()+1).
                                       arg(GetActiveWindow()->textCursor().columnNumber()+1), 2000);
        }
}

void MainWindow::UpdateWindowMenu()
{
    ui->menuW->clear();//清空所有菜单栏
    /*重新加载已有的菜单*/
    ui->menuW->addAction(ui->actionClose);
    ui->menuW->addAction(ui->actionCloseAll);
    ui->menuW->addSeparator();
    ui->menuW->addAction(ui->actionTile);
    ui->menuW->addAction(ui->actionCascade);
    ui->menuW->addSeparator();
    ui->menuW->addAction(ui->actionNext);
    ui->menuW->addAction(ui->actionPrevious);
    //加载间隔器
    ui->menuW->addAction(actionSeparator);

    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    actionSeparator->setVisible(!windows.isEmpty());

    for(int i = 0; i < windows.size(); i++)
        {
            MyMdi *child = qobject_cast<MyMdi*>(windows.at(i)->widget());
            QString text;
            if(i < 1)//这个时候变化数字就是其快捷键
                text = QStringLiteral("&% 1%2").arg(i+1).arg(child->get_current_file_name());//内容前面加了“&”表示可以使用快捷键，为第一个字母或数字
            else
                text = QStringLiteral("%1 %2").arg(i+1).arg(child->get_current_file_name());

            QAction *action = ui->menuW->addAction(text);//添加新的菜单动作
            action->setCheckable(true);
            action->setChecked(child == GetActiveWindow());//选中当前的活动窗口
            connect(action, SIGNAL(triggered()), window_mapper, SLOT(map()));//选中action会触发槽函数发送mapped()信号
            //该函数的作用是设置一个映射，当在运行action的信号函数map()时，该函数会自动发送信号mapped()，并且会以mapped(windows.at(i))来发送
            //此时会触发在构造函数中设置的连接，其槽函数为设置活动窗口
            window_mapper->setMapping(action, windows.at(i));
        }
}

void MainWindow::init_window()
{
    setWindowTitle(QStringLiteral("Simple Mutidocument Editor"));
    ui->mainToolBar->setWindowTitle(QStringLiteral("工具栏"));//设置工具栏的标题名称，右击时才可以看到

    //当需要的时候，设置水平垂直滚动条
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ui->statusBar->showMessage(QStringLiteral("欢迎使用多文档编辑器"));

    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Box | QFrame::Sunken);//设置label的形状和阴影模式的,这里采用的box形状和凹陷模式
    label->setText(QStringLiteral("<a href = \"www.cnblogs.com/tornadomeet\">www.cnblogs.com/tornadomeet</a>"));//设置文本内容
    label->setTextFormat(Qt::RichText);//设置文本格式为富文本格式，又称多文本格式，用于跨平台使用的
    label->setOpenExternalLinks(true);//运行打开label上的链接

    ui->statusBar->addPermanentWidget(label);//将label附加到状态栏上，永久性的

    ui->actionNew->setStatusTip(QStringLiteral("创建一个文件"));
    ui->actionOpen->setStatusTip(QStringLiteral("打开一个已经存在的文件"));
    ui->actionSave->setStatusTip(QStringLiteral("保存文档到硬盘"));
    ui->actionSaveAs->setStatusTip(QStringLiteral("以新的名称保存文档"));
    ui->actionExit->setStatusTip(QStringLiteral("退出应用程序"));
    ui->actionUndo->setStatusTip(QStringLiteral("撤销先前的操作"));
    ui->actionRedo->setStatusTip(QStringLiteral("恢复先前的操作"));
    ui->actionCut->setStatusTip(QStringLiteral("剪切选中的内容到剪贴板"));
    ui->actionCopy->setStatusTip(QStringLiteral("复制选中的内容到剪贴板"));
    ui->actionPaste->setStatusTip(QStringLiteral("粘贴剪贴板的内容到当前位置"));
    ui->actionClose->setStatusTip(QStringLiteral("关闭活动窗口"));
    ui->actionCloseAll->setStatusTip(QStringLiteral("关闭所有窗口"));
    ui->actionTile->setStatusTip(QStringLiteral("平铺所有窗口"));
    ui->actionCascade->setStatusTip(QStringLiteral("层叠所有窗口"));
    ui->actionNext->setStatusTip(QStringLiteral("将焦点移动到下一个窗口"));
    ui->actionPrevious->setStatusTip(QStringLiteral("将焦点移动到前一个窗口"));
    ui->actionAbout->setStatusTip(QStringLiteral("显示本软件的介绍"));
    ui->actionAboutQt->setStatusTip(QStringLiteral("显示Qt的介绍"));

}

void MainWindow::write_settings()
{
    QSettings settings("Qt", "MyMdi");//第一个为公司的名字，第二个为软件的名字
    settings.setValue("pos", pos());//写入该窗口相对于其父窗口的位置信息
    settings.setValue("size", size());//写入窗口大小信息
}

void MainWindow::read_settings()
{
    QSettings settings("Qt", "MyMdi");
    //settings.value()第二个参数为默认值，即如果key：“pos”不存在，则返回默认值
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    move(pos); //在构造函数中才调用read_settings()函数，因此这里重新移动窗口位置和设置窗口大小
    resize(size);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    ui->mdiArea->closeAllSubWindows();
    if(ui->mdiArea->currentSubWindow())//如果还有窗口没关闭，则忽略该事件。应该是上面的语句没有全部关闭成功。
        event->ignore();
    else
    {
        write_settings();//关闭前写入窗口设置
        event->accept();//关闭
    }
}
