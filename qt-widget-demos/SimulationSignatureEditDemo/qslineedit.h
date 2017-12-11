#ifndef QSLINEEDIT_H
#define QSLINEEDIT_H

#include <QCursor>
#include <QLineEdit>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>

class QSLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit QSLineEdit(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // QSLINEEDIT_H
