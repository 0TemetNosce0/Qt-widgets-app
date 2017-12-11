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
    //���Ӵ��ڱ��������²˵���
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(UpdateMenus()));

    window_mapper = new QSignalMapper(this);//�����źŷ�����
    connect(window_mapper, SIGNAL(mapped(QWidget*)), this, SLOT(set_active_sub_window(QWidget*)));//ͨ���źŷ��������û����

    UpdateWindowMenu();//���´����Ӳ˵�
    connect(ui->menuW, SIGNAL(aboutToShow()), this, SLOT(UpdateWindowMenu()));//�������Ӳ˵���Ҫ����ʱ���ʹ������´����Ӳ˵�

    read_settings();//��Ϊ���˳�����ʱ��ִ����write_settings()���������������˳�����ʱ�Ĵ���λ�ã��ߴ����Ϣ������´δ򿪸ó���ʱ����λ�óߴ�
                    //����Ϣ�ᱣ��
    init_window();//��ʼ������
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
//    MyMdi *new_mdi = new MyMdi();
//   ui->mdiArea->addSubWindow(new_mdi);

    /*Ϊʲô����ʹ������ķ����أ���Ϊ����ķ���û���漰���ĵ����ݸı�ʱ������ѡ�������֣��й����������ȡ�
     ��ʹ������UpdateMenus()���������ǹ�������connect�������ź�Ϊ�����µĻ���ڳ���ʱ������һ����
     �Ļ���ڳ��ֺ󣬺�����ĵ����ݵĸı�Ͳ��ᴥ���˵����͹�������Ӧaction�ı仯�ˡ�
    */
    MyMdi *new_mdi = CreateMyMdi();
    new_mdi->NewFile();//�½��ļ�
    new_mdi->show();
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this);//�ֶ�ѡ����Ҫ�򿪵��ļ�,��ʵ���ص�file_name�ǰ���·�������ļ���
    if(!file_name.isEmpty())
        {
            QMdiSubWindow *existing_window = FindMdiChild(file_name);
            if(existing_window) //������ļ���Ӧ�����Ѿ���
            {
                set_active_sub_window(existing_window);//���øô���Ϊ�����,��Ȼset_active_sub_window�Ǹ���ĳ�Ա���������ǲ���ʹ��
                                                        //ui->�����ã�ðʧui->���õĶ��Ǹ���������Զ����ɵ�һЩ��
                return ;
            }
            MyMdi *open_window = CreateMyMdi();//�����½��Ӵ���,�Ҽ��뵽���ĵ�������
            if(open_window->LoadFile(file_name))
                {
                    ui->statusBar->showMessage(QStringLiteral("���ļ��ɹ�"), 2000);//״̬����ʾ���ļ��ɹ�������2��
                    open_window->show();
                }
            else
                {
                    open_window->close();//�򲻿����ļ�ʱ���������½��Ĵ���
                }
        }
}

MyMdi* MainWindow::CreateMyMdi()
{
    MyMdi *child = new MyMdi();
    ui->mdiArea->addSubWindow(child);

    //�����Ƿ�ɸ��������ü��и��ƶ����Ƿ����
    connect(child, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
    connect(child, SIGNAL(copyAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));

    //�����ĵ�ʱ����ó����ͻָ���������Ӧ�ĳ����ָ������Ƿ����
    connect(child->document(), SIGNAL(undoAvailable(bool)), ui->actionUndo, SLOT(setEnabled(bool)));
    connect(child->document(), SIGNAL(redoAvailable(bool)), ui->actionRedo, SLOT(setEnabled(bool)));

    connect(child, SIGNAL(cursorPositionChanged()), this, SLOT(ShowTextRowCol()));
    return child;
}

QMdiSubWindow* MainWindow::FindMdiChild(const QString &file_name)
{
    QString canonical_file_path = QFileInfo(file_name).canonicalFilePath();//���͹���ľ���·��
    foreach(QMdiSubWindow *window, ui->mdiArea->subWindowList())
        {
            MyMdi *my_mdi = qobject_cast<MyMdi *>(window->widget());//qobject_castΪ����ǿ������ת��
            if(my_mdi->CurrentFilePath() == canonical_file_path)//����Ѿ����ڸô��ڣ��򷵻ء��Ƚϵ��Ǿ���·����+�ļ���
                return window;
        }
    return 0;//û�ҵ����򷵻�0
}

void MainWindow::set_active_sub_window(QWidget *window)
{
    if(!window)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(window));//����ǰ��������Ϊ���ĵ��еĻ����
}

