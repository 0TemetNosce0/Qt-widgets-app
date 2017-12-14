#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "toolbar.h"
#include "about.h"
#include "photoinfo.h"
#include "mirrorview.h"
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDesktopServices>
#include <QDropEvent>
#include <QMimeData>
#include <QDir>
#include <QLabel>
#include <QImage>
#include <QDebug>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QTranslator>


QStringList FileSuffix = (QStringList() << "png" <<
                          "jpg" << "jpeg" << "bmp" <<
                          "tif" << "tiff" << "webp" <<
                          "gif" << "jp2" << "dds" <<
                          "xpm" << "pnm" << "ppm" <<
                          "pgm" << "wbmp" << "ico" <<
                          "icns");

QStringList FileFilter = (QStringList() << "*.png" <<
                          "*.jpg" << "*.jpeg" << "*.bmp" <<
                          "*.tif" << "*.tiff" << "*.webp" <<
                          "*.gif" << "*.jp2" << "*.dds" <<
                          "*.xpm" << "*.pnm" << "*.ppm" <<
                          "*.pgm" << "*.wbmp" << "*.ico" <<
                          "*.icns");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    toolBar = new ToolBar();

    ui->statusBar->addPermanentWidget(toolBar,1);
    ui->photo->setPixmap(QPixmap(":/images/drop.png"));
    setCentralWidget(ui->photo);

    ui->statusBar->hide();

    connect(toolBar->ZoomIn,SIGNAL(clicked()),this,SLOT(ZoomIn()));
    connect(toolBar->ZoomOut,SIGNAL(clicked()),this,SLOT(ZoomOut()));
    connect(toolBar->ZoomFit,SIGNAL(clicked()),this,SLOT(ZoomFit()));
    connect(toolBar->Prev,SIGNAL(clicked()),this,SLOT(PhotoPrev()));
    connect(toolBar->Next,SIGNAL(clicked()),this,SLOT(PhotoNext()));
    connect(toolBar->FullScreen,SIGNAL(clicked()),this,SLOT(FullScreen()));
    connect(toolBar->RotateLeft,SIGNAL(clicked()),this,SLOT(RotateLeft()));
    connect(toolBar->RotateRight,SIGNAL(clicked()),this,SLOT(RotateRight()));
    connect(toolBar->FlipH,SIGNAL(clicked()),this,SLOT(FlipH()));
    connect(toolBar->FlipV,SIGNAL(clicked()),this,SLOT(FlipV()));
    connect(toolBar->Info,SIGNAL(clicked()),this,SLOT(Info()));
    connect(toolBar->Play,SIGNAL(clicked()),this,SLOT(Play()));
    connect(toolBar->Delete,SIGNAL(clicked()),this,SLOT(Delete()));


    PhotoIndex = 0;
    PhotoExist = false;
    ZoomFlag = false;
    RotateFlipFlag = false;
    ZoomFactor = 1.0;
    ZoomFactorFlag = true;
    windowMaxState = false;
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &purl, event->mimeData()->urls())
    {
        QFileInfo FileInfo(purl.toLocalFile());
        if(FileSuffix.contains(FileInfo.suffix(),Qt::CaseInsensitive))
        {
            PhotoMap.clear();
            PhotoMap[PhotoMap.count()] = FileInfo;
            QList<QFileInfo> fileInfoList = FileInfo.dir().entryInfoList(FileFilter);
            fileInfoList.removeOne(FileInfo);
            while(fileInfoList.count() > 0)
            {
                PhotoMap[PhotoMap.count()] = fileInfoList.takeFirst();
            }

            PhotoExist = true;
            ui->photo->setPixmap(FileInfo.absoluteFilePath());
            image.load(FileInfo.absoluteFilePath());
            image1.load(FileInfo.absoluteFilePath());
            PhotoIndex = 0;
            ui->statusBar->show();
            ZoomFit();
        }
    }
}


