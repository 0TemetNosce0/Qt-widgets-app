#include "builtindlg.h"
#include <QtGui>
#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QColorDialog>
#include <QErrorMessage>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QPageSetupDialog>
#include <QPrinter>
#include <QProgressDialog>
#include <QPrintDialog>
#include <QMessageBox>
#include <QWizard>
#include <QLabel>
CBuiltinDlg::CBuiltinDlg(QWidget* parent)
 :	QDialog(parent)
{
    displayTextEdit = new QTextEdit("Qt的标准通用对话11");

    QGridLayout* gridLayout = new QGridLayout;
    colorPushBtn 	 = new QPushButton(u8"颜色对话框11");
    errorPushBtn 	 = new QPushButton(u8"错误信息框1");
    filePushBtn 	 = new QPushButton(u8"打开文件对话框1");
    multifilePushBtn = new QPushButton(u8"打开多个文件对话框1");
    savefilePushBtn  = new QPushButton(u8"保存文件对话框1");
    getDirectory     = new QPushButton(u8"选择文件夹对话框1");
    fontPushBtn 	 = new QPushButton(u8"字体对话框1");
    inputPushBtn 	 = new QPushButton(u8"输入对话框1");
    pagePushBtn 	 = new QPushButton(u8"页设置对话框1");
    progressPushBtn  = new QPushButton(u8"进度对话框1");
    printPushBtn	 = new QPushButton(u8"打印对话框1");

    nameButton       = new QPushButton(u8"字符串输入1");
    sexButton        = new QPushButton(u8"下拉列表框输入1");
    ageButton        = new QPushButton(u8"Int类型输入1");
    statureButton    = new QPushButton(u8"Double类型输入1");

    questionBtn = new QPushButton(u8"问题消息框1");
    informationBtn = new QPushButton(u8"信息消息框1");
    warningBtn = new QPushButton(u8"警告消息框1");
    criticalBtn = new QPushButton(u8"错误消息框1");
    aboutBtn = new QPushButton(u8"关于消息框1");
    aboutQtBtn = new QPushButton(u8"关于Qt消息框1");
    customBtn = new QPushButton(u8"自定义消息框1");

    wizardBtn = new QPushButton(u8"向导对话框1");
    colorComboBox = new QComboBox;

    gridLayout->addWidget(colorPushBtn, 0, 0, 1, 1);
    gridLayout->addWidget(errorPushBtn, 0, 1, 1, 1);
    gridLayout->addWidget(filePushBtn, 0, 2, 1, 1);
    gridLayout->addWidget(multifilePushBtn, 0, 3, 1, 1);
    gridLayout->addWidget(savefilePushBtn, 1, 0, 1, 1);
    gridLayout->addWidget(fontPushBtn, 1, 1, 1, 1);
    gridLayout->addWidget(pagePushBtn, 1, 2, 1, 1);
    gridLayout->addWidget(getDirectory, 1, 3, 1, 1);
    gridLayout->addWidget(progressPushBtn, 2, 0, 1, 1);
    gridLayout->addWidget(printPushBtn, 2, 1, 1, 1);
    gridLayout->addWidget(nameButton, 2, 2, 1, 1);
    gridLayout->addWidget(sexButton, 2, 3, 1, 1);
    gridLayout->addWidget(ageButton, 3, 0, 1, 1);
    gridLayout->addWidget(statureButton, 3, 1, 1, 1);
    gridLayout->addWidget(questionBtn, 3, 2, 1, 1);
    gridLayout->addWidget(informationBtn, 3, 3, 1, 1);
    gridLayout->addWidget(warningBtn, 4, 0, 1, 1);
    gridLayout->addWidget(criticalBtn, 4, 1, 1, 1);
    gridLayout->addWidget(aboutBtn, 4, 2, 1, 1);
    gridLayout->addWidget(aboutQtBtn, 4, 3, 1, 1);
    gridLayout->addWidget(customBtn, 5, 0, 1, 1);
    gridLayout->addWidget(wizardBtn, 5, 1, 1, 1);
    gridLayout->addWidget(colorComboBox, 5, 2, 1, 1);
    gridLayout->addWidget(displayTextEdit, 6, 0, 3, 4);

    setLayout(gridLayout);

    connect(colorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(errorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(filePushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(multifilePushBtn, SIGNAL(clicked()), this, SLOT(MultiOpenFile()));
    connect(savefilePushBtn, SIGNAL(clicked()), this, SLOT(SaveFileName()));
    connect(getDirectory, SIGNAL(clicked()), this, SLOT(GettExistingDirectory()));
    connect(fontPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(inputPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(pagePushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(progressPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(printPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(nameButton,SIGNAL(clicked()),this,SLOT(slotName()));
    connect(sexButton,SIGNAL(clicked()),this,SLOT(slotSex()));
    connect(ageButton,SIGNAL(clicked()),this,SLOT(slotAge()));
    connect(statureButton,SIGNAL(clicked()),this,SLOT(slotStature()));
    connect(questionBtn,SIGNAL(clicked()),this,SLOT(slotQuestion()));
    connect(informationBtn,SIGNAL(clicked()),this,SLOT(slotInformation()));
    connect(warningBtn,SIGNAL(clicked()),this,SLOT(slotWarning()));
    connect(criticalBtn,SIGNAL(clicked()),this,SLOT(slotCritical()));
    connect(aboutBtn,SIGNAL(clicked()),this,SLOT(slotAbout()));
    connect(aboutQtBtn,SIGNAL(clicked()),this,SLOT(slotAboutQt()));
    connect(customBtn,SIGNAL(clicked()),this,SLOT(slotCustom()));
    connect(wizardBtn,SIGNAL(clicked()),this,SLOT(slotWizard()));

    QStringList colorList = QColor::colorNames();
    QString color;
    foreach(color,colorList) {
        QPixmap pix(QSize(70, 20));
        pix.fill(QColor(color));
        colorComboBox->addItem(QIcon(pix),NULL);
        colorComboBox->setIconSize(QSize(70, 20));
        colorComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
    connect(colorComboBox,SIGNAL(activated(int)),this,SLOT(slotColor(int)));

    setWindowTitle(u8"內建对话框1");
    resize(400, 400);
}

CBuiltinDlg::~CBuiltinDlg()
{
}

void CBuiltinDlg::doPushBtn()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(btn == colorPushBtn) {// 颜色对话框.
        QPalette palette = displayTextEdit->palette();
        const QColor& color = QColorDialog::getColor(palette.color(QPalette::Base), this);
        if(color.isValid()) {
            palette.setColor(QPalette::Base, color);
            displayTextEdit->setPalette(palette);
        }
    }
    else if(btn == errorPushBtn) {// 错误信息框.
        QErrorMessage box(this);
        box.setWindowTitle(u8"错误信息框1");
        box.showMessage(u8"错误信息框实例xx。1");
        box.showMessage(u8"错误信息框实例xx。1");
        box.showMessage(u8"错误信息框实例xx。1");
        box.showMessage(u8"错误信息框实例yy。1");
        box.showMessage(u8"错误信息框实例zz。1");
        box.exec();
    }
    else if(btn == filePushBtn) {// 文件对话框.
        /*QString fileName = QFileDialog::getOpenFileName(this,
                                                u8"打开文件",
                                                "/",
                                                u8"任何文件(*.*)"
                                                    ";;文本文件(*.txt)"
                                                    ";;C++文件(*.cpp)");
        if (fileName.length() != 0) {
          displayTextEdit->setText(fileName);
        }*/
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setWindowTitle(u8"Open Image1");
        fileDialog->setDirectory(".");
//        fileDialog->setFilter(u8"Source Files(*.cpp *.c)");
        if(fileDialog->exec() == QDialog::Accepted) {
            QString path = fileDialog->selectedFiles()[0];
            displayTextEdit->setText(path);
            //QMessageBox::information(NULL, u8"Path", u8"You selected " + path);
        } else {
            //QMessageBox::information(NULL, u8"Path", u8"You didn't select any files.");
        }
    }
    else if(btn == fontPushBtn) {// 字体对话框.
        bool ok;
        const QFont& font = QFontDialog::getFont(&ok,
                                    displayTextEdit->font(),
                                    this,
                                    u8"字体对话框1");
        if(ok) {// 如果<确定>,设置字体.
            displayTextEdit->setFont(font);
        }
    }
    else if(btn == inputPushBtn){// 输入对话框.
        bool ok;
        QString text = QInputDialog::getText(this,
                                            u8"输入对话框1",
                                            u8"输入文本：1",
                                            QLineEdit::Normal,
                                            QDir::home().dirName(),
                                            &ok);
        if (ok && !text.isEmpty())
           displayTextEdit->setText(text);
    }
    else if(btn == pagePushBtn) {// 页设置对话框.
        QPrinter printer;
        QPageSetupDialog dlg(&printer, this);
        dlg.setWindowTitle(u8"页设置对话框");
        if (dlg.exec() == QDialog::Accepted) {
            // 进行下一步的处理。
        }
    }
    else if(btn == progressPushBtn) {// 进度对话框.
        QProgressDialog progress(u8"正在复制文件...", u8"取消", 0, 1000, this);
        QFont font("ZYSong18030",10);
        progress.setFont(font);

        progress.setWindowModality(Qt::WindowModal);
        progress.setWindowTitle(u8"进度对话框1");
        progress.show();
        for (int i = 0; i < 1000; i++) {
            progress.setValue(i);
            qApp->processEvents();
            if (progress.wasCanceled())
                break;
            QTest::qWait(1);
            //... 复制文件处理。
        }
        progress.setValue(1000);
    }
    else if(btn == printPushBtn) {// 打印对话框.
        QPrinter printer;
        QPrintDialog dlg(&printer, this);
        dlg.setWindowTitle(u8"打印对话框");
        if (dlg.exec() == QDialog::Accepted) {
            // 进行下一步的处理。
        }
    }
}
void CBuiltinDlg::SaveFileName()
{
    /*
    //getOpenFileName()函数在Windows和MacOS X平台上提供的是本地的对话框
    QFileDialog::Options options;
    QString selectedFilter;
    options |= QFileDialog::DontUseNativeDialog;
    QString fileName = QFileDialog::getSaveFileName(this, u8"Save File",
                               displayTextEdit->toPlainText(),
                               u8"file (*.cpp *.c *.txt)",
                               &selectedFilter,
                               options);
     if (!fileName.isEmpty()) {
        //save fileName
        displayTextEdit->setText("save file:" + fileName);
     }
     */
     //QFileDialog提供的始终是Qt自己绘制的对话框
     QFileDialog* saveFileDialog = new QFileDialog(this);
     saveFileDialog->setWindowTitle(QString("Save File"));
     saveFileDialog->setFileMode(QFileDialog::AnyFile);
     saveFileDialog->setNameFilter(u8"file (*.cpp *.c *.txt)");
     QString* fileName=new QString();
     if(saveFileDialog->exec())
        *fileName = saveFileDialog->getSaveFileName();
     if(fileName->size() > 0) {
         displayTextEdit->setText("save file:" + *fileName);
     }
     delete fileName;
     fileName = NULL;
}

void CBuiltinDlg::MultiOpenFile()
{
    QStringList files = QFileDialog::getOpenFileNames(
                                    this, u8"Select one or more files to open",
                                    "/",
                                    u8"All Files (*);;Text Files (*.txt)");
    if (files.count()) {
        displayTextEdit->setText(QString("[%1]").arg(files.join(", ")));
    }
}

void CBuiltinDlg::GettExistingDirectory()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    options |= QFileDialog::DontUseNativeDialog;
    QString directory = QFileDialog::getExistingDirectory(this,
                                    u8"Open Directory",
                                    "/home",
                                    options);
    if (!directory.isEmpty())
        displayTextEdit->setText(directory);
}

void CBuiltinDlg::slotName()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                         u8"用户名",
                                         u8"请输入新的用户名:",
                                         QLineEdit::Normal,
                                         "name",
                                         &ok);
    if(ok && !name.isEmpty()) {
        displayTextEdit->setText(name);
    }
}

void CBuiltinDlg::slotSex()
{
    QStringList list;
    list << u8"男" << u8"女";
    bool ok;
    QString sex = QInputDialog::getItem(this,u8"性别",
                u8"请选择性别:",list,0,false,&ok);
    if (ok) {
        displayTextEdit->setText(sex);
    }
}

void CBuiltinDlg::slotAge()
{
    bool ok;
//    int age = QInputDialog::getInteger(this,u8"年龄",
//                u8"请输入年龄:", 20,0,150,1,&ok);
//    if(ok) {
//        displayTextEdit->setText(QString(u8"%1").arg(age));
//    }
}

void CBuiltinDlg::slotStature()
{
    bool ok;
    double high = QInputDialog::getDouble(this,u8"身高",
                u8"请输入身高:",175.00,0,230.00,1,&ok);
    if(ok) {
        displayTextEdit->setText(QString(u8"%1").arg(high));
    }
}

void CBuiltinDlg::slotQuestion()
{
    switch(QMessageBox::question(this,u8"询问",u8"重新开始?",
            QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    {
    case QMessageBox::Ok:
        displayTextEdit->setText(u8"询问按钮 / 确定");
        break;
    case QMessageBox::Cancel:
        displayTextEdit->setText(u8"询问按钮 / 取消");
        break;
    default:
        break;
    }
}
void CBuiltinDlg::slotInformation()
{
     QMessageBox::information(this,u8"提示",u8"提示信息");
     displayTextEdit->setText(u8"提示信息框");
}
void CBuiltinDlg::slotWarning()
{
    switch(QMessageBox::warning(this,u8"警告",u8"是否要保存文档?",
            QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel,QMessageBox::Save))
    {
    case QMessageBox::Save:
        displayTextEdit->setText(u8"警告对话框 / 保存");
        break;
    case QMessageBox::Discard:
        displayTextEdit->setText(u8"警告对话框 / 不保存");
        break;
    case QMessageBox::Cancel:
        displayTextEdit->setText(u8"警告对话框 / 取消");
        break;
    default:
        break;
    }
}
void CBuiltinDlg::slotCritical()
{
    QMessageBox::critical(this, u8"错误",u8"告诉用户一个严重的错误!");
    displayTextEdit->setText(u8"错误信息框");
}
void CBuiltinDlg::slotAbout()
{
    QMessageBox::about(this,u8"关于",u8"对话框例子!");
    displayTextEdit->setText(u8"关于信息框");
}
void CBuiltinDlg::slotAboutQt()
{
    QMessageBox::aboutQt(this, u8"关于Qt");
    displayTextEdit->setText(u8"关于Qt信息框");
}
void CBuiltinDlg::slotCustom()
{
    QMessageBox customMsgBox;
    customMsgBox.setWindowTitle(u8"自定义弹出对话框");
    QPushButton *lockButton = customMsgBox.addButton(u8"加锁",QMessageBox::ActionRole);
    QPushButton *unlockButton = customMsgBox.addButton(u8"解锁",QMessageBox::ActionRole);
    QPushButton *cancelButton = customMsgBox.addButton(QMessageBox::Cancel);
    customMsgBox.setText(u8"这是自定义对话框");
    customMsgBox.exec();

    if(customMsgBox.clickedButton() == lockButton)
        displayTextEdit->setText(u8"自定义对话框 / 加锁");
    if(customMsgBox.clickedButton() == unlockButton)
        displayTextEdit->setText(u8"自定义对话框 / 解锁");
    if(customMsgBox.clickedButton() == cancelButton)
        displayTextEdit->setText(u8"自定义对话框 / 取消");
}

void CBuiltinDlg::slotWizard()
{
    QWizard wizard;
    wizard.addPage(createFirstPage());
    wizard.addPage(createSecondPage());

    wizard.setWindowTitle(u8"向导对话框");
    wizard.exec();
}

QWizardPage* CBuiltinDlg::createFirstPage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(u8"简介");

    QLabel *label = new QLabel(u8"第一页");
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}
QWizardPage* CBuiltinDlg::createSecondPage()
{
     QWizardPage *page = new QWizardPage;
     page->setTitle(u8"正文");

     QLabel *label = new QLabel(u8"第二页");
     label->setWordWrap(true);

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(label);
     page->setLayout(layout);
     return page;
}
void CBuiltinDlg::slotColor(int index)
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[index]);
    QPalette p = displayTextEdit->palette();
    p.setColor(QPalette::Text, color);
    displayTextEdit->setPalette(p);
}