MyMdi* MainWindow::GetActiveWindow()
{
//    //����Ӵ��ں���Ҫ�����widget()
//    MyMdi *active_window = qobject_cast<MyMdi*>(ui->mdiArea->activeSubWindow()->widget());
//    if(active_window)
//        return active_window;
//    else
//        return 0;//��Ȼ�������������ָ�룬��������Ҳ���Է���0����ʾ���ǿ�ָ�롣
    /*����ķ����ں���ᱨ�ڴ����*/
    if(QMdiSubWindow *active_sub_window = ui->mdiArea->activeSubWindow())
        return qobject_cast<MyMdi*>(active_sub_window->widget());//Ϊʲô��Ҫ����widget()�أ�
    else
        return 0;
}

void MainWindow::on_actionExit_triggered()
{
    qApp->closeAllWindows();//qAppΪȫ��ָ�룬�ر����д���
}

void MainWindow::on_actionSave_triggered()
{
    if(GetActiveWindow() && GetActiveWindow()->Save())
        ui->statusBar->showMessage(QStringLiteral("�����ļ��ɹ�"), 2000);//״̬����ʾ����ɹ�����2��

}

void MainWindow::on_actionSaveAs_triggered()
{
    if(GetActiveWindow() && GetActiveWindow()->SaveAs())
        ui->statusBar->showMessage(QStringLiteral("�����ļ��ɹ�"), 2000);//״̬����ʾ����ɹ�����2��
}

void MainWindow::on_actionCut_triggered()
{
    if(GetActiveWindow())
        GetActiveWindow()->cut();//ֱ�ӵ���QTextEdit������cut()����
}

void MainWindow::on_actionCopy_triggered()
{
    if(GetActiveWindow())
        GetActiveWindow()->copy();//����
}

void MainWindow::on_actionPaste_triggered()
{
    if(GetActiveWindow())
        GetActiveWindow()->paste();//ճ��
}

void MainWindow::on_actionUndo_triggered()
{
    if(GetActiveWindow())
        GetActiveWindow()->undo();//����
}

void MainWindow::on_actionRedo_triggered()
{
    if(GetActiveWindow())
        GetActiveWindow()->redo();//�ָ�
}

void MainWindow::on_actionClose_triggered()
{
    ui->mdiArea->closeActiveSubWindow();//�رյ�ǰ�����
}

void MainWindow::on_actionCloseAll_triggered()
{
    ui->mdiArea->closeAllSubWindows();//�ر������Ӵ���
}

void MainWindow::on_actionTile_triggered()
{
    ui->mdiArea->tileSubWindows();//ƽ�̴���
}

void MainWindow::on_actionCascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();//�ص�����
}

void MainWindow::on_actionNext_triggered()
{
    ui->mdiArea->activateNextSubWindow();//��һ������
}

void MainWindow::on_actionPrevious_triggered()
{
    ui->mdiArea->activatePreviousSubWindow();//��һ������
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, QStringLiteral("���ڱ����"), QStringLiteral("�ο�www.yafeilinux.com��վ����һ��ʵ��"));
}

void MainWindow::on_actionAboutQt_triggered()
{
    qApp->aboutQt();//�����qApp��QApplication�����ȫ��ָ��
}

