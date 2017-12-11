/*
 * ����������������ͷ�ҳ���У������з���������Ҫ��̬�ı䱳���������
 *
 * */

#ifndef WENLIWIDGET_H
#define WENLIWIDGET_H

#include "basestylewidget.h"

#include <QWidget>

class QPropertyAnimation;

class WenliWidget : public BaseStyleWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    //ע������Ϊ��ʽ���ṩ�Զ���ֵ
    Q_PROPERTY(QString backPix READ backPix WRITE setBackPix DESIGNABLE true SCRIPTABLE true)

public:
    explicit WenliWidget(QWidget *parent = 0);
    void setColor(const QColor &color);
    const QColor &color()
    {
        return m_backgroundColor;
    }
    const QString &backPix()
    {
        return m_backgroundPix;
    }

    void setBackPix(const QString &backPix);

public slots:
    void setNums(int num);

protected:
    void paintEvent(QPaintEvent *);

private:
    void initAnimations();

private:
    int                 m_num;
    qreal               m_opacity;
    QColor              m_backgroundColor;
    QPixmap             m_guangYPix;
    QPixmap             m_wenliPix;
    QString             m_backgroundPix;

    QPropertyAnimation  *m_toOrange;
    QPropertyAnimation  *m_toYellow;
};

#endif // WENLIWIDGET_H
