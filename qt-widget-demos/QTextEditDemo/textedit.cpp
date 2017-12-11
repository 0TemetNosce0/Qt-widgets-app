#include "textedit.h"
#include "ui_textedit.h"
#include "mdichild.h"
#include "find_replace.h"
#include "ui_find_replace.h"//�Ӵ��ļ����ܲ���ui
#include <QColor>
#include <QTimer>
#include <QMimeData>
#include <QSettings>
#include <QComboBox>
#include <QFileInfo>
#include <QDateTime>
#include <QTextList>
#include <QFontDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QPrintDialog>
#include <QColorDialog>
#include <QMdiSubWindow>
#include <QSignalMapper>
#include <QDragEnterEvent>
#include <QPrintPreviewDialog>

TextEdit::TextEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEdit)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);

    // Q_FOREACH (QTabBar* tab, ui->mdiArea->findChildren())//QMdiArea tabs with close button
    // {
    //QTabBar* tab;
    //   tab->setTabsClosable(true);
    //   connect(tab, SIGNAL(tabCloseRequested(int)),
    //              this, SLOT(closeTab(int)));
    //}

    findReplace = new Find_Replace(this);//�����滻
    /**�����滻��صĹ���**/
    connect(findReplace->ui->cancleButtonF,SIGNAL(clicked()),findReplace,SLOT(close()));
    connect(findReplace->ui->nextButtonF,SIGNAL(clicked()),this,SLOT(findNextF()));//��������
    connect(findReplace->ui->cancleButtonR,SIGNAL(clicked()),findReplace,SLOT(close()));
    connect(findReplace->ui->nextButtonR,SIGNAL(clicked()),this,SLOT(findNextR()));
    connect(findReplace->ui->pushButtonReplace,SIGNAL(clicked()),this,SLOT(replace()));
    connect(findReplace->ui->pushButtonReplaceAll,SIGNAL(clicked()),this,SLOT(replaceAll()));

    readSettings();//��ȡ�ϴιرմ���ʱ���ڵĴ�С��λ��
    this->setCentralWidget(ui->mdiArea);//�����ĵ���������Ϊ���Ĳ���

    ui->mdiArea->setViewMode(QMdiArea::TabbedView);//��Ϊ��ǩ����ʾģʽ
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(updateMenus()));

    QTimer *timer = new QTimer(this);//�½���ʱ��
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));//������ʱ�������źź���Ӧ�Ĳۺ���
    timer->start(1000);//��ʱ����ʼ��ʱ������1000��ʾ1000ms��1��

    actGrp = new QActionGroup(this);//���Ķ��뷽ʽ
    left = new QAction(QIcon(":/images/textleft.png"),QStringLiteral("�����"),actGrp);
    left->setCheckable(true);
    center = new QAction(QIcon(":/images/textcenter.png"),QStringLiteral("���ж���"),actGrp);
    center->setCheckable(true);
    right = new QAction(QIcon(":/images/textright.png"),QStringLiteral("�Ҷ���"),actGrp);
    right->setCheckable(true);
    justify = new QAction(QIcon(":/images/textjustify.png"),QStringLiteral("���˶���"),actGrp);
    justify->setCheckable(true);

    toolBar = new QToolBar(this);//�½�������
    this->addToolBar(toolBar);
    toolBar->addActions(actGrp->actions());//���빤������
    ui->menu_O->addSeparator();
    ui->menu_O->addActions(actGrp->actions());//���롰��ʽ���˵���

    connect(actGrp,SIGNAL(triggered(QAction*)),this,SLOT(slotAlignment(QAction*)));//�������뷽ʽ���޸�

    //�ı�����
    QLabel *listAlign = new QLabel(QStringLiteral("����"));
    listBox = new QComboBox(toolBar);
    //�����ѡ������ʽ
    listBox->addItem(QStringLiteral("Standard"));
    listBox->addItem(QStringLiteral("Bullet List (Disc)"));
    listBox->addItem(QStringLiteral("Bullet List (Circle)"));
    listBox->addItem(QStringLiteral("Bullet List (Square)"));
    listBox->addItem(QStringLiteral("1 2 3 ... (Decimal)"));
    listBox->addItem(QStringLiteral("a b c ... (Alpha lower)"));
    listBox->addItem(QStringLiteral("A B C ... (Alpha upper)"));
    listBox->addItem(QStringLiteral("�� �� �� ...(Roman lower)"));
    listBox->addItem(QStringLiteral("�� �� �� ... (Roman upper)"));
    toolBar->addSeparator();
    toolBar->addWidget(listAlign);
    toolBar->addWidget(listBox);

    connect(listBox,SIGNAL(activated(int)),this,SLOT(slotList(int)));//��������

    actViewMode = new QActionGroup(this);//��ͼģʽ
    tabbedView = new QAction(QStringLiteral("��ǩģʽ(&T)"),actViewMode);
    tabbedView->setCheckable(true);
    tabbedView->setChecked(true);//Ĭ��ѡ��Ϊ��ǩģʽ
    windowView = new QAction(QStringLiteral("����ģʽ(&W)"),actViewMode);
    windowView->setCheckable(true);
    ui->menu_ViewMode->addActions(actViewMode->actions());
    connect(actViewMode,SIGNAL(triggered(QAction*)),this,SLOT(slotViewMode(QAction*)));

    windowMapper = new QSignalMapper(this);//�źŷ���ת����
    connect(windowMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(setActiveSubWindow(QWidget*)));
    connect(ui->menu_SelectW,SIGNAL(aboutToShow()),this,SLOT(updatemenuSelectw()));//���¡�ѡ�񴰿ڡ��˵�

    for(int i = 0; i < MaxRecentFiles; i++)//����������ļ��б�
    {
        recentFileActs[i] = new QAction(this);
        ui->menu_RecentFile->addAction(recentFileActs[i]);
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i],SIGNAL(triggered()),this,SLOT(openRecentFile()));
    }
    updateRecentFiles();//����������ļ��б�

    initStatusbar();//��ʼ��״̬��
    updateMenus();//���²˵�����
    //this->setGeometry(250,100,820,600);
}