void MainWindow::UpdateMenus()
{
    bool has_active_window; //����л���ڣ���Ϊ1��û����Ϊ0
    if(GetActiveWindow())
       has_active_window = true;
    else has_active_window = false;

    //���ü�����Ƿ���ʾ��ò��û��Ч����
   // actionSeparator->setVisible(has_active_window);

    //�����Ǹ����Ƿ���ڻ���������ø��������Ƿ����
    ui->actionSave->setEnabled(has_active_window);
    ui->actionSaveAs->setEnabled(has_active_window);
    ui->actionPaste->setEnabled(has_active_window);
    ui->actionClose->setEnabled(has_active_window);
    ui->actionCloseAll->setEnabled(has_active_window);
    ui->actionTile->setEnabled(has_active_window);
    ui->actionCascade->setEnabled(has_active_window);
    ui->actionNext->setEnabled(has_active_window);
    ui->actionPrevious->setEnabled(has_active_window);

    //ֻ�е��л���ڣ��������ֱ�ѡ��ʱ�����к͸��ƹ��ܲſ���ʹ��
    bool has_text_selection;
  //  QTextEdit->textCursor().hasSelection()�����ж��Ƿ����ı���ѡ��
    has_text_selection = (GetActiveWindow() && GetActiveWindow()->textCursor().hasSelection());
    ui->actionCut->setEnabled(has_text_selection);
    ui->actionCopy->setEnabled(has_text_selection);

    //�л���ڣ���ϵͳ�жϿ���ִ�г�������ʱ����ʾ��������,�жϻָ�������ִ��ʱ�ָ������ſ���
    ui->actionUndo->setEnabled(GetActiveWindow() && GetActiveWindow()->document()->isUndoAvailable());
    ui->actionRedo->setEnabled(GetActiveWindow() && GetActiveWindow()->document()->isRedoAvailable());
}

//״̬������ʾ�����кź��к�
void MainWindow::ShowTextRowCol()
{
    if(GetActiveWindow())
        {
            ui->statusBar->showMessage(QStringLiteral("%1�� %2��").arg(GetActiveWindow()->textCursor().blockNumber()+1).
                                       arg(GetActiveWindow()->textCursor().columnNumber()+1), 2000);
        }
}

void MainWindow::UpdateWindowMenu()
{
    ui->menuW->clear();//������в˵���
    /*���¼������еĲ˵�*/
    ui->menuW->addAction(ui->actionClose);
    ui->menuW->addAction(ui->actionCloseAll);
    ui->menuW->addSeparator();
    ui->menuW->addAction(ui->actionTile);
    ui->menuW->addAction(ui->actionCascade);
    ui->menuW->addSeparator();
    ui->menuW->addAction(ui->actionNext);
    ui->menuW->addAction(ui->actionPrevious);
    //���ؼ����
    ui->menuW->addAction(actionSeparator);

    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    actionSeparator->setVisible(!windows.isEmpty());

    for(int i = 0; i < windows.size(); i++)
        {
            MyMdi *child = qobject_cast<MyMdi*>(windows.at(i)->widget());
            QString text;
            if(i < 1)//���ʱ��仯���־������ݼ�
                text = QStringLiteral("&% 1%2").arg(i+1).arg(child->get_current_file_name());//����ǰ����ˡ�&����ʾ����ʹ�ÿ�ݼ���Ϊ��һ����ĸ������
            else
                text = QStringLiteral("%1 %2").arg(i+1).arg(child->get_current_file_name());

            QAction *action = ui->menuW->addAction(text);//����µĲ˵�����
            action->setCheckable(true);
            action->setChecked(child == GetActiveWindow());//ѡ�е�ǰ�Ļ����
            connect(action, SIGNAL(triggered()), window_mapper, SLOT(map()));//ѡ��action�ᴥ���ۺ�������mapped()�ź�
            //�ú���������������һ��ӳ�䣬��������action���źź���map()ʱ���ú������Զ������ź�mapped()�����һ���mapped(windows.at(i))������
            //��ʱ�ᴥ���ڹ��캯�������õ����ӣ���ۺ���Ϊ���û����
            window_mapper->setMapping(action, windows.at(i));
        }
}

