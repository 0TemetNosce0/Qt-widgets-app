#include "frminput.h"
#include "ui_frminput.h"
#include "qdesktopwidget.h"

frmInput *frmInput::_instance = 0;
frmInput::frmInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmInput)
{
    ui->setupUi(this);
    this->InitProperty();
    this->InitForm();
    this->ChangeStyle();
}

frmInput::~frmInput()
{
    delete ui;
}

void frmInput::Init(QString position, QString style, int btnFontSize, int labFontSize)
{
    this->currentPosition = position;
    this->currentStyle = style;
    this->btnFontSize = btnFontSize;
    this->labFontSize = labFontSize;
    this->ChangeStyle();
    this->ChangeFont();
}

void frmInput::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void frmInput::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void frmInput::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

int frmInput::InitForm()
{
    int res,ret = -1;
    this->mousePressed = false;
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    QDesktopWidget w;
    deskWidth = w.availableGeometry().width();
    deskHeight = w.availableGeometry().height();
    frmWidth = this->width();
    frmHeight = this->height();

    ret--;
    QSqlDatabase dbConn;
    dbConn = QSqlDatabase::addDatabase("QSQLITE");
    qDebug()<<"applicationDirPath:"<<qApp->applicationDirPath();
    dbConn.setDatabaseName(qApp->applicationDirPath() + "/pinyin.db");
//    dbConn.setDatabaseName(":/db/pinyin.db");
//    dbConn.setDatabaseName("c:/pinyin.db");
    bool isSuccess = dbConn.open();
    if(!isSuccess)
    {
        qDebug()<<dbConn.lastError().text();
        qDebug("dbConn.open failed");
        return ret;
    }

    ret--;
    QSqlQuery query;
    //--------------------查找声母
    QString sql = "select [zimu] from [pinyin] where isshengmu=1;";
    isSuccess = query.exec(sql);
    if(!isSuccess)
    {
        dbConn.close();
        return ret;
    }

    //逐个将查询到的声母保存到列表
    while(query.next())
    {
        QString result = query.value(0).toString();
        m_shengmuList.append(result);
    }

    //--------------------查找韵母
    ret--;
    sql = "select [zimu] from [pinyin] where isyunmu=1;";
    isSuccess = query.exec(sql);
    if(!isSuccess)
    {
        dbConn.close();
        return ret;
    }

    //逐个将查询到的韵母保存到列表
    while(query.next())
    {
        QString result = query.value(0).toString();
        if("m" == result)
        {
            //“呒”这个字很少用，多音字读m
            continue;
        }
        m_yunmuList.append(result);
    }

    //--------------------查找既是声母又是韵母
    ret--;
    sql = "select [zimu] from [pinyin] where isshengmu=1 and isyunmu=1;";
    isSuccess = query.exec(sql);
    if(!isSuccess)
    {
        dbConn.close();
        return ret;
    }

    //逐个将查询到的结果保存到列表
    while(query.next())
    {
        QString result = query.value(0).toString();
        if("m" == result)
        {
            //“呒”这个字很少用，多音字读m
            continue;
        }
        m_smAndymList.append(result);
    }

    isFirst = true;
    isPress = false;
    timerPress = new QTimer(this);
    connect(timerPress, SIGNAL(timeout()), this, SLOT(reClicked()));

    currentWidget = 0;
    currentLineEdit = 0;
    currentTextEdit = 0;
    currentPlain = 0;
    currentBrowser = 0;
    currentEditType = "";

    //如果需要更改输入法面板的显示位置,改变currentPosition这个变量即可
    //control--显示在对应输入框的正下方 bottom--填充显示在底部  center--窗体居中显示
    currentPosition = "";

    //如果需要更改输入法面板的样式,改变currentStyle这个变量即可
    //blue--淡蓝色  dev--dev风格  black--黑色  brown--灰黑色  lightgray--浅灰色  darkgray--深灰色  gray--灰色  silvery--银色
    currentStyle = "";

    //输入法面板字体大小,如果需要更改面板字体大小,该这里即可
    btnFontSize = 10;
    labFontSize = 10;

    //如果需要更改输入法初始模式,改变currentType这个变量即可
    //min--小写模式  max--大写模式  chinese--中文模式
    currentType = "min";
    changeType(currentType);

    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        connect(b, SIGNAL(clicked()), this, SLOT(btn_clicked()));
    }

    //绑定全局改变焦点信号槽
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
    //绑定按键事件过滤器
    qApp->installEventFilter(this);
}

