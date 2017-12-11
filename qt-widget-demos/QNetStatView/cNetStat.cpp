#include "cNetStat.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QProcess>


cNetStat::cNetStat(){

}


void cNetStat::run(){
    getNetStat();
    emit endReadStat(save_netstat);
}

QVector<sNetStat> cNetStat::getTable(){
    sNetStat netstat;
    QVector<sNetStat> result;


#if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
    QVector<QString> prots;     // Протоколы
    QList<QString>  states;     // Статусы подключений

    // Список протоколов
    prots << "tcp" << "udp" << "tcp6" << "udp6" << "icmp";

    // Массив статусов подключений
    states << "" << "ESTABLISHED" << "SYN_SENT" << "SYN_RECV" << "FIN_WAIT1" <<  "FIN_WAIT2";
    states << "TIME_WAIT" <<  "CLOSE" << "CLOSE_WAIT" << "LAST_ACK" << "LISTEN";
    states << "CLOSING" <<  "CLOSED";

    // Обновление списка процесов
    ProcessListLinux proc;
    proc.initProccessList();


    for (int p=0;p<prots.size();p++){
        QFile file("/proc/net/"+prots.at(p));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << file.errorString();
            return result;
        }

        QTextStream in(&file);
        QStringList buf = in.readAll().split("\n");
        file.close();
        for (int i=1;i<buf.size()-1;i++){
            //("", "sl", "local_address", "rem_address", "st", "tx_queue", "rx_queue", "tr", "tm->when", "retrnsmt", "uid", "timeout", "inode", "")
            //("", "18:", "4B80A8C0:DA90", "5480A8C0:008B", "01", "00000000:00000000", "02:000A6A42", "00000000", "500", "0", "7793475", "2", "d6798fc0", "20", "3", "32", "10", "-1", "")
            QStringList ns = buf.at(i).split(QRegExp("\\s+"));

            netstat.prot=prots.at(p).toUpper();
            netstat.local_address=convAddress(ns.at(2),netstat.prot);
            netstat.rem_address=convAddress(ns.at(3),netstat.prot);
            netstat.stat=states[ns.at(4).toInt(0,16)];
            netstat.process = proc.getProc(ns.at(10));

            result.append(netstat);
        }
    }

#endif


#if defined(Q_OS_WIN)
    //Имя    Локальный адрес        Внешний адрес          Состояние       PID
    //TCP    0.0.0.0:80             0.0.0.0:0              LISTENING       3480
    //TCP    0.0.0.0:135            0.0.0.0:0              LISTENING       1708

    ProcessListWindows proc;
    proc.initProccessList();


    QProcess *myProcess = new QProcess();
    myProcess->start("netstat.exe", QStringList() << "-n" << "-a" << "-o");

    if (myProcess->waitForFinished(2000)==false){
        qDebug() << myProcess->errorString();
        return result;
    }

    QStringList table = QString(myProcess->readAll()).split("\n");
    for (int t=3;t<table.size();t++){
        QStringList ns = table.at(t).split(QRegExp("\\s+"));

        //qDebug() << ns;

        if (ns.size()<2) continue;

        if (ns.at(1)=="TCP"){
            netstat.prot=ns.at(1);
            netstat.local_address=ns.at(2);
            netstat.rem_address=ns.at(3);
            netstat.stat=ns.at(4);
            netstat.process = proc.getProc(ns.at(5));
            result.append(netstat);
        }
        if (ns.at(1)=="UDP"){
            netstat.prot=ns.at(1);
            netstat.local_address=ns.at(2);
            netstat.rem_address=ns.at(3);
            netstat.stat="";
            netstat.process = proc.getProc(ns.at(4));

            netstat.rem_address.replace("*:*","0.0.0.0:0");
            netstat.rem_address.replace("*:*","0.0.0.0:0");
            result.append(netstat);
        }

    }

#endif


