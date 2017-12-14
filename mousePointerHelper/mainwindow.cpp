#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    offset_x = 5;
    offset_y = 5;
    canvas_width = 500;
    canvas_height = 390;
    setMaximumOnStartup = false;
    onChangingCanvasSize = false;

    loadConfig();//加载已存储配置（如果有）

    clickOnFrame = false;//是否点击到面板上
    drawCanDragCover = false;
    ui->showOptBoxBtn->setVisible(false);

    //窗口调节大小动画
    optSlideAnimation = new QPropertyAnimation(ui->optionBox, "geometry");
    optSlideAnimation->setDuration(600);
    optSlideAnimation->setEasingCurve(QEasingCurve::OutCirc);

    //this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);//无边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);// | Qt::Tool
    this->setAttribute(Qt::WA_TranslucentBackground, true);//背景透明（需要上一行配合）
    timer = new QTimer(this);//控制刷新定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));

    timer->start(27);

    this->repaint();
    if (setMaximumOnStartup) {
        setCanvasMaximum(true);
    } else {
        ui->canvasHSpinbox->setValue(canvas_height);
        ui->canvasWSpinbox->setValue(canvas_width);
    }
    ui->xoffsetSpinBox->setValue(offset_x);
    ui->yoffsetSpinBox->setValue(offset_y);

}

void MainWindow::Update()
{
    int mouse_x = QCursor::pos().x();
    int mouse_y = QCursor::pos().y();

    int canvas_x = this->pos().x();
    int canvas_y = this->pos().y();

    int x = mouse_x - canvas_x - 5 + offset_x;// 减5由鼠标图片左边距而定
    int y = mouse_y - canvas_y - 5 + offset_y;// 减5由鼠标图片上边距而定
    ui->cursorLable->move(x,y);

    ui->xposLable->setText("X ("+QString::number(mouse_x)+","+QString::number(x)+")");
    ui->yposLable->setText("Y ("+QString::number(mouse_y)+","+QString::number(y)+")");
}

MainWindow::~MainWindow()
{
    saveConfig();
    delete timer;
    delete ui;
}

void MainWindow::on_xoffsetSpinBox_valueChanged(int arg1)
{
    offset_x = arg1;
}

void MainWindow::on_yoffsetSpinBox_valueChanged(int arg1)
{
    offset_y = arg1;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        drag_pos = event->pos();
        clickOnFrame = true;//点击到窗口框架上才会变成true，改动之后新增功能：判断点击是否在边框右侧
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    clickOnFrame = false;//弹起鼠标按键时，恢复
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && clickOnFrame)
    {
        move(event->globalPos() - drag_pos);
        event->accept();
    }
}

void MainWindow::on_moveCanvasCheckr_clicked(bool checked)
{
    drawCanDragCover = checked;
    this->repaint();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (drawCanDragCover)
    {
        painter.setBrush(QBrush(QColor(255, 255, 255, 120)));
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, width(), height());
    }
}

void MainWindow::doHideOptBox(bool doHide)
{
    QRect startRect, endRect;
    if (doHide) {
        ui->showOptBoxBtn->setVisible(true);
        startRect = QRect(ui->optionBox->geometry().x(),
                          ui->optionBox->geometry().y(),
                          ui->optionBox->geometry().width(),
                          ui->optionBox->geometry().height());
        endRect = QRect(this->geometry().width() - ui->optionBox->geometry().width() - 15,
                        0 - ui->optionBox->geometry().height(),
                        ui->optionBox->geometry().width(),
                        ui->optionBox->geometry().height());
    } else {
        ui->showOptBoxBtn->setVisible(false);
        startRect = QRect(this->geometry().width() - ui->optionBox->geometry().width() - 15,
                          0 - ui->optionBox->geometry().height(),
                          ui->optionBox->geometry().width(),
                          ui->optionBox->geometry().height());
        endRect = QRect(this->geometry().width() - ui->optionBox->geometry().width() - 15,
                        15,
                        ui->optionBox->geometry().width(),
                        ui->optionBox->geometry().height());
    }
    optSlideAnimation->stop();
    optSlideAnimation->setStartValue(startRect);
    optSlideAnimation->setEndValue(endRect);
    optSlideAnimation->start();
    this->repaint();
}

void MainWindow::on_exitBtn_clicked()
{
    qApp->exit();//主窗口关闭后，关闭程序
}

void MainWindow::on_hideOptBoxBtn_clicked()
{
    doHideOptBox(true);
}

void MainWindow::on_showOptBoxBtn_clicked()
{
    doHideOptBox(false);
}

void MainWindow::on_canvasSizeBtn_clicked()
{
    if (!isMaximized()) {
        setCanvasMaximum(true);
    } else
        setCanvasMaximum(false);
}

void MainWindow::saveConfig()
{
    QFile file(QCoreApplication::applicationDirPath() + "/config.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    stream << (quint32)0x78297000
           << ui->xoffsetSpinBox->value()
           << ui->yoffsetSpinBox->value()
           << isMaximized()
           << ui->canvasWSpinbox->value()
           << ui->canvasHSpinbox->value();
    file.close();
}

void MainWindow::loadConfig()
{
    QFile file(QCoreApplication::applicationDirPath() + "/config.dat");
    if (!file.open(QIODevice::ReadOnly)) return;
    QDataStream stream(&file);
    quint32 magic;
    stream >> magic;
    if (magic == 0x78297000)
    {
        int dataInt = 0;
        stream >> dataInt;
        offset_x = dataInt;
        stream >> dataInt;
        offset_y = dataInt;
        bool dataBool = false;
        stream >> dataBool;
        setMaximumOnStartup = dataBool;
        stream >> dataInt;
        canvas_width = dataInt;
        stream >> dataInt;
        canvas_height = dataInt;
    }
    file.close();
}

void MainWindow::setCanvasMaximum(bool arg1)
{
    onChangingCanvasSize = true;
    if (arg1 && !isMaximized()) {
        ui->canvasSizeBtn->setText("Normal");
        QWidget::showMaximized();
        //this->move(0,0);不能设否则会出问题，什么问题不妨去掉看看，原因不明
    } else {
        ui->canvasSizeBtn->setText("Maximum");
        QWidget::showNormal();
    }
    ui->canvasWSpinbox->setValue(this->geometry().width());
    ui->canvasHSpinbox->setValue(this->geometry().height());
    this->repaint();
    onChangingCanvasSize = false;
}

void MainWindow::on_canvasWSpinbox_valueChanged(int arg1)
{
    if (onChangingCanvasSize || isMaximized()) return;
    this->resize( QSize(arg1,this->geometry().height()) );
    this->repaint();
}

void MainWindow::on_canvasHSpinbox_valueChanged(int arg1)
{
    if (onChangingCanvasSize || isMaximized()) return;
    this->resize( QSize( this->geometry().width(), arg1 ));
    //this->setFixedSize();和setMaximumSize虽然能够设置大小，但之后就不能用调整窗口大小了。
    this->repaint();
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->optionBox->move(QPoint(this->geometry().width() - ui->optionBox->geometry().width() - 15,15));
    ui->showOptBoxBtn->move(QPoint(this->geometry().width()- ui->showOptBoxBtn->geometry().width() - 15,15));
    this->repaint();
}