void frmInput::InitProperty()
{
    ui->btnOther1->setProperty("btnOther", true);
    ui->btnOther2->setProperty("btnOther", true);
    ui->btnOther3->setProperty("btnOther", true);
    ui->btnOther4->setProperty("btnOther", true);
    ui->btnOther5->setProperty("btnOther", true);
    ui->btnOther6->setProperty("btnOther", true);
    ui->btnOther7->setProperty("btnOther", true);
    ui->btnOther8->setProperty("btnOther", true);
    ui->btnOther9->setProperty("btnOther", true);
    ui->btnOther10->setProperty("btnOther", true);
    ui->btnOther11->setProperty("btnOther", true);
    ui->btnOther12->setProperty("btnOther", true);
    ui->btnOther13->setProperty("btnOther", true);
    ui->btnOther14->setProperty("btnOther", true);
    ui->btnOther15->setProperty("btnOther", true);
    ui->btnOther16->setProperty("btnOther", true);
    ui->btnOther17->setProperty("btnOther", true);
    ui->btnOther18->setProperty("btnOther", true);
    ui->btnOther19->setProperty("btnOther", true);
    ui->btnOther20->setProperty("btnOther", true);
    ui->btnOther21->setProperty("btnOther", true);

    ui->btnDot->setProperty("btnOther", true);
    ui->btnSpace->setProperty("btnOther", true);
    ui->btnDelete->setProperty("btnOther", true);

    ui->btn0->setProperty("btnNum", true);
    ui->btn1->setProperty("btnNum", true);
    ui->btn2->setProperty("btnNum", true);
    ui->btn3->setProperty("btnNum", true);
    ui->btn4->setProperty("btnNum", true);
    ui->btn5->setProperty("btnNum", true);
    ui->btn6->setProperty("btnNum", true);
    ui->btn7->setProperty("btnNum", true);
    ui->btn8->setProperty("btnNum", true);
    ui->btn9->setProperty("btnNum", true);
    ui->btn00->setProperty("btnNum", true);

    ui->btna->setProperty("btnLetter", true);
    ui->btnb->setProperty("btnLetter", true);
    ui->btnc->setProperty("btnLetter", true);
    ui->btnd->setProperty("btnLetter", true);
    ui->btne->setProperty("btnLetter", true);
    ui->btnf->setProperty("btnLetter", true);
    ui->btng->setProperty("btnLetter", true);
    ui->btnh->setProperty("btnLetter", true);
    ui->btni->setProperty("btnLetter", true);
    ui->btnj->setProperty("btnLetter", true);
    ui->btnk->setProperty("btnLetter", true);
    ui->btnl->setProperty("btnLetter", true);
    ui->btnm->setProperty("btnLetter", true);
    ui->btnn->setProperty("btnLetter", true);
    ui->btno->setProperty("btnLetter", true);
    ui->btnp->setProperty("btnLetter", true);
    ui->btnq->setProperty("btnLetter", true);
    ui->btnr->setProperty("btnLetter", true);
    ui->btns->setProperty("btnLetter", true);
    ui->btnt->setProperty("btnLetter", true);
    ui->btnu->setProperty("btnLetter", true);
    ui->btnv->setProperty("btnLetter", true);
    ui->btnw->setProperty("btnLetter", true);
    ui->btnx->setProperty("btnLetter", true);
    ui->btny->setProperty("btnLetter", true);
    ui->btnz->setProperty("btnLetter", true);

    labCh.append(ui->labCh0);
    labCh.append(ui->labCh1);
    labCh.append(ui->labCh2);
    labCh.append(ui->labCh3);
    labCh.append(ui->labCh4);
    labCh.append(ui->labCh5);
    labCh.append(ui->labCh6);
    labCh.append(ui->labCh7);
    labCh.append(ui->labCh8);
    labCh.append(ui->labCh9);
    //执行了qApp->installEventFilter(this)操作后，再执行下面的操作会造成【点击一次label，eventFilter被调用两次的情况】
//    for (int i = 0; i < 10; i++) {
//        labCh[i]->installEventFilter(this);
//    }
}

