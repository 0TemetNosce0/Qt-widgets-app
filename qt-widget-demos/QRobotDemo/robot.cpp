#include "robot.h"

#include <QGridLayout>
#include <QNetworkReply>

const QString Robot::answer_code = "code";

Robot::Robot(QWidget* w)
    : QWidget(w)
    , panel(this)
    , send("Send")
    , clear("Clear")
    , screenshot("Screenshot")
{
    setWindowTitle(QStringLiteral("图灵机器人"));
    network = Network::instance();
    Answer *answer = new Answer(QStringLiteral("你好,我是机器人图灵,有什么可以帮您"),&*panel);
    panel->addDialog(answer);

    setButton();
    setLine();
    setPanel();

    QGridLayout* lay = new QGridLayout(this);
    lay->addWidget(&panel, 0, 0, 1, 3);
    lay->addWidget(&line, 1, 0, 1, 3);
    lay->addWidget(&screenshot, 2, 0);
    lay->addWidget(&clear, 2, 1);
    lay->addWidget(&send, 2, 2);

    setStyleSheet("background-color:rgb(61, 61, 61);");
    my::moveToScrCenter(this);

    connect(&send, SIGNAL(clicked()), this, SLOT(newQuestion()));
    connect(&clear, SIGNAL(clicked()), this, SLOT(clearAllContents()));
    connect(&screenshot, SIGNAL(clicked()), this, SLOT(saveScreenshot()));
    connect(network, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleDownload(QNetworkReply*)));
}

Dialog* Robot::addQuestion(QString str)
{
    Question *question = new Question(str,&*panel);
    panel->addDialog(question);
    return question;
}

Dialog* Robot::addAnswer(QString str)
{
    Answer *answer = new Answer(str,&*panel);
    panel->addDialog(answer);
    panel->update();
    return answer;
}

void Robot::clearAllContents()
{
    panel->clearDialog();
}

void Robot::saveScreenshot()
{
    panel->saveScreenShot();
}

void Robot::newQuestion()
{
    const QString &str = line.text();

    if(str.size() == 0)
    {
        return;
    }

    addQuestion(str);

    QString what("http://www.tuling123.com/openapi/api?key=你在图灵机器人网申请的KEY&info=");
    what.append(str);
    what.append(QStringLiteral("&userid=随便填"));
    network->get(what);
    line.setText("");
}

void Robot::setButton()
{
    send.setColor(QColor(105, 105, 105));
    send.setAnimated(true);
    send.setTextColor(Qt::white);
    send.setTranparentBackground(true);
    send.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    clear.setColor(QColor(105, 105, 105));
    clear.setAnimated(true);
    clear.setTextColor(Qt::white);
    clear.setTranparentBackground(true);
    clear.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    screenshot.setColor(QColor(105, 105, 105));
    screenshot.setAnimated(true);
    screenshot.setTextColor(Qt::white);
    screenshot.setTranparentBackground(true);
    screenshot.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    clear.setMinimumHeight(45);
    send.setMinimumHeight(45);
    screenshot.setMinimumHeight(45);
}

void Robot::setLine()
{
    QFont f(QStringLiteral("微软雅黑"));
    f.setPixelSize(12);
    line.setFont(f);
    line.setMinimumHeight(40);
    line.setStyleSheet("border:5px groove rgb(255,127,39);"
                       "padding:0px ;"
                       "background-color:white;");
    line.setFocus();
    connect(&line, SIGNAL(returnPressed()), this, SLOT(newQuestion()));
}

void Robot::setPanel()
{
    panel.setMinimumSize(395, 500);
}

void Robot::handleDownload(QNetworkReply* reply)
{
    Info info = _replys[reply];

    if(info.isText())
    {
        QString what;

        QString codestr;

        what = QString::fromUtf8(reply->readAll());
        int pos = what.indexOf(answer_code);

        for(int i = pos + 6; ; i++)
        {
            if(what.at(i) == QChar(','))
            {
                break;
            }

            if(what.at(i) == QChar('}'))
            {
                break;
            }

            if(what.at(i) == QChar('"'))
            {
                break;
            }

            if(i >= what.size())
            {
                break;
            }
            codestr += what.at(i);
        }

        if(codestr == "100000")
        {
            QString &answer = handleText(what);
            addAnswer(answer);
        }
        else if(codestr == "305000")
        {
            QString &answer = handleText(what);
            addAnswer(answer);
            handleTrainSchedule(what);
        }
    }
    else
    {
        //这个时候下截来的图片,肯定是属于某一个对话的
        Dialog* d = info.getDialog();

        QPixmap pix;
        pix.loadFromData(reply->readAll());
        d->setPix(pix);
    }

    _replys.erase(reply);
    reply->deleteLater();
}