TextEdit::~TextEdit()
{
    delete ui;
}

void TextEdit::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TextEdit::slotViewMode(QAction *a)//��ͼģʽ
{
    if(a == tabbedView)
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);//��Ϊ��ǩ����ʾģʽ
    if(a == windowView)
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);//��Ϊ������ʾģʽ
    //ֻ���ڴ���ģʽ��ƽ�̺Ͳ����������
    bool isSubWindowView = (activeMdiChild() && ui->mdiArea->viewMode() == QMdiArea::SubWindowView);
    ui->action_Cascade->setEnabled(isSubWindowView);
    ui->action_Tile->setEnabled(isSubWindowView);
}

void TextEdit::openRecentFile()//������ļ��б�ָ���ļ�
{
    QAction *action = qobject_cast<QAction *>(sender());
    if(action)
    {
        QString canonicalFilePath = QFileInfo(action->data().toString()).canonicalFilePath();
        bool hasOpened = false;//�Ƿ��Ѿ��򿪸��ļ�
        foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
        {
            MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
            if( mdiChild->currentFile() == canonicalFilePath)
            {
                hasOpened = true;
                ui->mdiArea->setActiveSubWindow(window);
                continue;
            }
        }
        if(!hasOpened)//���δ����򿪸��ļ�
        {
            MdiChild *child = new MdiChild;
            ui->mdiArea->addSubWindow(child);
            if(child->loadFile(action->data().toString()))
            {
                child->setVisible(true);
                secondStatuslabel->setText(QStringLiteral("�򿪳ɹ�"));
                initConnect();//��ʼ������
            }
        }
    }
}

