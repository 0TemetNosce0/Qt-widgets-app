#include"dialog.h"

#include <QPainter>
#include <QScrollBar>
#include <QMessageBox>

int Dialog::_space = 8;

Dialog::Dialog(QString str,QAPanel* parent)
    : QWidget(parent)
    , mypanel(parent)
    , m_backgroundColor(QColor(160, 230, 90))
    , m_fontColor(Qt::black)
    , m_translucent(false)
    , m_radius(10)
    , x(Dialog::_space)
    , y(Dialog::_space)
{
    handleText(str);
    QFont f(tr("微软雅黑"));
    f.setPixelSize(18);
    setFont(f);
    resize(sizeHint());
}

void Dialog::setFontFamily(QString s)
{
    QFont f = font();
    f.setFamily(s);
    setFont(f);
}

void Dialog::setFontSize(int s)
{
    QFont f = font();
    f.setPixelSize(s);
    setFont(f);
}

void Dialog::setPix(const QPixmap& p)
{
    pixcontent = p.scaled(mypanel->width() / 3, mypanel->width() / 3,
                          Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //尺寸这个时候肯定会变
    const QSize& s = sizeHint();
    int w = pixcontent.width() + headpix.width()>width() ? 
                pixcontent.width() + headpix.width() : width();
    int h = height() + pixcontent.height();
    resize(w, h);
    //通知mypanel,自己的尺寸已经变了
    mypanel->adjustAllDialog();
}

void Dialog::handleText(const QString & str)
{
    QString line("");
    QFontMetrics& me = fontMetrics();
    for(int i = 0; i < str.size(); i++)
    {
        if(me.width(line) > mypanel->width() / 3)
        {
            _text.append(line);
            _text.append("\n");
            line = "";
            line += str.at(i);
            continue;
        }
        line += str.at(i);
    }
    _text.append(line);
}

QSize Dialog::sizeHint()const
{
    QSize s = fontMetrics().size(Qt::TextExpandTabs, _text);
    const int& w = s.width() + 10;
    const int& h = s.height() + 10;
    return QSize(w, h);
}

Question::Question(QString str, QAPanel* parent)
    : Dialog(str, parent)
{
    headpix.load(":/me.png");
    headpix = headpix.scaled(QSize(40,40), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    resize(sizeHint());
}

QSize Question::sizeHint()const
{
    QSize s = fontMetrics().size(Qt::TextExpandTabs,_text);

    int w = headpix.width() + s.width() + Dialog::_space;
    int temp = s.height() + 10;
    int h = headpix.height() > temp ? headpix.height() : temp;
    return QSize(w, h);
}

void Question::adjustx()
{
    //画在右边
    x = mypanel->width() - width() - Dialog::_space;
}

void Question::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int& textwidth = sizeHint().width() - headpix.width();//textwidth只包含文字区域，不包括图片和头像
    const int& textheight = sizeHint().height();//textwidth只包含文字区域，不包括图片和头像

    if(m_translucent)
    {
        ;
    }
    else
    {
        p.setPen(m_backgroundColor);
        p.setBrush(m_backgroundColor);
        p.drawRoundedRect(headpix.width(), 0, textwidth, textheight, m_radius, m_radius);
    }

    p.setPen(m_fontColor);
    p.drawText(headpix.width(), 0, textwidth, textheight, Qt::AlignCenter, _text);
    p.drawPixmap(0, 0, headpix);

    if(pixcontent.isNull())
    {
        return;
    }

    p.drawPixmap(headpix.width() + Dialog::_space, textheight + Dialog::_space, pixcontent);
}


Answer::Answer(QString str, QAPanel* parent)
    : Dialog(str, parent)
{
    headpix.load(":/robot.png");
    headpix = headpix.scaled(QSize(40,40), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    resize(sizeHint());
}

QSize Answer::sizeHint()const
{
    QSize s = fontMetrics().size(Qt::TextExpandTabs, _text);

    int w = headpix.width() + s.width() + Dialog::_space;
    int temp = s.height() + Dialog::_space;
    int h = headpix.height() > temp ? headpix.height() : temp;
    return QSize(w, h);
}

void Answer::adjustx()
{
    //画在左边
    x = Dialog::_space;
}


void Answer::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int& textwidth = sizeHint().width() - headpix.width();//textwidth只包含文字区域，不包括图片和头像
    const int& textheight = sizeHint().height();//textwidth只包含文字区域，不包括图片和头像

    if(m_translucent)
    {
        ;
    }
    else
    {
        p.setPen(m_backgroundColor);
        p.setBrush(m_backgroundColor);
        p.drawRoundedRect(headpix.width()/* + 5*/, 0, textwidth, textheight, m_radius, m_radius);
    }

    p.setPen(m_fontColor);
    p.drawText(headpix.width()/* + 5*/, 0, textwidth, textheight, Qt::AlignCenter, _text);
    p.drawPixmap(0, 0, headpix);

    if(pixcontent.isNull())
    {
        return;
    }

    p.drawPixmap(headpix.width() + Dialog::_space, textheight + Dialog::_space, pixcontent);
}



QAPanel::QAPanel(QWidget* w, QAPanelScroll* s)
    : QWidget(w)
    , myview(s)
    , _width(380)
{
    resize(sizeHint());
}

void QAPanel::clearDialog()
{
    foreach(Dialog* d,dialogs)
    {
        delete d;
    }
    dialogs.clear();
    resize(sizeHint());
}

int QAPanel::currentStartLevel() const
{
    int h = Dialog::_space;
    foreach (Dialog* d, dialogs)
    {
        h += d->height() + d->_space;
    }
    return h;
}

void QAPanel::adjustAllDialog()//对话大小可能会变，比如对话的图片加载进来了
{
    int h = Dialog::_space;

    foreach (Dialog* d, dialogs)
    {
        d->sety(h);
        d->move(d->x, d->y);
        h += d->height() + d->_space;
    }
    //自己也要扩大板面，不然容不下了
    resize(QAPanel::_width,h);
    myview->moveScrollToEnd();
}

void QAPanel::addDialog(Dialog* d)
{
    d->adjustx();
    const int &y = currentStartLevel();
    d->sety(y);
    d->move(d->x,y);
    dialogs.append(d);
    resize(sizeHint());
    d->show();
    myview->moveScrollToEnd();
}

QSize QAPanel::sizeHint () const
{
    const int &h = currentStartLevel();
    return QSize(_width, h);
}

void QAPanel::saveScreenShot()
{
    QPixmap &pix = QPixmap::grabWidget(this);

    //QPixmap &pix=QPixmap::grabWindow(QApplication::desktop()->winId());
    if(pix.save("screenshot.png", "png"))
    {
        QMessageBox::information(this,"Screenshot",
                                 "<b>screenshot.png</b> save successfully");
    }
    else
    {
        QMessageBox::warning(this,"Screenshot"
                             ,"<b>screenshot.png</b> can not save");
    }
}

QAPanelScroll::QAPanelScroll(QWidget* w)
    : QScrollArea(w)
    , panel(new QAPanel(w, this))
{
    setWidget(panel);
    resize(400, 580);
    setStyleSheet("background-color:rgb(240,240,240);");
}

void QAPanelScroll::moveScrollToEnd()
{
    QScrollBar *bar = this->verticalScrollBar();
    bar->setValue(bar->maximum());
}