void frmInput::ShowPanel()
{
    this->setVisible(true);

    int width = ui->btn0->width();
    width = width > 40 ? width : 40;
    ui->btnPre->setMinimumWidth(width);
    ui->btnPre->setMaximumWidth(width);
    ui->btnNext->setMinimumWidth(width);
    ui->btnNext->setMaximumWidth(width);
    ui->btnClose->setMinimumWidth(width);
    ui->btnClose->setMaximumWidth(width);
}

//事件过滤器,用于识别鼠标单击汉字标签处获取对应汉字
bool frmInput::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (obj == ui->labCh0) {
            setChinese(0);
        } else if (obj == ui->labCh1) {
            setChinese(1);
        } else if (obj == ui->labCh2) {
            setChinese(2);
        } else if (obj == ui->labCh3) {
            setChinese(3);
        } else if (obj == ui->labCh4) {
            setChinese(4);
        } else if (obj == ui->labCh5) {
            setChinese(5);
        } else if (obj == ui->labCh6) {
            setChinese(6);
        } else if (obj == ui->labCh7) {
            setChinese(7);
        } else if (obj == ui->labCh8) {
            setChinese(8);
        } else if (obj == ui->labCh9) {
            setChinese(9);
        } else if (currentEditType != "" && obj != ui->btnClose) {
            ShowPanel();
        }
        btnPress = (QPushButton *)obj;
        if (checkPress()) {
            isPress = true;
            timerPress->start(500);
        }
        return false;
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        btnPress = (QPushButton *)obj;
        if (checkPress()) {
            isPress = false;
            timerPress->stop();
        }
        return false;
    }
    else if (event->type() == QEvent::KeyPress)
    {
        //如果输入法窗体不可见,则不需要处理
        if (!isVisible()) {
            return QWidget::eventFilter(obj, event);
        }

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        //Shift切换输入法模式,esc键关闭输入法面板,空格取第一个汉字,退格键删除
        //中文模式下回车键取拼音,中文模式下当没有拼音时可以输入空格
        if (keyEvent->key() == Qt::Key_Space) {
            if (ui->labPY->text() != "") {
                setChinese(0);
                return true;
            } else {
                return false;
            }
        } else if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            insertValue(ui->labPY->text());
            ui->labPY->setText("");
            selectChinese();
            return true;
        } else if (keyEvent->key() == Qt::Key_Shift) {
            ui->btnType->click();
            return true;
        } else if (keyEvent->key() == Qt::Key_Escape) {
            ui->btnClose->click();
            return true;
        } else if (keyEvent->key() == Qt::Key_Backspace) {
            ui->btnDelete->click();
            return true;
        } else if (keyEvent->text() == "+" || keyEvent->text() == "=") {
            if (ui->labPY->text() != "") {
                ui->btnNext->click();
                return true;
            } else {
                return false;
            }
        } else if (keyEvent->text() == "-" || keyEvent->text() == "_") {
            if (ui->labPY->text() != "") {
                ui->btnPre->click();
                return true;
            } else {
                return false;
            }
        } else if (keyEvent->key() == Qt::Key_CapsLock) {
            if (currentType != "max") {
                currentType = "max";
            } else {
                currentType = "min";
            }
            changeType(currentType);
            return true;
        } else {
            if (currentEditType == "QWidget") {
                return false;
            }
            QString key;
            if (currentType == "chinese") {
                key = keyEvent->text();
            } else if (currentType == "min") {
                key = keyEvent->text().toLower();
            } else if (currentType == "max") {
                key = keyEvent->text().toUpper();
            }
            QList<QPushButton *> btn = this->findChildren<QPushButton *>();
            foreach (QPushButton * b, btn) {
                if (b->text() == key) {
                    b->click();
                    return true;
                }
            }
        }
        return false;
    }
    return QWidget::eventFilter(obj, event);
}

bool frmInput::checkPress()
{
    //只有属于输入法键盘的合法按钮才继续处理
    bool num_ok = btnPress->property("btnNum").toBool();
    bool other_ok = btnPress->property("btnOther").toBool();
    bool letter_ok = btnPress->property("btnLetter").toBool();
    if (num_ok || other_ok || letter_ok) {
        return true;
    }
    return false;
}

