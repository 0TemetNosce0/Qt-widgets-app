#ifndef SCROLLTEXT_H
#define SCROLLTEXT_H

#include <QWidget>
#include <QLabel>
#include <QStaticText>
#include <QTimer>


/* This class is a slightly modified version of a class contributed by leemes of StackOverflow
 *
 *                              Please thank him for this great class !
 *
 * */

class ScrollingLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString separator READ separator WRITE setSeparator)

public:
    explicit ScrollingLabel(QWidget *parent = 0);

public slots:
    QString text() const;
    inline void setText(QString &text)
    {
        _text = text;
        updateText(); //Sets if the label will be on scrolling mode
        update();
    }

    QString separator() const;
    void setSeparator(QString separator);

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);

private:
    void updateText();
    //Attributes
    QString _text;
    QString _separator;
    QStaticText staticText;
    int singleTextWidth;
    QSize wholeTextSize;
    int leftMargin;
    bool scrollEnabled;
    int scrollPos;
    QImage alphaChannel;
    QImage buffer;
    QTimer timer;

private slots:
    virtual void timer_timeout();
};

#endif // SCROLLTEXT_H
