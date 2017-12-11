#include <QLabel>
#include <QApplication>

#include "character_widget.h"

CharacterWidget::CharacterWidget(QWidget *parent)
    :QWidget(parent)
{
    mouse_press = false;
    mouse_move = false;
    current_index = 0;
    current_pos_x = 0;

    this->resize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    setWindowFlags(Qt::FramelessWindowHint);

    background_label = new QLabel(this);
    background_label->setPixmap(QPixmap(":/newCharacter/bg_bottom"));
    background_label->setGeometry(QRect(0, 0, this->width(), this->height()));

    //将4张图片合成一张
    QPixmap pixmap(QSize(this->width()*WINDOW_PAGE_COUNT, WINDOW_HEIGHT));
    QPainter painter(&pixmap);
    for(int i = 0; i < WINDOW_PAGE_COUNT; i++)
    {
        painter.drawImage(QRect(WINDOW_WIDTH*i, 0, WINDOW_WIDTH, WINDOW_HEIGHT),
                          QImage(QString(":/newCharacter/desktop_%1").arg(i)));
    }
    total_label = new QLabel(this);
    total_label->resize(pixmap.size());
    total_label->setPixmap(pixmap);
    total_label->move(WINDOW_START_X, WINDOW_START_Y);

    close_button = new PushButton(this);
    this->translateLanguage();
    for(int i = 0; i < WINDOW_BUTTON_COUNT; i++)
    {
        CLabel *label = new CLabel(this);
        label = new CLabel(this);
        label->resize(QSize(155, 45));
        label->setPixmap(QPixmap(QString(":/newCharacter/btn_%1").arg(i)));
        label->setText(name_list.at(i));
        label->move(8+i*170, 319);
        connect(label, SIGNAL(signalLabelPress(CLabel*)), this, SLOT(changeCurrentPage(CLabel*)));
        label_array[i] = label;
    }
    label_array[0]->setMousePressFlag(true);

    close_button->loadPixmap(":/sysButton/close");
    close_button->move(this->width()-52, 0);
    connect(close_button, SIGNAL(clicked()), this, SLOT(hide()));
}

CharacterWidget::~CharacterWidget()
{
    for (int i = 0; i < WINDOW_PAGE_COUNT; i++)
    {
        delete label_array[i];
    }
    delete total_label;

    delete close_button;
    delete background_label;
}

void CharacterWidget::translateLanguage()
{
    name_list << tr("function") << tr("clear cookie") << tr("triggerman") << tr("booster");
    close_button->setToolTip(tr("close"));
}

void CharacterWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_mouseSrcPos = e->pos();

        if(m_mouseSrcPos.y() <= 40)
        {
            mouse_move = true;
        }
        else
        {
            current_pos_x = total_label->x();
            mouse_press = true;
        }
    }
    else if(e->button() == Qt::RightButton)
    {
        if(label_move)
        {
            if(current_index > 0)
            {
                current_index--;
                moveCurrentPage(false); //右移
            }
        }
    }
}

void CharacterWidget::mouseReleaseEvent(QMouseEvent *e)
{
    int xpos = 0;

    if (mouse_press)
    {
        if (label_move)
        {
            m_mouseDstPos = e->pos();

            xpos = m_mouseDstPos.x() - m_mouseSrcPos.x();

            if(xpos > 0)//右移
            {
                if(xpos >= WINDOW_ONEBUTTON_WIDTH)
                {
                    if(current_index > 0)
                    {
                        current_index--;
                        moveCurrentPage(false); //右移
                    }
                    else
                    {
                        moveCurrentPage(true); //左移
                    }
                }
                else
                {
                    moveCurrentPage(true); //左移
                }
            }
            else //左移
            {
                if(xpos <= -WINDOW_ONEBUTTON_WIDTH)
                {
                    if(current_index < WINDOW_PAGE_COUNT-1)
                    {
                        current_index++;
                        moveCurrentPage(true); //左移
                    }
                    else
                    {
                        moveCurrentPage(false); //右移
                    }
                }
                else
                {
                    moveCurrentPage(false); //右移
                }
            }

            mouse_press = false;
        }
    }
    else if(mouse_move)
    {
        mouse_move = false;
    }
}

