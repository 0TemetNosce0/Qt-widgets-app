#ifndef QRIBBONTEST_H
#define QRIBBONTEST_H

#include <QMainWindow>

class QRibbonTest : public QMainWindow
{
    Q_OBJECT

public:
    QRibbonTest();
    ~QRibbonTest();

public slots:
    void action();
    void indexChanged(int tab);
};

#endif // QRIBBONTEST_H
