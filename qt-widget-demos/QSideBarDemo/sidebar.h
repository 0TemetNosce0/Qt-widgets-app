#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QIcon>
#include <QWidget>
#include <QAction>
#include <QPainter>
#include <QPaintEvent>

class SideBar : public QWidget
{
    Q_OBJECT

public:
    SideBar(QWidget *parent = 0);
    ~SideBar();

    void addAction(QAction *action);
    QAction *addAction(const QString &text, const QIcon &icon = QIcon());

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QSize minimumSizeHint() const;

    QAction* actionAt(const QPoint &at);

private:
    QList<QAction*> m_actionList;
    QAction *pressedAction;
    QAction *checkedAction;
};

#endif // SIDEBAR_H
