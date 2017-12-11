#ifndef CTOOLTIP_H
#define CTOOLTIP_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CToolTip : public QWidget
{
    Q_OBJECT
public:
    explicit CToolTip(QWidget *parent = 0);
    void showMessage(const QPixmap *pixmap, QString name, QString info, QPoint point);
    void showMessage(const QPixmap *pixmap, QPoint point);

signals:

public slots:

private:
    QLabel *labelIcon;
    QLabel *labelName;
    QLabel *labelInfo;

    QHBoxLayout *horLayout;
    QVBoxLayout *verlayout;

    QGroupBox *groupBox;

protected:
    void hoverEvent(QHoverEvent *);
};

#endif // CTOOLTIP_H
