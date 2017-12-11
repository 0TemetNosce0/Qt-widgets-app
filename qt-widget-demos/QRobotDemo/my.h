#ifndef MY_HEADER
#define MY_HEADER

class QWidget;
class QPropertyAnimation;

#include<QPen>
#include<QWidget>
#include<QMouseEvent>

namespace my
{
static const QColor background(39, 50, 56);
void moveToScrCenter(QWidget* object);
static int Animate_Distance = 20;

class Button : public QWidget
{
    Q_OBJECT

public:
    Button(const QString& text,QWidget* parent=0);
    ~Button();

    inline const QString& text()const{return _text;}
    inline void setPenColor(const QColor& c){pen.setColor(c);}
    inline void setColor(const QColor& c){_color = c;}
    inline void setRadius(int r){radius = r;}
    inline void setAnimated(bool ok){_animated = ok;}
    inline void setStartSize(const QSize& s){_start_size = s;}
    inline void setEndSize(const QSize& s){_end_size = s;}
    inline void setDuration(int d){_animate_duration = d;}
    inline void setTextColor(const QColor&c){pen.setColor(c);}
    inline void setWhiteSize(int size){white_size = size;}
    inline void setTranparentBackground(bool ok){tranparent_background = ok;}
    inline void setAnimateDistance(int d){Animate_Distance = d;}

    void setSize(int w,int h);
    void setTextPixelSize(int size);

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);

    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent* );
    void leaveEvent(QEvent* );

signals:
    void clicked();

private:
    QPen pen;
    QFont _font;
    QColor _color;
    QString _text;
    QSize _start_size;//保留动画前的大小，有动画时启用
    QSize _end_size;//保留鼠标停留后的大小,用动画时启用
    QPropertyAnimation *_animation;
    int _animate_duration;
    int radius;
    int white_size;//按钮白边大小，没白边时=-1
    bool _animated;//是否有动画，当鼠标进入时
    bool tranparent_background,_trans;//背景透明，文字不透明

    void adjustMySize();
};
}
#endif