void MainWindow::ZoomIn()
{
    if(PhotoExist)
    {
        if(!ZoomFlag)
        {
            Zoom();
            ZoomFlag = true;
        }
        ZoomFactor += 0.02;
        if(ZoomFactor >= 10.0)
            ZoomFactor = 10.0;
        QTransform tr = QTransform::fromScale(ZoomFactor,ZoomFactor);
        QImage image2 = image1.transformed(tr,Qt::SmoothTransformation);
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        SetToolBarLabel();
    }
}


void MainWindow::ZoomOut()
{
    if(PhotoExist)
    {
        if(!ZoomFlag)
        {
            Zoom();
            ZoomFlag = true;
        }
        ZoomFactor -= 0.02;
        if(ZoomFactor <= 0.01)
            ZoomFactor = 0.01;
        QTransform tr = QTransform::fromScale(ZoomFactor,ZoomFactor);
        QImage image2 = image1.transformed(tr,Qt::SmoothTransformation);
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        SetToolBarLabel();
    }
}

void MainWindow::ZoomFit()
{
    if(PhotoExist)
    {
        qreal pw = image1.width();
        qreal ph = image1.height();
        qreal ww = ui->photo->width();
        qreal wh = ui->photo->height();
        QImage image2;

        if(pw <= ww && ph <= wh)
        {
            image2 = image1;
        }
        else
        {
            image2 = image1.scaled(ui->photo->width(),ui->photo->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        Zoom();
        SetToolBarLabel();
    }
}


void MainWindow::PhotoNext()
{
    if(PhotoExist)
    {
        if(RotateFlipFlag)
        {
            QMessageBox SaveMsg(this);
            int answer;
            SaveMsg.setWindowTitle(tr("Save Changes"));
            SaveMsg.setText(tr("The Photo has been edited."));
            SaveMsg.setInformativeText(tr("Do you want to save your changes?"));
            SaveMsg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            SaveMsg.setDefaultButton(QMessageBox::Save);
            SaveMsg.setButtonText(QMessageBox::Save, tr("Save"));
            SaveMsg.setButtonText(QMessageBox::Discard, tr("Discard"));
            SaveMsg.setButtonText(QMessageBox::Cancel, tr("Cancel"));
            answer = SaveMsg.exec();
            if(answer == QMessageBox::Save)
            {
                on_actionSave_triggered();
            }
            else if (answer == QMessageBox::Discard)
            {
                if(++PhotoIndex >= PhotoMap.count())
                {
                    PhotoIndex = 0;
                }

                SwitchPhoto(PhotoIndex);
            }
            else if (answer == QMessageBox::Cancel)
            {
                ;
            }
        }
        else
        {
            if(++PhotoIndex >= PhotoMap.count())
            {
                PhotoIndex = 0;
            }

            SwitchPhoto(PhotoIndex);
        }
    }
}

void MainWindow::PhotoPrev()
{
    if(PhotoExist)
    {
        if(RotateFlipFlag)
        {
            QMessageBox SaveMsg(this);
            int answer;
            SaveMsg.setWindowTitle(tr("Save Changes"));
            SaveMsg.setText(tr("The Photo has been edited."));
            SaveMsg.setInformativeText(tr("Do you want to save your changes?"));
            SaveMsg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            SaveMsg.setDefaultButton(QMessageBox::Save);
            SaveMsg.setButtonText(QMessageBox::Save, tr("Save"));
            SaveMsg.setButtonText(QMessageBox::Discard, tr("Discard"));
            SaveMsg.setButtonText(QMessageBox::Cancel, tr("Cancel"));
            answer = SaveMsg.exec();
            if(answer == QMessageBox::Save)
            {
                on_actionSave_triggered();
            }
            else if (answer == QMessageBox::Discard)
            {
                if(--PhotoIndex < 0)
                {
                    PhotoIndex = PhotoMap.count() - 1;
                }

                SwitchPhoto(PhotoIndex);
            }
            else if (answer == QMessageBox::Cancel)
            {
                ;
            }
        }
        else
        {
            if(--PhotoIndex < 0)
            {
                PhotoIndex = PhotoMap.count() - 1;
            }

            SwitchPhoto(PhotoIndex);
        }
    }
}


void MainWindow::SwitchPhoto(int index)
{
    image.load(PhotoMap.value(index).absoluteFilePath());
    image1 = image;
    ZoomFlag = false;
    RotateFlipFlag = false;
    ZoomFit();
}

void MainWindow::resizeEvent (QResizeEvent *)
{
    if(PhotoExist == true)
    {
        ZoomFit();
    }
}

void MainWindow::FullScreen()
{
    if(PhotoExist)
    {
        if(this->isFullScreen())
        {  
            if(windowMaxState)
            {
                this->showMaximized();
            }
            else
            {
                this->showNormal();
            }
            toolBar->FullScreen->setIcon(QIcon(":/images/fullscreen.png"));
            toolBar->FullScreen->setToolTip(tr("Exit Full Screen"));
        }
        else
        {
            if(Qt::WindowMaximized == this->windowState())
                windowMaxState = true;
            else
                windowMaxState = false;
            toolBar->FullScreen->setIcon(QIcon(":/images/fullscreenexit.png"));
            toolBar->FullScreen->setToolTip(tr("Full Screen"));
            this->showFullScreen();
        }
    }
}


void MainWindow::RotateLeft()
{
    if(PhotoExist)
    {
        QTransform tr;
        qreal pw;
        qreal ph;
        qreal ww;
        qreal wh;
        QImage image2;

        tr.rotate(-90);
        if(ZoomFlag)
        {
            image1 = image.transformed(tr,Qt::SmoothTransformation);
            ZoomFlag = false;
        }
        else
        {
            image1 = image1.transformed(tr,Qt::SmoothTransformation);
        }

        pw = image1.width();
        ph = image1.height();
        ww = ui->photo->width();
        wh = ui->photo->height();

        if(pw <= ww && ph <= wh)
        {
            image2 = image1;
        }
        else
        {
            image2 = image1.scaled(ui->photo->width(),ui->photo->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->photo->setPixmap(QPixmap::fromImage(image2));


        RotateFlipFlag = true;
    }
}

void MainWindow::RotateRight()
{
    if(PhotoExist)
    {
        QTransform tr;
        qreal pw;
        qreal ph;
        qreal ww;
        qreal wh;
        QImage image2;
        tr.rotate(90);
        if(ZoomFlag)
        {
            image1 = image.transformed(tr,Qt::SmoothTransformation);
            ZoomFlag = false;
        }
        else
        {
            image1 = image1.transformed(tr,Qt::SmoothTransformation);
        }

        pw = image1.width();
        ph = image1.height();
        ww = ui->photo->width();
        wh = ui->photo->height();

        if(pw <= ww && ph <= wh)
        {
            image2 = image1;
        }
        else
        {
            image2 = image1.scaled(ui->photo->width(),ui->photo->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        RotateFlipFlag = true;
    }
}

void MainWindow::FlipV()
{
    if(PhotoExist)
    {
        qreal pw;
        qreal ph;
        qreal ww;
        qreal wh;
        QImage image2;

        if(ZoomFlag)
        {
            image1 = (image.mirrored(false,true));
            ZoomFlag = false;
        }
        else
        {
            image1 = (image1.mirrored(false,true));
        }
        pw = image1.width();
        ph = image1.height();
        ww = ui->photo->width();
        wh = ui->photo->height();

        if(pw <= ww && ph <= wh)
        {
            image2 = image1;
        }
        else
        {
            image2 = image1.scaled(ui->photo->width(),ui->photo->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        RotateFlipFlag = true;
    }
}

void MainWindow::FlipH()
{
    if(PhotoExist)
    {
        qreal pw;
        qreal ph;
        qreal ww;
        qreal wh;
        QImage image2;

        if(ZoomFlag)
        {
            image1 = (image.mirrored(true,false));
            ZoomFlag = false;
        }
        else
        {
            image1 = (image1.mirrored(true,false));
        }
        pw = image1.width();
        ph = image1.height();
        ww = ui->photo->width();
        wh = ui->photo->height();

        if(pw <= ww && ph <= wh)
        {
            image2 = image1;
        }
        else
        {
            image2 = image1.scaled(ui->photo->width(),ui->photo->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        RotateFlipFlag = true;
    }
}

void MainWindow::Play()
{
    if(PhotoExist)
    {
        if(ui->actionEffect1->isChecked())
        {
            if(PhotoMap.count() > 0)
            {
                mirrorView = new MirrorView();
                connect(mirrorView,SIGNAL(neededPhoto(int)),this,SLOT(photoNeeded(int)));
                connect(mirrorView,SIGNAL(hideMe()),this,SLOT(hideMirrorView()));
                mirrorView->setImageList(PhotoMap.keys());
                int imageCount = 7;
                if(imageCount > PhotoMap.keys().count())
                    imageCount  = PhotoMap.keys().count();

                for(int i = 0; i < imageCount; ++i)
                {
                    mirrorView->loadImage(PhotoMap.keys().at(i),
                                          QPixmap(PhotoMap.value(PhotoMap.keys().at(i)).absoluteFilePath()));
                }
                mirrorView->showFullScreen();
            }
        }

        if(ui->actionEffect2->isChecked())
        {
            if(PhotoMap.count() > 0)
            {
                slideShow = new SlideShow(this);
                connect(slideShow,SIGNAL(hideMe()),this,SLOT(hideSlideShow()));
                slideShow->showFullScreen();
            }
        }
    }
}

void MainWindow::hideMirrorView()
{
    mirrorView->close();
    delete mirrorView;
    mirrorView = NULL;
}

void MainWindow::hideSlideShow()
{
    slideShow->close();
    delete slideShow;
    slideShow = NULL;
}

void MainWindow::photoNeeded(int index)
{
    if(PhotoMap.keys().contains(index))
    {
        if(PhotoMap.value(index).exists())
            mirrorView->loadImage(index,QPixmap(PhotoMap.value(index)
                                                .absoluteFilePath()));
        else
            mirrorView->removeIndex(index);
    }
}

void MainWindow::Info()
{
    if(PhotoExist)
    {
        PhotoInfo *photoInfo = new PhotoInfo(this);
        photoInfo->exec();
    }
}

void MainWindow::Delete()
{
    if(PhotoExist)
    {
        QFileInfo FileInfo = PhotoMap[PhotoIndex];
        QFile file(FileInfo.absoluteFilePath());
        if(file.remove())
        {
            PhotoMap.remove(PhotoIndex);
            PhotoIndex--;

            QList<QFileInfo> ListInfo = PhotoMap.values();
            PhotoMap.clear();
            int i = 0;
            for(i = 0;i < ListInfo.count();++i)
            {
               PhotoMap.insert(i,ListInfo.value(i));
            }
            PhotoNext();
        }
        else
        {
            QMessageBox msg(this);
            msg.setIcon(QMessageBox::Critical);
            msg.setWindowTitle(tr("Error"));
            msg.setText(tr("Can't Write File"));
            msg.setStandardButtons(QMessageBox::Ok);
            msg.setButtonText(QMessageBox::Ok, tr("OK"));
            msg.exec();
        }
    }
}


void MainWindow::on_actionHomePage_triggered()
{
    QDesktopServices::openUrl(QUrl("http://www.jianshu.com/users/0d339158f1a6/latest_articles"));
}

void MainWindow::on_actionAbout_triggered()
{
    About *about = new About(this);
    about->exec();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::exit(0);
}

void MainWindow::on_actionPrint_triggered()
{
    if(PhotoExist)
    {
        QPrinter PhotoPrint;

        QPrintDialog *PhotoPrintDialog = new QPrintDialog(&PhotoPrint,0);

        if(PhotoPrintDialog->exec() == QDialog::Accepted)
        {
            QImage Photo(image1);
            QPainter painter(&PhotoPrint);
            painter.drawImage(QPoint(0,0),Photo);
            painter.end();
        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    if(PhotoExist)
    {
        QFileInfo SaveFile = PhotoMap[PhotoIndex];

        if(SaveFile.suffix() == "png" || SaveFile.suffix() == "PNG" || SaveFile.suffix() == "jpg"
                || SaveFile.suffix() == "JPG" || SaveFile.suffix() == "jpeg" || SaveFile.suffix() == "JPEG"
                || SaveFile.suffix() == "bmp" || SaveFile.suffix() == "BMP" || SaveFile.suffix() == "tif"
                || SaveFile.suffix() == "tiff" || SaveFile.suffix() == "TIF" || SaveFile.suffix() == "TIFF"
                || SaveFile.suffix() == "webp" || SaveFile.suffix() == "WEBP" || SaveFile.suffix() == "jp2"
                || SaveFile.suffix() == "JP2" || SaveFile.suffix() == "dds" || SaveFile.suffix() == "DDS"
                || SaveFile.suffix() == "ppm" || SaveFile.suffix() == "PPM" || SaveFile.suffix() == "xpm"
                || SaveFile.suffix() == "XPM" || SaveFile.suffix() == "pgm" || SaveFile.suffix() == "PGM"
                || SaveFile.suffix() == "xbm" || SaveFile.suffix() == "XBM" || SaveFile.suffix() == "pbm"
                || SaveFile.suffix() == "PBM")
        {
            if(QFile(SaveFile.absoluteFilePath()).open(QIODevice::ReadWrite))
            {
                image1.save(SaveFile.absoluteFilePath());
            }
            else
            {
                QMessageBox msg(this);
                msg.setIcon(QMessageBox::Critical);
                msg.setWindowTitle(tr("Error"));
                msg.setText(tr("Can't Write File"));
                msg.setStandardButtons(QMessageBox::Ok);
                msg.setButtonText(QMessageBox::Ok, tr("OK"));
                msg.exec();
            }
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog OpenPhoto(this);
    OpenPhoto.setFileMode(QFileDialog::ExistingFile);
    OpenPhoto.setNameFilter("All Supported Files (*.png ; *.jpg ; *.jpeg ; *.bmp ; *.tif ; *.tiff ; *.webp ;"
                               "*.gif ; *.jp2 ; *.dds ; *.xpm ; *.pnm ; *.ppm ; *.pgm ; *.wbmp ; *.xbm ; *.pbm ;"
                               "*.ico ; *.icns);; All Files(*)");

    OpenPhoto.setWindowTitle(tr("Open Photo"));


    if(OpenPhoto.exec())
    {
        QStringList PhotoFile;
        PhotoFile = OpenPhoto.selectedFiles();

        QFileInfo FileInfo(PhotoFile.at(0));
        if(FileSuffix.contains(FileInfo.suffix(),Qt::CaseInsensitive))
        {
            PhotoMap.clear();
            PhotoMap[PhotoMap.count()] = FileInfo;
            QList<QFileInfo> fileInfoList = FileInfo.dir().entryInfoList(FileFilter);
            fileInfoList.removeOne(FileInfo);
            while(fileInfoList.count() > 0)
            {
                PhotoMap[PhotoMap.count()] = fileInfoList.takeFirst();
            }
            PhotoExist = true;
            ui->photo->setPixmap(FileInfo.absoluteFilePath());
            image.load(FileInfo.absoluteFilePath());
            image1.load(FileInfo.absoluteFilePath());
            PhotoIndex = 0;
            ui->statusBar->show();
            ZoomFit();
        }
    }
}

void MainWindow::on_actionEffect1_triggered()
{
    ui->actionEffect2->setChecked(false);
    ui->actionEffect1->setChecked(true);
}

void MainWindow::on_actionEffect2_triggered()
{
    ui->actionEffect1->setChecked(false);
    ui->actionEffect2->setChecked(true);
}

void MainWindow::on_actionSkin1_triggered()
{
    ui->actionSkin1->setChecked(true);
    ui->actionSkin2->setChecked(false);
    ui->actionSkin3->setChecked(false);
    QFile file(":/images/white.css");
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
}

void MainWindow::on_actionSkin2_triggered()
{
    ui->actionSkin1->setChecked(false);
    ui->actionSkin2->setChecked(true);
    ui->actionSkin3->setChecked(false);
    QFile file(":/images/blue.css");
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
}

void MainWindow::on_actionSkin3_triggered()
{
    ui->actionSkin1->setChecked(false);
    ui->actionSkin2->setChecked(false);
    ui->actionSkin3->setChecked(true);

    QFile file(":/images/gray.css");
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
}

void MainWindow::on_actionZH_triggered()
{
    ui->actionEN->setChecked(false);
    ui->actionZH->setChecked(true);
    QTranslator *translator = new QTranslator;
    translator->load(":/translation/photoview_zh.qm");
    QApplication::installTranslator(translator);
    SwitchLanguage();
    SetToolBarLabel();
}

void MainWindow::on_actionEN_triggered()
{
    ui->actionEN->setChecked(true);
    ui->actionZH->setChecked(false);
    QTranslator *translator = new QTranslator;
    translator->load(":/translation/photoview_en.qm");
    QApplication::installTranslator(translator);
    SwitchLanguage();
    SetToolBarLabel();
}

QFileInfo MainWindow::GetFileInfo()
{
    return PhotoMap.value(PhotoIndex);
}

QMap<int,QFileInfo> MainWindow::GetAllFileInfo()
{
    return PhotoMap;
}


void MainWindow::Zoom()
{
    qreal pw = image1.width();
    qreal ph = image1.height();
    qreal ww = ui->photo->width();
    qreal wh = ui->photo->height();

    qreal widthFactor = ww / pw;
    qreal heightFactor = wh / ph;

    ZoomFactorFlag = widthFactor <= heightFactor ? true : false;

    if(pw <= ww && ph <= wh)
    {
        ZoomFactor = 1.0;
    }
    else
    {
        if(ZoomFactorFlag)
        {
            ZoomFactor = widthFactor;
        }
        else
        {
            ZoomFactor = heightFactor;
        }
    }

}

void MainWindow::SetToolBarLabel()
{
    QString str;
    int zoom = ZoomFactor * 100;
    str = tr("Zoom ") + QString::number(zoom) + "% | " + PhotoMap.value(PhotoIndex).fileName()
           + " | " + QString::number(image1.width()) + " x " + QString::number(image1.height());
    toolBar->label->setText(str);
}


void MainWindow::SwitchLanguage()
{
    ui->retranslateUi(this);
    toolBar->SwitchLanguage();
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    if(RotateFlipFlag)
    {
        QMessageBox SaveMsg(this);
        int answer;
        SaveMsg.setWindowTitle(tr("Save Changes"));
        SaveMsg.setText(tr("The Photo has been edited."));
        SaveMsg.setInformativeText(tr("Do you want to save your changes?"));
        SaveMsg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        SaveMsg.setDefaultButton(QMessageBox::Save);
        SaveMsg.setButtonText(QMessageBox::Save, tr("Save"));
        SaveMsg.setButtonText(QMessageBox::Discard, tr("Discard"));
        SaveMsg.setButtonText(QMessageBox::Cancel, tr("Cancel"));
        answer = SaveMsg.exec();
        if(answer == QMessageBox::Save)
        {
            on_actionSave_triggered();
        }
        else if (answer == QMessageBox::Discard)
        {
            close();
        }
        else if (answer == QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
}