void TextEdit::updateRecentFiles()//����������ļ��б�
{
    QSettings settings("QT","MDI example");
    QStringList files = settings.value("recentFiles").toStringList();

    int numRecentFiles = qMin(files.size(),(int)MaxRecentFiles);
    for(int i= 0;i < numRecentFiles;i++)
    {
        QString text = QStringLiteral("&%1 %2").arg(i+1).arg(files[i]);
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for(int i = numRecentFiles;i < MaxRecentFiles; ++i)
        recentFileActs[i]->setVisible(false);

}
void TextEdit::updateMenus()//���²˵����ͱ������ʾ״̬��
{
    bool hasMdiChild = (activeMdiChild() != 0);
    ui->action_AllSelect->setEnabled(hasMdiChild);
    ui->action_Asave->setEnabled(hasMdiChild);
    ui->action_Clear->setEnabled(hasMdiChild);
    ui->action_Find->setEnabled(hasMdiChild);
    ui->action_Font->setEnabled(hasMdiChild);
    ui->action_FontColor->setEnabled(hasMdiChild);
    ui->action_Paste->setEnabled(hasMdiChild);
    ui->action_Undo->setEnabled(hasMdiChild && activeMdiChild()->document()->isUndoAvailable());
    ui->action_Redo->setEnabled(hasMdiChild && activeMdiChild()->document()->isRedoAvailable());
    ui->action_Save->setEnabled(hasMdiChild);
    ui->action_PDF->setEnabled(hasMdiChild);
    ui->action_Print->setEnabled(hasMdiChild);
    ui->action_PrintPreview->setEnabled(hasMdiChild);
    ui->action_Switch->setEnabled(hasMdiChild);
    ui->action_HighLightShow->setEnabled(hasMdiChild);
    ui->action_AllClose->setEnabled(hasMdiChild);
    ui->action_Close->setEnabled(hasMdiChild);
    ui->action_Replace->setEnabled(hasMdiChild);
    ui->action_zoomIn->setEnabled(hasMdiChild);
    ui->action_zoomOut->setEnabled(hasMdiChild);
    actGrp->setEnabled(hasMdiChild);//���뷽ʽ
    listBox->setEnabled(hasMdiChild);//����
    ui->menu_SelectW->setEnabled(hasMdiChild);//��ѡ�񴰿ڡ��˵�
    firstStatuslabel->setText(hasMdiChild? firstStatuslabel->text():QStringLiteral("��ӭʹ�ö��ĵ��ı��༭��"));
    secondStatuslabel->setText(hasMdiChild? secondStatuslabel->text():QStringLiteral("yafeilinux����"));

    bool hasSelection = (activeMdiChild() &&
                         activeMdiChild()->textCursor().hasSelection());
    ui->action_Copy->setEnabled(hasSelection);
    ui->action_Cut->setEnabled(hasSelection);
    ui->action_Del->setEnabled(hasSelection);

    bool isSubWindowView = (activeMdiChild() && ui->mdiArea->viewMode() == QMdiArea::SubWindowView);
    ui->action_Cascade->setEnabled(isSubWindowView);//ֻ���ڴ���ģʽ��ƽ�̺Ͳ����������
    ui->action_Tile->setEnabled(isSubWindowView);

    ui->action_PreviousW->setEnabled(ui->mdiArea->subWindowList().count() > 1);//����������1ʱ����
    ui->action_NextW->setEnabled(ui->mdiArea->subWindowList().count() > 1);

    if(hasMdiChild)
    {
        this->setWindowTitle(ui->mdiArea->currentSubWindow()->windowTitle());//���±���������ʾ
        if(!activeMdiChild()->extraSelections().empty())//�жϵ�ǰ���ĵ��Ƿ������ʾ
            ui->action_HighLightShow->setChecked(true);
        else
            ui->action_HighLightShow->setChecked(false);

        if(activeMdiChild()->wordWrapMode() == QTextOption::WrapAnywhere)//�жϵ�ǰ���ĵ��Ƿ��Զ�����
            ui->action_Switch->setChecked(true);
        else
            ui->action_Switch->setChecked(false);
    }

}

void TextEdit::updatemenuSelectw()//���¡�ѡ�񴰿ڡ��˵�
{
    //�ڲ˵���"ѡ�񴰿�"��ʾ��ǰ�򿪵Ĵ���
    ui->menu_SelectW->clear();//ÿ�θ���ǰ���
    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    for (int i = 0; i < windows.size(); ++i)
    {
        MdiChild *child = qobject_cast<MdiChild *>(windows.at(i)->widget());
        QString text;
        if (i < 9)
        {
            text = QStringLiteral("&%1 %2").arg(i + 1)
                    .arg(child->windowTitle().remove("[*]"));
        }
        else
        {
            text = QStringLiteral("%1 %2").arg(i + 1)
                    .arg(child->windowTitle().remove("[*]"));
        }
        QAction *action  = ui->menu_SelectW->addAction(text);
        action->setCheckable(true);
        action->setChecked(child == activeMdiChild());
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows.at(i));
    }
}