void frmInput::reClicked()
{
    if (isPress) {
        timerPress->setInterval(30);
        btnPress->click();
    }
}

//将拼音分词
QString frmInput::splitPinyin(QString pinyinIn)
{
//    QStringList m_shengmuList;      //声母列表
//    QStringList m_yunmuList;        //韵母列表
//    QStringList m_smAndymList;      //既是声母又是韵母列表

    QSqlQuery query;
    QString outPinyin;
    QString dealPinyin;//待分词的字符串
    int index = pinyinIn.lastIndexOf('`');
    if(index >= 0)
    {
        outPinyin = pinyinIn.mid(0,index+1);
        dealPinyin = pinyinIn.mid(index+1);
    }
    else
    {
        dealPinyin = pinyinIn ;
    }

    QString::iterator it = dealPinyin.begin(),itend = dealPinyin.end();
    QString tmp,shengmu,yunmu;
    int i = 0;
    for (;it != itend; it++,i++)
    {
        tmp.append(*it);
        //尝试查询拼音
        QString sqlQueryCizu = "select [type] from [hzpy] where [pinyin]='" + tmp + "';";
        query.exec(sqlQueryCizu);
        //是否拼音
        if(query.next())
        {
            outPinyin.append(*it);
            continue;
        }
        //是否声母
        if(m_shengmuList.contains(tmp))//声母列表
        {
            outPinyin.append(*it);
            continue;
        }
        //------------以下处理既不是声母也不是拼音
        if(1 == tmp.length())//输入i或v时
        {
            outPinyin.append(*it);
            outPinyin.append('`');
            continue;
        }
        outPinyin.append('`');
        tmp.clear();
        it--;
    }

    //移除最后一个‘·’字符
    if(outPinyin.endsWith('`'))
    {
        outPinyin.remove(outPinyin.length()-1,1);
    }

    return outPinyin;
}

//将用户输入的词组拼音及选择的汉字词组写入数据库
int frmInput::saveHZCZtoDB(QString ciZuHZPinyin, QString ciZuHZ)
{
    int res,ret = -1;
    bool isSuccess = false;
    QSqlQuery query;
    //先在词组表查询，如果已经存在该词组拼音则将词组追加到词组表，如果不存在则创建拼音词组记录
    QString sqlQueryCizu = "select [cizu] from [pinyincizu] where [pinyin]='" + ciZuHZPinyin + "';";
    isSuccess = query.exec(sqlQueryCizu);
    if(!isSuccess)
    {
        return ret;
    }

    ret--;
    if(query.next())
    {
        QString result = query.value(0).toString();
        result.append(" ");
        result.append(ciZuHZ);
        QString sql = QString("UPDATE [pinyincizu] SET [cizu]='%1' where [pinyin]='%2'").arg(result).arg(ciZuHZPinyin);
        isSuccess = query.exec(sql);
        if(!isSuccess)
        {
            qDebug()<<query.lastError().text();
            return ret;
        }

        return 0;
    }

    ret--;
    //如果不存在则创建拼音词组记录
    QString sql = QString("insert into pinyincizu (pinyin,cizu) \
                          values('%1','%2')").arg(ciZuHZPinyin).arg(ciZuHZ);
    isSuccess = query.exec(sql);
    if(!isSuccess)
    {
        return ret;
    }

    return 0;
}

