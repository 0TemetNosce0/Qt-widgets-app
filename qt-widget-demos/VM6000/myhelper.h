#ifndef MYHELPER_H
#define MYHELPER_H

#include <QtCore>
#include <QtGui>
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif
#include <QtNetwork>
#include <QtSql>
#include "frmmessagebox.h"
#include "frminputbox.h"

/* ˵��:ȫ�ָ���������ʵ���ļ�
 * ����:������ʾ/��������/��������/�ļ�ѡ���븴��/�Ի����
 * ����:������  QQ:517216493
 * ʱ��:2013-12-30  ���:2014-1-10
 */
class myHelper: public QObject
{

public:

    //����Ϊ��������
    static void AutoRunWithSystem(bool IsAutoRun, QString AppName, QString AppPath)
    {
        QSettings *reg = new QSettings(
            "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
            QSettings::NativeFormat);

        if (IsAutoRun)
        {
            reg->setValue(AppName, AppPath);
        }
        else
        {
            reg->setValue(AppName, "");
        }
    }

    //���ñ���ΪUTF8
    static void SetUTF8Code() {
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif
    }

    //����Ϊ�����ַ�
    static void SetChinese()
    {
        QTranslator *translator = new QTranslator(qApp);
        translator->load(":/image/qt_zh_CN.qm");
        qApp->installTranslator(translator);
    }

    //����ָ����ʽ
    static void SetStyle(const QString &qssFile)
    {
        QFile file(qssFile);
        if (file.open(QFile::ReadOnly))
        {
            QString qss = QLatin1String(file.readAll());
            qApp->setStyleSheet(qss);
            QString PaletteColor = qss.mid(20, 7);
            qApp->setPalette(QPalette(QColor(PaletteColor)));
            file.close();
        }
    }

    //�ж��Ƿ���IP��ַ
    static bool IsIP(QString IP)
    {
        QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
        return RegExp.exactMatch(IP);
    }

    //��ʾ�����
    static QString ShowInputBox(QString info, bool &ok)
    {
        frmInputBox input;
        input.SetMessage(info);
        ok = input.exec();
        return input.GetValue();
    }

    //��ʾ��Ϣ��,��ȷ����ť
    static void ShowMessageBoxInfo(QString info)
    {
        frmMessageBox msg ;
        msg.SetMessage(info, 0);
        msg.exec();
    }

    //��ʾ�����,��ȷ����ť
    static void ShowMessageBoxError(QString info)
    {
        frmMessageBox msg;
        msg.SetMessage(info, 2);
        msg.exec();
    }

    //��ʾѯ�ʿ�,ȷ����ȡ����ť
    static int ShowMessageBoxQuesion(QString info)
    {
        frmMessageBox msg;
        msg.SetMessage(info, 1);
        return msg.exec();
    }

    //16�����ַ���ת�ֽ�����
    static QByteArray HexStrToByteArray(QString str)
    {
        QByteArray senddata;
        int hexdata, lowhexdata;
        int hexdatalen = 0;
        int len = str.length();
        senddata.resize(len / 2);
        char lstr, hstr;
        for (int i = 0; i < len; )
        {
            hstr = str[i].toLatin1();
            if (hstr == ' ')
            {
                i++;
                continue;
            }
            i++;

            if (i >= len)
            {
                break;
            }
            lstr = str[i].toLatin1();
            hexdata = ConvertHexChar(hstr);
            lowhexdata = ConvertHexChar(lstr);

            if ((hexdata == 16) || (lowhexdata == 16))
            {
                break;
            }
            else
            {
                hexdata = hexdata * 16 + lowhexdata;
            }
            i++;
            senddata[hexdatalen] = (char)hexdata;
            hexdatalen++;
        }
        senddata.resize(hexdatalen);
        return senddata;
    }

    static char ConvertHexChar(char ch)
    {
        if ((ch >= '0') && (ch <= '9'))
        {
            return ch - 0x30;
        }
        else if ((ch >= 'A') && (ch <= 'F'))
        {
            return ch - 'A' + 10;
        }
        else if ((ch >= 'a') && (ch <= 'f'))
        {
            return ch - 'a' + 10;
        }
        else
        {
            return (-1);
        }
    }

    //�ֽ�����ת16�����ַ���
    static QString ByteArrayToHexStr(QByteArray data)
    {
        QString temp = "";
        QString hex = data.toHex();
        for (int i = 0; i < hex.length(); i = i + 2)
        {
            temp += hex.mid(i, 2) + " ";
        }
        return temp.trimmed().toUpper();
    }

    //16�����ַ���ת10����
    static int StrHexToDecimal(QString strHex)
    {
        bool ok;
        return strHex.toInt(&ok, 16);
    }

    //10�����ַ���ת10����
    static int StrDecimalToDecimal(QString strDecimal)
    {
        bool ok;
        return strDecimal.toInt(&ok, 10);
    }