#if defined(Q_OS_OS2)
    //SOCK   TYPE       FOREIGN          LOCAL         FOREIGN         STATE
    //                   PORT             PORT            HOST
    //2302 STREAM               0            6881         0.0.0.0  LISTEN
    //2304  DGRAM               0            6881         0.0.0.0  UDP

    QProcess *myProcess = new QProcess();
    myProcess->start("netstat", QStringList() << "-s");

    if (myProcess->waitForFinished(2000)==false){
        qDebug() << myProcess->errorString();
        return result;
    }

    QString procData = myProcess->readAll();
    QStringList table = QString(procData).split("\n");

    for (int t=10;t<table.size();t++){

        QStringList ns = table.at(t).split(QRegExp("\\s+"));

        /*
        writeLog(table.at(t));
        QString d="";
        for (int l=0;l<ns.size();l++){
            d+=ns.at(l)+" {"+QString::number(l)+"}| ";
        }
        writeLog("["+QString::number(ns.size())+"]");
        writeLog(d);
        writeLog("-----\n");
        */

        if (ns.size()!=8) return result;


        QString foreign_port=ns.at(3);
        if (foreign_port.split("..").size()==2) foreign_port=foreign_port.split("..").at(1);

        QString local_port=ns.at(4);
        if (local_port.split("..").size()==2) local_port=local_port.split("..").at(1);

        if (ns.at(6)=="CLOSED") continue;

        if (ns.at(6)=="UDP"){
            netstat.stat="CLOSE";
            netstat.prot="UDP";
        }else{
            netstat.stat=ns.at(6);
            netstat.prot="TCP";
        }

        netstat.local_address="0.0.0.0:"+local_port;
        netstat.rem_address=ns.at(5)+":"+foreign_port;
        netstat.process = sProccess();
        result.append(netstat);

    }
#endif


    return result;
}




QVector<sNetStat> cNetStat::getNetStat(){

    // Получение данных о сетевых процессах
    sNetStat netstat;
    QVector<sNetStat> result;



    QVector<sNetStat>  TableNet = getTable();

    for (int i=0;i<TableNet.size();i++){
        netstat=TableNet.at(i);

        if (netstat.local_address.split(":").at(0)=="0.0.0.0") netstat.local_address="*:"+netstat.local_address.split(":").at(1);
        if (netstat.rem_address=="0.0.0.0:0") netstat.rem_address="*";


        netstat.operation=-1;
        if (save_netstat.size()>0){
            for (int s=0;s<save_netstat.size();s++){
                if ((netstat.local_address == save_netstat.at(s).local_address) &&  (netstat.rem_address == save_netstat.at(s).rem_address))
                {
                    if (QTime::currentTime() < save_netstat.at(s).timeEvent.addSecs(5)){
                        netstat.operation=save_netstat.at(s).operation;
                    }else{
                        netstat.operation=0;
                    }
                    break;
                }
            }
            if (netstat.operation==-1){
                netstat.operation=1;
                netstat.timeEvent=QTime::currentTime();
            }
        }else{
            netstat.operation=0;
        }
        result.append(netstat);
    }


    // Показ старых подключений
    bool isExistProc=false;
    for (int p=0;p<save_netstat.size();p++)
    {
        isExistProc=false;
        for (int n=0;n<result.size();n++)
        {
            if ((save_netstat.at(p).local_address == result.at(n).local_address) && (save_netstat.at(p).rem_address == result.at(n).rem_address))
            {
                isExistProc=true;
                break;
            }
        }
        if (isExistProc==false)
        {
            if (save_netstat.at(p).operation==2)
            {
                if (QTime::currentTime() < save_netstat.at(p).timeEvent.addSecs(5))
                {
                    netstat=save_netstat.at(p);
                    result.append(netstat);
                }
            }
            else
            {
                netstat=save_netstat.at(p);
                netstat.operation=2;
                netstat.timeEvent=QTime::currentTime();
                result.append(netstat);
            }
        }

    }



    save_netstat=result;

    return result;
}



QString cNetStat::convAddress(QString address,QString ipv){
    // Конвертирование IP адреса из 16-ричной в 10-ричную систему.
    QString result="";
    QStringList octet;
    bool ok;

    QString a= address.split(":").at(0);
    QString p= address.split(":").at(1);



    if (ipv=="TCP6" || ipv=="UDP6" || ipv=="ICMP6")
    {
        // Незнаю как тут правильно
        for (int i=16;i>0;i=i-4)
        {
            octet.append(a.mid(i-4,4));
        }
        result = octet.join(":");
    }
    else
    {
        for (int i=8;i>0;i=i-2)
        {
            octet.append(QString::number(a.mid(i-2,2).toInt(&ok,16)));
        }
        result = octet.join(".");
    }


    result += ":" + QString::number(p.toInt(&ok,16));

    return result;
}


void cNetStat::writeLog(QString str){
    QFile file(QDir::currentPath()+"/debug.log");

    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << str << "\n";
    file.close();
}