QString Robot::handleText(const QString& str)//code=100000
{
    //处理text内容
    QString answer("");
    int pos = str.indexOf(QStringLiteral("text"));
    for(int i = pos + 7; ; i++)
    {
        if(str.at(i) == QChar('}'))
        {
            break;
        }

        if(str.at(i) == QChar('"'))
        {
            break;
        }

        if(i >= str.size())
        {
            break;
        }
        answer += str.at(i);
    }

    return answer;
}

void Robot::handleTrainSchedule(const QString& str)//code=305000
{
    int pos = str.indexOf(QStringLiteral("\"list\":["));
    QString answer("");//list表里的内容

    for(int i = pos + 8; ;i++)
    {
        if(str.at(i) == QChar(']'))
        {
            break;
        }

        if(i >= str.size())
        {
            break;
        }

        answer += str.at(i);
    }

    handleTrainSchedule_step1(answer);
}

void Robot::handleTrainSchedule_step1(const QString& list)
{
    int pos = 1;
    QString train;//将list里的每一躺火车信息分割到train里
    for(; pos < list.size(); pos++)
    {
        if(list.at(pos) == QChar('}'))
        {
            QString icon,detailurl;
            QString text = handleTrainSchedule_step2(train,icon,detailurl);

            QNetworkReply* r = network->get(icon);

            Info info;
            info.setDialog(addAnswer(text));
            _replys[r] = info;
            train = "";
            continue;
        }

        train += list.at(pos);
    }
}

QString Robot::handleTrainSchedule_step2(const QString& info,
                                         QString& icon, QString& detailurl)
{
    QString traininfo;
    int pos = info.indexOf(QStringLiteral("trainnum"));
    QString trainnum("");

    for(int i = pos + 11; i < info.size(); i++)
    {
        if(info.at(i) == QChar('"'))
        {
            break;
        }
        trainnum += info.at(i);
    }

    pos = info.indexOf(QStringLiteral("start"));
    QString start("");

    for(int i = pos + 8; i < info.size(); i++)
    {
        if(info.at(i) == QChar('"'))
        {
            break;
        }
        start += info.at(i);
    }

    pos = info.indexOf(QStringLiteral("terminal"));
    QString terminal("");
    for(int i = pos + 11; i < info.size(); i++)
    {
        if(info.at(i) == QChar('"'))
        {
            break;
        }
        terminal += info.at(i);
    }
    pos = info.indexOf(QStringLiteral("starttime"));
    QString starttime("");
    for(int i = pos + 12; i < info.size(); i++)
    {
        if(info.at(i) == QChar('"'))
        {
            break;
        }
        starttime += info.at(i);
    }
    pos = info.indexOf(QStringLiteral("endtime"));
    QString endtime("");
    for(int i = pos + 10; i < info.size(); i++)
    {
        if(info.at(i) == QChar('"'))
        {
            break;
        }
        endtime += info.at(i);
    }
    //icon图标的地址
    pos = info.indexOf(QStringLiteral("icon"));

    for(int i = pos + 7; i < info.size(); i++)
    {
        if(info.at(i) == QChar('"'))
        {
            break;
        }
        icon += info.at(i);
    }
    //detailurl
    pos = info.indexOf(QStringLiteral("detailurl"));
    for(int i = pos + 12; i < info.size();  i++)
    {
        if(info.at(i) == QChar('"'))
        {
            break;
        }
        detailurl += info.at(i);
    }
    traininfo.append(QStringLiteral("列车车次：") + trainnum + "\n");
    traininfo.append(QStringLiteral("起点：") + start + "\n");
    traininfo.append(QStringLiteral("终点：") + terminal + "\n");
    traininfo.append(QStringLiteral("开始时间：") + starttime + "\n");
    traininfo.append(QStringLiteral("到达时间：") + endtime);
    return traininfo;
}

void Robot::handleUrl(const QString& )//code=200000
{

}

void Robot::handleNews(const QString& )//code=302000
{

}

void Robot::handleRecipe(const QString& )//code=308000
{

}