void frmInput::focusChanged(QWidget *oldWidget, QWidget *nowWidget)
{
    //qDebug() << "oldWidget:" << oldWidget << " nowWidget:" << nowWidget;
    if (nowWidget != 0 && !this->isAncestorOf(nowWidget)) {
        //在Qt5和linux系统中(嵌入式linux除外),当输入法面板关闭时,焦点会变成无,然后焦点会再次移到焦点控件处
        //这样导致输入法面板的关闭按钮不起作用,关闭后马上有控件获取焦点又显示.
        //为此,增加判断,当焦点是从有对象转为无对象再转为有对象时不要显示.
        //这里又要多一个判断,万一首个窗体的第一个焦点就是落在可输入的对象中,则要过滤掉
#ifndef __arm__
        if (oldWidget == 0x0 && !isFirst) {
            return;
        }
#endif

        isFirst = false;
        QWidget * pModalWidget = QApplication::activeModalWidget () ;
        QWidget * pPopupWidget = QApplication::activePopupWidget() ;
        QWidget * pWidget = QApplication::activeWindow() ;

        if (NULL != pModalWidget && pModalWidget->inherits("QDialog"))
        {
            Qt::WindowModality Modality = pModalWidget->windowModality();
          /*Qt::NonModal       The window is not modal and does not block input to other windows.
          非模态对话框

          Qt::WindowModal        The window is modal to a single window hierarchy and blocks input to its parent window, all grandparent windows, and all siblings of its parent and grandparent windows.
          窗口级模态对话框，即只会阻塞父窗口、父窗口的父窗口及兄弟窗口。（半模态对话框）

          Qt::ApplicationModal       The window is modal to the application and blocks input to all windows.
          应用程序级模态对话框，即会阻塞整个应用程序的所有窗口。（半模态对话框）
          */
            if(Qt::ApplicationModal == Modality)
            {
                //需要将输入法切换到最初的原始状态--小写,同时将之前的对象指针置为零
                currentWidget = 0;
                currentLineEdit = 0;
                currentTextEdit = 0;
                currentPlain = 0;
                currentBrowser = 0;
                currentEditType = "";
                currentType = "min";
                changeType(currentType);
                this->setVisible(false);
                return;
            }
        }
        if (nowWidget->inherits("QLineEdit")) {
            currentLineEdit = (QLineEdit *)nowWidget;
            currentEditType = "QLineEdit";
            ShowPanel();
        } else if (nowWidget->inherits("QTextEdit")) {
            currentTextEdit = (QTextEdit *)nowWidget;
            currentEditType = "QTextEdit";
            ShowPanel();
        } else if (nowWidget->inherits("QPlainTextEdit")) {
            currentPlain = (QPlainTextEdit *)nowWidget;
            currentEditType = "QPlainTextEdit";
            ShowPanel();
        } else if (nowWidget->inherits("QTextBrowser")) {
            currentBrowser = (QTextBrowser *)nowWidget;
            currentEditType = "QTextBrowser";
            ShowPanel();
        } else if (nowWidget->inherits("QComboBox")) {
            QComboBox *cbox = (QComboBox *)nowWidget;
            //只有当下拉选择框处于编辑模式才可以输入
            if (cbox->isEditable()) {
                currentLineEdit = cbox->lineEdit() ;
                currentEditType = "QLineEdit";
                ShowPanel();
            }
        } else if (nowWidget->inherits("QSpinBox") ||
                   nowWidget->inherits("QDoubleSpinBox") ||
                   nowWidget->inherits("QDateEdit") ||
                   nowWidget->inherits("QTimeEdit") ||
                   nowWidget->inherits("QDateTimeEdit")) {
            currentWidget = nowWidget;
            currentEditType = "QWidget";
            ShowPanel();
        } else {
            //需要将输入法切换到最初的原始状态--小写,同时将之前的对象指针置为零
            currentWidget = 0;
            currentLineEdit = 0;
            currentTextEdit = 0;
            currentPlain = 0;
            currentBrowser = 0;
            currentEditType = "";
            currentType = "min";
            changeType(currentType);
            this->setVisible(false);
        }

        //根据用户选择的输入法位置设置-居中显示-底部填充-显示在输入框正下方
        if (currentPosition == "center") {
            QPoint pos = QPoint(deskWidth / 2 - frmWidth / 2, deskHeight / 2 - frmHeight / 2);
            this->setGeometry(pos.x(), pos.y(), frmWidth, frmHeight);
        } else if (currentPosition == "bottom") {
            this->setGeometry(0, deskHeight - frmHeight, deskWidth, frmHeight);
        } else if (currentPosition == "control") {
            QRect rect = nowWidget->rect();
            QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
            pos = nowWidget->mapToGlobal(pos);
            this->setGeometry(pos.x(), pos.y(), frmWidth, frmHeight);
        }
    }
}