void CharacterWidget::mouseMoveEvent(QMouseEvent *e)
{
    int x = 0;
    if(mouse_press)
    {
        if(label_move)
        {
            m_mouseDstPos = e->pos();
            x = m_mouseDstPos.x() - m_mouseSrcPos.x();

            setLabelMove(false);
            total_label->move(current_pos_x + x, WINDOW_START_Y);
            setLabelMove(true);
        }
    }
    else if(mouse_move)
    {
        m_mouseDstPos = e->pos();
        this->move(this->pos() + m_mouseDstPos - m_mouseSrcPos);
    }
}

void CharacterWidget::keyPressEvent(QKeyEvent *e)
{
    if(label_move)
    {
        switch(e->key())
        {
        case Qt::Key_Left:
        case Qt::Key_Up:
            if(current_index > 0)
            {
                current_index--;
                moveCurrentPage(false); //右移
            }
            break;

        case Qt::Key_Right:
        case Qt::Key_Down:
            if(current_index < WINDOW_PAGE_COUNT-1)
            {
                current_index++;
                moveCurrentPage(true); //左移
            }
            break;

        default:
            break;
        }
    }
}

void CharacterWidget::changeCurrentPage(CLabel *label)
{
    for(int i=0; i<WINDOW_BUTTON_COUNT; i++)
    {
        if(label != label_array[i])
        {
            label_array[i]->setMousePressFlag(false);
        }
    }

    //获取点击的图标下标
    int index = 0;
    for(int i=0; i<WINDOW_PAGE_COUNT; i++)
    {
        if(label == label_array[i])
        {
            index = i;
            break;
        }
    }

    //若下标小于当前下标右移，否则左移
    if(index < current_index)
    {
        while(index != current_index)
        {
            current_index--;
            moveCurrentPage(false);
        }
    }
    else if(index > current_index)
    {
        while(index != current_index)
        {
            current_index++;
            moveCurrentPage(true);
        }
    }
}

void CharacterWidget::changeCurrentButton()
{
    for(int i=0; i<WINDOW_BUTTON_COUNT; i++)
    {
        if(i != current_index)
        {
            label_array[i]->setMousePressFlag(false);
        }
        else
        {
            label_array[i]->setMousePressFlag(true);
        }
    }
}

inline void CharacterWidget::setLabelMove(bool enable)
{
    label_move = enable;
}

void CharacterWidget::moveCurrentPage(bool direction)
{
    //改变当前页面对应的按钮
    changeCurrentButton();

    //图片的几个分割点
    //0-680, 680-1360, 1360-2040, 2040-2720
    //真:向左移;  假:向右移

    //左移的几种可能性,对于x坐标
    //index=0, 将label移动到-680*0
    //index=1, 将label移动到-680*1
    //index=2, 将label移动到-680*2
    //index=3, 将label移动到-680*3
    setLabelMove(false);
    int current_pos_x = total_label->x(); //当前label坐标
    int dest_pos_x = -WINDOW_WIDTH * current_index; //目标X坐标
    if(direction)
    {
        while(current_pos_x > dest_pos_x)
        {
            total_label->move(current_pos_x-WINDOW_PAGE_MOVE, WINDOW_START_Y);
            current_pos_x = total_label->x();
            qApp->processEvents(QEventLoop::AllEvents);
        }
    }
    else
    {
        while(current_pos_x < dest_pos_x)
        {
            total_label->move(current_pos_x+WINDOW_PAGE_MOVE, WINDOW_START_Y);
            current_pos_x = total_label->x();
            qApp->processEvents(QEventLoop::AllEvents);
        }
    }

    total_label->move(dest_pos_x, WINDOW_START_Y);
    setLabelMove(true);
}
