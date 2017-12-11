#ifndef DIALOG
#define DIALOG

#include<QWidget>
#include<QPixmap>
#include<QScrollArea>
#include<QResizeEvent>

//有一个bug,就是调用resizeEvent时,就会出现,还没解决
class QAPanel;

class Dialog : public QWidget
{
public:
    static int _space;//两个Dialog之间的间隔
    Dialog(QString str, QAPanel* parent);

    inline void setText(QString str){_text = str;}
    inline void setBackgroundColor(const QColor& c){m_backgroundColor = c;}
    inline void setRadius(int r){m_radius = r;}
    inline void setSpace(int s){_space = s;}
    inline void setPanel(QAPanel* p){mypanel = p;}
    inline void sety(int v){y = v;}

    void setFontSize(int s);
    void setFontFamily(QString s);
    void setPix(const QPixmap& p);

    virtual void adjustx() = 0;

    /**
     * @brief 注意这里的size没有把pixcontent考虑进来
     * @return
     */
    virtual QSize sizeHint() const;

protected:
    friend class QAPanel;
    QAPanel* mypanel;

    QColor m_backgroundColor,m_fontColor;
    QString _text;
    bool m_translucent;
    int m_radius;
    QPixmap headpix,pixcontent;//headpix是头像;pixcontent是文字区里可有可无的图片

    int x,y;//开始画的起始点

    virtual void paintEvent(QPaintEvent *) = 0;

    /**
     * @brief 当文字超过界面的边框时,加上回车符
     * @param str
     */
    void handleText(const QString & str);
};


class Question : public Dialog
{
public:
    Question(QString str, QAPanel* parent);

    void adjustx();
    QSize sizeHint()const;

protected:
    void paintEvent(QPaintEvent *);
};


class Answer : public Dialog
{
public:
    Answer(QString str, QAPanel* parent);

    void adjustx();
    QSize sizeHint()const;

protected:
    void paintEvent(QPaintEvent *);
};

/**
 * @brief 一个显示对话内容的板,由于没有滚动条,所以不用它
 */
class QAPanel : public QWidget
{
private:
    friend class Dialog;
    friend class Question;
    friend class Answer;

    int _width;
    QList<Dialog*> dialogs;

    /**
     * @brief 如果要添加对话,返回现在应当的位置,这里加了两个Dialog之间的间隔
     * @return
     */
    int currentStartLevel() const;

protected:
//    void resizeEvent(QResizeEvent* event)
//    {
//        foreach(Dialog* d,dialogs)
//        {
//            d->adjustx();
//            d->move(d->x,d->y);
//        }
//    }
    friend class QAPanelScroll;
    QAPanel(QWidget* w,QAPanelScroll*);
    QAPanelScroll* myview;//由于要实现自动滚动，所以把它加进来

public:
    void addDialog(Dialog* d);
    void clearDialog();

    /**
     * @brief 对话大小可能会变，比如对话的图片加载进来了
     */
    void adjustAllDialog();
    void saveScreenShot();

    int getDialogCount()const{return dialogs.size();}
    QSize sizeHint () const;
};



class QAPanelScroll : public QScrollArea
{
public:
    QAPanelScroll(QWidget* w=0);
    ~QAPanelScroll(){delete panel;}

    QAPanel& operator* (){return *panel;}
    QAPanel* operator->(){return panel;}

    /**
     * @brief 把滚动条滑至最底部
     */
    void moveScrollToEnd();

protected:
//    void resizeEvent(QResizeEvent* e)
//    {
//        panel->resize(e->size().width(),panel->width());
//    }

private:
    QAPanel* panel;
};
#endif // DIALOG