    //2�����ַ���ת10����
    static int StrBinToDecimal(QString strBin)
    {
        bool ok;
        return strBin.toInt(&ok, 2);
    }

    //16�����ַ���ת2�����ַ���
    static QString StrHexToStrBin(QString strHex)
    {
        uchar decimal = StrHexToDecimal(strHex);
        QString bin = QString::number(decimal, 2);
        uchar len = bin.length();
        if (len < 8)
        {
            for (int i = 0; i < 8 - len; i++)
            {
                bin = "0" + bin;
            }
        }
        return bin;
    }

    //10����ת2�����ַ���һ���ֽ�
    static QString DecimalToStrBin1(int decimal)
    {
        QString bin = QString::number(decimal, 2);
        uchar len = bin.length();
        if (len <= 8)
        {
            for (int i = 0; i < 8 - len; i++)
            {
                bin = "0" + bin;
            }
        }
        return bin;
    }

    //10����ת2�����ַ��������ֽ�
    static QString DecimalToStrBin2(int decimal)
    {
        QString bin = QString::number(decimal, 2);
        uchar len = bin.length();
        if (len <= 16)
        {
            for (int i = 0; i < 16 - len; i++)
            {
                bin = "0" + bin;
            }
        }
        return bin;
    }

    //10����ת16�����ַ���,����.
    static QString DecimalToStrHex(int decimal)
    {
        QString temp = QString::number(decimal, 16);
        if (temp.length() == 1)
        {
            temp = "0" + temp;
        }
        return temp;
    }

    //��ʱ
    static void Sleep(int sec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while ( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }

    //����ϵͳ����ʱ��
    static void SetSystemDateTime(int year, int month, int day, int hour, int min, int sec)
    {
        QProcess p(0);

        p.start("cmd");
        p.waitForStarted();
        p.write(QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1());
        p.closeWriteChannel();
        p.waitForFinished(1000);
        p.close();

        p.start("cmd");
        p.waitForStarted();
        p.write(QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1());
        p.closeWriteChannel();
        p.waitForFinished(1000);
        p.close();
    }

    //���������ʾ
    static void FormInCenter(QWidget *frm, int deskWidth, int deskHeigth)
    {
        int frmX = frm->width();
        int frmY = frm->height();
        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeigth / 2 - frmY / 2);
        frm->move(movePoint);
    }

    //��ȡѡ����ļ�
    static QString GetFileName(QString filter)
    {
        return QFileDialog::getOpenFileName(0, "ѡ���ļ�", QCoreApplication::applicationDirPath(), filter);
    }

    //��ȡѡ����ļ�����
    static QStringList GetFileNames(QString filter)
    {
        return QFileDialog::getOpenFileNames(0, "ѡ���ļ�", QCoreApplication::applicationDirPath(), filter);
    }

    //��ȡѡ���Ŀ¼
    static QString GetFolderName()
    {
        return QFileDialog::getExistingDirectory();;
    }

    //��ȡ�ļ���,����չ��
    static QString GetFileNameWithExtension(QString strFilePath)
    {
        QFileInfo fileInfo(strFilePath);
        return fileInfo.fileName();
    }

    //��ȡѡ���ļ����е��ļ�
    static QStringList GetFolderFileNames(QStringList filter)
    {
        QStringList fileList;
        QString strFolder = QFileDialog::getExistingDirectory();
        if (!strFolder.length() == 0)
        {
            QDir myFolder(strFolder);
            if (myFolder.exists())
            {
                fileList = myFolder.entryList(filter);
            }
        }
        return fileList;
    }

    //�ļ����Ƿ����
    static bool FolderIsExist(QString strFolder)
    {
        QDir tempFolder(strFolder);
        return tempFolder.exists();
    }

    //�ļ��Ƿ����
    static bool FileIsExist(QString strFile)
    {
        QFile tempFile(strFile);
        return tempFile.exists();
    }

    //�����ļ�
    static bool CopyFile(QString sourceFile, QString targetFile)
    {
        if (FileIsExist(targetFile))
        {
            if (ShowMessageBoxQuesion("�ļ��Ѿ�����,�Ƿ��滻?") == 1)
            {
                return false;
            }
        }
        return QFile::copy(sourceFile, targetFile);
    }

    //�������㷨
    static QString getXorEncryptDecrypt(QString str, char key)
    {
        QByteArray data = str.toLatin1();
        int size = data.size();
        for (int i = 0; i < size; i++)
        {
            data[i] = data[i] ^ key;
        }
        return QLatin1String(data);
    }

    //���������Ƿ�����
    static bool IPCEnable(QString rtspAddr)
    {
        QStringList temp = rtspAddr.split("/");
        QString ip = temp[2].split(":")[0];
        QTcpSocket tcpClient;
        tcpClient.abort();
        tcpClient.connectToHost(ip, 80);
        //100����û�����������жϸ������������
        bool ok = tcpClient.waitForConnected(100);
        return ok;
    }
};

#endif // MYHELPER_H