void frmInput::changeType(QString type)
{
    if (type == "max") {
        changeLetter(true);
        ui->btnType->setText("大写");
        ui->labInfo->setText("中文输入法--大写");
        ui->btnOther12->setText("/");
        ui->btnOther14->setText(":");
        ui->btnOther17->setText(",");
        ui->btnOther18->setText("\\");
        ui->btnOther21->setText("\"");
    } else if (type == "min") {
        changeLetter(false);
        ui->btnType->setText("小写");
        ui->labInfo->setText("中文输入法--小写");
        ui->btnOther12->setText("/");
        ui->btnOther14->setText(":");
        ui->btnOther17->setText(",");
        ui->btnOther18->setText("\\");
        ui->btnOther21->setText("\"");
    } else {
        changeLetter(false);
        ui->btnType->setText("中文");
        ui->labInfo->setText("中文输入法--中文111");
        ui->btnOther12->setText("。11");
        ui->btnOther14->setText("：11");
        ui->btnOther17->setText("，11");
        ui->btnOther18->setText("；11");
        ui->btnOther21->setText("“11");
    }
    //每次切换到模式,都要执行清空之前中文模式下的信息
    clearChinese();
    ui->labPY->setText("");
}

void frmInput::changeLetter(bool isUpper)
{
    QList<QPushButton *> btn = this->findChildren<QPushButton *>();
    foreach (QPushButton * b, btn) {
        if (b->property("btnLetter").toBool()) {
            if (isUpper) {
                b->setText(b->text().toUpper());
            } else {
                b->setText(b->text().toLower());
            }
        }
    }
}

//查询汉字
void frmInput::selectChinese()
{
    clearChinese();
    QSqlQuery query;
    QString currentPY = ui->labPY->text();
    //将拼音分词
    QString afterSplitPY = splitPinyin(currentPY);
    ui->labPY->setText(afterSplitPY);

    QStringList cizuPinyinList = afterSplitPY.split('`');
    currentHanzi_count = cizuPinyinList.count();         //当前用户输入拼音被拆分出的汉字数量

    QString cizuPinyin = currentPY.replace('`',"");
    m_inputPinyin = cizuPinyin;
    //先在词组表查询，再到汉字拼音表查询
    QString sqlQueryCizu = "select [cizu] from [pinyincizu] where [pinyin]='" + cizuPinyin + "';";
    query.exec(sqlQueryCizu);
    currentPYCZ_count = 0;          //当前拼音对应的词组数量
    //逐个将查询到的字词加入汉字队列
    while(query.next())
    {
        QString result = query.value(0).toString();
        QStringList text = result.split(" ");
        foreach (QString txt, text)
        {
            if (txt.length() > 0)
            {
                allPY.append(txt);
                currentPY_count++;
            }
        }
    }
    currentPYCZ_count = currentPY_count;          //当前拼音对应的词组数量
//    QString sql = "select [word] from [pinyin] where [pinyin]='" + currentPY + "';";
//    QString sql = "select [chinese] from [hzpy] where [pinyin]='" + currentPY + "'order by type desc;";
    QString sql = "select [chinese] from [hzpy] where [pinyin]='" + cizuPinyinList.at(currentSelect_index) + "'order by type desc;";
    query.exec(sql);
    //逐个将查询到的字词加入汉字队列
    while(query.next())
    {
        QString result = query.value(0).toString();
        if (result.length() > 0)
        {
            allPY.append(result);
            currentPY_count++;
        }
    }
    showChinese();
}

void frmInput::showChinese()
{
    //每个版面最多显示10个汉字
    int count = 0;
    currentPY.clear();
    for (int i = 0; i < 10; i++) {
        labCh[i]->setText("");
    }

    for (int i = currentPY_index; i < currentPY_count; i++) {
        if (count == 10) {
            break;
        }
        QString txt = QString("%1.%2").arg(count).arg(allPY[currentPY_index]);
        currentPY.append(allPY[currentPY_index]);
        labCh[count]->setText(txt);
        count++;
        currentPY_index++;
    }
    //qDebug() << "currentPY_index:" << currentPY_index << "currentPY_count:" << currentPY_count;
}