void TextEdit::initStatusbar()//��ʼ��״̬��
{
    QStatusBar* bar = ui->statusBar; //��ȡ״̬��
    firstStatuslabel = new QLabel; //�½���ǩ
    firstStatuslabel->setMinimumSize(200,20); //���ñ�ǩ��С�ߴ�
    firstStatuslabel->setFrameShape(QFrame::WinPanel); //���ñ�ǩ��״
    firstStatuslabel->setFrameShadow(QFrame::Sunken); //���ñ�ǩ��Ӱ

    secondStatuslabel = new QLabel; //2
    secondStatuslabel->setMinimumSize(200,20);
    secondStatuslabel->setFrameShape(QFrame::WinPanel);
    secondStatuslabel->setFrameShadow(QFrame::Sunken);

    thirdStatuslabel = new QLabel;//3
    thirdStatuslabel->setMinimumSize(200,20);
    thirdStatuslabel->setFrameShape(QFrame::WinPanel);
    thirdStatuslabel->setFrameShadow(QFrame::Sunken);

    bar->addWidget(firstStatuslabel);
    bar->addWidget(secondStatuslabel);
    bar->addWidget(thirdStatuslabel);

    firstStatuslabel->setText(QStringLiteral("��ӭʹ�ö��ĵ��ı��༭��")); //��ʼ������
    secondStatuslabel->setText(QStringLiteral("yafeilinux����"));
    thirdStatuslabel->setText(QStringLiteral("0000-00-00 00:00::00 ���� "));
}

void TextEdit::timerUpDate()//��ʱ������ʱ�����ʾ
{
    QDateTime time = QDateTime::currentDateTime();//��ȡϵͳ���ڵ�ʱ��
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");//����ϵͳʱ����ʾ��ʽ
    thirdStatuslabel->setText(str); //�ڱ�ǩ����ʾʱ��
}

void TextEdit::doCursorchanged()//��ȡ���λ�ã�����ʾ��״̬��
{
    QTextCursor cursor = activeMdiChild()->textCursor();
    //cursor.select(QTextCursor::LineUnderCursor);
    int rowNum = cursor.blockNumber(); //��ȡ��������е��к�
    int colNum = cursor.columnNumber(); //��ȡ��������е��к�
    firstStatuslabel->setText(QStringLiteral("%1�� %2��").arg(rowNum+1).arg(colNum+1));//��״̬����ʾ���λ��

    //���Ķ��밴ť��״̬
    if(activeMdiChild()->alignment() == (Qt::AlignLeft | Qt::AlignAbsolute) )
        left->setChecked(true);
    if(activeMdiChild()->alignment() == Qt::AlignHCenter)
        center->setChecked(true);
    if(activeMdiChild()->alignment() == Qt::AlignJustify)
        justify->setChecked(true);
    if(activeMdiChild()->alignment() == (Qt::AlignRight | Qt::AlignAbsolute) )
        right->setChecked(true);

    highlightCurrentLine(); //�������λ�����������ʾ
}

void TextEdit::documentWasModified()//�ĵ����ڱ��޸�
{
    secondStatuslabel->setText(QStringLiteral("�����޸�"));
}

void TextEdit::slotAlignment(QAction *a)//���Ķ��뷽ʽ
{
    if(a == left)
        activeMdiChild()->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == center)
        activeMdiChild()->setAlignment(Qt::AlignHCenter);
    else if (a == right)
        activeMdiChild()->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == justify)
        activeMdiChild()->setAlignment(Qt::AlignJustify);
}

