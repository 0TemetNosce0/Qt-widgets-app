#include "photoinfo.h"
#include "ui_photoinfo.h"
#include "mainwindow.h"
#include <QFileInfo>
#include <QDateTime>

PhotoInfo::PhotoInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhotoInfo)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(421,241);
}

PhotoInfo::~PhotoInfo()
{
    delete ui;
}


void PhotoInfo::showEvent(QShowEvent *)
{
    MainWindow *w = (MainWindow*)this->parentWidget();

    QFileInfo FileInfo = w->GetFileInfo();

    ui->NameVal->setText(FileInfo.fileName());
    ui->DirectoryVal->setText(FileInfo.path());

    if (FileInfo.size()<1024)
    {
        ui->SizeVal->setText(QString::number(FileInfo.size()) + " Byte");
    }
    else if(FileInfo.size() >= 1024)
    {
        ui->SizeVal->setText(QString::number(FileInfo.size()/1024) + " KB");
    }else if(FileInfo.size() >= 1024*1024)
    {
        ui->SizeVal->setText(QString::number(FileInfo.size()/1024/1024) + " MB");
    }
    else
    {
         ui->SizeVal->setText(QString::number(FileInfo.size()/1024/1024/1024) + " MB");
    }

    if(FileInfo.suffix() == "png" || FileInfo.suffix() == "PNG")
    {
        ui->TypeVal->setText("Portable Network Graphics");
    }
    else if(FileInfo.suffix() == "jpg" || FileInfo.suffix() == "JPG" ||
            FileInfo.suffix() == "jpeg" || FileInfo.suffix() == "JPEG")
    {
        ui->TypeVal->setText("JPEG Image");
    }
    else if(FileInfo.suffix() == "bmp" || FileInfo.suffix() == "BMP")
    {
        ui->TypeVal->setText("BMP file format");
    }
    else if(FileInfo.suffix() == "tif" || FileInfo.suffix() == "tiff" ||
            FileInfo.suffix() == "TIF" || FileInfo.suffix() == "TIFF")
    {
        ui->TypeVal->setText("Tagged Image File Format");
    }
    else if(FileInfo.suffix() == "webp" || FileInfo.suffix() == "WEBP")
    {
        ui->TypeVal->setText("WebP");
    }
    else if(FileInfo.suffix() == "gif" || FileInfo.suffix() == "GIF")
    {
        ui->TypeVal->setText("GIF Image");
    }
    else if(FileInfo.suffix() == "jp2" || FileInfo.suffix() == "JP2")
    {
        ui->TypeVal->setText("JPEG 2000");
    }
    else if(FileInfo.suffix() == "dds" || FileInfo.suffix() == "DDS")
    {
        ui->TypeVal->setText("DirectDraw Surface");
    }
    else if(FileInfo.suffix() == "ppm" || FileInfo.suffix() == "PPM")
    {
        ui->TypeVal->setText("Portable Pixmap");
    }
    else if(FileInfo.suffix() == "xpm" || FileInfo.suffix() == "XPM")
    {
        ui->TypeVal->setText("X11 Pixmap");
    }
    else if(FileInfo.suffix() == "pnm" || FileInfo.suffix() == "PNM")
    {
        ui->TypeVal->setText("PNM Image");
    }
    else if(FileInfo.suffix() == "ppm" || FileInfo.suffix() == "PPM")
    {
        ui->TypeVal->setText("PNM Image");
    }
    else if(FileInfo.suffix() == "pgm" || FileInfo.suffix() == "PGM")
    {
        ui->TypeVal->setText("Pgm Image");
    }
    else if(FileInfo.suffix() == "wbmp" || FileInfo.suffix() == "WBMP")
    {
        ui->TypeVal->setText("Wireless Bitmap");
    }
    else if(FileInfo.suffix() == "xbm" || FileInfo.suffix() == "XBM")
    {
        ui->TypeVal->setText("X11 Bitmap");
    }
    else if(FileInfo.suffix() == "ico" || FileInfo.suffix() == "ICO")
    {
        ui->TypeVal->setText("Windows Icon format");
    }
    else if(FileInfo.suffix() == "icns" || FileInfo.suffix() == "ICNS")
    {
        ui->TypeVal->setText("Apple Icon Image format");
    }
    else
    {
        if(!FileInfo.suffix().isEmpty())
        {
            ui->TypeVal->setText(FileInfo.suffix()+" File");
        }
        else
        {
            ui->TypeVal->setText("Unknown File Type");
        }
    }

    ui->WidthVal->setNum(QPixmap(FileInfo.absoluteFilePath()).width());
    ui->HeightVal->setNum(QPixmap(FileInfo.absoluteFilePath()).height());
    ui->TimeVal->setText(FileInfo.created().date().toString());
}



void PhotoInfo::on_OK_clicked()
{
    close();
}
