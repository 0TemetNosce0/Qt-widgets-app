#include "imgprocessor.h"
#include "ui_imgprocessor.h"

#include <QFile>
#include <QColor>
#include <QPrinter>
#include <QPainter>
#include <QTextList>
#include <QFileDialog>
#include <QTextStream>
#include <QPrintDialog>
#include <QColorDialog>

ImgProcessor::ImgProcessor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImgProcessor)
{
    ui->setupUi(this);

    setWindowTitle(QStringLiteral("Easy Word"));

    showWidget = new ShowWidget(this);
    setCentralWidget(showWidget);
    //�ڹ�������Ƕ��ؼ�
    //��������
    fontLabel1 = new QLabel(QStringLiteral("����:"));
    fontComboBox = new QFontComboBox;
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);

    fontLabel2 = new QLabel(QStringLiteral("�ֺ�:"));
    sizeComboBox = new QComboBox;
    QFontDatabase db;
    foreach(int size,db.standardSizes())
    {
        sizeComboBox->addItem(QString::number(size));
    }

    boldBtn = new QToolButton;
    boldBtn->setIcon(QIcon(":/images/bold.png"));
    boldBtn->setCheckable(true);
    italicBtn = new QToolButton;
    italicBtn->setIcon(QIcon(":/images/italic.png"));
    italicBtn->setCheckable(true);

    underlineBtn = new QToolButton;
    underlineBtn->setIcon(QIcon(":/images/underline.png"));
    underlineBtn->setCheckable(true);

    colorBtn = new QToolButton;
    colorBtn->setIcon(QIcon(":/images/color.png"));
    colorBtn->setCheckable(true);

    //����
    listLabel = new QLabel(QStringLiteral("����"));
    listComboBox = new QComboBox;
    listComboBox->addItem("Standard");
    listComboBox->addItem("QTextListFormat::ListDisc");
    listComboBox->addItem("QTextListFormat::ListCircle");
    listComboBox->addItem("QTextListFormat::ListSquare");
    listComboBox->addItem("QTextListFormat::ListDecimal");
    listComboBox->addItem("QTextListFormat::ListLowerAlpha");
    listComboBox->addItem("QTextListFormat::ListUpperAlpha");
    listComboBox->addItem("QTextListFormat::ListLowerRoman");
    listComboBox->addItem("QTextListFormat::ListUpperRoman");

    createActions();
    createMenus();
    createToolBars();

    if(img.load(":/images/image.png"))
    {
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    }

    connect(fontComboBox,SIGNAL(activated(QString)),this,SLOT(ShowFontComboBox(QString)));
    connect(sizeComboBox,SIGNAL(activated(QString)),this,SLOT(ShowSizeSpinBox(QString)));
    connect(boldBtn,SIGNAL(clicked()),this,SLOT(ShowBoldBtn()));
    connect(italicBtn,SIGNAL(clicked()),this,SLOT(ShowItalicBtn()));
    connect(underlineBtn,SIGNAL(clicked()),this,SLOT(ShowUnderlineBtn()));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(ShowColorBtn()));
    connect(showWidget->text,SIGNAL(currentCharFormatChanged(QtextCharFormat&)),this,SLOT(ShowCurrentFormatChanged(QTextCharFormat&)));

    connect(listComboBox,SIGNAL(activated(int)),this,SLOT(ShowList(int)));
    connect(showWidget->text->document(),SIGNAL(undoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(showWidget->text->document(),SIGNAL(redoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(showWidget->text,SIGNAL(cursorPositionChanged()),this,SLOT(ShowCursorPositionChanged()));
}


ImgProcessor::~ImgProcessor()
{
    delete ui;
}


void ImgProcessor::createActions()
{
    //"��"����
    openFileAction = new QAction(QIcon(":/images/open.png"),QStringLiteral("��"),this);
    openFileAction->setShortcut(QStringLiteral("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("��һ���ļ�"));
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(ShowOpenFile()));

    //"�½�"����
    NewFileAction = new QAction(QIcon(":/images/new.png"),QStringLiteral("�½�"),this);
    NewFileAction->setShortcut(QStringLiteral("Ctrl+N"));
    NewFileAction->setStatusTip(QStringLiteral("�½�һ���ļ�"));
    connect(NewFileAction,SIGNAL(triggered()),this,SLOT(ShowNewFile()));

    //"�˳�"����
    exitAction = new QAction(QStringLiteral("�˳�"),this);
    exitAction->setShortcut(QStringLiteral("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("�˳�����"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    //"����"����
    copyAction = new QAction(QIcon(":/images/copy.png"),QStringLiteral("����"),this);
    copyAction->setShortcut(QStringLiteral("Ctrl+C"));
    copyAction->setStatusTip(QStringLiteral("�����ļ�"));
    connect(copyAction,SIGNAL(triggered()),showWidget->text,SLOT(copy()));

    //"����"����
    cutAction = new QAction(QIcon(":/images/cut.png"),QStringLiteral("����"),this);
    cutAction->setShortcut(QStringLiteral("Ctrl+X"));
    cutAction->setStatusTip(QStringLiteral("�����ļ�"));
    connect(cutAction,SIGNAL(triggered()),showWidget->text,SLOT(cut()));

    //"ճ��"����
    pasteAction = new QAction(QIcon(":/images/paste.png"),QStringLiteral("ճ��"),this);
    pasteAction->setShortcut(QStringLiteral("Ctrl+V"));
    pasteAction->setStatusTip(QStringLiteral("ճ���ļ�"));
    connect(pasteAction,SIGNAL(triggered()),showWidget->text,SLOT(paste()));

    //"����"����
    aboutAction = new QAction(QStringLiteral("����"),this);
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(QApplication::aboutQt()));

    //"��ӡ�ı�"����
    PrintTextAction = new QAction(QIcon(":/images/printText.png"),QStringLiteral("��ӡ�ı�"), this);
    PrintTextAction->setStatusTip(QStringLiteral("��ӡһ���ı�"));
    connect(PrintTextAction,SIGNAL(triggered()),this,SLOT(ShowPrintText()));

    //"��ӡͼ��"����
    PrintImageAction = new QAction(QIcon(":/images/printImage.png"),QStringLiteral("��ӡͼ��"), this);
    PrintImageAction->setStatusTip(QStringLiteral("��ӡһ��ͼ��"));
    connect(PrintImageAction,SIGNAL(triggered()),this,SLOT(ShowPrintImage()));

    //"�Ŵ�"����
    zoomInAction = new QAction(QIcon(":/images/zoomin.png"),QStringLiteral("�Ŵ�"),this);
    zoomInAction->setStatusTip(QStringLiteral("�Ŵ�һ��ͼƬ"));
    connect(zoomInAction,SIGNAL(triggered()),this,SLOT(ShowZoomIn()));

    //"��С"����
    zoomOutAction = new QAction(QIcon(":/images/zoomout.png"),QStringLiteral("��С"),this);
    zoomOutAction->setStatusTip(QStringLiteral("��Сһ��ͼƬ"));
    connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(ShowZoomOut()));

    //ʵ��ͼ����ת�Ķ�����Action��
    //��ת90��
    rotate90Action = new QAction(QIcon(":/images/rotate90.png"),QStringLiteral("��ת90��"),this);
    rotate90Action->setStatusTip(QStringLiteral("��һ��ͼ��ת90��"));
    connect(rotate90Action,SIGNAL(triggered()),this,SLOT(ShowRotate90()));

    //��ת180��
    rotate180Action = new QAction(QIcon(":/images/rotate180.png"),QStringLiteral("��ת180��"), this);
    rotate180Action->setStatusTip(QStringLiteral("��һ��ͼ��ת180��"));
    connect(rotate180Action,SIGNAL(triggered()),this,SLOT(ShowRotate180()));

    //��ת270��
    rotate270Action = new QAction(QIcon(":/images/rotate270.png"),QStringLiteral("��ת270��"), this);
    rotate270Action->setStatusTip(QStringLiteral("��һ��ͼ��ת270��"));
    connect(rotate270Action,SIGNAL(triggered()),this,SLOT(ShowRotate270()));

    //ʵ��ͼ����Ķ�����Action��
    //������
    mirrorVerticalAction = new QAction(QStringLiteral ("������"),this);
    mirrorVerticalAction->setStatusTip(QStringLiteral("��һ��ͼ��������"));
    connect(mirrorVerticalAction,SIGNAL(triggered()),this,SLOT(ShowMirrorVertical()));

    //������
    mirrorHorizontalAction = new QAction(QStringLiteral("������"),this);
    mirrorHorizontalAction->setStatusTip(QStringLiteral("��һ��ͼ��������"));
    connect(mirrorHorizontalAction,SIGNAL(triggered()),this,SLOT(ShowMirrorHorizontal()));

    //����:����롢�Ҷ��롢���к����˶���
    actGrp = new QActionGroup(this);

    leftAction = new QAction(QIcon(":/images/left.png"),"�����",actGrp);
    leftAction->setCheckable(true);

    rightAction = new QAction(QIcon(":/images/right.png"),"�Ҷ���",actGrp);
    rightAction->setCheckable(true);

    centerAction = new QAction(QIcon(":/images/center.png"),"����",actGrp);
    centerAction->setCheckable(true);

    justifyAction = new QAction(QIcon(":/images/justify.png"),"���˶���",actGrp);
    justifyAction->setCheckable(true);

    connect(actGrp,SIGNAL(triggered(QAction*)),this,SLOT(ShowAlignment(QAction*)));

    //ʵ�ֳ����������Ķ�����Action��
    //����������
    undoAction = new QAction(QIcon(":/images/undo.png"),"����",this);
    connect(undoAction,SIGNAL(triggered()),showWidget->text,SLOT(undo()));
    redoAction = new QAction(QIcon(":/images/redo.png"),"����",this);
    connect(redoAction,SIGNAL(triggered()),showWidget->text,SLOT(redo()));
}

void ImgProcessor::createMenus()
{
    //�ļ��˵�
    fileMenu = menuBar()->addMenu(QStringLiteral("�ļ�"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(NewFileAction);
    fileMenu->addAction(PrintTextAction);
    fileMenu->addAction(PrintImageAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //���Ų˵�
    zoomMenu =menuBar()->addMenu(QStringLiteral("�༭"));
    zoomMenu->addAction(copyAction);
    zoomMenu->addAction(cutAction);
    zoomMenu->addAction(pasteAction);
    zoomMenu->addAction(aboutAction);
    zoomMenu->addSeparator();
    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);

    //��ת�˵�
    rotateMenu =menuBar()->addMenu(QStringLiteral("��ת"));
    rotateMenu->addAction(rotate90Action);
    rotateMenu->addAction(rotate180Action);
    rotateMenu->addAction(rotate270Action);

    //����˵�
    mirrorMenu =menuBar()->addMenu(QStringLiteral("����"));
    mirrorMenu->addAction(mirrorVerticalAction);
    mirrorMenu->addAction(mirrorHorizontalAction);
}

void ImgProcessor::createToolBars()
{
    //�ļ�������
    fileTool =addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(NewFileAction);
    fileTool->addAction(PrintTextAction);
    fileTool->addAction(PrintImageAction);

    //�༭������
    zoomTool =addToolBar("Edit");
    zoomTool->addAction(copyAction);
    zoomTool->addAction(cutAction);
    zoomTool->addAction(pasteAction);
    zoomTool->addSeparator();
    zoomTool->addAction(zoomInAction);
    zoomTool->addAction(zoomOutAction);

    //��ת������
    rotateTool =addToolBar("rotate");
    rotateTool->addAction(rotate90Action);
    rotateTool->addAction(rotate180Action);
    rotateTool->addAction(rotate270Action);

    //����������������
    doToolBar =addToolBar("doEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addAction(redoAction);

    //���幤����
    fontToolBar =addToolBar("Font");
    fontToolBar->addWidget(fontLabel1);
    fontToolBar->addWidget(fontComboBox);
    fontToolBar->addWidget(fontLabel2);
    fontToolBar->addWidget(sizeComboBox);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(boldBtn);
    fontToolBar->addWidget(italicBtn);
    fontToolBar->addWidget(underlineBtn);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(colorBtn);

    //���򹤾���
    listToolBar =addToolBar("list");
    listToolBar->addWidget(listLabel);
    listToolBar->addWidget(listComboBox);
    listToolBar->addSeparator();
    listToolBar->addActions(actGrp->actions());
}

void ImgProcessor::ShowNewFile()
{
    ImgProcessor *newImgProcessor =new ImgProcessor;
    newImgProcessor->show();
}

void ImgProcessor::ShowOpenFile()
{
    fileName =QFileDialog::getOpenFileName(this,"��");
    if(!fileName.isEmpty())
    {
        if(showWidget->text->document()->isEmpty())
        {
            loadFile(fileName);
        }
        else
        {
            ImgProcessor *newImgProcessor =new ImgProcessor;
            newImgProcessor->show();
            newImgProcessor->loadFile(fileName);
        }
    }
}

void ImgProcessor::loadFile(QString filename)
{
    printf("file name:%s\n",filename.data());

    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())
        {
            showWidget->text->append(textStream.readLine());
            printf("read line\n");
        }
        printf("end\n");
    }
}

void ImgProcessor::ShowPrintText()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec())
    {
        QTextDocument *doc =showWidget->text->document();
        doc->print(&printer);
    }
}

void ImgProcessor::ShowPrintImage()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec())
    {
        QPainter painter(&printer);
        QRect rect =painter.viewport();
        QSize size = img.size();
        size.scale(rect.size(),Qt::KeepAspectRatio);

        painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
        painter.setWindow(img.rect());
        painter.drawImage(0,0,img);
    }
}

void ImgProcessor::ShowZoomIn()
{
    if(img.isNull())
        return;
    QMatrix martix;
    martix.scale(2,2);
    img = img.transformed(martix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowZoomOut()
{
    if(img.isNull())
        return;
    QMatrix matrix;
    matrix.scale(0.5,0.5);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowRotate90()
{
    if(img.isNull())
        return;
    QMatrix matrix;
    matrix.rotate(90);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowRotate180()
{
    if(img.isNull())
        return;
    QMatrix matrix;
    matrix.rotate(180);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowRotate270()
{
    if(img.isNull())
        return;
    QMatrix matrix;
    matrix.rotate(270);
    img = img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowMirrorVertical()
{
    if(img.isNull())
        return;
    img=img.mirrored(false,true);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowMirrorHorizontal()
{
    if(img.isNull())
        return;
    img=img.mirrored(true,false);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::ShowFontComboBox(QString comboStr)       //��������
{
    QTextCharFormat fmt;
    fmt.setFontFamily(comboStr);
    mergeFormat(fmt);                       //���µĸ�ʽӦ�õ����ѡ���ڵ��ַ�
}

void ImgProcessor::mergeFormat(QTextCharFormat format)
{
    QTextCursor cursor =showWidget->text->textCursor();
    if(!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    showWidget->text->mergeCurrentCharFormat(format);
}

void ImgProcessor::ShowSizeSpinBox(QString spinValue)       //�����ֺ�
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(spinValue.toFloat());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void ImgProcessor::ShowBoldBtn()                            //����������ʾ�Ӵ�
{
    QTextCharFormat fmt;
    fmt.setFontWeight(boldBtn->isChecked()?QFont::Bold:QFont::Normal);
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void ImgProcessor::ShowItalicBtn()                          //����������ʾб��
{
    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void ImgProcessor::ShowUnderlineBtn()                       //�������ּ��»���
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(underlineBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void ImgProcessor::ShowColorBtn()                           //����������ɫ
{
    QColor color=QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        showWidget->text->mergeCurrentCharFormat(fmt);
    }
}

void ImgProcessor::ShowCurrentFormatChanged(const QTextCharFormat &fmt)
{
    fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamily()));
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.fontPointSize())));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.fontItalic());
    underlineBtn->setChecked(fmt.fontUnderline());
}

void ImgProcessor::ShowAlignment(QAction *act)
{
    if(act==leftAction)
        showWidget->text->setAlignment(Qt::AlignLeft);
    if(act==rightAction)
        showWidget->text->setAlignment(Qt::AlignRight);
    if(act==centerAction)
        showWidget->text->setAlignment(Qt::AlignCenter);
    if(act==justifyAction)
        showWidget->text->setAlignment(Qt::AlignJustify);
}

void ImgProcessor::ShowCursorPositionChanged()
{
    if(showWidget->text->alignment()==Qt::AlignLeft)
        leftAction->setChecked(true);
    if(showWidget->text->alignment()==Qt::AlignRight)
        rightAction->setChecked(true);
    if(showWidget->text->alignment()==Qt::AlignCenter)
        centerAction->setChecked(true);
    if(showWidget->text->alignment()==Qt::AlignJustify)
        justifyAction->setChecked(true);
}

void ImgProcessor::ShowList(int index)
{
    QTextCursor cursor=showWidget->text->textCursor();

    if(index!=0)
    {
        QTextListFormat::Style style=QTextListFormat::ListDisc;
        switch(index)                           //����style����ֵ
        {
        default:
        case 1:
            style=QTextListFormat::ListDisc; break;
        case 2:
            style=QTextListFormat::ListCircle; break;
        case 3:
            style=QTextListFormat::ListSquare; break;
        case 4:
            style=QTextListFormat::ListDecimal; break;
        case 5:
            style=QTextListFormat::ListLowerAlpha; break;
        case 6:
            style=QTextListFormat::ListUpperAlpha; break;
        case 7:
            style=QTextListFormat::ListLowerRoman; break;
        case 8:
            style=QTextListFormat::ListUpperRoman; break;
        }
        cursor.beginEditBlock();                //��������ֵ

        QTextBlockFormat blockFmt=cursor.blockFormat();
        QTextListFormat listFmt;

        if(cursor.currentList())
        {
            listFmt= cursor.currentList()->format();
        }
        else
        {
            listFmt.setIndent(blockFmt.indent()+1);
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