void TextEdit::slotList(int index)//�ı�����
{
    QTextCursor cursor =  activeMdiChild()->textCursor();
    if(index != 0)
    {
        QTextListFormat::Style style = QTextListFormat::ListDisc;
        switch(index)
        {
        default:
        case 1:
            style = QTextListFormat::ListDisc;
            break;
        case 2:
            style = QTextListFormat::ListCircle;
            break;
        case 3:
            style = QTextListFormat::ListSquare;
            break;
        case 4:
            style = QTextListFormat::ListDecimal;
            break;
        case 5:
            style = QTextListFormat::ListLowerAlpha;
            break;
        case 6:
            style = QTextListFormat::ListUpperAlpha;
            break;
        case 7:
            style = QTextListFormat::ListLowerRoman;
            break;
        case 8:
            style = QTextListFormat::ListUpperRoman;
            break;
        }
        cursor.beginEditBlock();//��end֮������в����൱��һ������
        QTextBlockFormat blockFmt = cursor.blockFormat();
        QTextListFormat listFmt;
        if (cursor.currentList())//�Ƿ�������
        {
            listFmt = cursor.currentList()->format();
        }
        else
        {
            listFmt.setIndent(blockFmt.indent() + 1);//�ڵ�ǰ���������Ļ����ϼ�1
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
        cursor.endEditBlock();
    }
    else
    {
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void TextEdit::on_action_New_triggered()//�½�
{
    MdiChild *child = new MdiChild;
    ui->mdiArea->addSubWindow(child);
    child->newFile();
    child->setVisible(true);
    secondStatuslabel->setText(QStringLiteral("�½��ɹ�"));
    initConnect();//��ʼ������
}

void TextEdit::on_action_Open_triggered()//��
{
    QString fileName = QFileDialog::getOpenFileName//���Ҫ�򿪵��ļ���
            (this,"open file",NULL,"(*.txt)"";;All File(*.*)"";;(*.html)");
    if(!fileName.isEmpty())
    {
        QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
        bool hasOpened = false;//�Ƿ��Ѿ��򿪸��ļ�
        foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
        {
            MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
            if( mdiChild->currentFile() == canonicalFilePath)
            {
                hasOpened = true;
                ui->mdiArea->setActiveSubWindow(window);
                continue;
            }
        }
        if(!hasOpened)
        {
            MdiChild *child = new MdiChild;
            ui->mdiArea->addSubWindow(child);
            if(child->loadFile(fileName))
            {
                child->setVisible(true);
                secondStatuslabel->setText(QStringLiteral("�򿪳ɹ�"));
            }
            else
                child->close();

            QSettings settings("QT","MDI example");
            QStringList files = settings.value("recentFiles").toStringList();
            files.removeAll(fileName);
            files.prepend(fileName);
            while(files.size() > MaxRecentFiles)
                files.removeLast();
            settings.setValue("recentFiles",files);
            updateRecentFiles();
            initConnect();//��ʼ������
        }
    }
}

void TextEdit::on_action_Save_triggered()//����
{
    if(activeMdiChild() && activeMdiChild()->save())
    {
        secondStatuslabel->setText(QStringLiteral("����ɹ�"));
    }
}

MdiChild *TextEdit::activeMdiChild()//���ؼ���״̬���Ӵ���ָ��
{
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
    {
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    }
    return 0;
}

void TextEdit::on_action_Asave_triggered()//���Ϊ
{
    if (activeMdiChild() && activeMdiChild()->saveAs())
    {
        secondStatuslabel->setText(QStringLiteral("���Ϊ�ɹ�"));
    }
}

void TextEdit::on_action_Quit_triggered()//�˳�
{
    qApp->closeAllWindows();
}

void TextEdit::on_action_Font_triggered()//��������
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,activeMdiChild()->font(),this,"font");
    if(ok)
    {
        activeMdiChild()->setCurrentFont(font);//current����undo
    }
}

void TextEdit::on_action_FontColor_triggered()//������ɫ����
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid())
    {
        activeMdiChild()->setTextColor(color);
    }
}

void TextEdit::on_action_Print_triggered()//��ӡ�ĵ�
{
    QPrinter printer;
    QPrintDialog dlg(&printer,ui->mdiArea->activeSubWindow());
    if(dlg.exec() == QDialog::Accepted)
    {
        /****/
    }
}

void TextEdit::on_action_PrintPreview_triggered()//��ӡԤ��
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer,this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)),
            SLOT(printPreview(QPrinter*)));
    preview.exec();
}

void TextEdit::printPreview(QPrinter *printer)//��ӡԤ��
{
#ifdef QT_NO_PRINTER
    Q_UNUSEd(printer);
#else
    // MdiChild *child = qobject_cast<MdiChild *>(ui->mdiArea->activeSubWindow()->widget());
    //child->print(printer);
    activeMdiChild()->print(printer);
#endif
}

void TextEdit::on_action_PDF_triggered()//���PDF�ĵ�
{
    if(activeMdiChild())
    {
        QString fileName = QFileDialog::getSaveFileName(
                    this, "Export PDF",activeMdiChild()->curFile + ".pdf","*.pdf");
        if (!fileName.isEmpty())
        {
            if (QFileInfo(fileName).suffix().isEmpty())
            {
                fileName.append(".pdf");
            }

            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);
            activeMdiChild()->document()->print(&printer);
            secondStatuslabel->setText(QStringLiteral("���PDF�ĵ��ɹ�"));
        }
    }
}

void TextEdit::on_action_Undo_triggered()//����
{
    activeMdiChild()->undo();
}

void TextEdit::on_action_Redo_triggered()//�ظ�
{
    activeMdiChild()->redo();
}

void TextEdit::on_action_Cut_triggered()//����
{
    activeMdiChild()->cut();
}