void frmInput::btn_clicked()
{
    //如果当前焦点控件类型为空,则返回不需要继续处理
    if (currentEditType == "") {
        return;
    }

    QPushButton *btn = (QPushButton *)sender();
    QString objectName = btn->objectName();
    if (objectName == "btnType") {
        if (currentType == "min") {
            currentType = "max";
        } else if (currentType == "max") {
            currentType = "chinese";
        } else if (currentType == "chinese") {
            currentType = "min";
        }
        changeType(currentType);
    } else if (objectName == "btnDelete") {
        //如果当前是中文模式,则删除对应拼音,删除完拼音之后再删除对应文本输入框的内容
        if (currentType == "chinese") {
            QString txt = ui->labPY->text();
            int len = txt.length();
            if (len > 0)
            {
                ui->labPY->setText(txt.left(len - 1));
                currentSelect_index = 0;
                m_selectHZ.clear();
                selectChinese();
            } else {
                deleteValue();
            }
        } else {
            deleteValue();
        }
    } else if (objectName == "btnPre") {
        if (currentPY_index >= 20) {
            //每次最多显示10个汉字,所以每次向前的时候索引要减20
            if (currentPY_index % 10 == 0) {
                currentPY_index -= 20;
            } else {
                currentPY_index = currentPY_count - (currentPY_count % 10) - 10;
            }
        } else {
            currentPY_index = 0;
        }
        showChinese();
    } else if (objectName == "btnNext") {
        if (currentPY_index < currentPY_count - 1) {
            showChinese();
        }
    } else if (objectName == "btnClose") {
        this->setVisible(false);
    } else if (objectName == "btnSpace") {
        insertValue(" ");
    } else {
        QString value = btn->text();
        //如果是&按钮，因为对应&被过滤,所以真实的text为去除前面一个&字符
        if (objectName == "btnOther7") {
            value = value.right(1);
        }
        //当前不是中文模式,则单击按钮对应text为传递参数
        if (currentType != "chinese")
        {
            insertValue(value);
        }
        else
        {
            //中文模式下,不允许输入特殊字符,单击对应数字按键取得当前索引的汉字
            if (btn->property("btnOther").toBool())
            {
                if (ui->labPY->text().length() == 0)
                {
                    insertValue(value);
                }
            }
            else if (btn->property("btnNum").toBool())
            {
                if (ui->labPY->text().length() == 0) {
                    insertValue(value);
                } else if (objectName == "btn0") {
                    setChinese(0);
                } else if (objectName == "btn1") {
                    setChinese(1);
                } else if (objectName == "btn2") {
                    setChinese(2);
                } else if (objectName == "btn3") {
                    setChinese(3);
                } else if (objectName == "btn4") {
                    setChinese(4);
                } else if (objectName == "btn5") {
                    setChinese(5);
                } else if (objectName == "btn6") {
                    setChinese(6);
                } else if (objectName == "btn7") {
                    setChinese(7);
                } else if (objectName == "btn8") {
                    setChinese(8);
                } else if (objectName == "btn9") {
                    setChinese(9);
                }
            } else if (btn->property("btnLetter").toBool())
            {
                ui->labPY->setText(ui->labPY->text() + value);
                currentSelect_index = 0;
                m_selectHZ.clear();
                selectChinese();
            }
        }
    }
}

void frmInput::insertValue(QString value)
{
    if (currentEditType == "QLineEdit") {
        currentLineEdit->insert(value);
    } else if (currentEditType == "QTextEdit") {
        currentTextEdit->insertPlainText(value);
    } else if (currentEditType == "QPlainTextEdit") {
        currentPlain->insertPlainText(value);
    } else if (currentEditType == "QTextBrowser") {
        currentBrowser->insertPlainText(value);
    } else if (currentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, QString(value));
        QApplication::sendEvent(currentWidget, &keyPress);
    }
}

void frmInput::deleteValue()
{
    if (currentEditType == "QLineEdit") {
        currentLineEdit->backspace();
    } else if (currentEditType == "QTextEdit") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentTextEdit->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QPlainTextEdit") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentPlain->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QTextBrowser") {
        //获取当前QTextEdit光标,如果光标有选中,则移除选中字符,否则删除光标前一个字符
        QTextCursor cursor = currentBrowser->textCursor();
        if(cursor.hasSelection()) {
            cursor.removeSelectedText();
        } else {
            cursor.deletePreviousChar();
        }
    } else if (currentEditType == "QWidget") {
        QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier, QString());
        QApplication::sendEvent(currentWidget, &keyPress);
    }
}

