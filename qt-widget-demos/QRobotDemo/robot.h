#ifndef ROBOT
#define ROBOT

#include<map>
#include<QWidget>

#include"my.h"
#include"dialog.h"
#include"network.h"
#include<qlineedit.h>

class Robot : public QWidget
{
    Q_OBJECT

public:
    Robot(QWidget* w = 0);

public slots:
    void newQuestion();
    void handleDownload(QNetworkReply*);

    /**
     * @brief 清除对话
     */
    void clearAllContents();
    void saveScreenshot();

private:
    QAPanelScroll panel;
    Network *network;
    my::Button send,clear,screenshot;
    QLineEdit line;

    /**
     * @brief 和QNetworkReply*一起使用,用来储存信息,是文字还是图片
     */
    class Info
    {
    public:
        Info() : type(TEXT), dialog(0){}
        bool isText()const{return type == TEXT;}
        bool isPhoto()const{return type == PHOTO;}
        /**
         * @brief 如果是图片,则还要有Dialog*,图片属于它
         * @return
         */
        Dialog* getDialog()const{return dialog;}
        void setDialog(Dialog* d){dialog = d; type = PHOTO;}

    private:
        enum DownloadType{TEXT, PHOTO};
        DownloadType type;
        Dialog* dialog;
    };

    std::map<QNetworkReply*,Info> _replys;

    static const QString answer_code;
    void setButton();
    void setLine();
    void setPanel();

    Dialog* addQuestion(QString str);
    void addQuestion(QString str,const QPixmap& p);

    Dialog* addAnswer(QString str);
    void addAnswer(QString str,const QPixmap& p);

    QString handleText(const QString& str);//code=100000

    void handleTrainSchedule(const QString& str);//code=305000 提取list里的内容，包含多个车次信息
    void handleTrainSchedule_step1(const QString& list);//将list里的火车信息内容分割，
    QString handleTrainSchedule_step2(const QString& info
                                      ,QString& icon,QString& detail);//提取火车信息中的trainnum等,并将icon,detail的地址赋值
    void handleUrl(const QString& str);//code=200000
    void handleNews(const QString& str);//code=302000
    void handleRecipe(const QString& str);//code=308000
};

#endif // ROBOT