void TextEdit::on_action_Copy_triggered()//����
{
    activeMdiChild()->copy();
}

void TextEdit::on_action_Paste_triggered()//ճ��
{
    activeMdiChild()->paste();
}

void TextEdit::on_action_Del_triggered()//ɾ��ѡ�е�����
{
    activeMdiChild()->textCursor().removeSelectedText();
}

void TextEdit::on_action_AllSelect_triggered()//ȫѡ
{
    activeMdiChild()->selectAll();
}

void TextEdit::on_action_Clear_triggered()//���
{
    activeMdiChild()->clear();
}

void TextEdit::on_action_Switch_triggered(bool checked)//�Ƿ��Զ�����
{
    if(checked == true)
    {
        activeMdiChild()->setWordWrapMode(QTextOption::WrapAnywhere);
    }
    else
    {
        activeMdiChild()->setWordWrapMode(QTextOption::NoWrap);
    }
}


void TextEdit::on_action_ToobarShow_triggered(bool checked)//�Ƿ���ʾ������
{
    if(checked == true)
    {
        ui->mainToolBar->show();
        toolBar->show();
    }
    else
    {
        ui->mainToolBar->hide();
        toolBar->hide();
    }
}

void TextEdit::on_action_StatusBarShow_triggered(bool checked)//�Ƿ���ʾ״̬��
{
    if(checked == true)
    {
        ui->statusBar->show();
    }
    else
    {
        ui->statusBar->hide();
    }
}

void TextEdit::on_action_HighLightShow_triggered(bool checked)//�Ƿ������ʾ��ǰ�༭����
{
    if(checked == true)
    {
        highlightCurrentLine();
    }
    else
    {
        QList<QTextEdit::ExtraSelection> extraSelections;
        activeMdiChild()->setExtraSelections(extraSelections);
        activeMdiChild()->extraSelections().clear();
    }
}

void TextEdit::highlightCurrentLine()//������ʾ��ǰ�༭����
{
    if(ui->action_HighLightShow->isChecked() == true)//�Ƿ�ѡ�и�����ʾ
    {
        QList<QTextEdit::ExtraSelection> extraSelections;

        if (!activeMdiChild()->isReadOnly())
        {
            QTextEdit::ExtraSelection selection;

            QColor lineColor = QColor(Qt::yellow).lighter(160);

            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, true);
            selection.cursor = activeMdiChild()->textCursor();
            selection.cursor.clearSelection();
            extraSelections.append(selection);
        }
        activeMdiChild()->setExtraSelections(extraSelections);
    }
}


void TextEdit::on_action_Tile_triggered()//ƽ��
{
    ui->mdiArea->tileSubWindows();
}

void TextEdit::on_action_Cascade_triggered()//���
{
    ui->mdiArea->cascadeSubWindows();
}

void TextEdit::on_action_NextW_triggered()//��һ����
{
    ui->mdiArea->activateNextSubWindow();
}

void TextEdit::on_action_PreviousW_triggered()//ǰһ����
{
    ui->mdiArea->activatePreviousSubWindow();
}

void TextEdit::on_action_Close_triggered()//�رյ�ǰ����
{
    ui->mdiArea->closeActiveSubWindow();
}

void TextEdit::on_action_AllClose_triggered()//�ر����д���
{
    ui->mdiArea->closeAllSubWindows();
}

void TextEdit::on_action_About_triggered()//����
{
    QMessageBox box;
    box.setWindowTitle(QStringLiteral("����"));
    box.setIcon(QMessageBox::Information);
    box.setText(QStringLiteral("�������yafeilinux�������ǿ�Դ�������������\n���������ϴ��������������أ����벻Ҫ������ҵ��;!\n\n���ĵ��ı��༭��V1.0 Beta\n���⽻����BUG��������ϵ��www.yafeilinux.com"));
    box.addButton(QStringLiteral("ȷ��"),QMessageBox::AcceptRole);//�����Զ���İ�ť
    if(box.exec() == QMessageBox::Accepted)
    {
        box.close();
    }
}

void TextEdit::on_action_AboutQt_triggered()//����Qt
{
    QMessageBox::aboutQt(this,QStringLiteral("����Qt"));
}