void MainWindow::init_window()
{
    setWindowTitle(QStringLiteral("Simple Mutidocument Editor"));
    ui->mainToolBar->setWindowTitle(QStringLiteral("������"));//���ù������ı������ƣ��һ�ʱ�ſ��Կ���

    //����Ҫ��ʱ������ˮƽ��ֱ������
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ui->statusBar->showMessage(QStringLiteral("��ӭʹ�ö��ĵ��༭��"));

    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Box | QFrame::Sunken);//����label����״����Ӱģʽ��,������õ�box��״�Ͱ���ģʽ
    label->setText(QStringLiteral("<a href = \"www.cnblogs.com/tornadomeet\">www.cnblogs.com/tornadomeet</a>"));//�����ı�����
    label->setTextFormat(Qt::RichText);//�����ı���ʽΪ���ı���ʽ���ֳƶ��ı���ʽ�����ڿ�ƽ̨ʹ�õ�
    label->setOpenExternalLinks(true);//���д�label�ϵ�����

    ui->statusBar->addPermanentWidget(label);//��label���ӵ�״̬���ϣ������Ե�

    ui->actionNew->setStatusTip(QStringLiteral("����һ���ļ�"));
    ui->actionOpen->setStatusTip(QStringLiteral("��һ���Ѿ����ڵ��ļ�"));
    ui->actionSave->setStatusTip(QStringLiteral("�����ĵ���Ӳ��"));
    ui->actionSaveAs->setStatusTip(QStringLiteral("���µ����Ʊ����ĵ�"));
    ui->actionExit->setStatusTip(QStringLiteral("�˳�Ӧ�ó���"));
    ui->actionUndo->setStatusTip(QStringLiteral("������ǰ�Ĳ���"));
    ui->actionRedo->setStatusTip(QStringLiteral("�ָ���ǰ�Ĳ���"));
    ui->actionCut->setStatusTip(QStringLiteral("����ѡ�е����ݵ�������"));
    ui->actionCopy->setStatusTip(QStringLiteral("����ѡ�е����ݵ�������"));
    ui->actionPaste->setStatusTip(QStringLiteral("ճ������������ݵ���ǰλ��"));
    ui->actionClose->setStatusTip(QStringLiteral("�رջ����"));
    ui->actionCloseAll->setStatusTip(QStringLiteral("�ر����д���"));
    ui->actionTile->setStatusTip(QStringLiteral("ƽ�����д���"));
    ui->actionCascade->setStatusTip(QStringLiteral("������д���"));
    ui->actionNext->setStatusTip(QStringLiteral("�������ƶ�����һ������"));
    ui->actionPrevious->setStatusTip(QStringLiteral("�������ƶ���ǰһ������"));
    ui->actionAbout->setStatusTip(QStringLiteral("��ʾ������Ľ���"));
    ui->actionAboutQt->setStatusTip(QStringLiteral("��ʾQt�Ľ���"));

}

void MainWindow::write_settings()
{
    QSettings settings("Qt", "MyMdi");//��һ��Ϊ��˾�����֣��ڶ���Ϊ���������
    settings.setValue("pos", pos());//д��ô���������丸���ڵ�λ����Ϣ
    settings.setValue("size", size());//д�봰�ڴ�С��Ϣ
}

void MainWindow::read_settings()
{
    QSettings settings("Qt", "MyMdi");
    //settings.value()�ڶ�������ΪĬ��ֵ�������key����pos�������ڣ��򷵻�Ĭ��ֵ
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    move(pos); //�ڹ��캯���вŵ���read_settings()������������������ƶ�����λ�ú����ô��ڴ�С
    resize(size);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    ui->mdiArea->closeAllSubWindows();
    if(ui->mdiArea->currentSubWindow())//������д���û�رգ�����Ը��¼���Ӧ������������û��ȫ���رճɹ���
        event->ignore();
    else
    {
        write_settings();//�ر�ǰд�봰������
        event->accept();//�ر�
    }
}