void frmInput::setChinese(int index)
{
    int count = currentPY.count();
    if (count > index)
    {
        insertValue(currentPY[index]);
        m_selectHZ.append(currentPY[index]);
        if(index < currentPYCZ_count)          //当前拼音对应的词组数量
        {
            //如果用户选择的是词组,清空当前汉字信息,等待重新输入
            clearChinese();
            ui->labPY->setText("");
        }
        else
        {
            currentSelect_index++;
            if(currentSelect_index >= currentHanzi_count)
            {
                clearChinese();
                ui->labPY->setText("");
                if(currentHanzi_count > 1)
                {
                    //将用户输入的词组拼音及选择的汉字词组写入数据库
                    saveHZCZtoDB(m_inputPinyin,m_selectHZ);
                }
            }
            else
            {
                selectChinese();
            }
        }
    }
}

void frmInput::clearChinese()
{
    //清空汉字,重置索引
    for (int i = 0; i < 10; i++) {
        labCh[i]->setText("");
    }
    allPY.clear();
    currentPY.clear();
    currentPY_index = 0;
    currentPY_count = 0;
}

void frmInput::ChangeStyle()
{
    if (currentStyle == "blue") {
        changeStyle("#DEF0FE", "#C0DEF6", "#C0DCF2", "#386487");
    } else if (currentStyle == "dev") {
        changeStyle("#C0D3EB", "#BCCFE7", "#B4C2D7", "#324C6C");
    } else if (currentStyle == "gray") {
        changeStyle("#E4E4E4", "#A2A2A2", "#A9A9A9", "#000000");
    } else if (currentStyle == "lightgray") {
        changeStyle("#EEEEEE", "#E5E5E5", "#D4D0C8", "#6F6F6F");
    } else if (currentStyle == "darkgray") {
        changeStyle("#D8D9DE", "#C8C8D0", "#A9ACB5", "#5D5C6C");
    } else if (currentStyle == "black") {
        changeStyle("#4D4D4D", "#292929", "#D9D9D9", "#CACAD0");
    } else if (currentStyle == "brown") {
        changeStyle("#667481", "#566373", "#C2CCD8", "#E7ECF0");
    } else if (currentStyle == "silvery") {
        changeStyle("#E1E4E6", "#CCD3D9", "#B2B6B9", "#000000");
    }
}

void frmInput::ChangeFont()
{
    QFont btnFont(this->font().family(), btnFontSize);
    QFont labFont(this->font().family(), labFontSize);

    QList<QPushButton *> btns = ui->widgetMain->findChildren<QPushButton *>();
    foreach (QPushButton * btn, btns) {
        btn->setFont(btnFont);
    }

    QList<QLabel *> labs = ui->widgetTop->findChildren<QLabel *>();
    foreach (QLabel * lab, labs) {
        lab->setFont(labFont);
    }
    ui->btnPre->setFont(labFont);
    ui->btnNext->setFont(labFont);
    ui->btnClose->setFont(labFont);
}

void frmInput::changeStyle(QString topColor, QString bottomColor, QString borderColor, QString textColor)
{
    QStringList qss;
    qss.append(QString("QWidget#frmInput{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(topColor).arg(bottomColor));
    qss.append("QPushButton{padding:5px;border-radius:3px;}");
    qss.append(QString("QPushButton:hover{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 %1,stop:1 %2);}")
               .arg(topColor).arg(bottomColor));
    qss.append(QString("QLabel,QPushButton{color:%1;}").arg(textColor));
    qss.append(QString("QPushButton#btnPre,QPushButton#btnNext,QPushButton#btnClose{padding:5px;}"));
    qss.append(QString("QPushButton{border:1px solid %1;}")
               .arg(borderColor));
    qss.append(QString("QLineEdit{border:1px solid %1;border-radius:5px;padding:2px;background:none;selection-background-color:%2;selection-color:%3;}")
               .arg(borderColor).arg(bottomColor).arg(topColor));
    this->setStyleSheet(qss.join(""));
}