void TextEdit::setActiveSubWindow(QWidget *window)//�����
{
    if (!window)
    {
        return;
    }
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void TextEdit::readSettings()//��ȡ�����ڵĴ�С��λ����Ϣ
{
    QSettings settings("yafeilinux", "MDI Example");
    QPoint pos = settings.value("pos", QPoint(250, 100)).toPoint();
    QSize size = settings.value("size", QSize(820, 600)).toSize();
    move(pos);
    resize(size);
}

void TextEdit::writeSettings()//��¼�����ڵĴ�С��λ����Ϣ
{
    QSettings settings("yafeilinux","MDI Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void TextEdit::closeEvent(QCloseEvent *event)//��д�ر��¼�
{
    ui->mdiArea->closeAllSubWindows();
    if (ui->mdiArea->currentSubWindow())
    {
        event->ignore();
    }
    else
    {
        writeSettings();
        event->accept();
    }
}

void TextEdit::doFind(QString findText)//���ҵ�ʵ�ֺ���
{
    if( (!senceF) && (!upFindF) )//�����ִ�Сд��������
    {
        if(!activeMdiChild()->find(findText))
        {
            QMessageBox::warning(this,QStringLiteral("����"),QStringLiteral("�Ҳ��� %1").arg(findText));
        }
    }
    else if( senceF && (!upFindF) )//���ִ�Сд��������
    {
        if(!activeMdiChild()->find(findText,QTextDocument::FindCaseSensitively))
        {
            QMessageBox::warning(this,QStringLiteral("����"),QStringLiteral("�Ҳ��� %1").arg(findText));
        }
    }
    else if( (!senceF) && upFindF )//�����ִ�Сд����ǰ����
    {
        if(!activeMdiChild()->find(findText,QTextDocument::FindBackward))
        {
            QMessageBox::warning(this,QStringLiteral("����"),QStringLiteral("�Ҳ��� %1").arg(findText));
        }
    }
    else if( senceF && upFindF)//���ִ�Сд����ǰ����
    {
        if(!activeMdiChild()->find(findText, QTextDocument::FindCaseSensitively | QTextDocument::FindBackward))
        {
            QMessageBox::warning(this,QStringLiteral("����"),QStringLiteral("�Ҳ��� %1").arg(findText));
        }
    }
}

void TextEdit::on_action_Find_triggered()//��ʾ���ҶԻ���
{
    findReplace->show();
    findReplace->ui->tabWidget->setCurrentWidget(findReplace->ui->find);//��ʾ����ҳ��
    findReplace->ui->lineEditF->setFocus();
    secondStatuslabel->setText(QStringLiteral("���ڲ���"));

}

void TextEdit::findNextF()//�����ҡ��ġ�������һ����
{
    QString findText = findReplace->ui->lineEditF->text();
    senceF = findReplace->ui->checkBoxSenceF->isChecked();//�Ƿ����ִ�Сд��1���� 0������
    upFindF = findReplace->ui->radioButtonUpF->isChecked();//��ǰ���������ң�1��ǰ 0���

    doFind(findText);

}

void TextEdit::on_action_Replace_triggered()//��ʾ�滻�Ի���
{
    findReplace->show();
    findReplace->ui->tabWidget->setCurrentWidget(findReplace->ui->replace);//��ʾ�滻ҳ��
    findReplace->ui->lineEditR->setFocus();
    secondStatuslabel->setText(QStringLiteral("�����滻"));
}

void TextEdit::findNextR()//���滻���ġ�������һ����
{
    QString findText = findReplace->ui->lineEditR->text();
    senceF = findReplace->ui->checkBoxSenceR->isChecked();//�Ƿ����ִ�Сд��1���� 0������
    upFindF = findReplace->ui->radioButtonUpR->isChecked();//��ǰ���������ң�1��ǰ 0���

    doFind(findText);
}

void TextEdit::replace()//�滻
{   
    QString findText = findReplace->ui->lineEditR->text();//Ҫ���ҵ�����
    QString replaceText = findReplace->ui->lineEditreplace->text();//Ҫ�滻������

    if(activeMdiChild()->textCursor().selectedText() == findText)
    {
        QTextCursor textCursor = activeMdiChild()->textCursor();
        textCursor.insertText(replaceText);
    }

    findNextR();//���滻���ġ�������һ����
}

void TextEdit::replaceAll()//ȫ���滻
{
    QTextCursor textCursor = activeMdiChild()->textCursor();
    textCursor.setPosition(0,QTextCursor::MoveAnchor);//���ù���������µ��ʼ
    activeMdiChild()->setTextCursor(textCursor);
    findReplace->ui->radioButtonUpR->setChecked(false);//ȷ��������
    senceF = findReplace->ui->checkBoxSenceR->isChecked();//�Ƿ����ִ�Сд��1���� 0������

    QString findText = findReplace->ui->lineEditR->text();//Ҫ���ҵ�����
    QString replaceText = findReplace->ui->lineEditreplace->text();//Ҫ�滻������

    while(doReplaceAllFind(findText))//ѭ���滻
    {
        if(activeMdiChild()->textCursor().selectedText().toLower() == findText.toLower())
        {
            QTextCursor textCursor = activeMdiChild()->textCursor();//�������textCursor��һ��
            textCursor.insertText(replaceText);
        }
    }
}
bool TextEdit::doReplaceAllFind(QString findText)//ȫ���滻�Ĳ���ʵ�ֺ���
{
    if( (!senceF) && (!upFindF) )//�����ִ�Сд��������
    {
        if(!activeMdiChild()->find(findText))
        {
            return false;
        }
    }
    else if( senceF && (!upFindF) )//���ִ�Сд��������
    {
        if(!activeMdiChild()->find(findText,QTextDocument::FindCaseSensitively))
        {
            return false;
        }
    }
    return true;
}

void TextEdit::on_action_zoomIn_triggered()//�Ŵ󣬶�ͼƬ�����������������û��Ч����
{
    activeMdiChild()->zoomIn(2);
}

void TextEdit::on_action_zoomOut_triggered()//��С
{
    activeMdiChild()->zoomOut(2);
}

void TextEdit::dragEnterEvent(QDragEnterEvent *e)//�Ͻ��¼�
{
    if(e->mimeData()->hasFormat("text/uri-list"))
    {
        e->acceptProposedAction();
    }
}

void TextEdit::dropEvent(QDropEvent *event)//�����¼�
{
    QList<QUrl> urls = event->mimeData()->urls();

    if (urls.isEmpty())
    {
        return;
    }

    QString fileName = urls.first().toLocalFile();

    if (fileName.isEmpty())
    {
        return;
    }

    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
    bool hasOpened = false;//�Ƿ��Ѿ��򿪸��ļ�
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
    {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());

        if( mdiChild->currentFile() == canonicalFilePath)
        {
            hasOpened = true;
            ui->mdiArea->setActiveSubWindow(window);
            continue;
        }
    }

    if(!hasOpened)
    {
        MdiChild *child = new MdiChild;
        ui->mdiArea->addSubWindow(child);

        if(child->loadFile(fileName))
        {
            child->setVisible(true);
            secondStatuslabel->setText(QStringLiteral("�򿪳ɹ�"));
            initConnect();
            QSettings settings("QT","MDI example");
            QStringList files = settings.value("recentFiles").toStringList();
            files.removeAll(fileName);
            files.prepend(fileName);
            while(files.size() > MaxRecentFiles)
            {
                files.removeLast();
            }
            settings.setValue("recentFiles",files);
            updateRecentFiles();
        }
        else
        {
            child->close();
        }
    }
}

void TextEdit::initConnect()//��ʼ������
{
    connect(activeMdiChild(),SIGNAL(cursorPositionChanged()),this,SLOT(doCursorchanged()));//�������λ��
    connect(activeMdiChild()->document(),SIGNAL(contentsChanged()),SLOT(documentWasModified()));
    connect(activeMdiChild()->document(),SIGNAL(undoAvailable(bool)),ui->action_Undo,SLOT(setEnabled(bool)));
    connect(activeMdiChild()->document(),SIGNAL(redoAvailable(bool)),ui->action_Redo,SLOT(setEnabled(bool)));
    connect(activeMdiChild(),SIGNAL(copyAvailable(bool)),ui->action_Copy,SLOT(setEnabled(bool)));
    connect(activeMdiChild(),SIGNAL(copyAvailable(bool)),ui->action_Cut,SLOT(setEnabled(bool)));
    connect(activeMdiChild(),SIGNAL(copyAvailable(bool)),ui->action_Del,SLOT(setEnabled(bool)));
    /**����ʵ���Զ����Ҽ��˵�**/
    connect(activeMdiChild(),SIGNAL(fontChang()),SLOT(on_action_Font_triggered()));
    connect(activeMdiChild(),SIGNAL(fontColor()),SLOT(on_action_FontColor_triggered()));
    connect(activeMdiChild(),SIGNAL(Del()),SLOT(on_action_Del_triggered()));
}

void TextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
}
